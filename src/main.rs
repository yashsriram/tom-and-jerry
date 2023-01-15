#[cfg(not(target_arch = "wasm32"))]
use bevy::asset::AssetServerSettings;
use bevy::{
    prelude::{
        shape::{Circle, Quad},
        *,
    },
    sprite::MaterialMesh2dBundle,
};

const ROOM_OUTER_COLOR: Color = Color::rgb(153. / 255., 76. / 255., 0. / 255.);
const ROOM_INNER_COLOR: Color = Color::rgb(255. / 255., 255. / 255., 153. / 255.);
const ROOM_PADDING: f32 = 50.;
const POCKET_RADIUS: f32 = 20.;
const PLACEMENT_LIMIT: f32 = 150.;
const PLACEMENT_LINEANCE: f32 = 10.;

#[derive(Component)]
pub struct TomMarker;

struct Tom {
    radius: f32,
    ds: Vec3,
}

impl Tom {
    const FRICTION_COEFFICIENT: f32 = 0.98;
    const COLOR: Color = Color::rgb(50. / 255., 50. / 255., 200. / 255.);
}

impl From<&Tom> for Mesh {
    fn from(tom: &Tom) -> Mesh {
        Mesh::from(Circle {
            radius: tom.radius,
            vertices: 64,
        })
    }
}

#[derive(Component)]
pub struct JerryMarker;

struct Jerry {
    radius: f32,
    ds: Vec3,
}

impl Jerry {
    const FRICTION_COEFFICIENT: f32 = 0.98;
    const AIM_SCALE: f32 = 0.2;
    const AIM_LIMIT: f32 = 20.;
    const COLOR: Color = Color::rgb(200. / 255., 50. / 255., 0. / 255.);
}

impl From<&Jerry> for Mesh {
    fn from(jerry: &Jerry) -> Mesh {
        Mesh::from(Circle {
            radius: jerry.radius,
            vertices: 64,
        })
    }
}

#[derive(Component)]
pub struct RoomMarker;

struct Game {
    score: usize,
}

fn main() {
    let mut app = App::new();
    #[cfg(not(target_arch = "wasm32"))]
    {
        app.insert_resource(AssetServerSettings {
            asset_folder: "static/assets".to_string(),
            ..default()
        });
    }
    app.insert_resource(WindowDescriptor {
        canvas: Some("#interactive".to_string()),
        fit_canvas_to_parent: true,
        ..default()
    })
    .insert_resource(ClearColor(ROOM_OUTER_COLOR))
    .insert_resource(Tom {
        radius: 45.,
        ds: Vec3::ZERO,
    })
    .insert_resource(Jerry {
        radius: 9.,
        ds: Vec3::ZERO,
    })
    .insert_resource(Game { score: 0 })
    .add_plugins(DefaultPlugins)
    .add_startup_system(init)
    .add_system(shoot)
    .add_system(tick_tom)
    .add_system(tick_jerry)
    .run();
}

fn init(
    mut commands: Commands,
    mut meshes: ResMut<Assets<Mesh>>,
    mut materials: ResMut<Assets<ColorMaterial>>,
    mut windows: ResMut<Windows>,
    tom: Res<Tom>,
    jerry: Res<Jerry>,
) {
    let window = windows.primary_mut();
    let physical_window_dims = Vec2::new(
        window.physical_width() as f32,
        window.physical_height() as f32,
    );
    let scale_factor = window.scale_factor() as f32;
    let window_dims = physical_window_dims / scale_factor;
    // Camera
    commands.spawn_bundle(Camera2dBundle::default());
    // Room
    let padded_window_dims = window_dims - Vec2::new(ROOM_PADDING, ROOM_PADDING);
    commands
        .spawn_bundle(MaterialMesh2dBundle {
            mesh: meshes.add(Mesh::from(Quad::new(Vec2::ONE))).into(),
            material: materials.add(ROOM_INNER_COLOR.into()),
            transform: Transform::default().with_scale(Vec3::new(
                padded_window_dims.x,
                padded_window_dims.y,
                1.,
            )),
            ..default()
        })
        .insert(RoomMarker);
    // Pockets
    commands.spawn_bundle(MaterialMesh2dBundle {
        mesh: meshes
            .add(Mesh::from(Circle {
                radius: 1.0,
                vertices: 64,
            }))
            .into(),
        material: materials.add(Color::BLACK.into()),
        transform: Transform::default()
            .with_scale(Vec3::new(POCKET_RADIUS, POCKET_RADIUS, 1.0))
            .with_translation(Vec3::new(
                window_dims.x / 2. - POCKET_RADIUS - ROOM_PADDING,
                window_dims.y / 2. - POCKET_RADIUS - ROOM_PADDING,
                1.0,
            )),
        ..default()
    });
    // Tom
    commands
        .spawn_bundle(MaterialMesh2dBundle {
            mesh: meshes.add(Mesh::from(&*tom)).into(),
            material: materials.add(Tom::COLOR.into()),
            transform: Transform::default().with_translation(Vec3::new(50., 50., 2.)),
            ..default()
        })
        .insert(TomMarker);
    // Jerry
    commands
        .spawn_bundle(MaterialMesh2dBundle {
            mesh: meshes.add(Mesh::from(&*jerry)).into(),
            material: materials.add(Jerry::COLOR.into()),
            transform: Transform::default().with_translation(Vec3::new(0., 0., 2.)),
            ..default()
        })
        .insert(JerryMarker);
}

