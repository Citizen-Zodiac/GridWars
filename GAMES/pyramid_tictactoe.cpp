#include "pyramid_tictactoe.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

//             Board Implementation

PyramidTicTacToeBoard::PyramidTicTacToeBoard() : Board<char>(3, 5) {
    movesCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';
        }
    }
}

bool PyramidTicTacToeBoard::isValidPosition(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= columns) return false;

    // Pyramid structure:
    // Row 0 (top): only column 2 (center) - 1 square
    // Row 1 (middle): columns 1,2,3 - 3 squares
    // Row 2 (bottom): columns 0-4 - 5 squares
    switch(row) {
        case 0: return (col == 2);            // Top: only center
        case 1: return (col >= 1 && col <= 3); // Middle: 3 squares
        case 2: return (col >= 0 && col <= 4); // Bottom: 5 squares
        default: return false;
    }
}

bool PyramidTicTacToeBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (!isValidPosition(x, y) || board[x][y] != ' ') {
        delete move;
        return false;
    }

    board[x][y] = symbol;
    n_moves++;
    movesCount++;
    delete move;
    return true;
}

bool PyramidTicTacToeBoard::checkWin() const {
    return checkHorizontal() || checkVertical() || checkDiagonal();
}

bool PyramidTicTacToeBoard::checkHorizontal() const {
    // Check all possible horizontal 3-in-a-row
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col <= columns - 3; col++) {
            if (isValidPosition(row, col) &&
                isValidPosition(row, col+1) &&
                isValidPosition(row, col+2)) {
                char cell = board[row][col];
                if (cell != ' ' &&
                    cell == board[row][col+1] &&
                    cell == board[row][col+2]) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool PyramidTicTacToeBoard::checkVertical() const {
    // Check vertical wins
    for (int col = 0; col < columns; col++) {
        for (int row = 0; row <= rows - 3; row++) {
            if (isValidPosition(row, col) &&
                isValidPosition(row+1, col) &&
                isValidPosition(row+2, col)) {
                char cell = board[row][col];
                if (cell != ' ' &&
                    cell == board[row+1][col] &&
                    cell == board[row+2][col]) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool PyramidTicTacToeBoard::checkDiagonal() const {
    // Check main diagonals ( \ )
    for (int row = 0; row <= rows - 3; row++) {
        for (int col = 0; col <= columns - 3; col++) {
            if (isValidPosition(row, col) &&
                isValidPosition(row+1, col+1) &&
                isValidPosition(row+2, col+2)) {
                char cell = board[row][col];
                if (cell != ' ' &&
                    cell == board[row+1][col+1] &&
                    cell == board[row+2][col+2]) {
                    return true;
                }
            }
        }
    }

    // Check anti-diagonals ( / )
    for (int row = 0; row <= rows - 3; row++) {
        for (int col = 2; col < columns; col++) {
            if (isValidPosition(row, col) &&
                isValidPosition(row+1, col-1) &&
                isValidPosition(row+2, col-2)) {
                char cell = board[row][col];
                if (cell != ' ' &&
                    cell == board[row+1][col-1] &&
                    cell == board[row+2][col-2]) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool PyramidTicTacToeBoard::is_win(Player<char>* player) {
    return checkWin();
}

bool PyramidTicTacToeBoard::is_lose(Player<char>* player) {
    return false;
}

bool PyramidTicTacToeBoard::is_draw(Player<char>* player) {
    return (movesCount >= MAX_MOVES) && !checkWin();
}

bool PyramidTicTacToeBoard::game_is_over(Player<char>* player) {
    return checkWin() || (movesCount >= MAX_MOVES);
}

//                 UI Implementation

PyramidTicTacToeUI::PyramidTicTacToeUI() : UI<char>("Pyramid Tic-Tac-Toe", 3) {
    srand(time(0));
}

Player<char>** PyramidTicTacToeUI::setup_players() {
    Player<char>** players = new Player<char>*[2];

    cout << "\n========================================\n";
    cout << "        PYRAMID TIC-TAC-TOE\n";
    cout << "========================================\n\n";

    cout << "Choose game mode:\n";
    cout << "1. Human vs Human\n";
    cout << "2. Human vs Computer\n";
    cout << "Choose: ";

    int gameMode;
    cin >> gameMode;

    while (gameMode != 1 && gameMode != 2) {
        cout << "Invalid choice! Choose 1 or 2: ";
        cin >> gameMode;
    }

    string name1, name2;
    PlayerType type1, type2;

    if (gameMode == 1) {
        // Human vs Human
        cout << "\n=== HUMAN vs HUMAN ===\n";
        cout << "Enter name for Player 1 (X): ";
        cin >> name1;
        cout << "Enter name for Player 2 (O): ";
        cin >> name2;

        type1 = PlayerType::HUMAN;
        type2 = PlayerType::HUMAN;

        players[0] = new Player<char>(name1, 'X', type1);
        players[1] = new Player<char>(name2, 'O', type2);
    } else {
        // Human vs Computer
        cout << "\n=== HUMAN vs COMPUTER ===\n";
        cout << "Enter your name: ";
        cin >> name1;
        name2 = "Computer";

        // Ask who goes first
        int firstChoice;
        cout << "Who goes first?\n";
        cout << "1. You (X)\n";
        cout << "2. Computer (X)\n";
        cout << "Choose: ";
        cin >> firstChoice;

        while (firstChoice != 1 && firstChoice != 2) {
            cout << "Invalid choice! Choose 1 or 2: ";
            cin >> firstChoice;
        }

        if (firstChoice == 1) {
            // Human is X (goes first), Computer is O
            type1 = PlayerType::HUMAN;
            type2 = PlayerType::COMPUTER;
            players[0] = new Player<char>(name1, 'X', type1);
            players[1] = new Player<char>(name2, 'O', type2);
        } else {
            // Computer is X (goes first), Human is O
            type1 = PlayerType::COMPUTER;
            type2 = PlayerType::HUMAN;
            players[0] = new Player<char>(name2, 'X', type1);
            players[1] = new Player<char>(name1, 'O', type2);
        }
    }

    cout << "\nGame Setup Complete!\n";
    cout << players[0]->get_name() << " (" << players[0]->get_symbol() << ") vs "
         << players[1]->get_name() << " (" << players[1]->get_symbol() << ")\n\n";

    return players;
}

Move<char>* PyramidTicTacToeUI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";
        cout << "Enter row (0-2): ";
        cin >> x;
        cout << "Enter column (0-4): ";
        cin >> y;

        while (cin.fail() || x < 0 || x > 2 || y < 0 || y > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid! Enter row (0-2) and column (0-4): ";
            cin >> x >> y;
        }
    } else {
        // COMPUTER PLAYER
        cout << "\n" << player->get_name() << " (" << player->get_symbol() << ") is making a move...\n";

        // Get current board state
        Board<char>* boardPtr = player->get_board_ptr();
        vector<vector<char>> matrix;

        if (boardPtr) {
            matrix = boardPtr->get_board_matrix();
        } else {
            // Fallback: empty board
            matrix = vector<vector<char>>(3, vector<char>(5, ' '));
        }

        vector<pair<int, int>> validMoves;

        // Collect all valid empty positions
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
                bool isValid = false;
                switch(i) {
                    case 0: isValid = (j == 2); break;
                    case 1: isValid = (j >= 1 && j <= 3); break;
                    case 2: isValid = (j >= 0 && j <= 4); break;
                }

                if (isValid && matrix[i][j] == ' ') {
                    validMoves.push_back({i, j});
                }
            }
        }

        if (!validMoves.empty()) {
            int idx = rand() % validMoves.size();
            x = validMoves[idx].first;
            y = validMoves[idx].second;
            cout << player->get_name() << " chooses position (" << x << ", " << y << ")\n";
        } else {
            x = 0;
            y = 2;
        }
    }

    return new Move<char>(x, y, player->get_symbol());
}

void PyramidTicTacToeUI::display_board_matrix(const vector<vector<char>>& matrix) const {
    cout << "\n";
    cout << "========================================\n";
    cout << "        PYRAMID TIC-TAC-TOE BOARD\n";
    cout << "========================================\n\n";

    // SIMPLE PYRAMID DISPLAY with * for borders
    cout << "Pyramid Board (* = border):\n\n";

    // Top border
    cout << "        * * * * *\n";

    // Row 0 (top) with border
    cout << "        * * ";
    if (matrix[0][2] == ' ') cout << ".";
    else cout << matrix[0][2];
    cout << " * *\n";

    // Row 1 (middle) with border
    cout << "        * ";
    for (int j = 1; j <= 3; j++) {
        if (matrix[1][j] == ' ') cout << ".";
        else cout << matrix[1][j];
        if (j < 3) cout << " ";
    }
    cout << " *\n";

    // Row 2 (bottom) - no border on sides
    cout << "        ";
    for (int j = 0; j < 5; j++) {
        if (matrix[2][j] == ' ') cout << ".";
        else cout << matrix[2][j];
        if (j < 4) cout << " ";
    }
    cout << "\n";

    // Bottom border
    cout << "        * * * * *\n\n";

    // Coordinate guide
    cout << "Valid Positions (9 total):\n";
    cout << "Top (row 0):                  (0,2)\n";
    cout << "Middle (row 1):         (1,1) (1,2) (1,3)\n";
    cout << "Bottom (row 2):   (2,0) (2,1) (2,2) (2,3) (2,4)\n\n";

    // Current board state
    cout << "Current Board:\n";
    cout << "Top:              [" << (matrix[0][2] == ' ' ? ' ' : matrix[0][2]) << "]\n";
    cout << "Middle:       [" << (matrix[1][1] == ' ' ? ' ' : matrix[1][1]) << "] ["
         << (matrix[1][2] == ' ' ? ' ' : matrix[1][2]) << "] ["
         << (matrix[1][3] == ' ' ? ' ' : matrix[1][3]) << "]\n";
    cout << "Bottom:   [" << (matrix[2][0] == ' ' ? ' ' : matrix[2][0]) << "] ["
         << (matrix[2][1] == ' ' ? ' ' : matrix[2][1]) << "] ["
         << (matrix[2][2] == ' ' ? ' ' : matrix[2][2]) << "] ["
         << (matrix[2][3] == ' ' ? ' ' : matrix[2][3]) << "] ["
         << (matrix[2][4] == ' ' ? ' ' : matrix[2][4]) << "]\n\n";
}