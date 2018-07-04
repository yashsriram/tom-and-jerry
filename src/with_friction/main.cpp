#include <simplecpp>

// there is a small glicth

int main() {
    initCanvas("Carrom Chase", 1100, 700);
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
    Line l1(375, 134, 725, 134);
    Line l2(375, 566, 725, 566);
    Line l3(334, 175, 334, 525);
    Line l4(766, 175, 766, 525);

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
    Circle ca1(345, 175, 11);
    ca1.setFill();
    Circle ca10(345, 175, 7);
    ca10.setColor(COLOR(255, 0, 0)).setFill();

    Circle ca2(345, 525, 11);
    ca2.setFill();
    Circle ca20(345, 525, 7);
    ca20.setColor(COLOR(255, 0, 0)).setFill();

    Circle ca3(755, 175, 11);
    ca3.setFill();
    Circle ca30(755, 175, 7);
    ca30.setColor(COLOR(255, 0, 0)).setFill();

    Circle ca4(755, 525, 11);
    ca4.setFill();
    Circle ca40(755, 525, 7);
    ca40.setColor(COLOR(255, 0, 0)).setFill();

    Circle ca5(375, 145, 11);
    ca5.setFill();
    Circle ca50(375, 145, 7);
    ca50.setColor(COLOR(255, 0, 0)).setFill();

    Circle ca6(725, 145, 11);
    ca6.setFill();
    Circle ca60(725, 145, 7);
    ca60.setColor(COLOR(255, 0, 0)).setFill();

    Circle ca7(375, 555, 11);
    ca7.setFill();
    Circle ca70(375, 555, 7);
    ca70.setColor(COLOR(255, 0, 0)).setFill();

    Circle ca8(725, 555, 11);
    ca8.setFill();
    Circle ca80(725, 555, 7);
    ca80.setColor(COLOR(255, 0, 0)).setFill();

    // mid circles
    Circle crefer(550, 350, 150);
    crefer.setColor(COLOR(255, 255, 102));

    Circle couter_mid_circle(550, 350, 75);

    Circle cinnerred(550, 350, 70);
    cinnerred.setColor(COLOR(255, 0, 0));
    cinnerred.setFill();

    Circle cinnercream(550, 350, 60);
    cinnercream.setColor(COLOR(255, 255, 153));
    cinnercream.setFill();

    // spikes
    Line k1(550, 300, 550, 400);
    Line k2(500, 350, 600, 350);
    Line k3(550 - 50 / sqrt(2), 350 - 50 / sqrt(2), 550 + 50 / sqrt(2), 350 + 50 / sqrt(2));
    Line k4(550 + 50 / sqrt(2), 350 - 50 / sqrt(2), 550 - 50 / sqrt(2), 350 + 50 / sqrt(2));

    // spike side
    Line k001(550 - 50, 350, 550 + 14 * cos(7 * PI / 8), 350 + 14 * sin(7 * PI / 8));
    Line k002(550 - 50, 350, 550 + 14 * cos(9 * PI / 8), 350 + 14 * sin(9 * PI / 8));

    Line k003(550 - 50 / sqrt(2), 350 - 50 / sqrt(2), 550 + 14 * cos(9 * PI / 8), 350 + 14 * sin(9 * PI / 8));
    Line k004(550 - 50 / sqrt(2), 350 - 50 / sqrt(2), 550 + 14 * cos(11 * PI / 8), 350 + 14 * sin(11 * PI / 8));

    Line k005(550, 350 - 50, 550 + 14 * cos(11 * PI / 8), 350 + 14 * sin(11 * PI / 8));
    Line k006(550, 350 - 50, 550 + 14 * cos(13 * PI / 8), 350 + 14 * sin(13 * PI / 8));

    Line k007(550 + 50 / sqrt(2), 350 - 50 / sqrt(2), 550 + 14 * cos(13 * PI / 8), 350 + 14 * sin(13 * PI / 8));
    Line k008(550 + 50 / sqrt(2), 350 - 50 / sqrt(2), 550 + 14 * cos(15 * PI / 8), 350 + 14 * sin(15 * PI / 8));

    Line k009(550 + 50, 350, 550 + 14 * cos(15 * PI / 8), 350 + 14 * sin(15 * PI / 8));
    Line k010(550 + 50, 350, 550 + 14 * cos(PI / 8), 350 + 14 * sin(PI / 8));

    Line k011(550 + 50 / sqrt(2), 350 + 50 / sqrt(2), 550 + 14 * cos(PI / 8), 350 + 14 * sin(PI / 8));
    Line k012(550 + 50 / sqrt(2), 350 + 50 / sqrt(2), 550 + 14 * cos(3 * PI / 8), 350 + 14 * sin(3 * PI / 8));

    Line k013(550, 350 + 50, 550 + 14 * cos(3 * PI / 8), 350 + 14 * sin(3 * PI / 8));
    Line k014(550, 350 + 50, 550 + 14 * cos(5 * PI / 8), 350 + 14 * sin(5 * PI / 8));

    Line k015(550 - 50 / sqrt(2), 350 + 50 / sqrt(2), 550 + 14 * cos(5 * PI / 8), 350 + 14 * sin(5 * PI / 8));
    Line k016(550 - 50 / sqrt(2), 350 + 50 / sqrt(2), 550 + 14 * cos(7 * PI / 8), 350 + 14 * sin(7 * PI / 8));

    // central circles
    Circle cenblack_outline(550, 350, 10);
    Circle cen_outer_black(550, 350, 14);
    Circle cenred(550, 350, 9);
    cenred.setColor(COLOR(255, 0, 0)).setFill();

    Circle cblack_outline2(550, 350, 70);
    Circle cblack_outline3(550, 350, 60);

    // sidelines
    Line s1(550 + 70, 350 - 70, 670 + 100, 230 - 100);
    Line s2(550 - 70, 350 - 70, 430 - 100, 230 - 100);
    Line s3(550 - 70, 350 + 70, 430 - 100, 470 + 100);
    Line s4(550 + 70, 350 + 70, 670 + 100, 470 + 100);

    int z, w;
    float x, y, a, b;
    while (true) {
        int i = 0;
        float p = 550, q = 350;

        // single game
        while (true) {

            // place puck
            while (true) {
                z = getClick();
                x = z / 65536;
                y = z % 65536;
                if ((x - 550) * (x - 550) + (y - 350) * (y - 350) <= 150 * 150) { break; }
                else { continue; }
            }
            Circle c1(x, y, 9);
            c1.setColor(COLOR(50, 50, 255)).setFill();

            // aiming circles creation
            while (true) {
                Circle c2(x, y, 50);
                Circle c3(x, y, 35);
                Circle c4(x, y, 20);
                c2.setColor(COLOR(255, 0, 0));
                c3.setColor(COLOR(255, 100, 100));
                c4.setColor(COLOR(255, 200, 200));
                w = getClick();
                a = w / 65536;
                b = w % 65536;
                if ((a - x) * (a - x) + (b - y) * (b - y) > 2500) { continue; }
                if ((a - x) * (a - x) + (b - y) * (b - y) <= 2500) { break; }
            }//the direction and the speed are taken in form of click


            float dx = (a - x) / 5, dy =
                    (b - y) / 5, dp = dx, dq = dy;//direction and speed taken care of by proportionality

            // chaser carrom created in every
            Circle cd(p, q, 45);
            cd.setColor(COLOR(204, 102, 0)).setFill();

            while (true) {
                wait(0.01);
                if (p <= 335 || p >= 765) { dp = -dp; }
                if (q <= 135 || q >= 565) { dq = -dq; }

                if (x <= 300 || x >= 800) { dx = -dx; }
                if (y <= 100 || y >= 600) { dy = -dy; }
                //bouncing condns

                //moving conditions
                c1.move(dx, dy);
                //friction control
                dx = dx - dx / 100;
                dy = dy - dy / 100;
                if ((dx >= -0.1 && dx <= 0.1) && (dy >= -0.1 && dy <= 0.1)) { break; }

                float Dp = i * dp, Dq = i * dq;
                cd.move(Dp, Dq);
                //friction control
                if ((dp <= -0.05 || dp >= 0.05) || (dq <= -0.05 || dq >= 0.05)) {
                    dp = dp - dp / 50;
                    dq = dq - dq / 50;
                }
                //co-ordinated data collection
                x = c1.getX();
                y = c1.getY();
                p = cd.getX();
                q = cd.getY();

                //caught by chaser condn
                if ((x - p) * (x - p) + (y - q) * (y - q) <= 3500) {
                    cd.setColor(COLOR(255, 0, 0)).setFill();
                    wait(2);
                    break;
                }

                //pocket conditions
                if ((x - 310) * (x - 310) + (y - 110) * (y - 110) <= 70) {
                    c1.setColor(COLOR(0, 0, 0));
                    wait(0.1);
                    i++;
                    break;
                }
                if ((x - 790) * (x - 790) + (y - 110) * (y - 110) <= 70) {
                    c1.setColor(COLOR(0, 0, 0));
                    wait(0.1);
                    i++;
                    break;
                }
                if ((x - 310) * (x - 310) + (y - 590) * (y - 590) <= 70) {
                    c1.setColor(COLOR(0, 0, 0));
                    wait(0.1);
                    i++;
                    break;
                }
                if ((x - 790) * (x - 790) + (y - 590) * (y - 590) <= 70) {
                    c1.setColor(COLOR(0, 0, 0));
                    wait(0.1);
                    i++;
                    break;
                }

            }

            // control reaches here then if both below condns are not satisfd then it means carrom is in pockets and this game continues
            if ((x - p) * (x - p) + (y - q) * (y - q) <= 3600) { break; }
            if ((dx >= -0.1 && dx <= 0.1) && (dy >= -0.1 && dy <= 0.1)) { break; }

        }

        //single game ends
        //score output and ask for another game
        cout << "Your score is =" << " " << i << endl << "do you want to play another game? y or n" << endl;
        char replay;
        cin >> replay;
        if (replay == 'n') { break; }
        if (replay == 'y') { continue; }
        //if no then game play ends and eventually main program ends
    }
}
