#ifndef INFINITY_H
#define INFINITY_H

#include "BoardGame_Classes.h"
#include <vector>
#include <queue>
using namespace std;


class Infinity_ComputerPlayer : public Player<char> {
public:
    Infinity_ComputerPlayer(string name, char symbol);
    Move<char>* get_infinity_computer_move();
};


class Infinity_Board : public Board<char> {

private:
    queue<pair<int, int>> move_order; // track oldest moves

    bool infinity_three_in_row(char s);

public:
    Infinity_Board();

    bool update_board(Move<char>* move) override;

    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;
};


class Infinity_UI : public UI<char> {
public:
    Infinity_UI();

    Move<char>* get_move(Player<char>* p) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif

