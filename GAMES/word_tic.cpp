#include <iostream> 
#include <iomanip>
#include <cctype>  // for toupper()
#include "word_tic.h"
#include<limits>
#include<cstdlib>
#include<ctime>

using namespace std;

void record_move_word(int row, int col) {
	xV_word.push_back(row);
	yV_word.push_back(col);
}
int get_x_move_word(int index) {
	return xV_word[index];
}
int get_y_move_word(int index) {
	return yV_word[index];
}

void load_dictionary() {
	ifstream file("C:\\Users\\musta\\Documents\\A3_Grid_Wars\\dic.txt");
	string word;
	while (file >> word) {
		dictionary.insert(word);
	}
}

bool is_valid_word(const string& w) {
	return dictionary.count(w) > 0;
}

char random_letter()
{
	return 'A' + (rand() % 26);
}


Player<char>** players_word = new Player<char>*[2];
char letter;

bool Word_Board::update_board(Move<char>* move) {
	int x = move->get_x();
	int y = move->get_y();
	char mark = letter;

	// Validate move and apply if valid
	if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
		(board[x][y] == blank_symbol || mark == 0)) {

		if (mark == 0) { // Undo move
			n_moves--;
			board[x][y] = blank_symbol;
		}
		else {         // Apply move
			n_moves++;
			board[x][y] = toupper(mark);
		}
		return true;
	}
	return false;
}

Word_Board::Word_Board() : Board(3, 3) {
	// Initialize all cells with blank_symbol
	for (auto& row : board)
		for (auto& cell : row)
			cell = blank_symbol;
}


bool Word_Board::is_win(Player<char>* player) {
	load_dictionary();

	// Check rows 
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 1; ++j) {
			string w = "";
			w += board[i][j];
			w += board[i][j + 1];
			w += board[i][j + 2];
			if (is_valid_word(w))
			{
				return true;
			}

		}
	}
	// Check Columns
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 1; ++j) {
			string w = "";
			w += board[j][i];
			w += board[j + 1][i];
			w += board[j + 2][i];

			if (is_valid_word(w))
			{
				return true;
			}

		}
	}
	
	// Check diagonals for 3 in a row
	for (int i = 0; i < 1; ++i) {
		for (int j = 0; j < 1; ++j) {
			string w = "";
			w += board[i][j];
			w += board[i+1][j + 1];
			w += board[i+2][j + 2];
			if (is_valid_word(w))
			{
				return true;
			}
			

		}
	}

	for (int i = 0; i < 1; ++i) {
		for (int j = 0; j < 1; ++j) {
			string w = "";
			w += board[i][j+2];
			w += board[i + 1][j + 1];
			w += board[i + 2][j];

			if (is_valid_word(w))
			{
				return true;
			}

		}
	}
	return false;
}

bool Word_Board::is_lose(Player<char>* player) {
	return false;
}

bool Word_Board::is_draw(Player<char>* player) {
	return (n_moves == 9 && !is_win(player));
}

bool Word_Board::game_is_over(Player<char>* player) {
	return is_win(player) || is_draw(player);
}

Player<char>* Word_UI::create_player(string& name, char symbol, PlayerType type) {
	return new Player<char>(name, toupper(symbol), type);
}


Player<char>** Word_UI::setup_players() {
	int game_mode;

	cout << "Choose game mode:\n1. Human vs Human\n2. Human vs Computer\nChoose: ";
	cin >> game_mode;

	if (game_mode == 1) {
		// Human vs Human
		string name1, name2;
		cout << "Enter Player 1 name : ";
		cin >> name1;
		cout << "Enter Player 2 name : ";
		cin >> name2;
		char human_symbol1 = '$', human_symbol2 = '#';

		players_word[0] = create_player(name1, human_symbol1, PlayerType::HUMAN);
		players_word[1] = create_player(name2, human_symbol2, PlayerType::HUMAN);
	}
	else {
		// Human vs Computer 
		string name;
		
		cout << "Enter your name: ";
		cin >> name;

		string human_name = name;
		string computer_name = "Computer";

		players_word[0] = create_player(human_name, '$', PlayerType::HUMAN);
		players_word[1] = create_player(computer_name, '#', PlayerType::COMPUTER);
	}

	return players_word;
}

Word_UI::Word_UI() : UI<char>("Welcome to Word (Tic-Tac-Toe)!", 3) {}

Move<char>* Word_UI::get_move(Player<char>* player) {
	int x, y;
	bool check = false;
	int m = xV_word.size();

	if (player->get_type() == PlayerType::HUMAN)
	{
		cout << player->get_name() << ", enter your move (row and column): ";
		cin >> x >> y;
		cin >> letter;

		for (int i = 0; i < m; i++)
		{
			if (get_x_move_word(i) == x && get_y_move_word(i) == y)
			{
				cout << "Cell already occupied. Please enter a different move." << endl;
				check = true;
				break;
			}
		}
		while (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3 || check)
		{

			if (!check)
			{
				for (int j = 0; j < m; j++)
				{
					if ((get_x_move_word(j) == x && get_y_move_word(j) == y))
					{
						cout << "Cell already occupied. Please enter a different move." << endl;
						break;
					}
				}
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter row (0-2) and column (0-2): ";
			check = false;
			cin >> x >> y;
			cin >> letter;
		}
		bool double_check = false;
		while (!check)
		{
			for (int j = 0; j < m; j++)
			{
				if (get_x_move_word(j) == x && get_y_move_word(j) == y)
				{
					cout << "Cell already occupied. Please enter a different move." << endl;
					double_check = true;
					break;
				}
			}
			if (!double_check)
			{
				check = true;
				break;
			}
			if (double_check)
			{

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter row (0-2) and column (0,2): ";
				double_check = false;
				cin >> x >> y;
				cin >> letter;
			}

		}

		record_move_word(x, y);
	}

	else if (player->get_type() == PlayerType::COMPUTER) {
		x = rand() % player->get_board_ptr()->get_rows();
		y = rand() % player->get_board_ptr()->get_columns();
		letter=random_letter();

		for (int i = 0; i < m; i++)
		{
			if (get_x_move_word(i) == x && get_y_move_word(i) == y)
			{
				check = true;
				break;
			}
		}
		while (x < 0 || x >= 3 || y < 0 || y >= 3 || check)
		{

			if (!check)
			{
				for (int j = 0; j < m; j++)
				{
					if ((get_x_move_word(j) == x && get_y_move_word(j) == y))
					{
						break;
					}
				}
			}

			check = false;
			x = rand() % player->get_board_ptr()->get_rows();
			y = rand() % player->get_board_ptr()->get_columns();
			letter=random_letter();
		}
		bool double_check = false;
		while (!check)
		{
			for (int j = 0; j < m; j++)
			{
				if (get_x_move_word(j) == x && get_y_move_word(j) == y)
				{
					double_check = true;
					break;
				}
			}
			if (!double_check)
			{
				check = true;
				break;
			}
			if (double_check)
			{

				double_check = false;
				x = rand() % player->get_board_ptr()->get_rows();
				y = rand() % player->get_board_ptr()->get_columns();
				letter=random_letter();
			}

		}

		record_move_word(x, y);
	}

	return new Move<char>(x, y,letter );

}