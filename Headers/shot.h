// Charles Kraemer
class shot {
	public:
	 shot();
	 shot(int,int,int,int);
	 void draw();
	 void move();
	 int getX();
	 int getY();
	 bool miss(int,int);    // checks if shot missed target
	 bool hit(int,int,int);  // checks if shot hit target
	 bool inRange(int);   // checks if shot is within range of the target
	private:
	 int x, y;    // center coordinates of shot
	 int s;   // side length of shot
	 int v;   // speed of shot
};

