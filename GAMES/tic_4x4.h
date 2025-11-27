#ifndef _TIC_4X4_H
#define _TIC_4X4_H

#include "BoardGame_Classes.h"

class tic_4x4_Board : public Board<char> {
private:
    char current_player = 'X';

public:
    tic_4x4_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    // Special methods for our game
    bool move_token(int fromX, int fromY, int toX, int toY, char symbol);
    bool is_valid_move(int fromX, int fromY, int toX, int toY, char symbol) const;
    void switch_player();
    char get_current_player() const { return current_player; }
};

class tic_4x4_UI : public UI<char> {
private:
    tic_4x4_Board* board;

public:
    tic_4x4_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>** setup_players() override;

    void set_board(tic_4x4_Board* b) { board = b; }
};

#endif