#ifndef PYRAMID_TICTACTOE_H
#define PYRAMID_TICTACTOE_H

#include "BoardGame_Classes.h"


class PyramidTicTacToeBoard : public Board<char> {
private:
    static const int MAX_MOVES = 9;
    int movesCount;

    bool isValidPosition(int row, int col) const;
    bool checkWin() const;
    bool checkHorizontal() const;
    bool checkVertical() const;
    bool checkDiagonal() const;

public:
    PyramidTicTacToeBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class PyramidTicTacToeUI : public UI<char> {
public:
    PyramidTicTacToeUI();
    Player<char>** setup_players() override;
    Move<char>* get_move(Player<char>* player) override;
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};

#endif // PYRAMID_TICTACTOE_H