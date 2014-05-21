#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "glut.h"

int frame=0;

class wcPt2D{
public:
	float x, y;
};

float proportion = 0.0;
float theta =0.0;
float f_Translate =0.0, f_Translate2 =0.0, f_Translate3 =0.0, f_Translate4 = 0.0, f_Translate5 = 0.0, outro_Translate= 0.0;
float bar_Translate = 0.0;
float f_Scale=0.0;
float f_Rotate=0.0;
//float theta = 0;

wcPt2D carV[17] = {{645,440},{630,440},{630,470},{635,470},{640,490},{680,490},{695,470},
{705,470},{705,440},{665,440},{665,435},{680,435},{680,440},{650,440},{650,435},{645,435},{645,440}};

wcPt2D D[17] = {{650, 450},{670, 450},{690, 470},{700, 500},{690, 530},{680, 540},{660, 550},
{650, 550},{650, 540},{650, 530},{650, 520},{650, 510},{650, 500},{650, 490},{650, 480},{650, 470},{650, 460}};

wcPt2D tweenPoly[20];

void tween(wcPt2D source[20], wcPt2D destination[20], int numPoints, double proportion, wcPt2D tweenPoly[20])
{
	
	for( int i = 0; i < numPoints; i++)
        {
                // get the source point
		    double sourceX = source[i].x;
 		    double sourceY = source[i].y;

                // get the destination point
 		    double destinationX = destination[i].x;
 		    double destinationY = destination[i].y;

                // get the difference between source and destination
 		    double differenceX = (destinationX - sourceX);
 		    double differenceY = (destinationY - sourceY);

                // tween point is source position + proportion
             // of distance between source and destination
 		    double tweenX = sourceX + ( differenceX * proportion );
 		    double tweenY = sourceY + ( differenceY * proportion );

           // create point with tween co-ordinates in tween array
			tweenPoly[i].x = tweenX;
			tweenPoly[i].y = tweenY;
        }
}

void morph_DCar()
{
int i;
glColor3f(0.8,0.5,0.5);
tween(carV,D,17,proportion,tweenPoly);
glBegin(GL_LINE_STRIP);
for(i=0;i<17;i++)
{
glVertex2i(tweenPoly[i].x, tweenPoly[i].y);
}
glEnd();
proportion +=0.01;
	if(proportion >1.0) proportion =0.0;
}

void Timer( int value )
{
   if( value ) glutPostRedisplay();
   glutTimerFunc(40,Timer,value);
}

void visibility(int state)
{
 switch (state)
 {
   case GLUT_VISIBLE:
             Timer(1);
             break;
   case GLUT_NOT_VISIBLE:
             Timer(0);
             break;
   default:
             break;
 }
}

void renderSpacedBitmapString(float x,float y,int spacing,void *font,char *string) 
{
  char *c;
  int x1=x;
  for (c=string; *c != '\0'; c++) {
	glRasterPos2f(x1,y);
    	glutBitmapCharacter(font, *c);
	x1 = x1 + glutBitmapWidth(font,*c) + spacing;
  }
}
void drawCircle(float x_centre, float y_centre, float radius)
{
	glLineWidth(7.0);
	//glColor3f(0.0,0.0,0.0);
	double angle = 2*3.1415/20 ;
	float x;
	float y;
	int i; 
	int steps = 20 ;// the number of lines to be generated to draw the circle#

		glBegin(GL_LINE_LOOP);
		for(i=1; i <=steps; i++)
			{
			x= x_centre +radius * cos (i * angle);
			y= y_centre + radius * sin(i*angle);
			glVertex2f(x,y);

			}
	glEnd();	
}

