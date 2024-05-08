#ifndef PIECE
#define PIECE
class Piece {
private:
	char looks;
	bool color;//white = true, black = false
	int xLoc;
	int yLoc;

public:
	void setLook(char c) { looks = c; }
	void setColor(bool c) { color = c; }
	void setX(int x){xloc=x;}
	void setY(int y) { yloc = y; }
	bool retColor() { return color; }
	char retLool() { return looks; }
	int retY() { return yloc; }
	int retX(){return xloc;}

}

#endif