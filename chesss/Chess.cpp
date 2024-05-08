// Chess.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

/*
#include "Board.h"
#include "Cell.h"
#include "Cursor.h"
#include "Constants.h"*/
using namespace std;
//using namespace chrono;
//using namespace this_thread;


class Tile {
private:
    //vector<string> tile = {};
    //char piece;

public:


};

class Pawn {
private:
    bool color;

};

class Rook {
    bool color;
};

class Knight {
    bool color;
};

class Bishop {
    bool color;
};

class King {
    bool color;
};

class Queen {
    bool color;
};

// white pieces
const wchar_t w_king = L'\u2654';
const wchar_t w_queen = L'\u2655';
const wchar_t w_rook = L'\u2656';
const wchar_t w_bishop = L'\u2657';
const wchar_t w_knight = L'\u2658';
const wchar_t w_pawn = L'\u2659';

// black pieces
const wchar_t b_king = L'\u265A';
const wchar_t b_queen = L'\u265B';
const wchar_t b_rook = L'\u265C';
const wchar_t b_bishop = L'\u265D';
const wchar_t b_knight = L'\u265E';
const wchar_t b_pawn = L'\u265F';


int main()

    
{
    //TO DO MANUALLY :  set your console output to "MS GOTHIC"
    // you can run program  charmap.exe  on windows to see the characters in a font set.

    _setmode(_fileno(stdout), _O_U16TEXT);

    vector<wchar_t> board{ w_rook, w_knight, w_bishop, w_queen, w_king, w_bishop, w_knight, w_rook};
    vector<wchar_t> pawns(8, w_pawn);
    //vector<wchar_t> bboard{ w_rook, w_knight, w_bishop, w_queen, w_king, w_bishop, w_knight, w_rook };
    //wcout <<  w_king << endl << b_king <<endl;

    for (int i = 0; i < board.size(); i++) {
        wcout << board.at(i) << " ";
    }
    wcout << endl << endl << "h" << endl;
    
    for (int i = 0; i < 8; i++){
        wcout << w_pawn;
    }
    wcout << endl;
    for (int i = 0; i < 8; i++) {
        wcout << endl;
    }/*
    for (int i = 0; i < board.size(); i++) {
        wcout << board.at(i) << " ";
    }*/
    //L"♕" << endl << s << endl << t1 << endl << t2 << endl << t3 << endl <<
}

