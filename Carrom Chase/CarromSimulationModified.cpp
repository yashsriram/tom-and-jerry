#include<simplecpp>

main_program{

initCanvas("Carrom Simulation",800,700);

int centre=getClick();
int centrex,centrey,initialx,initialy,otherx,othery;
centrex=centre/65536;
centrey=centre%65536;
int side=400;
Rectangle r(centrex,centrey,side,side);

int initial=getClick();
initialx=initial/65536;
initialy=initial%65536;
Circle c(initialx,initialy,6);
c.setColor(COLOR(255,0,0));
c.setFill(1);

int other=getClick();
otherx=other/65536;
othery=other%65536;

float leftx,rightx,upy,downy;
leftx=centrex-(side/2);
rightx=centrex+(side/2);
upy=centrey-(side/2);
downy=centrey+(side/2);

float slope,directionx,x,ballx,bally,X,Y;
if(otherx!=initialx)
{
slope=(othery-initialy)/(otherx-initialx);  //(what if otherx==initialx????)

bool goingRight;
if((otherx-initialx)>0) goingRight=1;
else goingRight=0;

x=1;

if(goingRight) directionx=1;
else directionx=-1;

repeat(100000){
X=x*directionx;
Y=x*slope*directionx;
c.move(X,Y);
ballx=c.getX();
bally=c.getY();

if((ballx+6)>rightx || (ballx-6)<leftx) directionx=directionx*(-1);
else directionx=directionx*1;

if((ballx+6)>rightx|| (ballx-6)<leftx||(bally+6)>downy || (bally-6)<upy) slope=slope*(-1);
else slope=slope*1;
wait(0.00001);
}
}
else 
{float bally,directiony;
bool goingUp;
if((othery-initialy)<0) goingUp=1;
else goingUp=0;

float a=1;
X=0;

if(goingUp==1) directiony=-1;
else directiony=1;
repeat(100000)
{Y=directiony*a;
c.move(X,Y);
bally=c.getY();
if((bally-6)<upy || (bally+6)>downy) directiony=directiony*(-1);
else directiony=directiony*1;
wait(0.0001);
} 
} 
wait(10);
}
