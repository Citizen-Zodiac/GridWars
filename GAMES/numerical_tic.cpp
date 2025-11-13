#include "numerical_tic.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Helper functions for random numbers
int get_random_odd() {
    int odds[] = {1, 3, 5, 7, 9};
    return odds[rand() % 5];
}

int get_random_even() {
    int evens[] = {2, 4, 6, 8};
    return evens[rand() % 4];
}

// Computer Player Class
class NumericalComputerPlayer : public Player<int> {
public:
    NumericalComputerPlayer(string name, int symbol) : Player<int>(name, symbol, PlayerType::COMPUTER) {}
};

// NumericalTicBoard Implementation
NumericalTicBoard::NumericalTicBoard() : Board(3, 3) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = 0;
        }
    }
}

bool NumericalTicBoard::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int number = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;
    if (board[x][y] != 0) return false;

    board[x][y] = number;
    n_moves++;
    return true;
}

bool NumericalTicBoard::is_win(Player<int>* player) {
    int target = 15;

    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] + board[i][1] + board[i][2] == target &&
            board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0)
            return true;
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] + board[1][j] + board[2][j] == target &&
            board[0][j] != 0 && board[1][j] != 0 && board[2][j] != 0)
            return true;
    }

    // Check diagonals
    if (board[0][0] + board[1][1] + board[2][2] == target &&
        board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0)
        return true;

    if (board[0][2] + board[1][1] + board[2][0] == target &&
        board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0)
        return true;

    return false;
}

bool NumericalTicBoard::is_lose(Player<int>* player) {
    return false;
}

bool NumericalTicBoard::is_draw(Player<int>* player) {
    return (n_moves == 9) && !is_win(player);
}

bool NumericalTicBoard::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

// NumericalTic UI Implementation
Move<int>* NumericalTicUI::get_move(Player<int>* player) {
    if (player->get_type() == PlayerType::COMPUTER) {
        // Computer player - make random move
        cout << player->get_name() << " (Computer) is thinking..." << endl;
        // Find empty cell
        int x, y;
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (player->get_board_ptr()->get_board_matrix()[x][y] != 0);

        // Get appropriate number based on player symbol
        int number;
        if (player->get_symbol() == 1) {
            number = get_random_odd();
        } else {
            number = get_random_even();
        }

        cout << "Computer plays at (" << x << ", " << y << ") with number " << number << endl;
        return new Move<int>(x, y, number);
    }
    else {
        // Human player
        int x, y, number;
        cout << player->get_name() << ", Enter your move (row column number): ";
        cin >> x >> y >> number;
        return new Move<int>(x, y, number);
    }
}

Player<int>* NumericalTicUI::create_player(string& name, int symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER) {
        return new NumericalComputerPlayer(name, symbol);
    }
    return new Player<int>(name, symbol, type);
}