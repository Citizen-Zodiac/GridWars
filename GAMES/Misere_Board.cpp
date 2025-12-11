#include "Misere.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
using namespace std;


RandomMiserePlayer::RandomMiserePlayer(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::COMPUTER)
{
    srand((unsigned)time(nullptr));
}

Move<char>* RandomMiserePlayer::get_random_move() {
    auto mat = boardPtr->get_board_matrix();
    vector<pair<int, int>> emptyCells;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (mat[i][j] == ' ')
                emptyCells.push_back({ i,j });

    if (emptyCells.empty())
        return new Move<char>(0, 0, this->symbol);

    auto choice = emptyCells[rand() % emptyCells.size()];
    return new Move<char>(choice.first, choice.second, this->symbol);
}


MisereBoard::MisereBoard() : Board<char>(3, 3) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
    n_moves = 0;
}

bool MisereBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;
    if (board[x][y] != ' ') return false;

    board[x][y] = move->get_symbol();
    n_moves++;
    return true;
}

bool MisereBoard::three_in_row(char s) {
    for (int i = 0; i < 3; i++)
        if (board[i][0] == s && board[i][1] == s && board[i][2] == s)
            return true;

    for (int j = 0; j < 3; j++)
        if (board[0][j] == s && board[1][j] == s && board[2][j] == s)
            return true;

    if (board[0][0] == s && board[1][1] == s && board[2][2] == s) return true;
    if (board[0][2] == s && board[1][1] == s && board[2][0] == s) return true;

    return false;
}

bool MisereBoard::is_win(Player<char>* p) {
    char opp = (p->get_symbol() == 'X') ? 'O' : 'X';
    return three_in_row(opp);
}

bool MisereBoard::is_lose(Player<char>* p) {
    return three_in_row(p->get_symbol());
}

bool MisereBoard::is_draw(Player<char>* p) {
    return (n_moves == 9 && !is_win(p) && !is_lose(p));
}

bool MisereBoard::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}


MisereUI::MisereUI()
    : UI<char>("Welcome to Misere Tic Tac Toe!", 3) {}

Move<char>* MisereUI::get_move(Player<char>* p) {
    if (p->get_type() == PlayerType::COMPUTER) {
        auto* bot = dynamic_cast<RandomMiserePlayer*>(p);
        cout << p->get_name() << " (Computer) is thinking...\n";
        return bot->get_random_move();
    }

    int x, y;
    while (true) {
        cout << p->get_name() << " (" << p->get_symbol()
            << ") enter row and column (0-2): ";

        if (!(cin >> x >> y)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Try again.\n";
            continue;
        }

        return new Move<char>(x, y, p->get_symbol());
    }
}

int MisereUI::show_menu() {
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

Player<char>** MisereUI::setup_players() {
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

Player<char>* MisereUI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER)
        return new RandomMiserePlayer(name, symbol);
    else
        return new Player<char>(name, symbol, PlayerType::HUMAN);
}
