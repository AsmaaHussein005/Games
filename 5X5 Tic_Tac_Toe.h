#ifndef INC_5X5_TIC_TAC_TOE_H
#define INC_5X5_TIC_TAC_TOE_H

#include "Board_Game_Classes.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <cctype>

using namespace std;

template <typename T>
class I_5X5_Tic_Tac_Toe_Board : public Board<T> {
public:
    map<char, int> playSco_;

    I_5X5_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class I_5X5_Tic_Tac_Toe_Player : public Player<T> {
public:
    I_5X5_Tic_Tac_Toe_Player(string NAMEE_, T XorO_);
    void getmove(int& Z_, int& F_);
};

template <typename T>
class I_5X5_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
public:
    I_5X5_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

// Constructor for X_O_Board
template <typename T>
I_5X5_Tic_Tac_Toe_Board<T>::I_5X5_Tic_Tac_Toe_Board() {
    this->rows = this->columns = 5;
    this->board = new char* [this->rows];
    for (int H = 0; H < this->rows; H++) {
        this->board[H] = new char[this->columns];
        for (int J = 0; J < this->columns; J++) {
            this->board[H][J] = 0;
        }
    }
    this->n_moves = 0;
    playSco_['X'] = 0;
    playSco_['O'] = 0;
}

// Updates the board
template <typename T>
bool I_5X5_Tic_Tac_Toe_Board<T>::update_board(int L, int J, T MARK__) {
    if (L >= 0 && L < this->rows && J >= 0 && J < this->columns && this->board[L][J] == 0) {
        this->board[L][J] = toupper(MARK__);
        this->n_moves++;
        return true;
    }
    return false;
}

// Displays the board
template <typename T>
void I_5X5_Tic_Tac_Toe_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n----------------------------------------------";
    }
    cout << endl;
}

// Check for 3-in-a-row sequences and update scores
template <typename T>
bool I_5X5_Tic_Tac_Toe_Board<T>::is_win() {
    int scoreX__ = 0, scoreO__ = 0;

    // Check rows
    for (int K_ = 0; K_ < this->rows; ++K_) {
        for (int j = 0; j <= this->columns - 3; ++j) {
            if (this->board[K_][j] != 0 && this->board[K_][j] == this->board[K_][j + 1] && this->board[K_][j] == this->board[K_][j + 2]) {
                if (this->board[K_][j] == 'X') scoreX__++;
                else if (this->board[K_][j] == 'O') scoreO__++;
            }
        }
    }

    // Check columns
    for (int F_ = 0; F_ < this->columns; ++F_) {
        for (int i = 0; i <= this->rows - 3; ++i) {
            if (this->board[i][F_] != 0 && this->board[i][F_] == this->board[i + 1][F_] && this->board[i][F_] == this->board[i + 2][F_]) {
                if (this->board[i][F_] == 'X') scoreX__++;
                else if (this->board[i][F_] == 'O') scoreO__++;
            }
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int B_ = 0; B_ <= this->rows - 3; ++B_) {
        for (int j = 0; j <= this->columns - 3; ++j) {
            if (this->board[B_][j] != 0 && this->board[B_][j] == this->board[B_ + 1][j + 1] && this->board[B_][j] == this->board[B_ + 2][j + 2]) {
                if (this->board[B_][j] == 'X') scoreX__++;
                else if (this->board[B_][j] == 'O') scoreO__++;
            }
        }
    }

    // Check diagonals (top-right to bottom-left)
    for (int L_ = 0; L_ <= this->rows - 3; ++L_) {
        for (int j = 2; j < this->columns; ++j) {
            if (this->board[L_][j] != 0 && this->board[L_][j] == this->board[L_ + 1][j - 1] && this->board[L_][j] == this->board[L_ + 2][j - 2]) {
                if (this->board[L_][j] == 'X') scoreX__++;
                else if (this->board[L_][j] == 'O') scoreO__++;
            }
        }
    }

    playSco_['X'] = scoreX__;
    playSco_['O'] = scoreO__;

    return false;
}

// Check if the game is a draw
template <typename T>
bool I_5X5_Tic_Tac_Toe_Board<T>::is_draw() {
    return this->n_moves == 25;
}

// Game over condition
template <typename T>
bool I_5X5_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
I_5X5_Tic_Tac_Toe_Player<T>::I_5X5_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void I_5X5_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
I_5X5_Tic_Tac_Toe_Random_Player<T>::I_5X5_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void I_5X5_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}


#endif //INC_5X5_TIC_TAC_TOE_H
