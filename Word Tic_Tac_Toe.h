
#ifndef WORD_TIC_TAC_TOE
#define WORD_TIC_TAC_TOE

#include "Board_Game_Classes.h"

template <typename T>
class W_Tic_Tac_Toe_Board:public Board<T> {
public:
    W_Tic_Tac_Toe_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class W_Tic_Tac_Toe_Player : public Player<T> {
public:
    W_Tic_Tac_Toe_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class W_Tic_Tac_Toe_Random_Player : public RandomPlayer<T>{
public:
    W_Tic_Tac_Toe_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
W_Tic_Tac_Toe_Board<T>::W_Tic_Tac_Toe_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool W_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void W_Tic_Tac_Toe_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool W_Tic_Tac_Toe_Board<T>::is_win() {
    ifstream file("dic.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return false;
    }

    string instruction;
    while (getline(file, instruction)) {
        // Check rows and columns
        for (int i = 0; i < this->rows; i++) {
            if ((this->board[i][0] == instruction[0] && this->board[i][1] == instruction[1] && this->board[i][2] == instruction[2]) ||
                (this->board[0][i] == instruction[0] && this->board[1][i] == instruction[1] && this->board[2][i] == instruction[2])) {
                return true;
                }
        }

        // Check diagonals
        if ((this->board[0][0] == instruction[0] && this->board[1][1] == instruction[1] && this->board[2][2] == instruction[2]) ||
            (this->board[0][2] == instruction[0] && this->board[1][1] == instruction[1] && this->board[2][0] == instruction[2])) {
            return true;
            }
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool W_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool W_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
W_Tic_Tac_Toe_Player<T>::W_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void W_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) and your character separated by spaces: ";
    cin >> x >> y >> this->symbol;
}

// Constructor for X_O_Random_Player
template <typename T>
W_Tic_Tac_Toe_Random_Player<T>::W_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void W_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    this->symbol = char(rand() % (90 - 65 + 1) + 65);
}







#endif //WORD_TIC_TAC_TOE

