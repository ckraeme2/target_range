// Charles Kraemer
#include <iostream>
#include "shot.h"
#include "gfx.h"
#include <cmath>
#include <vector>
using namespace std;

shot::shot() { }

shot::shot(int x1, int y1, int s1, int v1) {
	x=x1;
	y=y1;
	s=s1;
	v=v1;

}

int shot::getX() { return x; }

int shot::getY() { return x; }

void shot::draw() {  // draws shot as a square
	gfx_color(255,255,255);
	gfx_line(x-s/2,y-s/2,x+s/2,y-s/2);
	gfx_line(x-s/2,y-s/2,x-s/2,y+s/2);
	gfx_line(x-s/2,y+s/2,x+s/2,y+s/2);
	gfx_line(x+s/2,y+s/2,x+s/2,y-s/2);
}

void shot::move() {
	x+=v;   // moves shot according to its velocity
}

bool shot::miss(int xt, int rt) {  // checks if the left most side of the shot is greater than the right most side of the target
	if((x-(s/2))>(xt+rt)) {
		return true;
	}
	else {
		return false;
	}
}

bool shot::hit(int xt, int yt, int rt) {
	bool collide= false;
	int xb, yb;
	bool found= false;   // stops looking for collision if it has already been found
	if(inRange(xt-rt)) {  // only check for collision if the shot is within range of the target
		for(int i=y-(s/2); i<=y+(s/2); i++) {  // checks if any ordered pair on the right side of the shot collides with the target
			if(found==false) {  
				xb= x+(s/2);
				if((xb<=(xt+rt))&&(xb>=(xt-rt))&&(i<=(yt+rt))&&(i>=(yt-rt))) {
					collide=true;
					found=true;
				}
			}
		}
		if(found==false) {
			for(int i=y-(s/2); i<=y+(s/2); i++) {  // checks if any ordered pair on the left side of the shot collides with the target
				if(found==false) {
					xb= x-(s/2);
					if((xb<=(xt+rt))&&(xb>=(xt-rt))&&(i<=(yt+rt))&&(i>=(yt-rt))) {
						collide=true;
						found=true;
					}
				}
			}
		}
		if(found==false) {
			for(int i=x-(s/2); i<=x+(s/2); i++) {  // checks if any ordered pair on the top side of the shot collides with the target
				if(found==false) {
					yb= y-(s/2);
					if((i<=(xt+rt))&&(i>=(xt-rt))&&(yb<=(yt+rt))&&(yb>=(yt-rt))) {
						collide=true;
						found=true;
					}
				}
			}
		}
		if(found==false) {
			for(int i=x-(s/2); i<=x+(s/2); i++) {  // checks if any ordered pair on the bottom side of the shot collides with the target
				if(found==false) {
					yb= y+(s/2);
					if((i<=(xt+rt))&&(i>=(xt-rt))&&(yb<=(yt+rt))&&(yb>=(yt-rt))) {
						collide=true;
						found=true;
					}
				}
			}
		}
	}
	if(collide) {
		return true;
	}
	else {
		return false;
	}
}

bool shot::inRange(int c) {  // will check if the right most point of the shot is at least equal to the left most point of the target
	if((x+(s/2))>=c) {
		return true;
	}
	else {
		return false;
	}
}






