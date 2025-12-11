#include "Diamond.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

Diamond_ComputerPlayer::Diamond_ComputerPlayer(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::COMPUTER)
{
    srand((unsigned)time(nullptr));
}

Move<char>* Diamond_ComputerPlayer::get_diamond_computer_move() {
    auto mat = boardPtr->get_board_matrix();
    vector<pair<int, int>> empty;

    for (int r = 0; r < 7; r++) {
        for (int c = 0; c < 7; c++) {
            if (abs(r - 3) + abs(c - 3) <= 3 && mat[r][c] == ' ')
                empty.push_back({ r,c });
        }
    }

    if (empty.empty())
        return new Move<char>(0, 0, this->symbol);

    auto choice = empty[rand() % empty.size()];
    return new Move<char>(choice.first, choice.second, this->symbol);
}

Diamond_Board::Diamond_Board() : Board<char>(7, 7) {

    for (int r = 0; r < 7; r++) {
        for (int c = 0; c < 7; c++) {
            if (abs(r - 3) + abs(c - 3) <= 3)
                board[r][c] = ' ';
            else
                board[r][c] = '#';
        }
    }
    n_moves = 0;
}

bool Diamond_Board::diamond_cell_valid(int r, int c) {
    if (r < 0 || r >= 7 || c < 0 || c >= 7) return false;
    return board[r][c] != '#';
}

bool Diamond_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();

    if (!diamond_cell_valid(r, c)) return false;
    if (board[r][c] != ' ') return false;

    board[r][c] = move->get_symbol();
    n_moves++;
    return true;
}


vector<vector<pair<int, int>>> Diamond_Board::diamond_get_lines(int length) {
    vector<vector<pair<int, int>>> lines;

    int dr[4] = { 0, 1, 1, 1 };
    int dc[4] = { 1, 0, 1, -1 };

    for (int r = 0; r < 7; r++) {
        for (int c = 0; c < 7; c++) {
            if (!diamond_cell_valid(r, c)) continue;

            for (int d = 0; d < 4; d++) {
                vector<pair<int, int>> line;
                int rr = r, cc = c;

                for (int k = 0; k < length; k++) {
                    if (!diamond_cell_valid(rr, cc)) {
                        line.clear();
                        break;
                    }
                    line.push_back({ rr,cc });
                    rr += dr[d];
                    cc += dc[d];
                }

                if (!line.empty())
                    lines.push_back(line);
            }
        }
    }

    return lines;
}

bool Diamond_Board::diamond_line_full(const vector<pair<int, int>>& line, char s) {
    for (auto& cell : line)
        if (board[cell.first][cell.second] != s)
            return false;
    return true;
}

bool Diamond_Board::find_lines(Player<char>* p, int length,
    vector<vector<pair<int, int>>>& outLines)
{
    char s = p->get_symbol();
    auto lines = diamond_get_lines(length);

    for (auto& L : lines)
        if (diamond_line_full(L, s))
            outLines.push_back(L);

    return !outLines.empty();
}


bool Diamond_Board::is_win(Player<char>* p) {

    vector<vector<pair<int, int>>> L3, L4;

    bool has3 = find_lines(p, 3, L3);
    bool has4 = find_lines(p, 4, L4);

    if (!has3 || !has4)
        return false;

    // Must be different slopes
    for (auto& a : L3) {
        for (auto& b : L4) {
            auto d1 = make_pair(a[1].first - a[0].first,
                a[1].second - a[0].second);
            auto d2 = make_pair(b[1].first - b[0].first,
                b[1].second - b[0].second);

            if (d1 != d2)
                return true;
        }
    }

    return false;
}

bool Diamond_Board::is_lose(Player<char>* p) {
    char opp = (p->get_symbol() == 'X' ? 'O' : 'X');
    Player<char> fake("temp", opp, PlayerType::HUMAN);
    return is_win(&fake);
}

bool Diamond_Board::is_draw(Player<char>* p) {
    return (n_moves == 25 && !is_win(p) && !is_lose(p));
}

bool Diamond_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}

Diamond_UI::Diamond_UI()
    : UI<char>("Welcome to Diamond Tic-Tac-Toe (7x7)!", 2) {}

Move<char>* Diamond_UI::get_move(Player<char>* p) {

    if (p->get_type() == PlayerType::COMPUTER) {
        auto* bot = dynamic_cast<Diamond_ComputerPlayer*>(p);
        cout << p->get_name() << " (Computer) is thinking...\n";
        return bot->get_diamond_computer_move();
    }

    int r, c;
    while (true) {
        cout << p->get_name() << " (" << p->get_symbol()
            << ") enter row and column (0-6): ";

        if (!(cin >> r >> c)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid. Try again.\n";
            continue;
        }

        return new Move<char>(r, c, p->get_symbol());
    }
}

int Diamond_UI::show_menu() {
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

Player<char>** Diamond_UI::setup_players() {
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


Player<char>* Diamond_UI::create_player(string& name, char symbol, PlayerType type) {

    if (type == PlayerType::COMPUTER)
        return new Diamond_ComputerPlayer(name, symbol);

    return new Player<char>(name, symbol, PlayerType::HUMAN);
}