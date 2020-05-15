// Charles Kraemer
class target {
	public:
	 target();
	 target(int,int,int,int);
	 void draw();
	 int getX();
	 int getY();
	 int getRad();
	 int getV();
	 void setRad(int);
	 void setV(int);
	 void move(int,int,int);
	 bool floor(int,int);   // ensures target does not go below game window
	 bool ceiling(int,int);   // ensures target does not go above game window
	private:
	int xc, yc; // center coordinates
	int rad;  // radius
	int v;  // speed
};
