#include <iostream>
#include "games/numerical_tic.h"
#include "games/BoardGame_Classes.h"
using namespace std;

void show_menu() {
    cout << "=== GRID WARS ===" << endl;
    cout << "1. Numerical Tic-Tac-Toe" << endl;
    cout << "2. Exit" << endl;
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
        else if (choice != 2) {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 2);

    cout << "Goodbye!" << endl;
    return 0;
}