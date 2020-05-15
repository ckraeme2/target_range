// Charles Kraemer
#include <cmath>
using namespace std;

#include "target.h"
#include "gfx.h"

target::target() { }

target::target(int x, int y, int r, int vy) {
	xc=x;
	yc=y;
	rad=r;
	v=vy;
}

int target::getX() { return xc; }

int target::getY() { return yc; }

int target::getRad() { return rad; }

int target::getV() { return v; }

void target::setRad(int r1) {
	rad=r1;
}

void target::setV(int v1) {
	v=v1;
}

void target::draw() {   // draws target as a set of circles
	gfx_color(255,0,0);
	gfx_circle(xc,yc,rad);
	gfx_color(255,255,255);
	gfx_circle(xc,yc,(3*rad)/4);
	gfx_color(255,0,0);
	gfx_circle(xc,yc,(rad)/2);
	gfx_color(255,255,255);
	gfx_circle(xc,yc,(rad)/4);
}


void target::move(int c, int f, int mg) {
	if(ceiling(c,mg)) {   // checks if target has hit upper border
		v=-v;  // reverses direction
	}
	if(floor(f,mg)) {  // checks if target has hit lower border
		v=-v;  // reverses direction
	}
	yc+=v;  // increment center y coordinate according to speed
}

bool target::ceiling(int c, int mg) {
	if((yc-rad-abs(v)>=(c+mg))) {
		return true;
	}
	else {
		return false;
	}
}

bool target::floor(int f, int mg) {
	if((yc+rad+abs(v))<=(f-mg)) {
		return true;
	}
	else {
		return false;
	}
}



