#include "Ultimate.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;


Ultimate_SubBoard::Ultimate_SubBoard() : finished(false), winner(' ') {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            cells[r][c] = ' ';
}

bool Ultimate_SubBoard::three_in_row(char s) {
    for (int r = 0; r < 3; r++)
        if (cells[r][0] == s && cells[r][1] == s && cells[r][2] == s)
            return true;

    for (int c = 0; c < 3; c++)
        if (cells[0][c] == s && cells[1][c] == s && cells[2][c] == s)
            return true;

    if (cells[0][0] == s && cells[1][1] == s && cells[2][2] == s)
        return true;

    if (cells[0][2] == s && cells[1][1] == s && cells[2][0] == s)
        return true;

    return false;
}

bool Ultimate_SubBoard::place_mark(int r, int c, char s) {
    if (finished) return false;
    if (r < 0 || r >= 3 || c < 0 || c >= 3) return false;
    if (cells[r][c] != ' ') return false;

    cells[r][c] = s;

    if (three_in_row(s)) {
        finished = true;
        winner = s;
    }
    else {
        bool full = true;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (cells[i][j] == ' ')
                    full = false;

        if (full)
            finished = true;
    }

    return true;
}

bool Ultimate_SubBoard::is_full() const {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (cells[r][c] == ' ')
                return false;
    return true;
}

bool Ultimate_SubBoard::is_finished() const {
    return finished;
}

char Ultimate_SubBoard::get_winner() const {
    return winner;
}

vector<vector<char>> Ultimate_SubBoard::get_matrix() const {
    vector<vector<char>> v(3, vector<char>(3));
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            v[r][c] = cells[r][c];
    return v;
}


Ultimate_MainBoard::Ultimate_MainBoard() : Board<char>(3, 3) {
    // main board shows winners of sub-boards (initially space)
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = ' ';
}

bool Ultimate_MainBoard::main_three_in_row(char s) {
    for (int r = 0; r < 3; r++)
        if (board[r][0] == s && board[r][1] == s && board[r][2] == s)
            return true;

    for (int c = 0; c < 3; c++)
        if (board[0][c] == s && board[1][c] == s && board[2][c] == s)
            return true;

    if (board[0][0] == s && board[1][1] == s && board[2][2] == s)
        return true;

    if (board[0][2] == s && board[1][1] == s && board[2][0] == s)
        return true;

    return false;
}

bool Ultimate_MainBoard::update_board(Move<char>* move) {
    if (!move) return false;

    int gx = move->get_x(); // global x 0..8
    int gy = move->get_y(); // global y 0..8

    if (gx < 0 || gx >= 9 || gy < 0 || gy >= 9) return false;

    int br = gx / 3; // sub-board row 0..2
    int bc = gy / 3; // sub-board col 0..2

    int r = gx % 3;  // local row in sub-board
    int c = gy % 3;  // local col in sub-board

    Ultimate_SubBoard& sb = sub[br][bc];

    if (sb.is_finished()) return false;

    if (!sb.place_mark(r, c, move->get_symbol()))
        return false;

    if (sb.get_winner() == move->get_symbol())
        board[br][bc] = move->get_symbol();

    n_moves++;
    return true;
}

bool Ultimate_MainBoard::is_win(Player<char>* p) {
    return main_three_in_row(p->get_symbol());
}

bool Ultimate_MainBoard::is_lose(Player<char>* p) {
    char opp = (p->get_symbol() == 'X' ? 'O' : 'X');
    return main_three_in_row(opp);
}

bool Ultimate_MainBoard::is_draw(Player<char>* p) {
    // main board full and no winner
    bool full = true;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == ' ')
                full = false;

    return (full && !is_win(p) && !is_lose(p));
}

bool Ultimate_MainBoard::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}

Ultimate_SubBoard& Ultimate_MainBoard::get_sub(int r, int c) {
    return sub[r][c];
}


Ultimate_ComputerPlayer::Ultimate_ComputerPlayer(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::COMPUTER)
{
    srand((unsigned)time(nullptr));
}

