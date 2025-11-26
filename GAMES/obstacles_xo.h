#ifndef _OBSTACLES_XO_H
#define _OBSTACLES_XO_H

#include"BoardGame_Classes.h"
#include<vector>
using namespace std;



static vector< int> xV_obs;
static vector< int> yV_obs;


void record_move_obs(int row, int col);
int get_x_move_obs(int index);
int get_y_move_obs(int index);



static int rounds_obstacles = 0;

class Obstacles_XO_Board : public Board<char> {
private:
	char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
	Obstacles_XO_Board();
	bool update_board(Move<char>* move) override;
	bool is_win( Player<char>* player) override;
	bool is_lose(Player<char>* player) override;
	bool is_draw(Player<char>* player) override;
	bool game_is_over(Player<char>* player) override;
};

class Obstacles_XO_UI : public UI<char> {
public:
	Obstacles_XO_UI();
	Move<char>* get_move(Player<char>* player) override;
	Player<char>* create_player(string& name, char symbol, PlayerType type) override;
	Player<char>** setup_players() override;
};

#endif // !_OBSTACLES_XO_H
