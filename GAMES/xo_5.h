#ifndef _XO_5_H
#define _XO_5_H

#include"BoardGame_Classes.h"
#include<vector>
#include<set>
#include<utility>
using namespace std;

const int MAX_MOVES_XO_5 = 24;
static int moves_XO_5 = 0;

static vector< int> xV;
static vector< int> yV;


void record_move(int row, int col);
int get_x_move(int index);
int get_y_move(int index);



static set<pair<int, int>> count1_rows;
static set<pair<int, int>> count1_columns;
static set<pair<int, int>> count1_diags;

static set<pair<int, int>> count2_rows;
static set<pair<int, int>> count2_columns;
static set<pair<int, int>> count2_diags;

class XO_5_Board : public Board<char> {
private:
	char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
	XO_5_Board();
	bool update_board(Move<char>* move) override;
	bool is_win(Player<char>* player) override;
	bool is_lose(Player<char>* player) override;
	bool is_draw(Player<char>* player) override;
	bool game_is_over(Player<char>* player) override;
};

class XO_5_UI : public UI<char> {
	public:
		XO_5_UI();
	Move<char>* get_move(Player<char>* player) override;
	Player<char>* create_player(string& name, char symbol, PlayerType type) override;
	Player<char>** setup_players() override;
};



#endif