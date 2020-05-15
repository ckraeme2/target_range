// Charles Kraemer
#include "gfx.h"
#include "player.h"

player::player() { }

player::player(int x1, int y1, int sd1, int sd2) {
	x=x1;
	y=y1;
	s1=sd1;
	s2=sd2;
}

int player::getX() { return x; }

int player::getY() { return y; }

void player::draw() { // draws gun as a square and two rectangles
	gfx_color(255,255,255);
	gfx_line(x,y,x,y+s1/2);
	gfx_line(x,y,x,y-s1/2);
	gfx_color(160,160,160);
	gfx_line(x,y+s1/2,x-s2,y+s1/2);
	gfx_line(x,y-s1/2,x-s2,y-s1/2);
	gfx_line(x-s2,y+s1/2,x-s2,y-s1/2);
	gfx_line(x-s2,y+s1/2,x-s2-s1,y+s1/2);
	gfx_line(x-s2-s1,y+s1/2,x-s2-s1,y-s1/2);
	gfx_line(x-s2,y-s1/2,x-s2-s1,y-s1/2);
	gfx_color(184,134,11);
	gfx_line(x-s2,y+s1/2,x-s2,y+s1/2+s2);
	gfx_line(x-s2-s1,y+s1/2,x-s2-s1,y+s1/2+s2);
	gfx_line(x-s2-s1,y+s1/2+s2,x-s2,y+s1/2+s2);
}

void player::down(int f) {
	int increment= 10;
	if(floor(f)) {   // checks if gun has hit the lower border
		y+=increment;  // moves gun downwards according to increment
	}
}

void player::up(int c) {
	int increment= 10;
	if(ceiling(c)) { // checks if gun has hit the upper border
		y-=increment;  // moves gun upwards according to increment
	}
}

bool player::floor(int f) {
	if((y+s1/2+s2+10)<=f) {  // checks if lowest point of gun will be below the border if it moves downwards
		return true;
	}
	else {
		return false;
	}
}

bool player::ceiling(int c) {
	if((y-s1/2-10)>=c) {   // checks if highest point of gun will be above the border if it moves upwards
		return true;
	}
	else {
		return false;
	}
}