Move<char>* Ultimate_ComputerPlayer::get_ultimate_computer_move() {
    // generate list of available global cells (0..8,0..8)
    vector<pair<int, int>> empty;
    Ultimate_MainBoard* mb = dynamic_cast<Ultimate_MainBoard*>(boardPtr);
    if (!mb) return new Move<char>(0, 0, this->symbol);

    for (int br = 0; br < 3; ++br) {
        for (int bc = 0; bc < 3; ++bc) {
            Ultimate_SubBoard& sb = mb->get_sub(br, bc);
            if (sb.is_finished()) continue;
            auto mat = sb.get_matrix();
            for (int r = 0; r < 3; ++r)
                for (int c = 0; c < 3; ++c)
                    if (mat[r][c] == ' ')
                        empty.push_back({ br * 3 + r, bc * 3 + c });
        }
    }

    if (empty.empty()) return new Move<char>(0, 0, this->symbol);

    auto pick = empty[rand() % empty.size()];
    return new Move<char>(pick.first, pick.second, this->symbol);
}


Ultimate_UI::Ultimate_UI()
    : UI<char>("Welcome to Ultimate Tic-Tac-Toe!", 2) {}

int Ultimate_UI::show_menu() {
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

Player<char>** Ultimate_UI::setup_players() {
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


void Ultimate_UI::display_ultimate_board(Ultimate_MainBoard* mb)
{
    if (!mb) return;

    cout << "\n=============== ULTIMATE TIC-TAC-TOE ===============\n\n";

    // for each big row of sub-boards
    for (int BR = 0; BR < 3; BR++)
    {
        // for each row inside sub-board
        for (int r = 0; r < 3; r++)
        {
            // for each big column of sub-boards
            for (int BC = 0; BC < 3; BC++)
            {
                vector<vector<char>> sub = mb->get_sub(BR, BC).get_matrix();

                // print row r of this sub-board
                cout << " ";
                cout << (sub[r][0] == ' ' ? '.' : sub[r][0]) << " "
                    << (sub[r][1] == ' ' ? '.' : sub[r][1]) << " "
                    << (sub[r][2] == ' ' ? '.' : sub[r][2]);

                if (BC < 2) cout << " | ";
            }
            cout << "\n";
        }
        if (BR < 2) {
            cout << "-----------+-----------+-----------\n";
        }
    }

    cout << "\n====================================================\n\n";
}

Move<char>* Ultimate_UI::get_move(Player<char>* p) {

    if (p->get_type() == PlayerType::COMPUTER) {
        auto* bot = dynamic_cast<Ultimate_ComputerPlayer*>(p);
        if (bot) return bot->get_ultimate_computer_move();
        return new Move<char>(0, 0, p->get_symbol());
    }

    int br, bc, r, c;

    while (true) {
        cout << p->get_name() << " (" << p->get_symbol() << ") enter your move:\n";
        cout << "Sub-board row (0-2): "; cin >> br;
        cout << "Sub-board col (0-2): "; cin >> bc;
        cout << "Cell row in sub-board (0-2): "; cin >> r;
        cout << "Cell col in sub-board (0-2): "; cin >> c;

        if (cin.fail() || br < 0 || br > 2 || bc < 0 || bc > 2 || r < 0 || r > 2 || c < 0 || c > 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. All numbers must be between 0 and 2. Try again.\n";
            continue;
        }

        int gx = br * 3 + r; // convert to global row
        int gy = bc * 3 + c; // convert to global col

        return new Move<char>(gx, gy, p->get_symbol());
    }
}

Player<char>* Ultimate_UI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER)
        return new Ultimate_ComputerPlayer(name, symbol);

    return new Player<char>(name, symbol, PlayerType::HUMAN);
}


void Ultimate_GameManager::run() {

    ui->display_ultimate_board(board);  // first display

    Player<char>* current;

    while (true) {

        for (int i = 0; i < 2; i++) {

            current = players[i];

            Move<char>* move = ui->get_move(current);

            while (!board->update_board(move)) {
                cout << "Invalid move. Try again.\n";
                move = ui->get_move(current);
            }

            ui->display_ultimate_board(board);   // show after every move

            if (board->is_win(current)) {
                ui->display_message(current->get_name() + " wins!");
                return;
            }

            if (board->is_lose(current)) {
                ui->display_message(players[1 - i]->get_name() + " wins!");
                return;
            }

            if (board->is_draw(current)) {
                ui->display_message("Draw!");
                return;
            }
        }
    }
}



  