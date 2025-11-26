#ifndef MISERE_UI_H
#define MISERE_UI_H

#include "BoardGame_Classes.h"
#include <limits>
#include <cstdlib>
#include <ctime>

// ---------------------------------------------------------------
// 1) Define Random Computer Player *INSIDE* the UI file
// ---------------------------------------------------------------
class RandomMiserePlayer : public Player<char> {
public:
    RandomMiserePlayer(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::COMPUTER)
    {
        srand((unsigned)time(nullptr));
    }

    Move<char>* get_random_move() {
        auto mat = boardPtr->get_board_matrix();
        vector<pair<int, int>> emptyCells;

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (mat[i][j] == ' ')
                    emptyCells.push_back({ i, j });

        if (emptyCells.empty())
            return new Move<char>(0, 0, this->symbol);

        auto choice = emptyCells[rand() % emptyCells.size()];
        return new Move<char>(choice.first, choice.second, this->symbol);
    }
};

// ---------------------------------------------------------------
// 2) UI Class
// ---------------------------------------------------------------
class MisereUI : public UI<char> {
public:
    MisereUI() : UI<char>("Welcome to Misere Tic Tac Toe!", 3) {}

    Move<char>* get_move(Player<char>* p) override {
        // If COMPUTER → generate random move
        if (p->get_type() == PlayerType::COMPUTER) {
            auto* bot = dynamic_cast<RandomMiserePlayer*>(p);
            if (bot) {
                cout << p->get_name()
                    << " (Computer) is thinking...\n";
                return bot->get_random_move();
            }
        }

        // HUMAN player → get keyboard input
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

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        if (type == PlayerType::COMPUTER)
            return new RandomMiserePlayer(name, symbol);
        else
            return new Player<char>(name, symbol, PlayerType::HUMAN);
    }
};

#endif