#ifndef _CONNECT_FOUR_H
#define _CONNECT_FOUR_H

#include"BoardGame_Classes.h"
#include<vector>
using namespace std;



static vector< int> xV_four;
static vector< int> yV_four;


void record_move_four(int row, int col);
int get_x_move_four(int index);
int get_y_move_four(int index);



class Four_Board : public Board<char> {
private:
	char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
	Four_Board();
	bool update_board(Move<char>* move) override;
	bool is_win(Player<char>* player) override;
	bool is_lose(Player<char>* player) override;
	bool is_draw(Player<char>* player) override;
	bool game_is_over(Player<char>* player) override;
};

class Four_UI : public UI<char> {
public:
	Four_UI();
	Move<char>* get_move(Player<char>* player) override;
	Player<char>* create_player(string& name, char symbol, PlayerType type) override;
	Player<char>** setup_players() override;
};

#endif 