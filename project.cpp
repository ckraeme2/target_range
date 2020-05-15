// Charles Kraemer
#include <iostream>
#include <unistd.h>
#include <vector>
#include <time.h>
using namespace std;

#include "player.h"
#include "target.h"
#include "shot.h"
#include "gfx.h"

void drawSquare(int x1, int y1, int x2, int y2, int x3, int y3);
int randomRadius(int w, int r);
int randomSpeed(int w, int v);
int randomColorA();
int randomColorB();
int randomColorC();
int main() {
	bool play= true;   // logical on/off switch for game loop
	char c;			   // user input variable
	int height= 750;   // game window dimensions
	int width= 750;
	int margin= 40;    // margin so as to produce neater looking output
	int playerSide1= 20;   // playerSide variables determine dimensions of the player's gun
	int playerSide2= 50;
	int targetRadius= 60;   // initial target radius
	int shotSpeed= 40;    // speed of shots
	int maxShots= 3;   // maximum number of shots that can be on screen at a given time
	int targetSpeed=10;   // initial target speed
	int radWeight= 0;   // weight variables affect randomization of target parameters as user plays the game
	int spdWeight= 0;
	int newRadius;    // new variables are used to change target parameters
	int newSpeed;
	int colorSpread;   // used to facilitate randomization of window color
	bool levelUp= false;   // determines if game level increases
	bool activeShot= false;   // checks if there is a shot on the game screen
	int r= 0;     // color variables
	int g= 0;
	int b= 255;
	gfx_open(height,width,"Target Challenge");
	player p(margin+playerSide2+playerSide1,height/2,playerSide1,playerSide2);  // draw gun of given dimensions within game window
	target t(width-margin-targetRadius,height/2,targetRadius,targetSpeed);   // draw target of given dimensions within game window
	vector<shot> shots;    // contains all active shots on the screen
	while(play) {
		gfx_clear();
		gfx_color(r,g,b);
		drawSquare(margin-15,margin,width-margin+15,margin,width-margin+15,height-margin);  // creates a colored frame for the game
		t.draw();   // procedurally update target location as it moves
		t.move(0,height,margin);
		p.draw();   // procedurally update gun location
		if(activeShot) {   // check if there is a shot on the screen
			for(auto it=shots.begin(); it<shots.end(); ++it) { // operate on each active shot
				(*it).draw();   // procedurally update each shot location
				(*it).move();
				if((*it).miss(width-margin,t.getRad())) {
					shots.erase(it);    // remove shot from vector if it misses the target
				}
				if((*it).hit(t.getX(),t.getY(),t.getRad())) {
					radWeight += 5;     // increase weights affecting target parameters as user moves to new levels
					spdWeight += 5;
					levelUp= true;
					shots.erase(it);   // remove shot from vector if it hits the target
				}
			}
		}
		if(gfx_event_waiting()) {  // check for user input
			c=gfx_wait();
			if((int)c==119) {  // move gun up if user presses 'w' key
				p.up(margin);
			}
			if((int)c==115) {    // move gun down if user presses 's' key
				p.down(height-margin);
			}
			if((int)c==102) {    // fire a shot if user presses 'f' key
				if(shots.size()<=(maxShots-1)) {   // check to see if the maximum number of shots has already been reached
					shot s(p.getX(), p.getY(), playerSide1, shotSpeed);  // initialize new shot variable
					shots.push_back(s);   // append new shot to vector
					activeShot= true;   // report that there is an active shot on the screen
				}
			}
			if(c=='q') {  // end game if user inputs 'q'
				play= false;
			}
		}

		if(levelUp) {
			shots.clear();    // clear all shots on screen for new level
			newRadius= randomRadius(radWeight, t.getRad());    // randomize radius to progressively lower values
			newSpeed= randomSpeed(spdWeight, t.getV());      // randomize speed to progressively higher values
			t.setRad(newRadius);         // change target parameters
			t.setV(newSpeed);
			srand(time(0));   
			colorSpread= rand()%6+1;  // randomize color distribution for game frame of next level
			if(colorSpread==1) {
				r= randomColorA();   // each color variable draws from a different range of values corresponding to different functions for more interesting frame colors
				g= randomColorB();
				b= randomColorC();
			}
			else if(colorSpread==2) {
				r= randomColorA();
				g= randomColorC();
				b= randomColorB();
			}
			else if(colorSpread==3) {
				r= randomColorB();
				g= randomColorA();
				b= randomColorC();
			}
			else if(colorSpread==4) {
				r= randomColorB();
				g= randomColorC();
				b= randomColorA();
			}
			else if(colorSpread==5) {
				r= randomColorC();
				g= randomColorA();
				b= randomColorB();
			}
			else if(colorSpread==6) {
				r= randomColorC();
				g= randomColorB();
				b= randomColorA();
			}
			levelUp= false;  // do not level up again until the user hits the new target
		}		
		gfx_flush();
		usleep(100000);   
	}
}
		
void drawSquare(int x1, int y1, int x2, int y2, int x3, int y3) {   // draws game frame
	gfx_line(x1,y1,x2,y2);
	gfx_line(x2,y2,x3,y3);
	gfx_line(x3,y3,x1,y3);
	gfx_line(x1,y3,x1,y1);
}

int randomRadius(int w, int r) {
	int max= r-w;    // minimum and maximum potential raidus values decrease as weight increases
	int min= r-w-10;   
	int a;
	if(min>20) {
		srand(time(0));
		a= rand()%(max-min+1)+min;
	}
	else {
		srand(time(0));     // stop progressively decreasing min and max values once a threshold is passed
		a= rand()%(30-20+1)+20;
	}

	return a;
}

int randomSpeed(int w, int v) {
	int max= v+w;    // maximum potential speed values increase as weight increases
	int min= v;    // minimum potential speed value of new target it the speed of the prior target
	int a;
	if(max<20) {
		srand(time(0));
		a= rand()%(max-min+1)+min;
	}
	else {          // stop progressively increasing min and max values once a threshold is passed
		srand(time(0));
		a= rand()%(30-20+1)+20;
	}

	return a;
}

int randomColorA() {   // returns random color value between 255 and 175
	int a;
	srand(time(0));
	a= rand()%(255-175+1)+175;
	
	return a;
}

int randomColorB() {   // returns random color value between 175 and 100
	int a;
	srand(time(0));
	a= rand()%(175-100+1)+100;

	return a;
}

int randomColorC() {   // returns random color value between 100 and 25
	int a;
	srand(time(0));
	a= rand()%(100-25+1)+25;

	return a;
}
	



		
