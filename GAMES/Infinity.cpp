#include "Infinity.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
using namespace std;


Infinity_ComputerPlayer::Infinity_ComputerPlayer(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::COMPUTER)
{
    srand((unsigned)time(nullptr));
}

Move<char>* Infinity_ComputerPlayer::get_infinity_computer_move() {
    auto matrix = boardPtr->get_board_matrix();
    vector<pair<int, int>> empty;

    // board is 3x3
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (matrix[r][c] == ' ')
                empty.push_back({ r, c });

    if (empty.empty())
        return new Move<char>(0, 0, this->symbol);

    auto pick = empty[rand() % empty.size()];
    return new Move<char>(pick.first, pick.second, this->symbol);
}

Infinity_Board::Infinity_Board() : Board<char>(3, 3), current_marks(0) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = ' ';

    n_moves = 0;
}

bool Infinity_Board::update_board(Move<char>* move) {
    if (!move) return false;

    int r = move->get_x();
    int c = move->get_y();

    if (r < 0 || r >= 3 || c < 0 || c >= 3)
        return false;

    if (board[r][c] != ' ')
        return false;

    board[r][c] = move->get_symbol();

    n_moves++;

    all_moves.push_back({ r, c });


    if (n_moves % 4 == 0) {
        int remove_index = (n_moves / 4) - 1;

        if (remove_index >= 0 && remove_index < (int)all_moves.size()) {
            auto old = all_moves[remove_index];
            int orow = old.first;
            int ocol = old.second;

            if (orow >= 0 && orow < 3 && ocol >= 0 && ocol < 3) {
                if (board[orow][ocol] != ' ') {
                    board[orow][ocol] = ' ';
                }
            }
        }
    }

    return true;
}



bool Infinity_Board::three_in_row(char s) {
    // rows
    for (int r = 0; r < 3; r++)
        if (board[r][0] == s && board[r][1] == s && board[r][2] == s)
            return true;

    // columns
    for (int c = 0; c < 3; c++)
        if (board[0][c] == s && board[1][c] == s && board[2][c] == s)
            return true;

    // diagonals
    if (board[0][0] == s && board[1][1] == s && board[2][2] == s)
        return true;

    if (board[0][2] == s && board[1][1] == s && board[2][0] == s)
        return true;

    return false;
}

bool Infinity_Board::is_win(Player<char>* p) {
    return three_in_row(p->get_symbol());
}

bool Infinity_Board::is_lose(Player<char>* p) {
    char opp = (p->get_symbol() == 'X') ? 'O' : 'X';
    return three_in_row(opp);
}

bool Infinity_Board::is_draw(Player<char>* p) {

    if (is_win(p) || is_lose(p)) return false;

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == ' ')
                return false;

    return true;
}


bool Infinity_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}


Infinity_UI::Infinity_UI()
    : UI<char>("Welcome to Infinity Tic-Tac-Toe!", 2) {}

int Infinity_UI::show_menu() {
    int choice;
    cout << "Choose game mode:\n";
    cout << "1. Human vs Human\n";
    cout << "2. Human vs Computer\n";
    cout << "Choose: ";

    while (true) {
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter 1 or 2: ";
            continue;
        }
        if (choice == 1 || choice == 2) break;
        cout << "Invalid choice. Enter 1 or 2: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

Player<char>** Infinity_UI::setup_players() {
    int choice = show_menu();

    Player<char>** players = new Player<char>*[2];

    string name1, name2;

    cout << "Enter name for Player 1: ";
    getline(cin, name1);
    if (name1.empty()) name1 = "Player1";

    players[0] = create_player(name1, 'X', PlayerType::HUMAN);

    if (choice == 1) {
        cout << "Enter name for Player 2: ";
        getline(cin, name2);
        if (name2.empty()) name2 = "Player2";
        players[1] = create_player(name2, 'O', PlayerType::HUMAN);
    }
    else {
        name2 = "Computer";
        players[1] = create_player(name2, 'O', PlayerType::COMPUTER);
    }

    return players;
}

Move<char>* Infinity_UI::get_move(Player<char>* p) {
    if (p->get_type() == PlayerType::COMPUTER) {
        auto* bot = dynamic_cast<Infinity_ComputerPlayer*>(p);
        cout << p->get_name() << " (Computer) is thinking...\n";
        return bot->get_infinity_computer_move();
    }

    int r, c;

    while (true) {
        cout << p->get_name() << " (" << p->get_symbol() << ") enter row and column (0-2): ";

        if (!(cin >> r >> c)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (r < 0 || r > 2 || c < 0 || c > 2) {
            cout << "Coordinates must be 0–2. Try again.\n";
            continue;
        }

        return new Move<char>(r, c, p->get_symbol());
    }
}

Player<char>* Infinity_UI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER)
        return new Infinity_ComputerPlayer(name, symbol);

    return new Player<char>(name, symbol, PlayerType::HUMAN);
}
