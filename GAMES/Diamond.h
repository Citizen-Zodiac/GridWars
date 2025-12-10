#ifndef DIAMOND_H
#define DIAMOND_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
using namespace std;


class Diamond_ComputerPlayer : public Player<char> {
public:
    Diamond_ComputerPlayer(string name, char symbol);
    Move<char>* get_diamond_computer_move();
};


class Diamond_Board : public Board<char> {

public:
    Diamond_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;

private:
    bool diamond_cell_valid(int r, int c);
    vector<vector<pair<int, int>>> diamond_get_lines(int length);
    bool diamond_line_full(const vector<pair<int, int>>& line, char s);

    bool find_lines(Player<char>* p, int length,
        vector<vector<pair<int, int>>>& outLines);
};


class Diamond_UI : public UI<char> {
public:
    Diamond_UI();

    Move<char>* get_move(Player<char>* p) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif
