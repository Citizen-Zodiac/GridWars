#ifndef NUMERICAL_TIC_H
#define NUMERICAL_TIC_H

#include "BoardGame_Classes.h"
#include <vector>

class NumericalTicBoard : public Board<int> {
public:
    NumericalTicBoard();
    bool update_board(Move<int>* move) override;
    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>* player) override;
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;
};

class NumericalTicUI : public UI<int> {
public:
    NumericalTicUI(string message, int cell_display_width) : UI<int>(message, cell_display_width) {}
    Move<int>* get_move(Player<int>* player) override;
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;
};

#endif