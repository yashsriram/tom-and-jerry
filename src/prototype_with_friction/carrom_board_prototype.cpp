#include<simplecpp>




main_program{
initCanvas("carrom_board",1500,700);
Rectangle r1(550,350,520,520);
Rectangle r2(550,350,550,550);
Circle c5(790,110,15);
Circle c6(310,110,15);
Circle c7(790,590,15);
Circle c8(310,590,15);
Circle c9(550,350,150);
int i=0;
int z,w;
float x,y,a,b;
while(true){
z=getClick();
x=z/65536;y=z%65536;
Circle c1(x,y,9);
c1.setColor(COLOR(50,50,255));
c1.setFill(1);
while(true){
            Circle c2(x,y,50);
            Circle c3(x,y,35);
            Circle c4(x,y,20);
            c2.setColor(COLOR(255,0,0));
            c3.setColor(COLOR(255,100,100));
            c4.setColor(COLOR(255,200,200));
            w=getClick();
            a=w/65536;b=w%65536;
            if((a-x)*(a-x)+(b-y)*(b-y)>2500) {continue;}
            if((a-x)*(a-x)+(b-y)*(b-y)<=2500) {break;} }//carrom is hit

float dx=(a-x)/5,dy=(b-y)/5;
while (true)
        {
        wait(0.01);
        if(x<=300||x>=800){dx=-dx;}
        if(y<=100||y>=600){dy=-dy;}
        c1.move(dx,dy);

        dx=dx-dx/50;

        dy=dy-dy/50;

        if((dx>=-0.1&&dx<=0.1)&&(dy>=-0.1&&dy<=0.1)){break;}



        x=c1.getX();
        y=c1.getY();
        //pocket conditions
        if((x-310)*(x-310)+(y-110)*(y-110)<=36){i++;break;}
        if((x-790)*(x-790)+(y-110)*(y-110)<=36){i++;break;}
        if((x-310)*(x-310)+(y-590)*(y-590)<=36){i++;break;}
        if((x-790)*(x-790)+(y-590)*(y-590)<=36){i++;break;}}
 cout<<"Your score is"<<" "<<i<<endl;


        }
 cout<<"Your score is"<<i<<endl;

}
