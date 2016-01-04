#include "DarkGDK.h"
#include "sncIOstream.h"
#include <string>
using namespace std;

unsigned const int BLACK = dbRGB(0,0,0);
unsigned const int RED = dbRGB(255,0,0);
unsigned const int GREEN = dbRGB(0,255,0);
unsigned const int BLUE = dbRGB(0,0,255);
unsigned const int PURPLE = dbRGB(0,130,130);
unsigned const int YELLOW = dbRGB(130,130,0);
unsigned const int WHITE = dbRGB(255,255,255);

const int picNum00		= 1;
const int picNum01		= 2;
const int picNum02		= 3;

void DarkGDK ()
{
	int i = 0;
	int j = 0;
	unsigned int total = 0;
	long float avg;
	long float avg2;
	long float avg3;
	unsigned int blur[500][480];
	int mouseX = 0;
	int mouseY = 0;
	int x = 0;
	int y = 0;
	int rad = 0;
	bool radon = true;
	bool enter = true;
	string picture;
	int picNum;

	cout << "Enter picture name" << endl;
	cin >> picture;

	if (picture == "charizard"){
		dbLoadImage("charizard.bmp", picNum00);
		picNum = picNum00;
	}
	if (picture == "background"){
		dbLoadImage("background.bmp", picNum01);
		picNum = picNum01;
	}

	dbPasteImage(picNum, 0, 0);

	//dbSizeSprite(picNum, 640, 480);

	for (i = 0; i <= 499; i++){
		for (j = 0; j <= 479; j++)
			blur[i][j] = dbPoint(i,j);}
	dbPasteImage(picNum, 0, 0);
NEWRAD:

	dbInk(WHITE, 0);
	//sncCenterText(320,240, "Enter a radius");	
	cout << "Enter a radius" << endl;
	cin >> rad;

	dbSyncOn();
	dbSyncRate(120);

	while ( !dbEscapeKey())
	{
		dbInk(WHITE, 0);
		sncCenterText(320,20, "Press spacekey to change radius");

		mouseX = dbMouseX();
		mouseY = dbMouseY();

		// set new radius
		if (dbSpaceKey())
			goto NEWRAD;

/////////////////////////////////////////////////////////////////////////////////////////////

		avg = (blur[mouseX+1][mouseY] + blur[mouseX][mouseY+1] + blur[mouseX+1][mouseY+1] + blur[mouseX-1][mouseY+1] +
		 blur[mouseX][mouseY-1] +  blur[mouseX-1][mouseY] +  blur[mouseX-1][mouseY-1] +  blur[mouseX+1][mouseY-1]) / 8;

		
		// avg2 creates the fuzzy border color
		//avg2 = (blur[mouseX+1][mouseY] + blur[mouseX][mouseY+1] + blur[mouseX+1][mouseY+1] + blur[mouseX-1][mouseY+1] +
		//blur[mouseX][mouseY-1] +  blur[mouseX-1][mouseY] +  blur[mouseX-1][mouseY-1] +  blur[mouseX+1][mouseY-1] + 
		//blur[510][5] + blur[510][5] + blur[510][5] + blur[510][5] + blur[510][5] + blur[510][5] + blur[510][5] +
		//blur[510][5]) / 16;

/////////////////////////////////////////////////////////////////////////////////////////////
///////////for some reason the avg equation above works but the one below does not//////////
////////////////// they seem like they do the exact same thing /////////////////////////////
		
/*
		total = 0;
		for (i = -rad; i <= rad; i++)
		{
			for (j = -rad; j <= rad; j++)
			{
				if (i == 0 && j == 0){}
				else
					total = total + (blur[mouseX + rad][mouseY + rad]);
			}
		}
		avg = total / (((rad + (rad + 1)) * (rad + (rad + 1))) - 1);*/
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

		// click and drag to draw
		if (dbMouseClick())
		{
			dbInk(avg, 0);
			for (i = 0; i < (rad - 5); i++)
			{
				dbCircle(mouseX, mouseY, i);
			}

			//dbInk(avg2, 0);
			//for (i = rad - 5; i < rad; i++)
			//{
			//	dbCircle(mouseX, mouseY, i);
			//}
		}

		// side bar that shows you the average color at all times
		for (i = 500; i <= 520; i++)
		{
			dbInk(avg, 0);
			for (j = 10; j <= 480; j++)
				dbDot(i, j);
			dbInk(BLACK, 0);
			for (j = 0; j <= 10; j++)
				dbDot(i, j);
		}
		
		dbSync();
	}

	dbSyncOff();
	dbInk(RED, 0);
	//dbCircle(320,240,10);
	cout << "HI" << endl;
	
	dbWaitKey();
	return;
}