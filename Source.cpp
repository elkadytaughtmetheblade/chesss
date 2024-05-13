#include <iostream>
#include <vector>
#include <thread>
#include "windows.h"
#include <mutex>
#include <ctime>
#include <chrono>

using namespace std;

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

class Cursor {
private:
    int x = 0;
    int y = 0;
    int xSelect = 0;
    int ySelect = 0;
    char shape = 'X';
public:
    int getX() { return x; }
    int getY() { return y; }
    int getxSelect() { return xSelect; }
    int getySelect() { return ySelect; }

    void moveCursor(int x1, int y1) {
        if (!(x == 0 && x1 < 0 || x == 7 && x1 > 0))
            x += x1;
        if (!(y == 0 && y1 < 0 || y == 7 && y1 > 0 ))
            y += y1;
    }
    char getShape() { return shape; }
    void setShape(char s) { shape = s; }
    void select() {
        shape = '+';
        xSelect = x;
        ySelect = y;
    }
};

void print(vector<vector<Cell>> board, Cursor cursor) {
    gotoxy(0, 0);
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (i == cursor.getY() && j == cursor.getX())
                cout << cursor.getShape();
            else cout << board.at(i).at(j).getPiece();
        }
        cout << endl;
    };
}

void boardUpdate(vector<vector<Cell>> board, Cursor& cursor, bool gameRunning) {
    while (gameRunning) {
        this_thread::sleep_for(chrono::milliseconds(100));
        print(board, cursor);
        cout << "cursor: " << cursor.getX() << ", " << cursor.getY() << endl;
        cout << "gamerunning: " << gameRunning << endl;
    }
}

void move(vector<vector<Cell>>& board, int x1, int y1, int x2, int y2) {
    char piece = board.at(y1).at(x1).getPiece();
    board.at(y1).at(x1).setPiece('_');
    board.at(y2).at(x2).setPiece(piece);
}


int main()
{
    vector<vector<Cell>> board(8, vector<Cell>(8, Cell()));
    Cursor cursor;

    board.at(0).at(0).setPiece('R');
    board.at(0).at(1).setPiece('N');
    board.at(0).at(2).setPiece('B');
    board.at(0).at(3).setPiece('Q');
    board.at(0).at(4).setPiece('K');
    board.at(0).at(5).setPiece('B');
    board.at(0).at(6).setPiece('N');
    board.at(0).at(7).setPiece('R');

    board.at(7).at(0).setPiece('R');
    board.at(7).at(1).setPiece('N');
    board.at(7).at(2).setPiece('B');
    board.at(7).at(3).setPiece('Q');
    board.at(7).at(4).setPiece('K');
    board.at(7).at(5).setPiece('B');
    board.at(7).at(6).setPiece('N');
    board.at(7).at(7).setPiece('R');

    for (int j = 0; j < 8; j++)
    {
        board.at(1).at(j).setPiece('P');
        board.at(6).at(j).setPiece('P');
    }

    bool gameRunning = 1;
    thread thread1(boardUpdate, board, ref(cursor), gameRunning);
    system("cls");

    do {
        system("pause>nul"); //wait for key
        if (GetAsyncKeyState(VK_DOWN)) {
            cursor.moveCursor(0, 1);
        }
        else if (GetAsyncKeyState(VK_UP)) {
            cursor.moveCursor(0, -1);
        }
        else if (GetAsyncKeyState(VK_RIGHT)) {
            cursor.moveCursor(1, 0);
        }
        else if (GetAsyncKeyState(VK_LEFT)) {
            cursor.moveCursor(-1, 0);
        }
        else if (GetAsyncKeyState(0x5A)) { // Z
            cursor.select();
        }
        else if (GetAsyncKeyState(VK_SPACE)) {
            move(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY());
        }
    } while (gameRunning);

}