void car(void){
	glLineWidth(1.0);
	glBegin(GL_POLYGON);//main body
		glColor3f(1.0, 1.0, 1.0);
		glVertex2i(150,160);
		glVertex2i(120,160);
		glVertex2i(120,180);
		glVertex2i(130,180);
		glVertex2i(130, 210);
		glVertex2i(150, 230);
		glVertex2i(270, 230);
		glVertex2i(300, 200);
		glVertex2i(340, 200);
		glVertex2i(350, 190);
		glVertex2i(350, 170);
		glVertex2i(355, 170);
		glVertex2i(355, 160);
		glVertex2i(320, 160);
glEnd();

glBegin(GL_LINES); //completing main body
	glColor3f(1.0, 0.5, 0.0);
	glVertex2i(190, 160);
	glVertex2i(280,160);
glEnd();

glBegin(GL_POLYGON); //front window
	glColor3f(0.0,0.0,0.0);
	glVertex2i(270, 225);
	glVertex2i(285,210);
	glVertex2i(285,200);
	glVertex2i(230, 200);
	glVertex2i(220, 225);
	glVertex2i(270, 225);
glEnd();
glBegin(GL_POLYGON); //rear window
	glColor3f(0.0,0.0,0.0);
	glVertex2i(210, 225);
	glVertex2i(220,200);
	glVertex2i(160,200);
	glVertex2i(160, 225);
	glVertex2i(210, 225);
glEnd();
glBegin(GL_TRIANGLES);
	glColor3f(1.0,0.0,0.0);
	glVertex2i(160, 200);
	glVertex2i(160, 225);
	glVertex2i(140, 200);
glEnd();
glBegin(GL_LINES); //extra borders
	glColor3f(0.0,0.0,0.0);
	glVertex2i(300, 170); // bumper line
	glVertex2i(350, 170);
	glVertex2i(230, 200);//front door line
	glVertex2i(230, 165);
	glVertex2i(230, 165);
	glVertex2i(285, 165);
	glVertex2i(285, 200);
	glVertex2i(285, 170);
	glVertex2i(220, 200);//backdoor line
	glVertex2i(220, 165);
	glVertex2i(220, 165);
	glVertex2i(160, 165);
	glVertex2i(160, 165);
	glVertex2i(160, 200);
	glVertex2i(240, 190);//door handle line
	glVertex2i(250, 190);
	glVertex2i(170, 190);
	glVertex2i(180, 190);
glEnd();
glBegin(GL_LINES);// F on car body
	glColor3f(1.0,0.0,0.0);
	glVertex2i(300, 170);
	glVertex2i(300, 190);
	glVertex2i(300, 190);
	glVertex2i(310, 190);
	glVertex2i(300, 180);
	glVertex2i(310, 180);
glEnd();

glColor3f(1.0,0.0,0.0);
drawCircle (170,150,18); //wheels
drawCircle(300,150,18);
drawCircle (170,150,9); //wheels
drawCircle(300,150,9);
}

