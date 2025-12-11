#include <iostream> 
#include <iomanip>
#include <cctype>  // for toupper()
#include "connect_four.h"
#include<limits>

using namespace std;

void record_move_four(int row, int col) {
	xV_four.push_back(row);
	yV_four.push_back(col);
}
int get_x_move_four(int index) {
	return xV_four[index];
}
int get_y_move_four(int index) {
	return yV_four[index];
}


Player<char>** players_four = new Player<char>*[2];


Four_Board::Four_Board() : Board(6, 7) {
	// Initialize all cells with blank_symbol
	for (auto& row : board)
		for (auto& cell : row)
			cell = blank_symbol;
}

bool Four_Board::update_board(Move<char>* move) {
	int x = move->get_x();
	int y = move->get_y();
	char mark = move->get_symbol();

	// Validate move and apply if valid
	if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
		(board[x][y] == mark == 0)) {

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

bool Four_Board::is_win(Player<char>* player) {
	char mark = toupper(player->get_symbol());
	// Check rows and columns for 4 in a row
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] == mark && board[i][j + 1] == mark && board[i][j + 2] == mark && board[i][j + 3] == mark)
			{
				return true;
			}
			if (board[j][i] == mark && board[j + 1][i] == mark && board[j + 2][i] == mark && board[j + 3][i] == mark)
			{
				return true;
			}
		}

	}
	// Check diagonals for 4 in a row
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] == mark && board[i + 1][j + 1] == mark && board[i + 2][j + 2] == mark && board[i + 3][j + 3] == mark)
			{
				return true;
			}
			if (board[i][j + 3] == mark && board[i + 1][j + 2] == mark && board[i + 2][j + 1] == mark && board[i + 3][j] == mark)
			{
				return true;
			}
		}
	}

	return false;

}

bool Four_Board::is_lose(Player<char>* player) {
	return false;
}

bool Four_Board::is_draw(Player<char>* player) {

	return (n_moves == 42 && !is_win(player));
}
bool Four_Board::game_is_over(Player<char>* player) {
	return is_win(player) || is_draw(player);
}

Player<char>* Four_UI::create_player(string& name, char symbol, PlayerType type) {
	return new Player<char>(name, toupper(symbol), type);
}


Player<char>** Four_UI::setup_players() {
	int game_mode;

	cout << "Choose game mode:\n1. Human vs Human\n2. Human vs Computer\nChoose: ";
	cin >> game_mode;

	if (game_mode == 1) {
		// Human vs Human
		string name1, name2;
		cout << "Enter Player 1 name (X): ";
		cin >> name1;
		cout << "Enter Player 2 name (O): ";
		cin >> name2;

		players_four[0] = create_player(name1, 'X', PlayerType::HUMAN);
		players_four[1] = create_player(name2, 'O', PlayerType::HUMAN);
	}

	else {
		// Human vs Computer 
		string name;
		int side_choice;

		cout << "Choose your side:\n1. X\n2. O\nChoose: ";
		cin >> side_choice;

		cout << "Enter your name: ";
		cin >> name;

		char human_symbol, computer_symbol;
		int human_role, computer_role;

		if (side_choice == 1) {
			human_symbol = 'X';
			computer_symbol = 'O';
			human_role = 1;
			computer_role = 2;
		}
		else {
			human_symbol = 'O';
			computer_symbol = 'X';
			human_role = 2;
			computer_role = 1;
		}

		string human_name = name;
		string computer_name = "Computer";

		players_four[human_role - 1] = create_player(human_name, human_symbol, PlayerType::HUMAN);
		players_four[computer_role - 1] = create_player(computer_name, computer_symbol, PlayerType::COMPUTER);
	}

	return players_four;
}

Four_UI::Four_UI() : UI<char>("Welcome to Connect Four (Tic-Tac-Toe)!", 3) {}

Move<char>* Four_UI::get_move(Player<char>* player) 
{
	int x, y;
	bool check = false;
	cout << player->get_name() << ": " << player->get_symbol() << endl;
	int m = xV_four.size();

	if (player->get_type() == PlayerType::HUMAN)
	{
		cout << player->get_name() << ", enter your move (row and column): ";
		cin >> x >> y;

		for (int i = 0; i < m; i++)
		{
			if (get_x_move_four(i) == x && get_y_move_four(i) == y)
			{
				cout << "Cell already occupied. Please enter a different move." << endl;
				check = true;
				break;
			}
		}
		while (cin.fail() || x < 0 || x >= 6 || y < 0 || y >= 7 || check)
		{

			if (!check)
			{
				for (int j = 0; j < m; j++)
				{
					if ((get_x_move_four(j) == x && get_y_move_four(j) == y))
					{
						cout << "Cell already occupied. Please enter a different move." << endl;
						break;
					}
				}
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter row (0-5) and column (0-6): ";
			check = false;
			cin >> x >> y;
		}
		bool double_check = false;
		while (!check)
		{
			for (int j = 0; j < m; j++)
			{
				if (get_x_move_four(j) == x && get_y_move_four(j) == y)
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
				cout << "Invalid input. Please enter row (0-5) and column (0,6): ";
				double_check = false;
				cin >> x >> y;
			}

		}
		for (int i = 5; i >= 0; i--)
		{
			if (player->get_board_ptr()->get_cell(i, y) == '.')
			{
				record_move_four(i, y);
				x = i;
				break;
			}
		}
	}

	else if (player->get_type() == PlayerType::COMPUTER)
	{
		x = rand() % player->get_board_ptr()->get_rows();
		y = rand() % player->get_board_ptr()->get_columns();


		for (int i = 0; i < m; i++)
		{
			if (get_x_move_four(i) == x && get_y_move_four(i) == y)
			{
				check = true;
				break;
			}
		}
		while (x < 0 || x >= 6 || y < 0 || y >= 7 || check)
		{

			if (!check)
			{
				for (int j = 0; j < m; j++)
				{
					if ((get_x_move_four(j) == x && get_y_move_four(j) == y))
					{
						break;
					}
				}
			}

			check = false;
			x = rand() % player->get_board_ptr()->get_rows();
			y = rand() % player->get_board_ptr()->get_columns();
		}
		bool double_check = false;
		while (!check)
		{
			for (int j = 0; j < m; j++)
			{
				if (get_x_move_four(j) == x && get_y_move_four(j) == y)
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
			}

		}
		for (int i = 5; i >= 0; i--)
		{
			if (player->get_board_ptr()->get_cell(i, y) == '.')
			{
				record_move_four(i, y);
				x = i;
				break;
			}
		}
	}
		return new Move<char>(x, y, player->get_symbol());

}
