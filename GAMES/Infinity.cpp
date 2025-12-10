#include "Infinity.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

Infinity_ComputerPlayer::Infinity_ComputerPlayer(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::COMPUTER)
{
    srand((unsigned)time(nullptr));
}

Move<char>* Infinity_ComputerPlayer::get_infinity_computer_move() {
    auto mat = boardPtr->get_board_matrix();
    vector<pair<int, int>> empty;

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (mat[r][c] == ' ')
                empty.push_back({ r,c });

    if (empty.empty())
        return new Move<char>(0, 0, this->symbol);

    auto pick = empty[rand() % empty.size()];
    return new Move<char>(pick.first, pick.second, this->symbol);
}


Infinity_Board::Infinity_Board() : Board<char>(3, 3) {

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = ' ';

    n_moves = 0;
}

bool Infinity_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();

    if (r < 0 || r >= 3 || c < 0 || c >= 3)
        return false;

    if (board[r][c] != ' ')
        return false;

    // Place the mark
    board[r][c] = move->get_symbol();
    n_moves++;

    move_order.push({ r,c });

    // After every 3 moves, remove oldest
    if (n_moves > 3) {
        auto old = move_order.front();
        move_order.pop();
        board[old.first][old.second] = ' ';
    }

    return true;
}


bool Infinity_Board::infinity_three_in_row(char s) {

    // rows
    for (int r = 0; r < 3; r++)
        if (board[r][0] == s && board[r][1] == s && board[r][2] == s)
            return true;

    // cols
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
    return infinity_three_in_row(p->get_symbol());
}

bool Infinity_Board::is_lose(Player<char>* p) {
    char opp = (p->get_symbol() == 'X' ? 'O' : 'X');
    return infinity_three_in_row(opp);
}

bool Infinity_Board::is_draw(Player<char>* p) {
    // Infinity tic-tac-toe doesn't really draw unless grid is full
    return (!is_win(p) && !is_lose(p) && n_moves >= 9);
}

bool Infinity_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}


Infinity_UI::Infinity_UI()
    : UI<char>("Welcome to Infinity Tic-Tac-Toe!", 2) {}

Move<char>* Infinity_UI::get_move(Player<char>* p) {

    if (p->get_type() == PlayerType::COMPUTER) {
        auto* bot = dynamic_cast<Infinity_ComputerPlayer*>(p);
        cout << p->get_name() << " (Computer) is thinking...\n";
        return bot->get_infinity_computer_move();
    }

    int r, c;
    while (true) {
        cout << p->get_name() << " (" << p->get_symbol()
            << ") enter row and column (0-2): ";

        if (!(cin >> r >> c)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid. Try again.\n";
            continue;
        }

        return new Move<char>(r, c, p->get_symbol());
    }
}

Player<char>* Infinity_UI::create_player(string& name,
    char symbol,
    PlayerType type)
{
    if (type == PlayerType::COMPUTER)
        return new Infinity_ComputerPlayer(name, symbol);

    return new Player<char>(name, symbol, PlayerType::HUMAN);
}