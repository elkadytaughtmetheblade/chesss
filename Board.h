#ifndef BOARD
#define BOARD

#include "Constant.h"
#include "Cursor.h"
using namespace std;

class Board{
private:
	int length; // X
	int height; // Y
	vector<Cell> gameBoard;
	Cursor curs;
	bool running;
	bool gameRunning;
	void ShowConsoleCursor(bool showFlag)
	{
		//-------do not change-------
		//hides the cursor, use only once at program start
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(out, &cursorInfo);
	}
	BOOL gotoxy(const WORD x, const WORD y) {
		//-------do not change-------
		COORD xy;
		xy.X = x;
		xy.Y = y;
		return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	}


public:
	Board(int x, int y) {
		length = x;
		height = y;
		running = true;
		gameBoard.resize(length * height, Cell());

		gameRunning = true;

	}
	Board() {
		length = boardL;
		height = boardW;
		running = true;
		gameRunning = true;
		gameBoard.resize(boardL * boardW, Cell());
	}
//	vector<Cell> getBoardCells() { return boardCells; }

	bool getGameRunning() { return gameRunning; }
	void setGameRunning(bool g) { gameRunning = g; }

	void gameOver() { running = false; }
	void moveCursor_Up() { curs.move_up(); }
	void moveCursor_Down() { curs.move_down(); }
	void moveCursor_Right() { curs.move_right(); }
	void moveCursor_Left() { curs.move_left(); }

	void print(){
		for (int i = 0; i < boardW; i++) {
			for(int i = 0; i < boardL; i++){
				cout << gameBoard.at(i).getPiece();
			}
			cout << endl;
		}
	}


void c_update() {
	while (gameRunning) {
		this_thread::sleep_for(chrono::milliseconds(500));
		curs.changeShape();
		gotoxy(0, 0);
		//printAll();
		print();
		//printTime();
	}
}


















};

#endif // !BOARD
