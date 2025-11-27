#include <iostream>
#include <cctype>
#include "tic_4x4.h"
using namespace std;

static int move_fromX, move_fromY, move_toX, move_toY;


tic_4x4_Board::tic_4x4_Board() : Board(4, 4) {
    board[0][0] = 'O'; board[0][1] = 'X'; board[0][2] = 'O'; board[0][3] = 'X';
    board[1][0] = ' '; board[1][1] = ' '; board[1][2] = ' '; board[1][3] = ' ';
    board[2][0] = ' '; board[2][1] = ' '; board[2][2] = ' '; board[2][3] = ' ';
    board[3][0] = 'X'; board[3][1] = 'O'; board[3][2] = 'X'; board[3][3] = 'O';
    current_player = 'X';
}

bool tic_4x4_Board::update_board(Move<char>* move) {
    return move_token(move_fromX, move_fromY, move_toX, move_toY, move->get_symbol());
}

bool tic_4x4_Board::move_token(int fromX, int fromY, int toX, int toY, char symbol) {

    if (symbol != current_player) {
        cout << "Not your turn! Current player is: " << current_player << endl;
        return false;
    }

    if (!is_valid_move(fromX, fromY, toX, toY, symbol)) {
        return false;
    }

    board[toX][toY] = symbol;
    board[fromX][fromY] = ' ';
    n_moves++;

    switch_player();
    return true;
}

bool tic_4x4_Board::is_valid_move(int fromX, int fromY, int toX, int toY, char symbol) const {
    // Check bounds
    if (fromX < 0 || fromX >= 4 || fromY < 0 || fromY >= 4 ||
        toX < 0 || toX >= 4 || toY < 0 || toY >= 4) {
        cout << "Coordinates out of bounds! Use 0-3." << endl;
        return false;
    }

    // Check if from position has player's token
    if (board[fromX][fromY] != symbol) {
        cout << "No " << symbol << " token at position (" << fromX << "," << fromY << ")!" << endl;
        return false;
    }

    // Check if to position is empty
    if (board[toX][toY] != ' ') {
        cout << "Target position (" << toX << "," << toY << ") is not empty!" << endl;
        return false;
    }

    // Check if move is adjacent (up, down, left, right)
    int rowDiff = abs(fromX - toX);
    int colDiff = abs(fromY - toY);

    if (!((rowDiff == 1 && colDiff == 0) || (rowDiff == 0 && colDiff == 1))) {
        cout << "Invalid move! Can only move up, down, left, or right (not diagonal)." << endl;
        return false;
    }

    return true;
}

bool tic_4x4_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();

    // Check horizontal lines
    for (int row = 0; row < 4; row++) {
        for (int startCol = 0; startCol <= 1; startCol++) {
            if (board[row][startCol] == symbol &&
                board[row][startCol+1] == symbol &&
                board[row][startCol+2] == symbol) {
                return true;
            }
        }
    }

    // Check vertical lines
    for (int col = 0; col < 4; col++) {
        for (int startRow = 0; startRow <= 1; startRow++) {
            if (board[startRow][col] == symbol &&
                board[startRow+1][col] == symbol &&
                board[startRow+2][col] == symbol) {
                return true;
            }
        }
    }

    // Check diagonals (\)
    for (int startRow = 0; startRow <= 1; startRow++) {
        for (int startCol = 0; startCol <= 1; startCol++) {
            if (board[startRow][startCol] == symbol &&
                board[startRow+1][startCol+1] == symbol &&
                board[startRow+2][startCol+2] == symbol) {
                return true;
            }
        }
    }

    // Check diagonals (/)
    for (int startRow = 0; startRow <= 1; startRow++) {
        for (int startCol = 2; startCol < 4; startCol++) {
            if (board[startRow][startCol] == symbol &&
                board[startRow+1][startCol-1] == symbol &&
                board[startRow+2][startCol-2] == symbol) {
                return true;
            }
        }
    }
    return false;
}

bool tic_4x4_Board::is_lose(Player<char>* player) {
    char opponent_symbol = (player->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> opponent("temp", opponent_symbol, PlayerType::HUMAN);
    return is_win(&opponent);
}

bool tic_4x4_Board::is_draw(Player<char>* player) {
    // No draw detection for now
    return false;
}

bool tic_4x4_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void tic_4x4_Board::switch_player() {
    current_player = (current_player == 'X') ? 'O' : 'X';
}

// UI implementation
tic_4x4_UI::tic_4x4_UI() : UI<char>("Welcome to 4x4 Tic-Tac-Toe!", 4) {
    board = nullptr;
}

Player<char>** tic_4x4_UI::setup_players() {
    int game_mode;
    cout << "Choose game mode:\n1. Human vs Human\n2. Human vs Computer\nChoose: ";
    cin >> game_mode;

    Player<char>** players = new Player<char>*[2];

    if (game_mode == 1) {
        // Human vs Human
        string name1, name2;
        cout << "Enter Player 1 name (X): ";
        cin >> name1;
        cout << "Enter Player 2 name (O): ";
        cin >> name2;

        players[0] = UI<char>::create_player(name1, 'X', PlayerType::HUMAN);
        players[1] = UI<char>::create_player(name2, 'O', PlayerType::HUMAN);
    } else {
        // Human vs Computer
        string name;
        int side_choice;

        cout << "Choose your side:\n1. X (Starts first)\n2. O (Starts second)\nChoose: ";
        cin >> side_choice;

        cout << "Enter your name: ";
        cin >> name;

        string computer_name = "Computer";

        if (side_choice == 1) {
            // Human is X, Computer is O
            players[0] = UI<char>::create_player(name, 'X', PlayerType::HUMAN);
            players[1] = UI<char>::create_player(computer_name, 'O', PlayerType::COMPUTER);
        } else {
            // Human is O, Computer is X
            players[0] = UI<char>::create_player(computer_name, 'X', PlayerType::COMPUTER);
            players[1] = UI<char>::create_player(name, 'O', PlayerType::HUMAN);
        }
    }

    return players;
}

Move<char>* tic_4x4_UI::get_move(Player<char>* player) {
    if (!board) return nullptr;

    bool valid_move = false;

    if (player->get_type() == PlayerType::HUMAN) {
        while (!valid_move) {
            cout << player->get_name() << " (" << player->get_symbol() << "), enter your move (fromRow fromCol toRow toCol): ";

            cin.clear();

            if (!(cin >> move_fromX >> move_fromY >> move_toX >> move_toY)) {

                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input! Please enter 4 numbers separated by spaces." << endl;
                continue;
            }

            cin.ignore(10000, '\n');


            valid_move = true;
        }
    } else {

        vector<pair<int, int>> possible_starts;
        char computer_symbol = player->get_symbol();


        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board->get_cell(i, j) == computer_symbol) {
                    possible_starts.push_back({i, j});
                }
            }
        }


        for (auto& start : possible_starts) {
            int fromX = start.first;
            int fromY = start.second;


            int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
            for (auto& dir : directions) {
                int toX = fromX + dir[0];
                int toY = fromY + dir[1];


                if (toX >= 0 && toX < 4 && toY >= 0 && toY < 4) {

                    if (board->get_cell(toX, toY) == ' ') {

                        move_fromX = fromX;
                        move_fromY = fromY;
                        move_toX = toX;
                        move_toY = toY;
                        valid_move = true;
                        cout << "Computer moves from (" << move_fromX << "," << move_fromY
                             << ") to (" << move_toX << "," << move_toY << ")" << endl;
                        break;
                    }
                }
            }
            if (valid_move) break;
        }
    }


    return new Move<char>(0, 0, player->get_symbol());
}