void roadLines()
{
	glColor3f(0.0,0.0,1.0);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glVertex2i(0,100);
	glVertex2i(1000,100);
	glVertex2i(0,250);
	glVertex2i(1000,250);
	glEnd();
	
}
void roadDotted(){
	glEnable(GL_LINE_STIPPLE);
		glColor3f(0.0,0.0,1.0);
		glLineStipple(8, 0x1c47);
		glBegin(GL_LINES);
			glLineWidth(5.0);
			glVertex2i(0, 200);
			glVertex2i(1000, 200);
		glEnd();
	glDisable(GL_LINE_STIPPLE);
}
void hills(){
	glLineWidth(1.0);
	glBegin(GL_POLYGON);
		glColor3f(0.5, 1.0, 0.5);
		glVertex2i(0, 300);//1st hill
		glVertex2i(100, 450);
		glVertex2i(130, 480);
		glVertex2i(150, 490);
		glVertex2i(160, 490);
		glVertex2i(180, 480);
		glVertex2i(200, 460);
		glVertex2i(240, 400);
		glVertex2i(290, 300);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0.0, 0.5, 0.0);
		glVertex2i(100, 450);//1st hill cover
		glVertex2i(120, 430);
		glVertex2i(140, 450);
		glVertex2i(170, 420);
		glVertex2i(190, 450);
		glVertex2i(230, 420);
		glVertex2i(200, 460);
		glVertex2i(180, 480);
		glVertex2i(160, 490);
		glVertex2i(150, 490);
		glVertex2i(130, 480);
	glEnd();
	glBegin(GL_POLYGON);//2nd hill
		glColor3f(0.5, 1.0, 0.0);
		glVertex2i(200, 300);
		glVertex2i(250, 380);
		glVertex2i(250, 380);
		glVertex2i(310, 450);
		glVertex2i(340, 470);
		glVertex2i(360, 480);
		glVertex2i(370, 480);
		glVertex2i(400, 460);
		glVertex2i(440, 400);
		glVertex2i(500, 300);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0.5, 1.0, 0.0);
		glVertex2i(500, 300);//3rd hill
		glVertex2i(600, 400);
		glVertex2i(650, 440);
		glVertex2i(700, 460);
		glVertex2i(720, 460);
		glVertex2i(750, 450);
		glVertex2i(780, 430);
		glVertex2i(850, 370);
		glVertex2i(920, 300);
	glEnd();
}
void moon(){
	glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,0);
		glVertex2i(850,640);
		glVertex2i(830, 620);
		glVertex2i(810, 580);
		glVertex2i(820, 530);
		glVertex2i(850, 500);
		glVertex2i(890, 490);
		glVertex2i(920, 490);
		glVertex2i(900, 500);
		glVertex2i(870, 520);
		glVertex2i(840, 560);
		glVertex2i(840, 600);
		glVertex2i(850, 640);
	glEnd();
}
void fuel(){
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 0.0, 0.0);//border
	glVertex2i(400, 600);
	glVertex2i(500, 500);
	glVertex2i(550, 500);
	glVertex2i(650, 600);
	glVertex2i(400, 600);
	glEnd();
	
	glBegin(GL_LINES);//F word
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(440, 570);
	glVertex2i(440, 590);
	glVertex2i(440, 580);
	glVertex2i(450, 580);
	glVertex2i(440, 590);
	glVertex2i(460, 590);
	glEnd();
	glBegin(GL_LINES);//E word
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(590, 570);
	glVertex2i(590, 590);
	glVertex2i(590, 590);
	glVertex2i(610, 590);
	glVertex2i(590, 580);
	glVertex2i(600, 580);
	glVertex2i(590, 570);
	glVertex2i(610, 570);
	glEnd();
	glBegin(GL_LINES);//measure bars
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(470, 550);//1
	glVertex2i(460, 560);
	glVertex2i(490, 550);//2
	glVertex2i(480, 560);
	glVertex2i(510, 550);//3
	glVertex2i(500, 570);
	glVertex2i(530, 550);//4
	glVertex2i(530, 560);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(550, 550);//5
	glVertex2i(560, 570);
	//glVertex2i(560, 550);//6
	//glVertex2i(570, 560);
	glVertex2i(580, 550);//7
	glVertex2i(590, 560);

	glEnd();
	
}
void fuelBar(){
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glBegin(GL_LINE_STRIP);//bar
		glColor3f(1.0, 0.0, 0.0);
		glVertex2i(530, 500);
		glVertex2i(580, 570);
	glEnd();
}
void battery(){
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP); //battery border
		glVertex2i(700, 600);
		glVertex2i(700, 500);
		glVertex2i(750, 500);
		glVertex2i(750, 600);
		glVertex2i(700, 600);
	glEnd();
	glBegin(GL_LINE_STRIP);//battery head
		glVertex2i(720, 600);
		glVertex2i(730, 600);
		glVertex2i(730, 610);
		glVertex2i(720, 610);
		glVertex2i(720, 600);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(1.0,0.0,0.0);
		glVertex2i(700, 570);
		glVertex2i(750, 570);
	glEnd();		
}
void batterySign(){
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);// battery sign 
		glColor3f(0.0,1.0,0.0);
		glVertex2i(730, 560);
		glVertex2i(710, 540);
		glVertex2i(740, 540);
		glVertex2i(710, 520);
	glEnd();
}
void car2(){
glLineWidth(1.0);
	glBegin(GL_POLYGON);//main body
		glColor3f(1.0, 0.5, 0.0);
		glVertex2i(150,160);
		glVertex2i(120,160);
		glVertex2i(120,180);
		glVertex2i(130,180);
		glVertex2i(130, 210);
		glVertex2i(150, 230);
		glVertex2i(270, 230);
		glVertex2i(300, 200);
		glVertex2i(340, 200);
		glVertex2i(350, 190);
		glVertex2i(350, 170);
		glVertex2i(355, 170);
		glVertex2i(355, 160);
		glVertex2i(320, 160);
		
	glEnd();
	glBegin(GL_LINES); //completing main body
		glColor3f(1.0, 0.5, 0.0);
		glVertex2i(190, 160);
		glVertex2i(280,160);
	glEnd();
	glBegin(GL_POLYGON); //front window
		glColor3f(0.0,0.0,0.0);
		glVertex2i(270, 225);
		glVertex2i(285,210);
		glVertex2i(285,200);
		glVertex2i(230, 200);
		glVertex2i(220, 225);
		glVertex2i(270, 225);
	glEnd();
	glBegin(GL_POLYGON); //rear window
		glColor3f(0.0,0.0,0.0);
		glVertex2i(210, 225);
		glVertex2i(220,200);
		glVertex2i(160,200);
		glVertex2i(160, 225);
		glVertex2i(210, 225);
	glEnd();
	glBegin(GL_LINES); //extra borders
		glColor3f(0.0,0.0,0.0);
		glVertex2i(230, 200);//front door line
		glVertex2i(230, 165);
		glVertex2i(230, 165);
		glVertex2i(285, 165);
		glVertex2i(285, 200);
		glVertex2i(285, 170);
		glVertex2i(220, 200);//backdoor line
		glVertex2i(220, 165);
		glVertex2i(220, 165);
		glVertex2i(160, 165);
		glVertex2i(160, 165);
		glVertex2i(160, 200);
		glVertex2i(240, 190);//door handle line
		glVertex2i(250, 190);
		glVertex2i(170, 190);
		glVertex2i(180, 190);

glEnd();
}
void car2Wheels(){
	glColor3f(1.0,0.0,0.0);
drawCircle (170,150,18); //wheels
drawCircle(300,150,18);
drawCircle (170,150,9); //wheels
drawCircle(300,150,9);

}
void trafficLight(){
	glBegin(GL_POLYGON);//traffic stand
	 glColor3f(1.0, 0.0, 0.0);
	 glVertex2i(360, 250);
	 glVertex2i(370, 250);
	 glVertex2i(370, 380);
	 glVertex2i(360, 380);
	glEnd();
	glBegin(GL_POLYGON);//traffic head
		glColor3f(1.0,1.0,1.0);
		glVertex2i(350, 380);
		glVertex2i(380, 380);
		glVertex2i(380, 450);
		glVertex2i(350, 450);
	glEnd();
}
void trafficRed(){
	glBegin(GL_POLYGON);//RED LIGHT
		glColor3f(1.0, 0.0, 0.0);
		glVertex2i(360, 430);
		glVertex2i(370, 430);
		glVertex2i(370, 440);
		glVertex2i(360, 440);
	glEnd();
}
void trafficAmber(){
	glBegin(GL_POLYGON);//amber LIGHT
		glColor3f(1.0, 0.5, 0.0);
		glVertex2i(360, 410);
		glVertex2i(370, 410);
		glVertex2i(370, 420);
		glVertex2i(360, 420);
	glEnd();
}
void trafficGreen(){	
glBegin(GL_POLYGON);//GREEN LIGHT
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(360, 390);
		glVertex2i(370, 390);
		glVertex2i(370, 400);
		glVertex2i(360, 400);
	glEnd();

}
void raceTrack(){
	glColor3f(0.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2i(380, 100);
	glVertex2i(410, 100);
	glVertex2i(380, 250);
	glVertex2i(350, 250);
	glEnd();
}
void flag(){
	 glColor3f (0.0, 0.0, 1.0);
	  glBegin(GL_POLYGON);	
      glVertex2i (400, 350);
      glVertex2i (450+rand()%20,350+rand()%20);
      glVertex2i (450+rand()%20,400+rand()%20);
      glVertex2i (400, 400);
   glEnd();
   glBegin(GL_LINES);
	  glColor3f(1.0,1.0,1.0);
	  glLineWidth(3.0);
	  glVertex2i(400, 250);
	  glVertex2i(400, 400);
   glEnd();
}
void ford(){
	glColor3f(0.8,0.5,0.5);
	glBegin(GL_LINE_STRIP); //F
		glVertex2i(350, 450);
		glVertex2i(350, 550);
		glVertex2i(400, 550);
	glEnd();
	glBegin(GL_LINES);
		glVertex2i(350, 500);
	    glVertex2i(380, 500);
	glEnd();

	glBegin(GL_LINE_LOOP);//O
		glVertex2i(440, 480);
		glVertex2i(440, 520);
		glVertex2i(460, 550);
		glVertex2i(490, 550);
		glVertex2i(510, 520);
		glVertex2i(510, 480);
		glVertex2i(490, 450);
		glVertex2i(460, 450);
	glEnd();

	glBegin(GL_LINE_STRIP);//R
		glVertex2i(550, 450);
		glVertex2i(550, 550);
		glVertex2i(600, 550);
		glVertex2i(600, 500);
		glVertex2i(550, 500);
		glVertex2i(600, 450);
	glEnd();
	/*
	glBegin(GL_LINE_LOOP);//D
		glVertex2i(650, 450);
		glVertex2i(670, 450);
		glVertex2i(690, 470);
		glVertex2i(700, 500);
		glVertex2i(690, 540);
		glVertex2i(670, 550);
		glVertex2i(650, 550);
	glEnd(); */
}
void carStand(){
	glBegin(GL_POLYGON);
		glColor3f(0,0,1);
		glVertex2i(30, 100);
		glVertex2i(330, 100);
		glVertex2i(330, 130);
		glVertex2i(30, 130);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0,1,0);
		glVertex2i(330, 100);
		glVertex2i(450, 220);
		glVertex2i(450, 250);
		glVertex2i(330, 130);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0.8,0.5,0.5);
		glVertex2i(30, 130);
		glVertex2i(330, 130);
		glVertex2i(450, 250);
		glVertex2i(150, 250);
	glEnd();
}
void carOutroSetup(){
	glPushMatrix();
		glTranslatef(0, -20, 0);
		carStand();
		glPopMatrix();
		
		car();

		glPushMatrix();
			glTranslatef(40,-25,0);
			flag();
		glPopMatrix();
}

