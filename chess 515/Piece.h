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
	void setX(int x) { xLoc = x; }
	void setY(int y) { yLoc = y; }
	bool retColor() { return color; }
	char retLool() { return looks; }
	int retY() { return yLoc; }
	int retX() { return xLoc; }
};

class Pawn : public Piece {
public:

};

class Rook : public Piece {
public:

};

class Knight : public Piece {
public:
	void moveUpLeft() {
		setX(retX() - 1);
		setY(retY() + 3);
	}
	void moveUpRight() {
		setX(retX() + 1);
		setY(retY() + 3);
	}
	void ShortUpLeft() {
		setX(retX() - 3);
		setY(retY() + 1);
	}
	void ShortUpRight() {
		setX(retX() + 3);
		setY(retY() + 1);
	}
	void moveDownLeft() {
		setX(retX() - 1);
		setY(retY() - 3);
	}
	void moveDownRight() {
		setX(retX() + 1);
		setY(retY() - 3);
	}
	void ShortDownLeft() {
		setX(retX() - 3);
		setY(retY() - 1);
	}
	void ShortDownRight() {
		setX(retX() + 3);
		setY(retY() - 1);
	}



};

class Bishop : public Piece {
public:

};

class King : public Piece {
public:

};

class Queen : public Piece {
public:

};

#endif

