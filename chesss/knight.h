#ifndef KNIGHT
#define KNIGHT
#include "Piece.h";

class Piece :public knight {


public:
	void moveUpLeft() {
		setX(retX() - 1);
		setY(retY() + 3);
	}

}



#endif
