/**
 * @file main.cpp
 * @brief Main menu for GRID WARS, a collection of Tic-Tac-Toe variants.
 *
 * This program allows the user to select from multiple Tic-Tac-Toe games,
 * set up players, run the selected game, and clean up resources afterward.
 */

#include <iostream>
#include "games/numerical_tic.h"
#include "games/BoardGame_Classes.h"
#include "games/xo_5.h"
#include "games/sus.h"
#include "games/obstacles_xo.h"
#include "games/Misere.h"
#include "games/tic_4x4.h"
#include "games/word_tic.h"
#include "games/connect_four.h"
#include "games/memory_xo.h"
#include "GAMES/Diamond.h"
#include "GAMES/Infinity.h"
#include "GAMES/pyramid_tictactoe.h"
#include "GAMES/Ultimate.h"

using namespace std;

/**
 * @brief Displays the main menu with all available games.
 *
 * The menu lists all Tic-Tac-Toe variants and allows the user to select one by number.
 */
void show_menu() {
    cout << "=== GRID WARS ===" << endl;
    cout << "1. Numerical (Tic-Tac-Toe)" << endl;
    cout << "2. 5x5 X-O (5x5 Tic-Tac-Toe)" << endl;
    cout << "3. SUS" << endl;
    cout << "4. Obstacles X-O" << endl;
    cout << "5. Misere Tic Tac Toe" << endl;
    cout << "6. 4x4 X-0 (4x4 Tic-Tac-Toe)" << endl;
    cout << "7. Word (Tic-Tac-Toe)" << endl;
    cout << "8. Connect Four (Tic-Tac-Toe)" << endl;
    cout << "9. Memory X-O (Tic-Tac-Toe with Memory)" << endl;
    cout << "10. Diamond Tic-Tac-Toe" << endl;
    cout << "11. Infinity Tic-Tac-Toe" << endl;
    cout << "12. Pyramid Tic-Tac-Toe" << endl;
    cout << "13. Ultimate Tic-Tac-Toe" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose: ";
}

/**
 * @brief Entry point for the GRID WARS program.
 *
 * This function runs the main loop that allows the user to:
 * 1. Choose a game from the menu.
 * 2. Set up the players.
 * 3. Run the selected game using the appropriate GameManager.
 * 4. Clean up all allocated resources.
 *
 * The loop continues until the user chooses to exit (option 0).
 *
 * @return int Returns 0 upon program exit.
 */
int main() {
    int choice;

    do {
        show_menu();
        cin >> choice;

        // --- Numerical Tic-Tac-Toe ---
        if (choice == 1) {
            NumericalTicBoard* board = new NumericalTicBoard();
            NumericalTicUI* ui = new NumericalTicUI("Numerical Tic-Tac-Toe", 3);
            Player<int>** players = ui->setup_players();
            GameManager<int> game(board, players, ui);
            game.run();

            // Cleanup
            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- 5x5 X-O ---
        else if (choice == 2) {
            XO_5_Board* board = new XO_5_Board();
            XO_5_UI* ui = new XO_5_UI();
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- SUS ---
        else if (choice == 3) {
            SUS_Board* board = new SUS_Board();
            SUS_UI* ui = new SUS_UI();
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- Obstacles X-O ---
        else if (choice == 4) {
            Obstacles_XO_Board* board = new Obstacles_XO_Board();
            Obstacles_XO_UI* ui = new Obstacles_XO_UI();
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- Misere Tic Tac Toe ---
        else if (choice == 5) {
            MisereBoard* board = new MisereBoard();
            MisereUI* ui = new MisereUI();
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- 4x4 Tic-Tac-Toe ---
        else if (choice == 6) {
            tic_4x4_Board* board = new tic_4x4_Board();
            tic_4x4_UI* ui = new tic_4x4_UI();
            ui->set_board(board);

            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- Word Tic-Tac-Toe ---
        else if (choice == 7) {
            Word_Board* board = new Word_Board();
            Word_UI* ui = new Word_UI();
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- Connect Four ---
        else if (choice == 8) {
            Four_Board* board = new Four_Board();
            Four_UI* ui = new Four_UI();
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- Memory X-O ---
        else if (choice == 9) {
            Memory_XO_Board* board = new Memory_XO_Board();
            Memory_XO_UI* ui = new Memory_XO_UI();
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- Diamond Tic-Tac-Toe ---
        else if (choice == 10) {
            Diamond_Board* board = new Diamond_Board();
            Diamond_UI* ui = new Diamond_UI();
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- Infinity Tic-Tac-Toe ---
        else if (choice == 11) {
            Infinity_Board* board = new Infinity_Board();
            Infinity_UI* ui = new Infinity_UI();
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- Pyramid Tic-Tac-Toe ---
        else if (choice == 12) {
            PyramidTicTacToeBoard* board = new PyramidTicTacToeBoard();
            PyramidTicTacToeUI* ui = new PyramidTicTacToeUI();
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- Ultimate Tic-Tac-Toe ---
        else if (choice == 13) {
            Ultimate_MainBoard* board = new Ultimate_MainBoard();
            Ultimate_UI* ui = new Ultimate_UI();
            Player<char>** players = ui->setup_players();
            Ultimate_GameManager game(board, players, ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        // --- Invalid choice ---
        else if (choice < 0 || choice > 13) {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    cout << "Goodbye!" << endl;
    return 0;
}
