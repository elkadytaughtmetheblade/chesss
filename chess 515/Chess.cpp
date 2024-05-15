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
#include "stdio.h"
#include <fcntl.h>
#include <cstdlib>
#include "Cursor.h"
#include "Piece.h"
#include "Board.h"

using namespace std;
//using namespace chrono;
//using namespace this_thread;

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

inline int number() {
    string temp;
    int number;
    getline(cin, temp);
    stringstream(temp) >> number;
    return number;
}

inline string word() {
    string temp;
    getline(cin, temp);
    return temp;
}

inline void endl() {
    cout << endl;
}

BOOL gotoxy(const WORD x, const WORD y) {
    COORD xy;
    xy.X = x;
    xy.Y = y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}


void printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            if (i%2) {
                printf("%c%c", 255, 255);
                printf("%c%c", 219, 219);

            }
            else {
                printf("%c%c", 219, 219);
                printf("%c%c", 255, 255);
            }


        }
        cout << endl;

    }
}



//    thread thread_obj(&Board::c_update, &myBoard, time, score); //thread for cursor update






int main(){
    Board myBoard;
    int game_running = 0;
    thread thread_obj(&Board::c_update, &myBoard); //thread for cursor update

    do {
        //system("pause>nul"); //wait for key
        if (GetAsyncKeyState(VK_DOWN)) {
            myBoard.moveCursor_Down();
        }
        else if (GetAsyncKeyState(VK_UP)) {
            myBoard.moveCursor_Up();
        }
        else if (GetAsyncKeyState(VK_RIGHT)) {
            myBoard.moveCursor_Right();
        }
        else if (GetAsyncKeyState(VK_LEFT)) {
            myBoard.moveCursor_Left();
        }
        else if (GetAsyncKeyState(VK_ESCAPE)) {
            game_running = 2;
        }

    } while (game_running == 0);


    myBoard.setGameRunning(false);
   
    system("cls");



    return 0;
}
    











/*

    bool w_turn, mate = false;
    //TO DO MANUALLY :  set your console output to "MS GOTHIC"
    // you can run program  charmap.exe  on windows to see the characters in a font set.

   // printBoard();

    gotoxy(0, 0);
    _setmode(_fileno(stdout), _O_U16TEXT);



    vector<wchar_t> pawns(8, w_pawn);


    for (vector<wchar_t> i : board) {
        for (wchar_t j : i) {
            wcout << j << " ";
        }
        wcout << endl;
        //wcout << board.at(i) << " ";
    }
    wcout << endl;



*/









    //vector<wchar_t> bboard{ w_rook, w_knight, w_bishop, w_queen, w_king, w_bishop, w_knight, w_rook };
    //wcout <<  w_king << endl << b_king <<endl;
    /*
    for (int i = 0; i < board.size(); i++) {
        wcout << board.at(i) << " ";
    }
    wcout << endl << endl << "h" << endl;

    for (int i = 0; i < 8; i++) {
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

    /*

    //thread thread_obj(&Board::c_update, &myBoard, time, score); //thread for cursor update
    //thread timerObj(&Board::timer, &myBoard);
    system("cls");

    do{
        system("pause>nul");


    }while(!mate)

    //thread_obj.join(); //stops cursor updates
    //timerObj.join();

    system("cls");
    gotoxy(0, 0);
    */



