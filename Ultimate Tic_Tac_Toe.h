
#ifndef ULTIMATE_TIC_TAC_TOE_H
#define ULTIMATE_TIC_TAC_TOE_H


#include "Board_Game_Classes.h"

template <typename T>
class U_Tic_Tac_Toe_Board:public Board<T> {
public:
    U_Tic_Tac_Toe_Board ();
    T** w_board;
    bool update_board (int x , int y , T c);
    void display_board () ;
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void chck_Smlbrd_win();      // Function to check win conditions in smaller boards
    void display_win_board();
};




template <typename T>
class U_Tic_Tac_Toe_Player : public Player<T> {
public:
    U_Tic_Tac_Toe_Player (string nae, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class U_Tic_Tac_Toe_Random_Player : public RandomPlayer<T>{
public:
    U_Tic_Tac_Toe_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <bits/stdc++.h>
using namespace std;

// Constructor for X_O_Board
template <typename T>
U_Tic_Tac_Toe_Board<T>::U_Tic_Tac_Toe_Board() {
    // for the 9*9 board
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int O_ = 0; O_ < this->rows; O_++) {
        this->board[O_] = new char[this->columns];
        for (int Y__ = 0; Y__ < this->columns; Y__++) {
            this->board[O_][Y__] = 0;
        }
    }

    //for the 3*3 win_board
    this->w_board = new char*[3];
    for (int T_ = 0; T_ < 3; T_++) {
        this->w_board[T_] = new char[3];
        for (int R_ = 0; R_ < 3; R_++) {
            this->w_board[T_][R_] = 0;
        }
    }

    this->n_moves = 0;
}


template <typename T>
void U_Tic_Tac_Toe_Board<T>::display_win_board() {
    cout << "\nUpdated w_board:\n\n";

    // Top row with column numbers
    cout << "    ";
    for (int R_ = 0; R_ < 3; R_++) {
        cout << "  " << R_ << "   ";
    }
    cout << "\n";

    // Top border
    cout << "   +";
    for (int E_ = 0; E_ < 3; E_++) {
        cout << "-----+";
    }
    cout << "\n";

    // Rows
    for (int G_ = 0; G_ < 3; G_++) {
        // Row content
        cout << " " << G_ << " |";
        for (int W_ = 0; W_ < 3; W_++) {
            if (this->w_board[G_][W_] == 0) {
                cout << "     |";
            } else {
                cout << "  " << this->w_board[G_][W_] << "  |";
            }
        }
        cout << "\n";

        // Row border
        cout << "   +";
        for (int D_ = 0; D_ < 3; D_++) {
            cout << "-----+";
        }
        cout << "\n";
    }
}



// Display the board and the pieces on it
template <typename T>
void U_Tic_Tac_Toe_Board<T>::display_board() {
    cout<<"\n";
    // Top row with column numbers
    cout << "    ";
    for (int G_ = 0; G_ < this->columns; G_++) {
        cout << "  " << G_ << "   ";
    }
    cout << endl;

    // Top border
    cout << "   +";
    for (int G_ = 0; G_ < this->columns; G_++) {
        cout << "-----+";
    }
    cout << endl;

    // Rows
    for (int G_ = 0; G_ < this->rows; G_++) {
        // Row content
        cout << setw(2) << G_ << " |";
        for (int r_ = 0; r_ < this->columns; r_++) {
            cout << "  " << setw(2) << this->board[G_][r_] << " |";
        }
        cout << endl;

        // Row border
        cout << "   +";
        for (int E_ = 0; E_ < this->columns; E_++) {
            cout << "-----+";
        }
        cout << endl;
    }
}



template <typename T>
void U_Tic_Tac_Toe_Board<T>::chck_Smlbrd_win() {
    for (int Block_Row = 0; Block_Row < 3; ++Block_Row) {
        for (int BBlock_Col = 0; BBlock_Col < 3; ++BBlock_Col) {
            int startRow = Block_Row * 3;
            int startCol = BBlock_Col * 3;
            T Win_ = 0;

            // Check rows in the block
            for (int G = 0; G < 3; ++G) {
                if (this->board[startRow + G][startCol] == this->board[startRow + G][startCol + 1] &&
                    this->board[startRow + G][startCol + 1] == this->board[startRow + G][startCol + 2] &&
                    this->board[startRow + G][startCol] != 0) {
                    Win_ = this->board[startRow + G][startCol];
                    break;
                }
            }

            // Check columns in the block
            if (Win_ == 0) {
                for (int F = 0; F < 3; ++F) {
                    if (this->board[startRow][startCol + F] == this->board[startRow + 1][startCol + F] &&
                        this->board[startRow + 1][startCol + F] == this->board[startRow + 2][startCol + F] &&
                        this->board[startRow][startCol + F] != 0) {
                        Win_ = this->board[startRow][startCol + F];
                        break;
                    }
                }
            }

            // Check main diagonal in the block
            if (Win_ == 0 &&
                this->board[startRow][startCol] == this->board[startRow + 1][startCol + 1] &&
                this->board[startRow + 1][startCol + 1] == this->board[startRow + 2][startCol + 2] &&
                this->board[startRow][startCol] != 0) {
                Win_ = this->board[startRow][startCol];
            }

            // Check secondary diagonal in the block
            if (Win_ == 0 &&
                this->board[startRow][startCol + 2] == this->board[startRow + 1][startCol + 1] &&
                this->board[startRow + 1][startCol + 1] == this->board[startRow + 2][startCol] &&
                this->board[startRow][startCol + 2] != 0) {
                Win_ = this->board[startRow][startCol + 2];

            }

            if (Win_ != 0 && this->w_board[Block_Row][BBlock_Col] == 0) {
                this->w_board[Block_Row][BBlock_Col] = Win_;
                // Display the Win_ of the small board and the updated w_board
                cout << "\nSmall board won by: " << Win_ << "\n";
                this->display_win_board(); // Call display function here
            }
        }
    }
}


template <typename T>
bool U_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T c) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) &&
        (this->board[x][y] == 0 || c == 0)) {
        if (c == 0) {  // Undo move
            this->n_moves--;
            this->board[x][y] = 0;
        } else {  // Make a move
            this->n_moves++;
            this->board[x][y] = toupper(c);
        }

        // Call chck_Smlbrd_win() to update the w_board
        this->chck_Smlbrd_win();
        return true;
    }
    return false;
}



