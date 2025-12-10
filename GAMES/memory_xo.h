#ifndef MEMORY_XO_H
#define MEMORY_XO_H

#include "BoardGame_Classes.h"
#include<vector>
using namespace std;


static vector< int> xV_mem;
static vector< int> yV_mem;


void record_move_mem(int row, int col);
int get_x_move_mem(int index);
int get_y_move_mem(int index);

static vector<vector<char>> real(3,vector<char>(3,'.'));



class Memory_XO_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
    Memory_XO_Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*);
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};


class Memory_XO_UI : public UI<char> {
public:
    Memory_XO_UI();
    virtual Move<char>* get_move(Player<char>* player);
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    Player<char>** setup_players() override;
};

#endif // MEMORY_XO_H
