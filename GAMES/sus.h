#ifndef _SUS_H
#define _SUS_H

#include"BoardGame_Classes.h"
#include<vector>
#include<set>
#include<utility>
using namespace std;

const int MAX_MOVES_SUS = 9;
static int moves_sus = 0;

static vector< int> xVs;
static vector< int> yVs;


void record_move_sus(int row, int col);
int get_x_move_sus(int index);
int get_y_move_sus(int index);



static set<pair<int, int>> count1_rows_sus;
static set<pair<int, int>> count1_columns_sus;
static set<pair<int, int>> count1_diags_sus;

static set<pair<int, int>> count2_rows_sus;
static set<pair<int, int>> count2_columns_sus;
static set<pair<int, int>> count2_diags_sus;

class SUS_Board : public Board<char> {
private:
	char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
	SUS_Board();
	bool update_board(Move<char>* move) override;
	bool is_win(Player<char>* player) override;
	bool is_lose(Player<char>* player) override;
	bool is_draw(Player<char>* player) override;
	bool game_is_over(Player<char>* player) override;
};

class SUS_UI : public UI<char> {
public:
	SUS_UI();
	Move<char>* get_move(Player<char>* player) override;
	Player<char>* create_player(string& name, char symbol, PlayerType type) override;
	Player<char>** setup_players() override;
};



#endif