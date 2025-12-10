#ifndef _WORD_TIC_H
#define _WORD_TIC_H

#include"BoardGame_Classes.h"
#include<vector>
#include<set>
#include<unordered_set>
#include<fstream>

using namespace std;

static vector< int> xV_word;
static vector< int> yV_word;


void record_move_word(int row, int col);
int get_x_move_word(int index);
int get_y_move_word(int index);

static unordered_set<std::string> dictionary;

void load_dictionary();
bool is_valid_word(const std::string& w);

char random_letter();


class Word_Board : public Board<char> {
private:
	char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
	Word_Board();
	bool update_board(Move<char>* move) override;
	bool is_win(Player<char>* player) override;
	bool is_lose(Player<char>* player) override;
	bool is_draw(Player<char>* player) override;
	bool game_is_over(Player<char>* player) override;
};

class Word_UI : public UI<char> {
public:
	Word_UI();
	Move<char>* get_move(Player<char>* player) override;
	Player<char>* create_player(string& name, char symbol, PlayerType type) override;
	Player<char>** setup_players() override;
};


#endif
