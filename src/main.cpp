#include <simplecpp>
#include <sstream>
#include "utils.cpp"


const Vector2d CENTER_OF_BOARD(550, 350);
const Vector2d POCKET1_POSITION(310, 110);
const Vector2d POCKET2_POSITION(790, 110);
const Vector2d POCKET3_POSITION(310, 590);
const Vector2d POCKET4_POSITION(790, 590);

const Vector2d YES_BTN_POSITION(500, 740);
const Vector2d NO_BTN_POSITION(600, 740);
const double IN_POCKET_DISTANCE = sqrt(70);

class Runner {
    constexpr static double AIM_LIMIT = 50;
    constexpr static double AIM_SCALE = 0.2;
    constexpr static double FRICTION_COEFFICIENT = 0.99;
    Circle circle;
    Vector2d ds;
public:
    constexpr static double CIRCLE_RADIUS = 9;

    Runner() = default;

    void place(double x, double y) {
        circle.reset(x, y, CIRCLE_RADIUS);
        circle.setColor(COLOR(50, 50, 255)).setFill();
        circle.show();
    }

    Vector2d aim() {
        Vector2d aimPoint;
        Vector2d runnerPosition(circle.getX(), circle.getY());
        while (true) {
            // create aim circles
            Circle c2(runnerPosition.x, runnerPosition.y, 50);
            c2.setColor(COLOR(255, 0, 0));
            Circle c3(runnerPosition.x, runnerPosition.y, 35);
            c3.setColor(COLOR(255, 100, 100));
            Circle c4(runnerPosition.x, runnerPosition.y, 20);
            c4.setColor(COLOR(255, 200, 200));
            registerClick(&aimPoint);
            ds = Vector2d::diffOf(&aimPoint, &runnerPosition);
            if (ds.length() <= AIM_LIMIT) { break; }
        }
        // direction and the speed are taken from aimVector
        ds.mulBy(AIM_SCALE);
        return ds;
    }

    void bounceIfOnWall() {
        double x = circle.getX();
        double y = circle.getY();
        if (x <= 300) { ds.x = abs(ds.x); }
        else if (x >= 800) { ds.x = -abs(ds.x); }
        if (y <= 100) { ds.y = abs(ds.y); }
        else if (y >= 600) { ds.y = -abs(ds.y); }
    }

    void move() {
        circle.move(ds.x, ds.y);
        //friction control
        ds.mulBy(FRICTION_COEFFICIENT);
    }

    bool isAtRest() {
        return abs(ds.x) <= 0.1 && abs(ds.y) <= 0.1;
    }

    Vector2d getPosition() {
        return {circle.getX(), circle.getY()};
    }

    void onFallingInPocket() {
        circle.setColor(COLOR(0, 0, 0));
        wait(0.1);
        circle.hide();
    }
};

class Chaser {
    constexpr static double FRICTION_COEFFICIENT = 0.98;
    Circle circle;
    Vector2d ds;
public:
    constexpr static double CIRCLE_RADIUS = 45;

    Chaser(double x, double y) {
        circle.reset(x, y, CIRCLE_RADIUS);
        circle.setColor(COLOR(0, 0, 0)).setFill();
    }

    void setDs(const Vector2d ds) {
        this->ds = ds;
    }

    void bounceIfOnWall() {
        double x = circle.getX();
        double y = circle.getY();
        if (x <= 335) { ds.x = abs(ds.x); }
        else if (x >= 765) { ds.x = -abs(ds.x); }
        if (y <= 135) { ds.y = abs(ds.y); }
        else if (y >= 565) { ds.y = -abs(ds.y); }
    }

    void move(double speedScale = 1) {
        circle.move(ds.x * speedScale, ds.y * speedScale);
        //friction control
        ds.mulBy(FRICTION_COEFFICIENT);
    }

    bool isAtRest() {
        return abs(ds.x) <= 0.1 && abs(ds.y) <= 0.1;
    }

    Vector2d getPosition() {
        return {circle.getX(), circle.getY()};
    }

