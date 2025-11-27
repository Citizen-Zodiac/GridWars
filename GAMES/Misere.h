#ifndef MISERE_UI_H
#define MISERE_UI_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
using namespace std;


class RandomMiserePlayer : public Player<char> {
public:
    RandomMiserePlayer(string name, char symbol);
    Move<char>* get_random_move();
};


class MisereBoard : public Board<char> {
public:
    MisereBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;

private:
    bool three_in_row(char s);
};


class MisereUI : public UI<char> {
public:
    MisereUI();

    Move<char>* get_move(Player<char>* p) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif
