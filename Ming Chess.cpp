// Ming Chess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include "windows.h"
#include <fstream>
#include <cctype>
#include <ctime>
#include <mutex>
#include <io.h>
#include <fcntl.h>

using namespace std;
using namespace chrono;
using namespace this_thread;

const char W_ROOK = 'R';
const char W_KNIGHT = 'N';
const char W_BISHOP = 'B';
const char W_QUEEN = 'Q';
const char W_KING = 'K';
const char W_PAWN = 'P';

const char EMPTY = '_';
const char CURSOR = 'X';
const char SELECTED = '+';

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
    char piece = EMPTY;
    bool cursor = 0;
public:
    char getPiece() { return piece; }
    void setPiece(char p) { piece = p; }
    // bool getCursor() { return cursor; }
    // void setCursor(bool c) { cursor = c; }
};

class Cursor {
private:
    int x = 0;
    int y = 0;
    int xSelect = 0;
    int ySelect = 0;
    char shape = CURSOR;
public:
    int getX() { return x; }
    int getY() { return y; }
    int getxSelect() { return xSelect; }
    int getySelect() { return ySelect; }

    void moveCursor(int x1, int y1) {
        if (!(x == 0 && x1 < 0 || x == 7 && x1 > 0))
            x += x1;
        if (!(y == 0 && y1 < 0 || y == 7 && y1 > 0))
            y += y1;
    }
    char getShape() { return shape; }
    void setShape(char s) { shape = s; }
    void select() {
        shape = SELECTED;
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

void boardUpdate(vector<vector<Cell>>& board, Cursor& cursor, bool& gameRunning, string& legality) {
    while (gameRunning) {
        sleep_for(milliseconds(100));
        print(board, cursor);
        cout << "cursor: " << cursor.getX() << ", " << cursor.getY() << endl;
        cout << "selection: " << cursor.getxSelect() << ", " << cursor.getySelect() << ", " << board.at(cursor.getySelect()).at(cursor.getxSelect()).getPiece() << endl;
        cout << "gamerunning: " << gameRunning << endl;
        cout << "move legal?: " << legality << endl;
    }
}

void move(vector<vector<Cell>>& board, int x1, int y1, int x2, int y2) {

    char piece = board.at(y1).at(x1).getPiece();

    board.at(y1).at(x1).setPiece(EMPTY);
    board.at(y2).at(x2).setPiece(piece);
}

bool isLegal(char piece, int x1, int y1, int x2, int y2) {
    return 1;
}

bool whitePawn(int x1, int y1, int x2, int y2) {
    return (y1 + 1 == y2);
}

bool blackPawn(int x1, int y1, int x2, int y2) {
    return (y1 - 1 == y2);
}

bool rook(vector<vector<Cell>> board, int x1, int y1, int x2, int y2) {
    int block = 0;
    int n1, n2;

    if (x1 == x2) {
        n2 = ((y2 - y1) == abs(y2 - y1)) ? 1 : -1;
        for (int i = y1; i != y2; i += n2) {
            block += (board.at(i).at(x1).getPiece() != EMPTY) ? 1 : 0;
        }
    }
    else if (y1 == y2) {
        n1 = ((x2 - x1) == abs(x2 - x1)) ? 1 : -1;
        for (int i = x1; i != x2; i += n1) {
            block += (board.at(y1).at(i).getPiece() != EMPTY) ? 1 : 0;
        }
    }
    return block;
}

bool bishop(vector<vector<Cell>> board, int x1, int y1, int x2, int y2) {
    return (abs(x2 - x1) == abs(y2 - y1));
}

bool queen(vector<vector<Cell>> board, int x1, int y1, int x2, int y2) {
    return ((x1 == x2 || y1 == y2)
        || (x2 - x1 == y2 - y1));
}

bool king(vector<vector<Cell>> board, int x1, int y1, int x2, int y2) {
    return (x2 >= x1 - 1
        && x2 <= x1 + 1
        && y2 >= y1 - 1
        && y2 <= y1 + 1);
}

bool knight(vector<vector<Cell>> board, int x1, int y1, int x2, int y2) {
    return ((abs(x1 - x2) == 1) && (abs(y1 - y2) == 2)
        || (abs(x1 - x2) == 2) && (abs(y1 - y2) == 1));
}

void check(string& legality) {
    legality = (legality == "legal") ? "not legal" : "legal";
}
int main() {

    ShowConsoleCursor(false);
    bool gameRunning = 1;
    Cursor cursor;
    int turn_counter = 1;
    string legality = "not checked";
    char origin, destination;


    vector<vector<Cell>> board(8, vector<Cell>(8, Cell()));

    board.at(0).at(0).setPiece(W_ROOK);
    board.at(0).at(1).setPiece(W_KNIGHT);
    board.at(0).at(2).setPiece(W_BISHOP);
    board.at(0).at(3).setPiece(W_QUEEN);
    board.at(0).at(4).setPiece(W_KING);
    board.at(0).at(5).setPiece(W_BISHOP);
    board.at(0).at(6).setPiece(W_KNIGHT);
    board.at(0).at(7).setPiece(W_ROOK);

    board.at(7).at(0).setPiece(W_ROOK);
    board.at(7).at(1).setPiece(W_KNIGHT);
    board.at(7).at(2).setPiece(W_BISHOP);
    board.at(7).at(3).setPiece(W_QUEEN);
    board.at(7).at(4).setPiece(W_KING);
    board.at(7).at(5).setPiece(W_BISHOP);
    board.at(7).at(6).setPiece(W_KNIGHT);
    board.at(7).at(7).setPiece(W_ROOK);

    for (int j = 0; j < 8; j++)
    {
        board.at(1).at(j).setPiece(W_PAWN);
        board.at(6).at(j).setPiece(W_PAWN);
    }

    
    thread thread1(boardUpdate, ref(board), ref(cursor), ref(gameRunning), ref(legality));
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
            board.at(cursor.getY()).at(cursor.getX()).getPiece() != EMPTY ? cursor.select() : check(legality);
        }
        else if (GetAsyncKeyState(0x58)) { // X
            //knight(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY());
            origin = board.at(cursor.getySelect()).at(cursor.getxSelect()).getPiece();
            destination = board.at(cursor.getY()).at(cursor.getX()).getPiece();
            switch (origin) {
                case W_ROOK:
                    rook(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY()) ? move(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY()) : check(legality);
                    break;
                case W_KNIGHT:
                    knight(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY()) ? move(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY()) : check(legality);
                    break;
                case W_BISHOP:
                    bishop(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY()) ? move(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY()) : check(legality);
                    break;
                case W_QUEEN:
                    queen(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY()) ? move(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY()) : check(legality);
                    break;
                case W_KING:
                    king(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY()) ? move(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY()) : check(legality);
                    break;
                case W_PAWN:
                    rook(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY()) ? move(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY()) : check(legality);
                    break;
            }
            cursor.setShape(CURSOR);
        }
    } while (gameRunning);
    thread1.join();
    system("cls");
    gotoxy(0, 0);
}

    /*  switch (board.at(cursor.getySelect()).at(cursor.getxSelect()).getPiece()) {
        case W_ROOK:
            if (rook(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY())) {
                check = "legal";
                move(board, cursor.getxSelect(), cursor.getySelect(), cursor.getX(), cursor.getY());
            }
            break;
        cursor.setShape(CURSOR);
    }*/

/*

        x1 = (x1 < x2) ? x1 : x2;
        x2 = (x2 > x1) ? x2 : d1;
        y1 = (y1 < y2) ? y1 : y2;
        y2 = (y2 > y1) ? y2 : d1;*/