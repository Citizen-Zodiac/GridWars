#include <iostream>
#include "games/numerical_tic.h"
#include "games/BoardGame_Classes.h"
#include "games/xo_5.h"
#include "games/sus.h"
#include "games/Misere_UI.h"
using namespace std;

void show_menu() {
    cout << "=== GRID WARS ===" << endl;
    cout << "1. Numerical (Tic-Tac-Toe)" << endl;
    cout << "2. 5x5 X-O (5x5 Tic-Tac-Toe)" << endl;
    cout << "3. SUS" << endl;
    cout << "4. Misère Tic Tac Toe" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose: ";
}

int main() {
    int choice;

    do {
        show_menu();
        cin >> choice;

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

        else if (choice == 2) {
            XO_5_Board* board = new XO_5_Board();
            XO_5_UI* ui = new XO_5_UI();
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            // Cleanup
            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }

        else if (choice == 3)
        {
            SUS_Board* board = new SUS_Board();
            SUS_UI* ui = new SUS_UI();
            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            // Cleanup
            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }
        else if (choice == 4)
        {
            MisereBoard* board = new MisereBoard();
            MisereUI* ui = new MisereUI();

            Player<char>** players = ui->setup_players();

            GameManager<char> game(board, players, ui);
            game.run();

            // Cleanup
            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
            delete ui;
        }
        else if (choice != 1 || choice != 2 || choice != 3 || choice != 4 || choice != 5) {
            cout << "Invalid choice. Please try again." << endl;
        }


    } while (choice != 5);

    cout << "Goodbye!" << endl;
    return 0;
}