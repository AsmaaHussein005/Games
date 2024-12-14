#ifndef MISERE_TIC_TAC_TOE_H
#define MISERE_TIC_TAC_TOE_H

#include "Board_Game_Classes.h"
#include <cstdlib> // For rand()
#include <ctime>   // For srand()
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

// Misere Tic Tac Toe Board
template <typename T>
class MISERE_TIC_TAC_TOE_Board : public Board<T> {
public:
    MISERE_TIC_TAC_TOE_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;  // Check if the current player loses
    bool is_draw() override; // Check if it's a draw
    bool game_is_over() override;
    string detect_winner(const string& player1_n_, T player1_symbol, const string& player2_n_, T player2_symbol);
};

template <typename T>
class MISERE_TIC_TAC_TOE_Player : public Player<T> {
public:
    MISERE_TIC_TAC_TOE_Player(string name, T symbol) : Player<T>(name, symbol) {}
    void getmove(int& x, int& y) override; // Human move input
};

template <typename T>
class MISERE_TIC_TAC_TOE_Random_Player : public RandomPlayer<T> {
public:
    MISERE_TIC_TAC_TOE_Random_Player(T symbol) : RandomPlayer<T>(symbol) { srand(static_cast<unsigned int>(time(0))); }
    void getmove(int& x, int& y) override; // Generate random move
};

// Misere_Board Implementation
template <typename T>
MISERE_TIC_TAC_TOE_Board<T>::MISERE_TIC_TAC_TOE_Board() {
    this->rows = this->columns = 3;
    this->board = new T * [this->rows];
    for (int L__ = 0; L__ < this->rows; L__++) {
        this->board[L__] = new T[this->columns]();
    }
    this->n_moves = 0;
}

template <typename T>
bool MISERE_TIC_TAC_TOE_Board<T>::update_board(int x, int P__, T symbol) {
    if (x >= 0 && x < this->rows && P__ >= 0 && P__ < this->columns && this->board[x][P__] == 0) {
        this->board[x][P__] = symbol;
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void MISERE_TIC_TAC_TOE_Board<T>::display_board() {
    for (int U_ = 0; U_ < this->rows; U_++) {
        cout << "\n| ";
        for (int j_ = 0; j_ < this->columns; j_++) {
            cout << setw(2) << (this->board[U_][j_] == 0 ? '.' : this->board[U_][j_]) << " |";
        }
        cout << "\n--------------";
    }
    cout << endl;
}

template <typename T>
bool MISERE_TIC_TAC_TOE_Board<T>::is_win() {
    // Check rows and columns
    for (int K_ = 0; K_ < this->rows; K_++) {
        if ((this->board[K_][0] == this->board[K_][1] && this->board[K_][1] == this->board[K_][2] && this->board[K_][0] != 0) ||
            (this->board[0][K_] == this->board[1][K_] && this->board[1][K_] == this->board[2][K_] && this->board[0][K_] != 0)) {
            return true;
        }
    }
    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }
    return false;
}

template <typename T>
bool MISERE_TIC_TAC_TOE_Board<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

template <typename T>
bool MISERE_TIC_TAC_TOE_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Misere_Player Implementation
template <typename T>
void MISERE_TIC_TAC_TOE_Player<T>::getmove(int& x, int& y__) {
    cout << "Enter your move (row and column, 0-2): ";
    cin >> x >> y__;
}

// Misere_Random_Player Implementation
template <typename T>
void MISERE_TIC_TAC_TOE_Random_Player<T>::getmove(int& x__, int& y) {
    x__ = rand() % 3;
    y = rand() % 3;
}

template <typename T>
string MISERE_TIC_TAC_TOE_Board<T>::detect_winner(const string& player1_name, T player1_symbol, const string& player2_name, T player2_symbol) {
    if (is_win()) {
        // Check for rows, columns, and diagonals for player1 or player2
        for (int O_ = 0; O_ < this->rows; O_++) {
            // Check rows and columns for player1 or player2
            if ((this->board[O_][0] == player1_symbol && this->board[O_][1] == player1_symbol && this->board[O_][2] == player1_symbol) ||
                (this->board[0][O_] == player1_symbol && this->board[1][O_] == player1_symbol && this->board[2][O_] == player1_symbol)) {
                return player2_name + " is the winner!";
            }
            if ((this->board[O_][0] == player2_symbol && this->board[O_][1] == player2_symbol && this->board[O_][2] == player2_symbol) ||
                (this->board[0][O_] == player2_symbol && this->board[1][O_] == player2_symbol && this->board[2][O_] == player2_symbol)) {
                return player1_name + " is the winner!";
            }
        }

        // Check diagonals for player1 or player2
        if ((this->board[0][0] == player1_symbol && this->board[1][1] == player1_symbol && this->board[2][2] == player1_symbol) ||
            (this->board[0][2] == player1_symbol && this->board[1][1] == player1_symbol && this->board[2][0] == player1_symbol)) {
            return player2_name + " is the winner!";
        }
        if ((this->board[0][0] == player2_symbol && this->board[1][1] == player2_symbol && this->board[2][2] == player2_symbol) ||
            (this->board[0][2] == player2_symbol && this->board[1][1] == player2_symbol && this->board[2][0] == player2_symbol)) {
            return player1_name + " is the winner!";
        }
    }
    return "No winner yet!";
}

#endif //MISERE_TIC_TAC_TOE_H
