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
const ROOM_SIDE_LEN: f32 = 450.;
const ROOM_PADDING: f32 = 50.;
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

struct Pockets {
    centers: Vec<Vec3>,
    radius: f32,
}

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
        width: 700.,
        height: 500.,
        canvas: Some("#interactive".to_string()),
        fit_canvas_to_parent: true,
        ..default()
    })
    .insert_resource(ClearColor(Color::BLACK))
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
    tom: Res<Tom>,
    jerry: Res<Jerry>,
) {
    // Camera
    commands.spawn_bundle(Camera2dBundle::default());
    // Room
    commands.spawn_bundle(MaterialMesh2dBundle {
        mesh: meshes
            .add(Mesh::from(Quad::new(Vec2::new(
                ROOM_SIDE_LEN + ROOM_PADDING,
                ROOM_SIDE_LEN + ROOM_PADDING,
            ))))
            .into(),
        material: materials.add(ROOM_OUTER_COLOR.into()),
        ..default()
    });
    commands.spawn_bundle(MaterialMesh2dBundle {
        mesh: meshes
            .add(Mesh::from(Quad::new(Vec2::new(
                ROOM_SIDE_LEN,
                ROOM_SIDE_LEN,
            ))))
            .into(),
        material: materials.add(ROOM_INNER_COLOR.into()),
        ..default()
    });
    commands.spawn_bundle(MaterialMesh2dBundle {
        mesh: meshes
            .add(Mesh::from(Circle {
                radius: 10.,
                vertices: 64,
            }))
            .into(),
        material: materials.add(Color::BLACK.into()),
        ..default()
    });
    // Tom
    commands
        .spawn_bundle(MaterialMesh2dBundle {
            mesh: meshes.add(Mesh::from(&*tom)).into(),
            material: materials.add(Tom::COLOR.into()),
            transform: Transform::default().with_translation(Vec3::Z),
            ..default()
        })
        .insert(TomMarker);
    // Jerry
    commands
        .spawn_bundle(MaterialMesh2dBundle {
            mesh: meshes.add(Mesh::from(&*jerry)).into(),
            material: materials.add(Jerry::COLOR.into()),
            transform: Transform::default().with_translation(Vec3::Z),
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
    mut tom_query: Query<(&TomMarker, &mut Transform)>,
) {
    let (_, mut tom_transform) = tom_query.single_mut();
    let center_limit = ROOM_SIDE_LEN / 2. - tom.radius;
    if tom_transform.translation.x.abs() > center_limit {
        tom.ds.x = -tom.ds.x;
        tom_transform.translation.x = center_limit * tom_transform.translation.x.signum();
    }
    if tom_transform.translation.y.abs() > center_limit {
        tom.ds.y = -tom.ds.y;
        tom_transform.translation.y = center_limit * tom_transform.translation.y.signum();
    }
    tom_transform.translation += tom.ds * (1. + game.score as f32 * 0.1);
    tom.ds *= Tom::FRICTION_COEFFICIENT;
    if tom.ds.x.abs() < 0.1 && tom.ds.y.abs() < 0.1 && tom.ds.z.abs() < 0.1 {
        tom.ds = Vec3::ZERO;
    }
}

fn tick_jerry(mut jerry: ResMut<Jerry>, mut jerry_query: Query<(&JerryMarker, &mut Transform)>) {
    let (_, mut jerry_transform) = jerry_query.single_mut();
    let center_limit = ROOM_SIDE_LEN / 2. - jerry.radius;
    if jerry_transform.translation.x.abs() > center_limit {
        jerry.ds.x = -jerry.ds.x;
        jerry_transform.translation.x = center_limit * jerry_transform.translation.x.signum();
    }
    if jerry_transform.translation.y.abs() > center_limit {
        jerry.ds.y = -jerry.ds.y;
        jerry_transform.translation.y = center_limit * jerry_transform.translation.y.signum();
    }
    jerry_transform.translation += jerry.ds;
    jerry.ds *= Jerry::FRICTION_COEFFICIENT;
    if jerry.ds.x.abs() < 0.1 && jerry.ds.y.abs() < 0.1 && jerry.ds.z.abs() < 0.1 {
        jerry.ds = Vec3::ZERO;
    }
}
