#include <iostream>
#include "Board_Game_Classes.h"
#include "Pyramic Tic_Tac_Toe.h"
#include "Word Tic_Tac_Toe.h"
#include "5X5 Tic_Tac_Toe.h"
#include "Misere Tic_Tac_Toe.h"
#include "SUS.h"
#include "Ultimate Tic_Tac_Toe.h"
#include "Four-in-a-row.h"
using namespace std;

int main() {
    int gameChoice, choiceP1, choiceP2;
    Player<char>* players[2];
    string playerXName, player2Name;

    while (true) {
        cout << "Welcome to FCAI Tic_Tac_Toe Games. :)\n";
        cout << "Choose a game:\n";
        cout << "1. Pyramide Tic-Tac-Toe\n";
        cout << "2. Four-in-a-row\n";
        cout << "3. 5X5 Tic-Tac-Toe\n";
        cout << "4. Word Tic-Tac-Toe\n";
        cout << "5. Numerical Tic-Tac-Toe\n";
        cout << "6. Misere Tic-Tac-Toe\n";
        cout << "8. Ultimate Tic-Tac-Toe\n";
        cout << "9. SUS\n";
        cout << "0. EXIT\n";
        cout << "Enter your choice: ";
        cin >> gameChoice;

        if (gameChoice == 0) {
            cout << "Exiting the game.\n";
            break;  // Exit the loop and terminate the program
        }

        // Set up player 1
        cout << "Enter Player X name: ";
        cin >> playerXName;
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choiceP1;

        // Set up player 2
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choiceP2;

        if (gameChoice == 1) {
            // Pyramide Tic-Tac-Toe
            P_Tic_Tac_Toe_Board<char>* B = new P_Tic_Tac_Toe_Board<char>();

            switch(choiceP1) {
                case 1:
                    players[0] = new P_Tic_Tac_Toe_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new P_Tic_Tac_Toe_Random_Player<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            switch(choiceP2) {
                case 1:
                    players[1] = new P_Tic_Tac_Toe_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new P_Tic_Tac_Toe_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            // Create the game manager and run the game
            GameManager<char> P_Tic_Tac_Toe_game(B, players);
            P_Tic_Tac_Toe_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
        else if (gameChoice == 2) {

        }
        else if (gameChoice == 3) {
            Player<char>* p_[2];
            I_5X5_Tic_Tac_Toe_Board<char>* board = new I_5X5_Tic_Tac_Toe_Board<char>();

            cout << "Welcome to FCAI 5x5 XO Game. :)\n";

            switch (choiceP1) {
                case 1:
                    p_[0] = new I_5X5_Tic_Tac_Toe_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    p_[0] = new I_5X5_Tic_Tac_Toe_Random_Player<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    delete board;
                    return 1;
            }

            switch (choiceP2) {
                case 1:
                    p_[1] = new I_5X5_Tic_Tac_Toe_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    p_[1] = new I_5X5_Tic_Tac_Toe_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    delete board;
                    delete p_[0];
                    return 1;
            }

            // Start the game
            GameManager<char> game(board, p_);
            game.run();

            // Display final results
            cout << "Final Scores:\n";
            int player1Score = board->playSco_['X'];
            int player2Score = board->playSco_['O'];
            cout << "Player X (" << p_[0]->getname() << "): " << player1Score << "\n";
            cout << "Player O (" << p_[1]->getname() << "): " << player2Score << "\n";

            // Announce the winner
            if (player1Score > player2Score) {
                cout << "Congratulations, " << playerXName << "! You are the winner!\n";
            }
            else if (player1Score < player2Score) {
                cout << "Congratulations, " << player2Name << "! You are the winner!\n";
            }
            else {
                cout << "It's a tie! Well played both of you!\n";
            }

            // Cleanup
            delete board;
            delete p_[0];
            delete p_[1];
        }
        else if (gameChoice == 4) {
            // Word Tic-Tac-Toe
            W_Tic_Tac_Toe_Board<char>* B = new W_Tic_Tac_Toe_Board<char>();

            switch(choiceP1) {
                case 1:
                    players[0] = new W_Tic_Tac_Toe_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new W_Tic_Tac_Toe_Random_Player<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            switch(choiceP2) {
                case 1:
                    players[1] = new W_Tic_Tac_Toe_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new W_Tic_Tac_Toe_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            // Create the game manager and run the game
            GameManager<char> W_Tic_Tac_Toe_game(B, players);
            W_Tic_Tac_Toe_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
        else if (gameChoice == 5) {
            // Numerical Tic-Tac-Toe
            cout << "Numerical Tic-Tac-Toe game selected. Implement this game logic.\n";
        }
        else if (gameChoice == 6) {
            Player<char>* play__[2];
            Board<char>* board = new MISERE_TIC_TAC_TOE_Board<char>();

            cout << "Welcome to Misere Tic-Tac-Toe!\n";

            if (choiceP1 == 1) {
                play__[0] = new MISERE_TIC_TAC_TOE_Player<char>(" ", 'X');
            }
            else {
                play__[0] = new MISERE_TIC_TAC_TOE_Random_Player<char>('X');
            }
            play__[0]->setBoard(board);

            if (choiceP2 == 1) {
                play__[1] = new MISERE_TIC_TAC_TOE_Player<char>(" ", 'O');
            }
            else {
                play__[1] = new MISERE_TIC_TAC_TOE_Random_Player<char>('O');
            }
            play__[1]->setBoard(board);

            GameManager<char> MISERE_TIC_TAC_TOE_game(board, play__);
            MISERE_TIC_TAC_TOE_game.run();

            // Cast the board pointer to Misere_Board<char> to call detect_winner
            MISERE_TIC_TAC_TOE_Board<char>* misereBoard = dynamic_cast<MISERE_TIC_TAC_TOE_Board<char>*>(board);
            if (misereBoard) {
                string winner__ = misereBoard->detect_winner(playerXName, 'X', player2Name, 'O');
                cout << winner__ << endl; // Output the winner
            }
            else {
                cout << "Error: Board is not of type Misere_Board!" << endl;
            }

            delete board;
            delete play__[0];
            delete play__[1];
        }
        else if (gameChoice == 8) {
                Player<char>* players[2];
                U_Tic_Tac_Toe_Board<char>* B = new U_Tic_Tac_Toe_Board<char>();
                string play1Na_, _play2Na_;

                cout << "Welcome to FCAI Ultimate Tic Tac Toe Game. :)\n";

                switch(choiceP1) {
                    case 1:
                        players[0] = new U_Tic_Tac_Toe_Player<char>(play1Na_, 'O');
                    break;
                    case 2:
                        players[0] = new  U_Tic_Tac_Toe_Random_Player<char>('O');
                    break;

                    default:
                        cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
                }


                switch(choiceP2) {
                    case 1:
                        players[1] = new U_Tic_Tac_Toe_Player<char>(_play2Na_, 'X');
                    break;
                    case 2:
                        players[1] = new  U_Tic_Tac_Toe_Random_Player<char>('X');
                    break;

                    default:
                        cout << "Invalid ch__ for Player 2. Exiting the game.\n";
                    return 1;
                }

                // Create the game manager and run the game
                GameManager<char> U_Tic_Tac_Toe(B, players);
                U_Tic_Tac_Toe.run();

                // Clean up
                delete B;
                for (int i = 0; i < 2; ++i) {
                    delete players[i];
                }
        }
        else if (gameChoice == 9) {
            // SUS Tic-Tac-Toe
            SUS_Board<char>* B = new SUS_Board<char>();

            switch(choiceP1) {
                case 1:
                    players[0] = new SUS_Player<char>(playerXName, 'S');
                break;
                case 2:
                    players[0] = new SUS_Random_Player<char>('S');
                break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
            }

            switch(choiceP2) {
                case 1:
                    players[1] = new SUS_Player<char>(player2Name, 'U');
                break;
                case 2:
                    players[1] = new SUS_Random_Player<char>('U');
                break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
            }

            // Create the game manager and run the game
            GameManager<char> SUS_game(B, players);
            SUS_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
    }

    return 0;
}