void display (void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	frame++;
	fprintf(stdout, "frame: %i\n",frame); 
	
	if ((frame>0)&&(frame<100)){
		hills();
		roadLines();
		roadDotted();
		trafficLight();
		raceTrack();
		flag();
		
		glPushMatrix();
		glTranslatef(140, 100, 0);
		moon();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0,50,0);
		car2();
		car2Wheels();
		glPopMatrix();
		
		car();
		
		f_Translate += 0;
		f_Translate2 += 0;
	}
	
	if((frame>33)&&(frame<300)){trafficRed();} // traffic lights turn by turn
	if((frame>66)&&(frame<300)){trafficAmber();}
	if((frame>99)&&(frame<300)){trafficGreen();}
	if((frame>33)&&(frame<66)){ // message on each traffic light
		
		glPushMatrix();
		glTranslatef(300,600,0);
		glScalef(f_Scale, f_Scale,0.0);
		glScalef(1.5, 1.5, 0.0);
		renderSpacedBitmapString(0,0,5,GLUT_BITMAP_HELVETICA_18,"On Your Mark!");
		glPopMatrix();
	}
	if((frame>66)&&(frame<99)){
		glPushMatrix();
		glTranslatef(350,550,0);
		glScalef(f_Scale, f_Scale,0.0);
		glScalef(1.5, 1.5, 0.0);
		renderSpacedBitmapString(0,0,5,GLUT_BITMAP_HELVETICA_18,"Get Set!!");
		glPopMatrix();
	}
	if((frame>99) && (frame<132)){
		//int i;
	int red = rand()%255;
	int green = rand()%255;
	int blue = rand()%255;
	glColor3f (float(red)/255.0, float(green)/255.0, float(blue)/255.0); 

	//glColor3f(0.5,0.0,0.5);
	glPushMatrix();

	glTranslatef(400, 500,0);
	glScalef(f_Scale, f_Scale, 0.0);
	glScalef(1.5, 1.5,0.0);
	renderSpacedBitmapString(0,0,5,GLUT_BITMAP_HELVETICA_18,"GO!!!");
	glPopMatrix();	
		
	}
	
	if ((frame>100)&&(frame<300)){
		hills();
		roadLines();
		roadDotted();
		trafficLight();
		trafficRed();
		trafficAmber();
		trafficGreen();
		raceTrack();
		flag();
		
		glPushMatrix();
		glTranslatef(140, 100, 0);
		moon();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(f_Translate2, 0.0, 0.0);
		glTranslatef(0,50,0);
		car2();
		car2Wheels();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(f_Translate,0.0, 0.0);
		car();
		glPopMatrix();
		f_Translate += 6.0;
		f_Translate2 += 4.8;
	}
	if((frame>300)&&(frame<550)){ //drawings after 300 frames || 2nd Scene
		roadLines();
		roadDotted();
		hills();

		glPushMatrix();
		glTranslatef(140, 100, 0);
		moon();
		glPopMatrix();
	}
	
	if ((frame>300)&&(frame<375)){
		
		
		/*
		glPushMatrix();
		glTranslatef(0,50,0);
		car2();
		car2Wheels();
		trafficLight();
		glPopMatrix(); */
	
		glPushMatrix();
		glTranslatef(-150,50,0);
		glTranslatef(f_Translate4, 0.0, 0.0);
		car2();
		car2Wheels();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(f_Translate3, 0.0, 0.0);
		glTranslatef(0,0,0);
		car();
		glPopMatrix();
		
		f_Translate3 += 6.0;
		f_Translate4 += 4.0;
		
	}
	if((frame>375)&&(frame<550)){ //car stops as no fuel
		
		glPushMatrix();
		glTranslatef(-150,50,0);
		glTranslatef(f_Translate4, 0.0, 0.0);
		car2();
		car2Wheels();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(f_Translate3, 0.0, 0.0);
		glTranslatef(0,0,0);
		car();
		glPopMatrix();
		
		f_Translate3 += 0;
		f_Translate4 += 0;
	}
	if((frame>380)&&(frame<550)){
		glPushMatrix();
		glTranslatef(250,300,0);
		//glScalef(f_Scale2, f_Scale2,0.0);
		renderSpacedBitmapString(0,0,0,GLUT_BITMAP_HELVETICA_18,"OH NO! What do i do :'(");
		glPopMatrix();

		//f_Scale2 += 0.01;
	}
	if((frame> 400)&&(frame<445)){
		glColor3f(0,1,0);
		glPushMatrix();
		glTranslatef(650,250,0);
		//glScalef(f_Scale2, f_Scale2,0.0);
		renderSpacedBitmapString(0,0,0,GLUT_BITMAP_HELVETICA_18,"No Problemo ;)");
		glPopMatrix();	
	}
	if ((frame>320)&&(frame<550)){
		fuel();
		fuelBar();

		glPushMatrix();
		glTranslatef(400,620,0);
	//glScalef(f_Scale, f_Scale, 0.0);
		glScalef(1.5, 1.5, 0.0);
		renderSpacedBitmapString(0,0,0,GLUT_BITMAP_HELVETICA_18,"Warning: No Fuel!!");
		glPopMatrix();
	}
	if((frame>400)&&(frame<550)){
		battery();
		batterySign();

		glColor3f(1.0,1.0,1.0);
		if((frame>420)&&(frame<425))glColor3f(1,0,0); //white, red and finaly green flashing!
		if((frame>425)&&(frame<430))glColor3f(1,1,1);
		if((frame>430)&&(frame<435))glColor3f(1,0,0);
		if((frame>435)&&(frame<440))glColor3f(1,1,1);
		if(frame>440)glColor3f(0,1,0);

		glPushMatrix();
		glTranslatef(700,630,0);
		//glScalef(f_Scale, f_Scale, 0.0);
		glScalef(1.5, 1.5, 0.0);
		renderSpacedBitmapString(0,0,0,GLUT_BITMAP_HELVETICA_18,"Battery: ON");
		glPopMatrix();
	}
	if((frame>445)&&(frame<550)){	//battery on. start car1 moving!
		f_Translate3 += 6.0;
	}
	
	if((frame>550)&&(frame<700)){ //drawings after 550 frames || 3rd Scene
		roadLines();
		roadDotted();
		hills();

		glPushMatrix();
		glTranslatef(260,0,0);
		flag();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(140, 100, 0);
		moon();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(300,0,0);
		raceTrack();
		glPopMatrix();
	}
	
	if((frame>550)&&(frame<650)){ 
		glPushMatrix();
		glTranslatef(f_Translate5, 0.0, 0.0);
		glTranslatef(0,0,0);
		car();
		glPopMatrix();

		f_Translate5 += 6.0;
	}

	if((frame>650)&&(frame<700)){
		f_Translate5 += 0;
		glPushMatrix();
		glTranslatef(f_Translate5, 0.0, 0.0);
		glTranslatef(0,0,0);
		car();
		glPopMatrix();
	}
	if((frame>700)&&(frame<720)){			//car outro setup
		glPushMatrix();
		glTranslatef(outro_Translate, 0.0, 0.0);
		carOutroSetup();
		glPopMatrix();
		
		outro_Translate += 20;

		
	}
	if((frame>720)&&(frame<830)){
		glPushMatrix();
		glTranslatef(outro_Translate, 0.0, 0.0);
		carOutroSetup();
		glPopMatrix();
		outro_Translate += 0;
	}
	
	if((frame>730)&&(frame<750)){ // faster
		
		glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(300,600,0);
		glScalef(1.5, 1.5, 0.0);
		renderSpacedBitmapString(0,0,5,GLUT_BITMAP_HELVETICA_18,"Faster...");
		glPopMatrix();
	}
	if((frame>750)&&(frame<765)){ //rotation
		theta = theta-25.57;
		glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(350,550,0);
		glRotatef(theta, 0, 0, 1);
		glScalef(1.5, 1.5, 0.0);
		renderSpacedBitmapString(0,0,5,GLUT_BITMAP_HELVETICA_18,"Smoother...");
		glPopMatrix();
	}
	if((frame>765)&&(frame<785)){ //Smoother...
		glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(350,550,0);
		glScalef(1.5, 1.5, 0.0);
		renderSpacedBitmapString(0,0,5,GLUT_BITMAP_HELVETICA_18,"Smoother...");
		glPopMatrix();
	}
	if((frame>785)&&(frame<830)){ //and now on battery powered!!
		
		glColor3f(1.0,1.0,1.0);
		if((frame>785)&&(frame<789))glColor3f(1,0,0); //white, red and finaly green flashing!
		if((frame>789)&&(frame<793))glColor3f(1,1,1);
		if((frame>793)&&(frame<797))glColor3f(1,0,0);
		if((frame>797)&&(frame<801))glColor3f(1,1,1);
		if(frame>801)glColor3f(0,1,0);

		glPushMatrix();
		glTranslatef(350,500,0);
		glScalef(1.5, 1.5, 0.0);
		renderSpacedBitmapString(0,0,5,GLUT_BITMAP_HELVETICA_18,"Hybrid car of 2013!!");
		glPopMatrix();
	}

	if((frame>830)){ //final scene
		car();

		glPushMatrix();
			glTranslatef(0,0,0);
			morph_DCar(); // morph
			ford();
		glPopMatrix();
		

		glPushMatrix();
		glColor3f(1.0,1.0,1.0);
		glTranslatef(600,400,0);
		//glScalef(f_Scale, f_Scale, 0.0);
		glScalef(1.5, 1.5, 0.0);
		renderSpacedBitmapString(0,0,0,GLUT_BITMAP_HELVETICA_18,"Go Further");
		glPopMatrix();
	}
	f_Rotate += 90.0f;
	f_Scale += 0.01;
	//bar_Translate +=2.0;
	glutSwapBuffers();
	glFlush();
}


void init(void)
{
glClearColor(0, 0, 0, 0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0, 1000.0, 0.0, 700.0);
}


int main ( int argc , char** argv)
{
	glutInit(&argc ,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (1000, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Advertisement");
	init();
	glutDisplayFunc(display);
	glutVisibilityFunc(visibility);
	glutMainLoop();
	return 0;
}