template <typename T>
bool U_Tic_Tac_Toe_Board<T>::is_win() {
    for (int D_ = 0; D_ < 3; ++D_) {
        // Check rows and columns in w_board
        if ((this->w_board[D_][0] == this->w_board[D_][1] &&
             this->w_board[D_][1] == this->w_board[D_][2] &&
             this->w_board[D_][0] != 0) ||
            (this->w_board[0][D_] == this->w_board[1][D_] &&
             this->w_board[1][D_] == this->w_board[2][D_] &&
             this->w_board[0][D_] != 0)) {
            return true;
        }
    }

    // Check diagonals in w_board
    if ((this->w_board[0][0] == this->w_board[1][1] &&
         this->w_board[1][1] == this->w_board[2][2] &&
         this->w_board[0][0] != 0) ||
        (this->w_board[0][2] == this->w_board[1][1] &&
         this->w_board[1][1] == this->w_board[2][0] &&
         this->w_board[0][2] != 0)) {
        return true;
    }

    return false;
}


// Return true if 9 moves are done and no winner
template <typename T>
bool U_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 80 && !is_win());
}

template <typename T>
bool U_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
U_Tic_Tac_Toe_Player<T>::U_Tic_Tac_Toe_Player(string nae, T symbol) : Player<T>(nae, symbol) {}

template <typename T>
void U_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
    while (cin.fail() || x < 0 || x >= 9 || y < 0 || y >= 9) {
        cout << "Invalid move! Please enter values between 0 and 8: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> x >> y;
    }
}

// Constructor for X_O_Random_Player
template <typename T>
U_Tic_Tac_Toe_Random_Player<T>::U_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void U_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}




#endif //ULTIMATE_TIC_TAC_TOE_H
