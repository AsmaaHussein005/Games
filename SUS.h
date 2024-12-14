#ifndef SUS_H
#define SUS_H

#include "Board_Game_Classes.h"

template <typename T>
class SUS_Board : public Board<T> {
    static int scorep1;
    static int scorep2;
    T currentPlayer;  // Add currentPlayer to keep track of the player
public:
    multiset<int> NSEQSUS;

    SUS_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    T getCurrentPlayer() { return currentPlayer; } // Function to return the current player
    void switchPlayer() { currentPlayer = (currentPlayer == 'S') ? 'U' : 'S'; } // Switch between players
};
template <typename T>
int SUS_Board<T>::scorep1 = 0;  // Initialize static scorep1

template <typename T>
int SUS_Board<T>::scorep2 = 0;

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T>{
public:
    SUS_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
SUS_Board<T>::SUS_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    this->scorep1 = 0;
    this->scorep2 = 0;
    this->currentPlayer = 'S'; // Set 'S' as the first player
}

template <typename T>
bool SUS_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        // After every valid move, switch players
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void SUS_Board<T>::display_board() {
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
bool SUS_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] == 'S' && this->board[i][1] == 'U' && this->board[i][2] == 'S') {
            auto it1 = NSEQSUS.find(3 * i + 1); auto it2 = NSEQSUS.find(3 * i + 2); auto it3 = NSEQSUS.find( 3 * i + 3);
            if(it1 == NSEQSUS.end() || it2 == NSEQSUS.end() || it3 == NSEQSUS.end() ) {
                if(it1 == NSEQSUS.end())NSEQSUS.insert(3 * i + 1);
                if(it2 == NSEQSUS.end())NSEQSUS.insert(3 * i + 2);
                if(it3 == NSEQSUS.end())NSEQSUS.insert(3 * i + 3);
                if(currentPlayer == 'S') ++scorep1;
                else ++scorep2;
            }
        }
        if(this->board[0][i] == 'S' && this->board[1][i] == 'U' && this->board[2][i] == 'S') {
            auto it1 = NSEQSUS.find(i + 1); auto it2 = NSEQSUS.find(i + 4); auto it3 = NSEQSUS.find( i + 7);
            if(it1 == NSEQSUS.end() || it2 == NSEQSUS.end() || it3 == NSEQSUS.end() ) {
                if(it1 == NSEQSUS.end())NSEQSUS.insert(i + 1);
                if(it2 == NSEQSUS.end())NSEQSUS.insert(i + 4);
                if(it3 == NSEQSUS.end())NSEQSUS.insert(i + 7);
                if(currentPlayer == 'S') ++scorep1;
                else ++scorep2;

            }
        }
    }// Check diagonals
    if (this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S') {
            auto it1 = NSEQSUS.find( 1); auto it2 = NSEQSUS.find(5); auto it3 = NSEQSUS.find( 9);
            if(it1 == NSEQSUS.end() || it2 == NSEQSUS.end() || it3 == NSEQSUS.end() ) {
                if(it1 == NSEQSUS.end())NSEQSUS.insert(1);
                if(it2 == NSEQSUS.end())NSEQSUS.insert(5);
                if(it3 == NSEQSUS.end())NSEQSUS.insert(9);
                if(currentPlayer == 'S') ++scorep1;
                else ++scorep2;
            }
        }
    if (this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S') {
        auto it1 = NSEQSUS.find( 4); auto it2 = NSEQSUS.find(5); auto it3 = NSEQSUS.find( 7);
        if(it1 == NSEQSUS.end() || it2 == NSEQSUS.end() || it3 == NSEQSUS.end() ) {
            if(it1 == NSEQSUS.end())NSEQSUS.insert(3);
            if(it2 == NSEQSUS.end())NSEQSUS.insert(5);
            if(it3 == NSEQSUS.end())NSEQSUS.insert(7);
            if(currentPlayer == 'S') ++scorep1;
            else ++scorep2;
        }
    }
    if (scorep1 > scorep2 && this->n_moves == 9) {
        cout << "Player 1 score is  : " << scorep1 << endl;
        cout << "Player 2 score is  : " << scorep2 << endl;
        return true;
    }
    if (scorep2 > scorep1 && this->n_moves == 9) {
        cout << "Player 1 score is  : " << scorep1 << endl;
        cout << "Player 2 score is  : " << scorep2 << endl;
        return true;
    }if(scorep1 == scorep2 && this->n_moves == 9) {
        cout << "Player 1 score is  : " << scorep1 << endl;
        cout << "Player 2 score is  : " << scorep2 << endl;
        cout <<"No winner \n";
    }switchPlayer();
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool SUS_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool SUS_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}





#endif //SUS_H
