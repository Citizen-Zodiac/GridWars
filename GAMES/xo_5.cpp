#include <iostream> 
#include <iomanip>
#include <cctype>  // for toupper()
#include "xo_5.h"

using namespace std;




void record_move(int row, int col) {
	xV.push_back(row);
	yV.push_back(col);
}
int get_x_move(int index) {
	return xV[index];
}
int get_y_move(int index) {
	return yV[index];
}




Player<char>** players = new Player<char>*[2];


XO_5_Board::XO_5_Board() : Board(5, 5) {
	// Initialize all cells with blank_symbol
	for (auto& row : board)
		for (auto& cell : row)
			cell = blank_symbol;
}

bool XO_5_Board::update_board(Move<char>* move) {
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

bool XO_5_Board::is_win(Player<char>* player) {
	char mark = toupper(player->get_symbol());
	// Check rows and columns for 3 in a row
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] == mark && board[i][j + 1] == mark && board[i][j + 2] == mark)
			{

				if (player == players[0])
					count1_rows.insert({ i,j });
				else if (player == players[1])
					count2_rows.insert({ i,j });

			}
			if (board[j][i] == mark && board[j + 1][i] == mark && board[j + 2][i] == mark)
			{

				if (player == players[0])
					count1_columns.insert({ j,i });
				else if (player == players[1])
					count2_columns.insert({ j,i });

			}
		}

	}
	// Check diagonals for 3 in a row
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] == mark && board[i + 1][j + 1] == mark && board[i + 2][j + 2] == mark)
			{
				if (player == players[0])
					count1_diags.insert({ i,j });
				else if (player == players[1])
					count2_diags.insert({ i,j });
			}
			if (board[i][j + 2] == mark && board[i + 1][j + 1] == mark && board[i + 2][j] == mark)
			{
				if (player == players[0])
					count1_diags.insert({ i,j + 2 });
				else if (player == players[1])
					count2_diags.insert({ i,j + 2 });
			}
		}
	}
	if (moves_XO_5 == MAX_MOVES_XO_5)
	{
		cout << players[0]->get_name() << ": " << count1_rows.size() + count1_columns.size() + count1_diags.size()
			<< endl << players[1]->get_name() << ": " <<
			count2_rows.size() + count2_columns.size() + count2_diags.size() << endl;


		if (count2_rows.size() + count2_columns.size() + count2_diags.size() >
			count1_rows.size() + count1_columns.size() + count1_diags.size())
		{
			return true;
		}

	}
	return false;

}

bool XO_5_Board::is_lose(Player<char>* player) {
	if (moves_XO_5 == MAX_MOVES_XO_5)

	{
		if (count1_rows.size() + count1_columns.size() + count1_diags.size() >
			count2_rows.size() + count2_columns.size() + count2_diags.size())
		{
			return true;
		}
	}
	return false;
}

bool XO_5_Board::is_draw(Player<char>* player) {
	return n_moves == MAX_MOVES_XO_5 && (count2_rows.size() + count2_columns.size() + count2_diags.size() ==
		count1_rows.size() + count1_columns.size() + count1_diags.size());
}
bool XO_5_Board::game_is_over(Player<char>* player) {
	return is_win(player) || is_draw(player);
}

Player<char>* XO_5_UI::create_player(string& name, char symbol, PlayerType type) {
	return new Player<char>(name, toupper(symbol), type);
}


Player<char>** XO_5_UI::setup_players() {
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

		players[0] = create_player(name1, 'X', PlayerType::HUMAN);
		players[1] = create_player(name2, 'O', PlayerType::HUMAN);
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

		players[human_role - 1] = create_player(human_name, human_symbol, PlayerType::HUMAN);
		players[computer_role - 1] = create_player(computer_name, computer_symbol, PlayerType::COMPUTER);
	}

	return players;
}

XO_5_UI::XO_5_UI() : UI<char>("Welcome to 5x5 X-O!", 3) {}

Move<char>* XO_5_UI::get_move(Player<char>* player) {
	int x, y;
	bool check = false;
	cout << player->get_symbol() << endl;
	int m = xV.size();

	if (player->get_type() == PlayerType::HUMAN)
	{
		cout << player->get_name() << ", enter your move (row and column): ";
		cin >> x >> y;

		for (int i = 0; i < m; i++)
		{
			if (get_x_move(i) == x && get_y_move(i) == y)
			{
				cout << "Cell already occupied. Please enter a different move." << endl;
				check = true;
				break;
			}
		}
		while (cin.fail() || x < 0 || x >= 5 || y < 0 || y >= 5 || check)
		{

			if (!check)
			{
				for (int j = 0; j < m; j++)
				{
					if ((get_x_move(j) == x && get_y_move(j) == y))
					{
						cout << "Cell already occupied. Please enter a different move." << endl;
						break;
					}
				}
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter row (0-4) and column (0-4): ";
			check = false;
			cin >> x >> y;
		}
		bool double_check = false;
		while (!check)
		{
			for (int j = 0; j < m; j++)
			{
				if (get_x_move(j) == x && get_y_move(j) == y)
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
				cout << "Invalid input. Please enter row (0-4) and column (0,4): ";
				double_check = false;
				cin >> x >> y;
			}

		}

		record_move(x, y);
	}

	else if (player->get_type() == PlayerType::COMPUTER) {
		x = rand() % player->get_board_ptr()->get_rows();
		y = rand() % player->get_board_ptr()->get_columns();


		for (int i = 0; i < m; i++)
		{
			if (get_x_move(i) == x && get_y_move(i) == y)
			{
				check = true;
				break;
			}
		}
		while (x < 0 || x >= 5 || y < 0 || y >= 5 || check)
		{

			if (!check)
			{
				for (int j = 0; j < m; j++)
				{
					if ((get_x_move(j) == x && get_y_move(j) == y))
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
				if (get_x_move(j) == x && get_y_move(j) == y)
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

		record_move(x, y);
	}


	moves_XO_5++;
	return new Move<char>(x, y, player->get_symbol());

}