    void onCatchingRunner() {
        circle.setColor(COLOR(255, 0, 0)).setFill();
    }
};

class CarromChase {
    constexpr static double PLACEMENT_LIMIT = 150;
    constexpr static double PLACEMENT_LINEANCE = 10;
public:

    int startGame() {
        int score = 0;
        srand(time(NULL));

        Runner runner;
        Chaser chaser(CENTER_OF_BOARD.x, CENTER_OF_BOARD.y);
        // single game
        while (true) {
            // place runner
            Vector2d currentChaserPosition = chaser.getPosition();
            while (true) {
                double r = rand() % (int) PLACEMENT_LIMIT + 1;
                double theta = rand() % 360;
                Vector2d newRunnerPosition(r * cosine(theta) + CENTER_OF_BOARD.x, r * sine(theta) + CENTER_OF_BOARD.y);
                if (Vector2d::diffOf(&newRunnerPosition, &currentChaserPosition).length() >
                    Runner::CIRCLE_RADIUS + Chaser::CIRCLE_RADIUS + PLACEMENT_LINEANCE) {
                    runner.place(newRunnerPosition.x, newRunnerPosition.y);
                    break;
                }
            }

            {
                Text message(550, 30, "Help little Jerry get to a hole safely.");
                Vector2d ds = runner.aim();
                chaser.setDs(ds);
            }

            while (true) {
                wait(0.01);

                // bounce if on wall
                runner.bounceIfOnWall();
                chaser.bounceIfOnWall();

                // movement
                runner.move();
                chaser.move(1 + score * 0.1);

                Vector2d runnerPosition = runner.getPosition();
                Vector2d chaserPosition = chaser.getPosition();

                // in pocket
                if (Vector2d::diffOf(&runnerPosition, &POCKET1_POSITION).length() <= IN_POCKET_DISTANCE
                    || Vector2d::diffOf(&runnerPosition, &POCKET2_POSITION).length() <= IN_POCKET_DISTANCE
                    || Vector2d::diffOf(&runnerPosition, &POCKET3_POSITION).length() <= IN_POCKET_DISTANCE
                    || Vector2d::diffOf(&runnerPosition, &POCKET4_POSITION).length() <= IN_POCKET_DISTANCE) {

                    runner.onFallingInPocket();
                    score++;
                    break;
                }

                // both at rest
                if (runner.isAtRest() && chaser.isAtRest()) {
                    Text message(550, 30, "Alas! Jerry has not escaped!");
                    wait(1.5);
                    return score;
                }

                // caught by chaser
                if (Vector2d::diffOf(&runnerPosition, &chaserPosition).length() <= 60) {
                    chaser.onCatchingRunner();
                    Text message(550, 30, "Alas! Tom caught Jerry!");
                    wait(1.5);
                    return score;
                }
            }
        }
    }
};


