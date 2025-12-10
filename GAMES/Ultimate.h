#ifndef ULTIMATE_H
#define ULTIMATE_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;


class Ultimate_SubBoard {
private:
    char cells[3][3];
    bool finished;
    char winner; // 'X', 'O', or ' '

    bool three_in_row(char s);

public:
    Ultimate_SubBoard();

    bool place_mark(int r, int c, char s);
    bool is_full() const;
    bool is_finished() const;
    char get_winner() const;

    vector<vector<char>> get_matrix() const;
};


class Ultimate_MainBoard : public Board<char> {
private:
    Ultimate_SubBoard sub[3][3];

    bool main_three_in_row(char s);

public:
    Ultimate_MainBoard();

    // x,y expected 0..8 coordinates (global)
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;

    Ultimate_SubBoard& get_sub(int r, int c);
};


class Ultimate_ComputerPlayer : public Player<char> {
public:
    Ultimate_ComputerPlayer(string name, char symbol);
    Move<char>* get_ultimate_computer_move();
};


class Ultimate_UI : public UI<char> {
public:
    Ultimate_UI();

    Move<char>* get_move(Player<char>* p) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    // Display the full 3x3 of 3x3 sub-boards
    void display_ultimate_board(Ultimate_MainBoard* board);
};


class Ultimate_GameManager {
private:
    Ultimate_MainBoard* board;
    Player<char>* players[2];
    Ultimate_UI* ui;

public:
    Ultimate_GameManager(Ultimate_MainBoard* b, Player<char>* p[2], Ultimate_UI* u)
        : board(b), ui(u)
    {
        players[0] = p[0];
        players[1] = p[1];

        // ensure players know the board pointer
        players[0]->set_board_ptr(b);
        players[1]->set_board_ptr(b);
    }

    void run();
};

#endif 