fn shoot(
    mouse_button_input: Res<Input<MouseButton>>,
    mut windows: ResMut<Windows>,
    mut jerry: ResMut<Jerry>,
    mut tom: ResMut<Tom>,
    jerry_query: Query<(&JerryMarker, &Transform)>,
) {
    if mouse_button_input.just_pressed(MouseButton::Left) {
        let window = windows.primary_mut();
        if let Some(cursor) = window.physical_cursor_position() {
            let cursor = Vec2::new(cursor.x as f32, cursor.y as f32);
            let semi_viewport_axes = Vec2::new(
                window.physical_width() as f32 / 2.,
                window.physical_height() as f32 / 2.,
            );
            let unscaled_click = cursor - semi_viewport_axes;
            let scale_factor = window.scale_factor() as f32;
            let click = unscaled_click / scale_factor;
            let (_, jerry_transform) = jerry_query.single();
            let aim =
                click - Vec2::new(jerry_transform.translation.x, jerry_transform.translation.y);
            let aim = aim * Jerry::AIM_SCALE;
            let shoot = aim.clamp_length_max(Jerry::AIM_LIMIT);
            jerry.ds.x = shoot.x;
            jerry.ds.y = shoot.y;
            tom.ds.x = shoot.x;
            tom.ds.y = shoot.y;
            // info!("aim = {:?}", shoot);
        }
    }
}

fn tick_tom(
    game: Res<Game>,
    mut tom: ResMut<Tom>,
    mut transforms: Query<&mut Transform>,
    mut tom_query: Query<(Entity, &TomMarker)>,
    room_query: Query<(Entity, &RoomMarker)>,
) {
    let (room_entity, _) = room_query.single();
    let room_half_scale = transforms.get(room_entity).unwrap().scale / 2.;
    let room_x_center_boundary = room_half_scale.x - tom.radius;
    let room_y_center_boundary = room_half_scale.y - tom.radius;
    let (tom_entity, _) = tom_query.single_mut();
    let mut tom_transform = transforms.get_mut(tom_entity).unwrap();
    if tom_transform.translation.x.abs() > room_x_center_boundary {
        tom.ds.x = -tom.ds.x;
        tom_transform.translation.x = room_x_center_boundary * tom_transform.translation.x.signum();
    }
    if tom_transform.translation.y.abs() > room_y_center_boundary {
        tom.ds.y = -tom.ds.y;
        tom_transform.translation.y = room_y_center_boundary * tom_transform.translation.y.signum();
    }
    tom_transform.translation += tom.ds * (1. + game.score as f32 * 0.1);
    tom.ds *= Tom::FRICTION_COEFFICIENT;
    if tom.ds.x.abs() < 0.1 && tom.ds.y.abs() < 0.1 && tom.ds.z.abs() < 0.1 {
        tom.ds = Vec3::ZERO;
    }
}

fn tick_jerry(
    mut jerry: ResMut<Jerry>,
    mut transforms: Query<&mut Transform>,
    mut jerry_query: Query<(Entity, &JerryMarker)>,
    room_query: Query<(Entity, &RoomMarker)>,
) {
    let (room_entity, _) = room_query.single();
    let room_half_scale = transforms.get(room_entity).unwrap().scale / 2.;
    let (jerry_entity, _) = jerry_query.single_mut();
    let room_x_center_boundary = room_half_scale.x - jerry.radius;
    let room_y_center_boundary = room_half_scale.y - jerry.radius;
    let mut jerry_transform = transforms.get_mut(jerry_entity).unwrap();
    if jerry_transform.translation.x.abs() > room_x_center_boundary {
        jerry.ds.x = -jerry.ds.x;
        jerry_transform.translation.x =
            room_x_center_boundary * jerry_transform.translation.x.signum();
    }
    if jerry_transform.translation.y.abs() > room_y_center_boundary {
        jerry.ds.y = -jerry.ds.y;
        jerry_transform.translation.y =
            room_y_center_boundary * jerry_transform.translation.y.signum();
    }
    jerry_transform.translation += jerry.ds;
    jerry.ds *= Jerry::FRICTION_COEFFICIENT;
    if jerry.ds.x.abs() < 0.1 && jerry.ds.y.abs() < 0.1 && jerry.ds.z.abs() < 0.1 {
        jerry.ds = Vec3::ZERO;
    }
}
