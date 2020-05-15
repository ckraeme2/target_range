// Charles Kraemer
class player {
	public:
	 player();
	 player(int,int,int,int);
	 int getX();
	 int getY();
	 void draw();
	 void up(int);
	 void down(int);
	 bool ceiling(int);   // ensures gun does not go above game window
	 bool floor(int);   // ensures gun does not go below game window
	private:
	 int x,y;    // x and y coordinates of the center of the gun's tip
	 int s1,s2;  // size parameters of gun
};
	 

