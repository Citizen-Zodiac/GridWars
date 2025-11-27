#include "numerical_tic.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include<limits>

using namespace std;

NumericalTicBoard::NumericalTicBoard() : Board(3, 3) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = 0;
        }
    }
    srand(time(0));
}

bool NumericalTicBoard::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int number = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;
    if (board[x][y] != 0) return false;

    if (find(used_numbers.begin(), used_numbers.end(), number) != used_numbers.end()) {
        return false;
    }

    board[x][y] = number;
    n_moves++;
    used_numbers.push_back(number);
    return true;
}

bool NumericalTicBoard::is_win(Player<int>* player) {
    int target = 15;

    // Check rows - three consecutive cells in a row
    for (int i = 0; i < 3; i++) {
        int row_sum = board[i][0] + board[i][1] + board[i][2];
        if (row_sum == target && board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0) {
            return true;
        }
    }

    // Check columns - three consecutive cells in a column
    for (int j = 0; j < 3; j++) {
        int col_sum = board[0][j] + board[1][j] + board[2][j];
        if (col_sum == target && board[0][j] != 0 && board[1][j] != 0 && board[2][j] != 0) {
            return true;
        }
    }

    // Check main diagonal - three consecutive cells
    int diag1_sum = board[0][0] + board[1][1] + board[2][2];
    if (diag1_sum == target && board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0) {
        return true;
    }

    // Check anti-diagonal - three consecutive cells
    int diag2_sum = board[0][2] + board[1][1] + board[2][0];
    if (diag2_sum == target && board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0) {
        return true;
    }

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

Move<int>* NumericalTicUI::get_move(Player<int>* player) {
    if (player->get_type() == PlayerType::COMPUTER) {
        NumericalTicBoard* board = dynamic_cast<NumericalTicBoard*>(player->get_board_ptr());

        // Keep trying random moves until valid
        int attempts = 0;
        while (attempts < 100) {
            int x = rand() % 3;
            int y = rand() % 3;
            int number;

            if (player->get_symbol() == 1) {
                number = (rand() % 5) * 2 + 1; // 1,3,5,7,9
            } else {
                number = (rand() % 4) * 2 + 2; // 2,4,6,8
            }

            // Test if this move would be valid
            if (board->get_board_matrix()[x][y] == 0) {
                bool number_used = false;
                auto board_state = board->get_board_matrix();
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (board_state[i][j] == number) {
                            number_used = true;
                            break;
                        }
                    }
                    if (number_used) break;
                }

                if (!number_used) {
                    cout << player->get_name() << " plays: " << x << " " << y << " " << number << endl;
                    return new Move<int>(x, y, number);
                }
            }
            attempts++;
        }

        return new Move<int>(0, 0, player->get_symbol() == 1 ? 1 : 2);
    }
    else {
        int x, y, number;
        cout << player->get_name() << ", enter your move (row column number): ";
        cin >> x >> y >> number;
        while(cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3 ||
               (player->get_symbol() == 1 && (number < 1 || number > 9 || number % 2 == 0)) ||
               (player->get_symbol() == 2 && (number < 2 || number > 8 || number % 2 != 0))) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter row (0-2), column (0-2), and a valid number: ";
            cin >> x >> y >> number;
		}

        return new Move<int>(x, y, number);

    }
}

Player<int>* NumericalTicUI::create_player(string& name, int symbol, PlayerType type) {
    return new Player<int>(name, symbol, type);
}

Player<int>** NumericalTicUI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    int game_mode;

    cout << "Choose game mode:\n1. Human vs Human\n2. Human vs Computer\nChoose: ";
    cin >> game_mode;

    if (game_mode == 1) {
        // Human vs Human
        string name1, name2;
        cout << "Enter Player 1 name (Odds): ";
        cin >> name1;
        cout << "Enter Player 2 name (Evens): ";
        cin >> name2;

        players[0] = create_player(name1, 1, PlayerType::HUMAN);
        players[1] = create_player(name2, 2, PlayerType::HUMAN);
    }
    else {
        // Human vs Computer - WITH ODD/EVEN CHOICE
        string name;
        int side_choice;

        cout << "Choose your side:\n1. Odds (1,3,5,7,9)\n2. Evens (2,4,6,8)\nChoose: ";
        cin >> side_choice;

        cout << "Enter your name: ";
        cin >> name;

        int human_symbol, computer_symbol;
        string human_role, computer_role;

        if (side_choice == 1) {
            human_symbol = 1;
            computer_symbol = 2;
            human_role = " (Odds)";
            computer_role = " (Evens)";
        }
        else {
            human_symbol = 2;
            computer_symbol = 1;
            human_role = " (Evens)";
            computer_role = " (Odds)";
        }

        string human_name = name + human_role;
        string computer_name = "Computer" + computer_role;

        players[0] = create_player(human_name, human_symbol, PlayerType::HUMAN);
        players[1] = create_player(computer_name, computer_symbol, PlayerType::COMPUTER);
    }

    return players;
}