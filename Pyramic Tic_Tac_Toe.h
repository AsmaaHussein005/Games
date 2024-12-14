
#ifndef PYRAMIC_TIC_TAC_TOE_H
#define PYRAMIC_TIC_TAC_TOE_H

#include "Board_Game_Classes.h"

template <typename T>
class P_Tic_Tac_Toe_Board:public Board<T> {
public:
    P_Tic_Tac_Toe_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class P_Tic_Tac_Toe_Player : public Player<T> {
public:
    P_Tic_Tac_Toe_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class P_Tic_Tac_Toe_Random_Player : public RandomPlayer<T>{
public:
    P_Tic_Tac_Toe_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
P_Tic_Tac_Toe_Board<T>::P_Tic_Tac_Toe_Board() {
    this->rows = 3;
    this->columns = 5;
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
bool P_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns ||
        (y <= 1 && x <= 1 && x+y < 2) || (x <= 1 && (x + y != 4) && (y == 3 || y == 4) )
        || (x == 0 && y == 4))
        && (this->board[x][y] == 0|| mark == 0)) {
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
void P_Tic_Tac_Toe_Board<T>::display_board() {
    int MIN = this->rows - 1;
    int MAX = this->columns - 2;
    for (int i = 0; i < this->rows; i++) {
        cout << "\n ";
        for (int j = 0; j < MIN; j++) {
            cout << "        ";
        }

        for (int j = MIN; j < MAX; j++) {
            cout << "(" << i << "," << j << ")" ;
            cout << setw(2) << this->board[i][j] ;
            if(j < MAX - 1)
            cout  << " | ";
        }
        --MIN;
        ++MAX;
        cout << "\n-------------------------------------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool P_Tic_Tac_Toe_Board<T>::is_win() {
    // Check rows and columns
    if((this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] && this->board[1][1] != 0) ||
       (this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][0] != 0) ||
       (this->board[2][1] == this->board[2][2] && this->board[2][2] == this->board[2][3] && this->board[2][1] != 0) ||
       (this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4] && this->board[2][2] != 0) ||
       (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != 0)) {
            return true;
        }

    // Check diagonals
    if ((this->board[0][2] == this->board[1][0] && this->board[1][0] == this->board[2][0] && this->board[0][2] != 0) ||
        (this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool P_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool P_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
P_Tic_Tac_Toe_Player<T>::P_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void P_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
    cin.ignore();
}

// Constructor for X_O_Random_Player
template <typename T>
P_Tic_Tac_Toe_Random_Player<T>::P_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void P_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {

    x = rand() % 3;  // Random number between 0 and 2
    y = rand() % 5;  // Random number between 0 and 4
}







#endif //PYRAMIC_TIC_TAC_TOE_H
