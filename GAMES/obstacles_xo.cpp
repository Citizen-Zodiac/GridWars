#include <iostream> 
#include <iomanip>
#include <cctype>  // for toupper()
#include "obstacles_xo.h"

using namespace std;

void record_move_obs(int row, int col) {
	xV_obs.push_back(row);
	yV_obs.push_back(col);
}
int get_x_move_obs(int index) {
	return xV_obs[index];
}
int get_y_move_obs(int index) {
	return yV_obs[index];
}


Player<char>** players_obs = new Player<char>*[2];


Obstacles_XO_Board::Obstacles_XO_Board() : Board(6, 6) {
	// Initialize all cells with blank_symbol
	for (auto& row : board)
		for (auto& cell : row)
			cell = blank_symbol;
}

bool Obstacles_XO_Board::update_board(Move<char>* move) {
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

bool Obstacles_XO_Board::is_win(Player<char>* player) {
	char mark = toupper(player->get_symbol());
	// Check rows and columns for 3 in a row
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
	// Check diagonals for 3 in a row
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

bool Obstacles_XO_Board::is_lose(Player<char>* player) {
	return false;
}

bool Obstacles_XO_Board::is_draw(Player<char>* player) {

	return (n_moves == 18 && !is_win(player));
}
bool Obstacles_XO_Board::game_is_over(Player<char>* player) {
	return is_win(player) || is_draw(player);
}

Player<char>* Obstacles_XO_UI::create_player(string& name, char symbol, PlayerType type) {
	return new Player<char>(name, toupper(symbol), type);
}


Player<char>** Obstacles_XO_UI::setup_players() {
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

		players_obs[0] = create_player(name1, 'X', PlayerType::HUMAN);
		players_obs[1] = create_player(name2, 'O', PlayerType::HUMAN);
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

		players_obs[human_role - 1] = create_player(human_name, human_symbol, PlayerType::HUMAN);
		players_obs[computer_role - 1] = create_player(computer_name, computer_symbol, PlayerType::COMPUTER);
	}

	return players_obs;
}

Obstacles_XO_UI::Obstacles_XO_UI() : UI<char>("Welcome to Obstacles X-O!", 3) {}

Move<char>* Obstacles_XO_UI::get_move(Player<char>* player) {
	int x, y;
	bool check = false;
	cout << player->get_name() << ": " << player->get_symbol() << endl;
	int m = xV_obs.size();

	if (player->get_type() == PlayerType::HUMAN)
	{
		cout << player->get_name() << ", enter your move (row and column): ";
		cin >> x >> y;

		for (int i = 0; i < m; i++)
		{
			if (get_x_move_obs(i) == x && get_y_move_obs(i) == y)
			{
				cout << "Cell already occupied. Please enter a different move." << endl;
				check = true;
				break;
			}
		}
		while (cin.fail() || x < 0 || x >= 6 || y < 0 || y >= 6 || check)
		{

			if (!check)
			{
				for (int j = 0; j < m; j++)
				{
					if ((get_x_move_obs(j) == x && get_y_move_obs(j) == y))
					{
						cout << "Cell already occupied. Please enter a different move." << endl;
						break;
					}
				}
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter row (0-5) and column (0-5): ";
			check = false;
			cin >> x >> y;
		}
		bool double_check = false;
		while (!check)
		{
			for (int j = 0; j < m; j++)
			{
				if (get_x_move_obs(j) == x && get_y_move_obs(j) == y)
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
				cout << "Invalid input. Please enter row (0-5) and column (0,5): ";
				double_check = false;
				cin >> x >> y;
			}

		}

		record_move_obs(x, y);
	}

	else if (player->get_type() == PlayerType::COMPUTER) {
		x = rand() % player->get_board_ptr()->get_rows();
		y = rand() % player->get_board_ptr()->get_columns();


		for (int i = 0; i < m; i++)
		{
			if (get_x_move_obs(i) == x && get_y_move_obs(i) == y)
			{
				check = true;
				break;
			}
		}
		while (x < 0 || x >= 6 || y < 0 || y >= 6 || check)
		{

			if (!check)
			{
				for (int j = 0; j < m; j++)
				{
					if ((get_x_move_obs(j) == x && get_y_move_obs(j) == y))
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
				if (get_x_move_obs(j) == x && get_y_move_obs(j) == y)
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
		record_move_obs(x, y);
	}
	rounds_obstacles++;

	// obstacles
	if (rounds_obstacles == 2)
	{
		check = false;
		int l, k, w, z;
		m = xV_obs.size();

		l = rand() % player->get_board_ptr()->get_rows();
		k = rand() % player->get_board_ptr()->get_columns();


		for (int i = 0; i < m; i++)
		{
			if (get_x_move_obs(i) == l && get_y_move_obs(i) == k)
			{
				check = true;
				break;
			}
		}
		while (l < 0 || l >= 6 || k < 0 || k >= 6 || check)
		{

			if (!check)
			{
				for (int j = 0; j < m; j++)
				{
					if ((get_x_move_obs(j) == l && get_y_move_obs(j) == k))
					{
						break;
					}
				}
			}

			check = false;
			l = rand() % player->get_board_ptr()->get_rows();
			k = rand() % player->get_board_ptr()->get_columns();
		}
		bool double_check = false;
		while (!check)
		{
			for (int j = 0; j < m; j++)
			{
				if (get_x_move_obs(j) == l && get_y_move_obs(j) == k)
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
				l = rand() % player->get_board_ptr()->get_rows();
				k = rand() % player->get_board_ptr()->get_columns();
			}

		}

		record_move_obs(l, k);

		m = xV_obs.size();
		check = false;
		w = rand() % player->get_board_ptr()->get_rows();
		z = rand() % player->get_board_ptr()->get_columns();


		for (int i = 0; i < m; i++)
		{
			if (get_x_move_obs(i) == w && get_y_move_obs(i) == z)
			{
				check = true;
				break;
			}
		}
		while (w < 0 || w >= 6 || z < 0 || z >= 6 || check)
		{

			if (!check)
			{
				for (int j = 0; j < m; j++)
				{
					if ((get_x_move_obs(j) == w && get_y_move_obs(j) == z))
					{
						break;
					}
				}
			}

			check = false;
			w = rand() % player->get_board_ptr()->get_rows();
			z = rand() % player->get_board_ptr()->get_columns();
		}

		double_check = false;
		while (!check)
		{
			for (int j = 0; j < m; j++)
			{
				if (get_x_move_obs(j) == w && get_y_move_obs(j) == z)
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
				w = rand() % player->get_board_ptr()->get_rows();
				z = rand() % player->get_board_ptr()->get_columns();
			}

		}

		record_move_obs(w, z);
		rounds_obstacles = 0;
		player->get_board_ptr()->update_board(new Move<char>(l, k, '#'));
		player->get_board_ptr()->update_board(new Move<char>(w, z, '#'));

		return new Move<char>(x, y, player->get_symbol());
	}
	return new Move<char>(x, y, player->get_symbol());

}