#ifndef CURSOR
#define CURSOR
#include <vector>
#include "Constant.h"
using namespace std;
class Cursor {
private:
	int xLoc;
	int yLoc;
	int boardLength = 8;
	int boardHeight = 8;
	vector<char> shape_chars = { '\\', '|', '/', '-' };
	int shape_choice = 0;

public:
	Cursor(int x, int y, int z, int a) {
		xLoc = x;
		yLoc = y;
		boardLength = z;
		boardHeight = a;
	}
	Cursor() {
		yLoc = 0;
		xLoc = 0;
		boardLength = 10; //change later *
		boardHeight = 10; // change later *

	}

	int getX() { return xLoc; }
	int getY() { return yLoc; }
	int getXY() { return yLoc * boardLength + xLoc; }

	void setX(int x) { xLoc = x; }
	void setY(int y) { yLoc = y; }
	void setXY(int x, int y) {
		xLoc = x;
		yLoc = y;
	}
	void setBoardLength(int z) { boardLength = z; }
	void setBoardHeight(int a) { boardHeight = a; }

	char Show_Cursor() {

		return shape_chars.at(shape_choice);

	}
	void changeShape() {
		shape_choice++;
		if (shape_choice > 3) { shape_choice = 0; }
	}

	void moveCursor(int x, int y) {
		if (!(xLoc == 0 && x < 0 || xLoc == 7 && x > 0))
			xLoc += x;
		if (!(yLoc == 0 && y < 0 || yLoc == 7 && y > 0))
			yLoc += y;
	}
	void move_up() { if (yLoc != 0) { yLoc--; } }
	void move_down() { if (yLoc != boardL - 1) { yLoc++; } }
	void move_left() { if (xLoc != 0) { xLoc--; } }
	void move_right() { if (yLoc != boardW - 1) { xLoc++; } }




};

class Cell {
private:
	char piece = '_';
	bool cursor = 0;
public:
	char getPiece() { return piece; }
	void setPiece(char p) { piece = p; }
	bool getCursor() { return cursor; }
	void setCursor(char p) { cursor = 1; }
};


#endif 