int main() {
    initCanvas("Tom and Jerry", 1100, 800);
    // board
    Rectangle r2(550, 350, 570, 570);
    r2.setColor(COLOR(153, 76, 0)).setFill();
    Rectangle r1(550, 350, 520, 520);
    r1.setColor(COLOR(255, 255, 153)).setFill();

    // side rectangles
    Rectangle r3(550, 145, 350, 20);
    Rectangle r4(550, 555, 350, 20);
    Rectangle r5(345, 350, 20, 350);
    Rectangle r6(755, 350, 20, 350);
    /* Line l1(375, 134, 725, 134); */
    /* Line l2(375, 566, 725, 566); */
    /* Line l3(334, 175, 334, 525); */
    /* Line l4(766, 175, 766, 525); */

    // pockets
    Circle c5(790, 110, 15);
    c5.setColor(COLOR(255, 255, 255)).setFill();
    Circle c50(790, 110, 15);

    Circle c6(310, 110, 15);
    c6.setColor(COLOR(255, 255, 255)).setFill();
    Circle c60(310, 110, 15);

    Circle c7(790, 590, 15);
    c7.setColor(COLOR(255, 255, 255)).setFill();
    Circle c70(790, 590, 15);

    Circle c8(310, 590, 15);
    c8.setColor(COLOR(255, 255, 255)).setFill();
    Circle c80(310, 590, 15);

    // connecting circles
    Circle conn1(360, 540, 15 * 1 / sqrt(2));
    Circle conn2(740, 540, 15 * 1 / sqrt(2));
    Circle conn3(740, 160, 15 * 1 / sqrt(2));
    Circle conn4(360, 160, 15 * 1 / sqrt(2));

    // red dots
    /* Circle ca1(345, 175, 11); */
    /* ca1.setFill(); */
    /* Circle ca10(345, 175, 7); */
    /* ca10.setColor(COLOR(255, 0, 0)).setFill(); */

    /* Circle ca2(345, 525, 11); */
    /* ca2.setFill(); */
    /* Circle ca20(345, 525, 7); */
    /* ca20.setColor(COLOR(255, 0, 0)).setFill(); */

    /* Circle ca3(755, 175, 11); */
    /* ca3.setFill(); */
    /* Circle ca30(755, 175, 7); */
    /* ca30.setColor(COLOR(255, 0, 0)).setFill(); */

    /* Circle ca4(755, 525, 11); */
    /* ca4.setFill(); */
    /* Circle ca40(755, 525, 7); */
    /* ca40.setColor(COLOR(255, 0, 0)).setFill(); */

    /* Circle ca5(375, 145, 11); */
    /* ca5.setFill(); */
    /* Circle ca50(375, 145, 7); */
    /* ca50.setColor(COLOR(255, 0, 0)).setFill(); */

    /* Circle ca6(725, 145, 11); */
    /* ca6.setFill(); */
    /* Circle ca60(725, 145, 7); */
    /* ca60.setColor(COLOR(255, 0, 0)).setFill(); */

    /* Circle ca7(375, 555, 11); */
    /* ca7.setFill(); */
    /* Circle ca70(375, 555, 7); */
    /* ca70.setColor(COLOR(255, 0, 0)).setFill(); */

    /* Circle ca8(725, 555, 11); */
    /* ca8.setFill(); */
    /* Circle ca80(725, 555, 7); */
    /* ca80.setColor(COLOR(255, 0, 0)).setFill(); */

    // mid circles
    /* Circle couter_mid_circle(550, 350, 75); */

    /* Circle cinnerred(550, 350, 70); */
    /* cinnerred.setColor(COLOR(255, 0, 0)); */
    /* cinnerred.setFill(); */

    /* Circle cinnercream(550, 350, 60); */
    /* cinnercream.setColor(COLOR(255, 255, 153)); */
    /* cinnercream.setFill(); */

    // spikes
    /* Line k1(550, 300, 550, 400); */
    /* Line k2(500, 350, 600, 350); */
    /* Line k3(550 - 50 / sqrt(2), 350 - 50 / sqrt(2), 550 + 50 / sqrt(2), 350 + 50 / sqrt(2)); */
    /* Line k4(550 + 50 / sqrt(2), 350 - 50 / sqrt(2), 550 - 50 / sqrt(2), 350 + 50 / sqrt(2)); */

    // spike side
    /* Line k001(550 - 50, 350, 550 + 14 * cos(7 * PI / 8), 350 + 14 * sin(7 * PI / 8)); */
    /* Line k002(550 - 50, 350, 550 + 14 * cos(9 * PI / 8), 350 + 14 * sin(9 * PI / 8)); */

    /* Line k003(550 - 50 / sqrt(2), 350 - 50 / sqrt(2), 550 + 14 * cos(9 * PI / 8), 350 + 14 * sin(9 * PI / 8)); */
    /* Line k004(550 - 50 / sqrt(2), 350 - 50 / sqrt(2), 550 + 14 * cos(11 * PI / 8), 350 + 14 * sin(11 * PI / 8)); */

    /* Line k005(550, 350 - 50, 550 + 14 * cos(11 * PI / 8), 350 + 14 * sin(11 * PI / 8)); */
    /* Line k006(550, 350 - 50, 550 + 14 * cos(13 * PI / 8), 350 + 14 * sin(13 * PI / 8)); */

    /* Line k007(550 + 50 / sqrt(2), 350 - 50 / sqrt(2), 550 + 14 * cos(13 * PI / 8), 350 + 14 * sin(13 * PI / 8)); */
    /* Line k008(550 + 50 / sqrt(2), 350 - 50 / sqrt(2), 550 + 14 * cos(15 * PI / 8), 350 + 14 * sin(15 * PI / 8)); */

    /* Line k009(550 + 50, 350, 550 + 14 * cos(15 * PI / 8), 350 + 14 * sin(15 * PI / 8)); */
    /* Line k010(550 + 50, 350, 550 + 14 * cos(PI / 8), 350 + 14 * sin(PI / 8)); */

    /* Line k011(550 + 50 / sqrt(2), 350 + 50 / sqrt(2), 550 + 14 * cos(PI / 8), 350 + 14 * sin(PI / 8)); */
    /* Line k012(550 + 50 / sqrt(2), 350 + 50 / sqrt(2), 550 + 14 * cos(3 * PI / 8), 350 + 14 * sin(3 * PI / 8)); */

    /* Line k013(550, 350 + 50, 550 + 14 * cos(3 * PI / 8), 350 + 14 * sin(3 * PI / 8)); */
    /* Line k014(550, 350 + 50, 550 + 14 * cos(5 * PI / 8), 350 + 14 * sin(5 * PI / 8)); */

    /* Line k015(550 - 50 / sqrt(2), 350 + 50 / sqrt(2), 550 + 14 * cos(5 * PI / 8), 350 + 14 * sin(5 * PI / 8)); */
    /* Line k016(550 - 50 / sqrt(2), 350 + 50 / sqrt(2), 550 + 14 * cos(7 * PI / 8), 350 + 14 * sin(7 * PI / 8)); */

    // central circles
    /* Circle cenblack_outline(550, 350, 10); */
    /* Circle cen_outer_black(550, 350, 14); */
    /* Circle cenred(550, 350, 9); */
    /* cenred.setColor(COLOR(255, 0, 0)).setFill(); */

    /* Circle cblack_outline2(550, 350, 70); */
    /* Circle cblack_outline3(550, 350, 60); */

    // sidelines
    /* Line s1(550 + 70, 350 - 70, 670 + 100, 230 - 100); */
    /* Line s2(550 - 70, 350 - 70, 430 - 100, 230 - 100); */
    /* Line s3(550 - 70, 350 + 70, 430 - 100, 470 + 100); */
    /* Line s4(550 + 70, 350 + 70, 670 + 100, 470 + 100); */

    CarromChase carromChase;

    while (true) {
        int score = carromChase.startGame();

        // output score and ask for another game
        ostringstream oss;
        oss << "Your score is = " << score << ". " << "Do you want to play another game?";
        Text message(550, 680, oss.str());
        // yes no buttons
        Circle yesBtn(YES_BTN_POSITION.x, YES_BTN_POSITION.y, 30);
        yesBtn.setColor(COLOR(0, 255, 0)).setFill();
        Text yesBtnText(YES_BTN_POSITION.x, YES_BTN_POSITION.y, "Yes");
        Circle noBtn(NO_BTN_POSITION.x, NO_BTN_POSITION.y, 30);
        noBtn.setColor(COLOR(255, 0, 0)).setFill();
        Text noBtnText(NO_BTN_POSITION.x, NO_BTN_POSITION.y, "No");

        while (true) {
            Vector2d click;
            registerClick(&click);
            if (Vector2d::diffOf(&click, &YES_BTN_POSITION).length() <= 20) { break; }
            if (Vector2d::diffOf(&click, &NO_BTN_POSITION).length() <= 20) { return 0; }
        }
    }
}
