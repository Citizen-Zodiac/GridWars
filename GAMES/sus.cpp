#include <iostream> 
#include <iomanip>
#include <cctype>  // for toupper()
#include "sus.h"

using namespace std;




void record_move_sus(int row, int col) {
	xVs.push_back(row);
	yVs.push_back(col);
}
int get_x_move_sus(int index) {
	return xVs[index];
}
int get_y_move_sus(int index) {
	return yVs[index];
}




Player<char>** players_sus = new Player<char>*[2];


SUS_Board::SUS_Board() : Board(3, 3) {
	// Initialize all cells with blank_symbol
	for (auto& row : board)
		for (auto& cell : row)
			cell = blank_symbol;
}

bool SUS_Board::update_board(Move<char>* move) {
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

bool SUS_Board::is_win(Player<char>* player) {
	// Check rows and columns for 3 in a row
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 1; ++j) {
			if (board[i][j] == players_sus[0]->get_symbol() && board[i][j + 1] == players_sus[1]->get_symbol() && board[i][j + 2] == players_sus[0]->get_symbol())
			{

				if (player == players_sus[0]&& count2_rows_sus.find({i,j}) == count2_rows_sus.end())
					count1_rows_sus.insert({ i,j });
				else if (player == players_sus[1] && count1_rows_sus.find({i,j})== count1_rows_sus.end())
					count2_rows_sus.insert({ i,j });

			}
			if (board[j][i] == players_sus[0]->get_symbol() && board[j + 1][i] == players_sus[1]->get_symbol() && board[j + 2][i] == players_sus[0]->get_symbol())
			{

				if (player == players_sus[0] && count2_columns_sus.find({j,i})==count2_columns_sus.end())
					count1_columns_sus.insert({ j,i });
				else if (player == players_sus[1]&&count1_columns_sus.find({j,i})==count1_columns_sus.end())
					count2_columns_sus.insert({ j,i });

			}
		}

	}
	// Check diagonals for 3 in a row
	for (int i = 0; i < 1; ++i) {
		for (int j = 0; j < 1; ++j) {
			if (board[i][j] == players_sus[0]->get_symbol() && board[i + 1][j + 1] == players_sus[1]->get_symbol() && board[i + 2][j + 2] == players_sus[0]->get_symbol())
			{
				if (player == players_sus[0] && count2_diags_sus.find({ i,j }) == count2_diags_sus.end())
					count1_diags_sus.insert({ i,j });
				else if (player == players_sus[1] && count1_diags_sus.find({i,j}) == count1_diags_sus.end())
					count2_diags_sus.insert({ i,j });
			}
			if (board[i][j + 2] == players_sus[0]->get_symbol() && board[i + 1][j + 1] == players_sus[1]->get_symbol() && board[i + 2][j] == players_sus[0]->get_symbol())
			{
				if (player == players_sus[0]&& count2_diags_sus.find({i,j+2}) == count2_diags_sus.end())
					count1_diags_sus.insert({ i,j + 2 });
				else if (player == players_sus[1]&& count1_diags_sus.find({i,j+2}) == count1_diags_sus.end())
					count2_diags_sus.insert({ i,j + 2 });
			}
		}
	}
	if (moves_sus == MAX_MOVES_SUS)
	{
		cout << players_sus[0]->get_name() << ": " << count1_rows_sus.size() + count1_columns_sus.size() + count1_diags_sus.size()
			<< endl << players_sus[1]->get_name() << ": " <<
			count2_rows_sus.size() + count2_columns_sus.size() + count2_diags_sus.size() << endl;


		if (count1_rows_sus.size() + count1_columns_sus.size() + count1_diags_sus.size() >
			count2_rows_sus.size() + count2_columns_sus.size() + count2_diags_sus.size())
		{
			return true;
		}

	}
	return false;

}

bool SUS_Board::is_lose(Player<char>* player) {
	if (moves_sus == MAX_MOVES_SUS)

	{
		if (count2_rows_sus.size() + count2_columns_sus.size() + count2_diags_sus.size() >
			count1_rows_sus.size() + count1_columns_sus.size() + count1_diags_sus.size())
		{
			return true;
		}
	}
	return false;
}

bool SUS_Board::is_draw(Player<char>* player) {
	return n_moves == MAX_MOVES_SUS && (count2_rows_sus.size() + count2_columns_sus.size() + count2_diags_sus.size() ==
		count1_rows_sus.size() + count1_columns_sus.size() + count1_diags_sus.size());
}
bool SUS_Board::game_is_over(Player<char>* player) {
	return is_win(player) || is_draw(player);
}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
	return new Player<char>(name, toupper(symbol), type);
}


Player<char>** SUS_UI::setup_players() {
	int game_mode;

	cout << "Choose game mode:\n1. Human vs Human\n2. Human vs Computer\nChoose: ";
	cin >> game_mode;

	if (game_mode == 1) {
		// Human vs Human
		string name1, name2;
		cout << "Enter Player 1 name (S): ";
		cin >> name1;
		cout << "Enter Player 2 name (U): ";
		cin >> name2;

		players_sus[0] = create_player(name1, 'S', PlayerType::HUMAN);
		players_sus[1] = create_player(name2, 'U', PlayerType::HUMAN);
	}
	else {
		// Human vs Computer 
		string name;
		int side_choice;

		cout << "Choose your side:\n1. S\n2. U\nChoose: ";
		cin >> side_choice;

		cout << "Enter your name: ";
		cin >> name;

		char human_symbol, computer_symbol;
		int human_role, computer_role;

		if (side_choice == 1) {
			human_symbol = 'S';
			computer_symbol = 'U';
			human_role = 1;
			computer_role = 2;
		}
		else {
			human_symbol = 'U';
			computer_symbol = 'S';
			human_role = 2;
			computer_role = 1;
		}

		string human_name = name;
		string computer_name = "Computer" ;

		players_sus[human_role - 1] = create_player(human_name, human_symbol, PlayerType::HUMAN);
		players_sus[computer_role - 1] = create_player(computer_name, computer_symbol, PlayerType::COMPUTER);
	}

	return players_sus;
}

SUS_UI::SUS_UI() : UI<char>("Welcome to SUS!", 3) {}

Move<char>* SUS_UI::get_move(Player<char>* player) {
	int x, y;
	bool check = false;
	int m = xVs.size();

	if (player->get_type() == PlayerType::HUMAN)
	{
		cout << player->get_name() << ", enter your move (row and column): ";
		cin >> x >> y;

		for (int i = 0; i < m; i++)
		{
			if (get_x_move_sus(i) == x && get_y_move_sus(i) == y)
			{
				cout << "Cell already occupied. Please enter a different move." << endl;
				check = true;
				break;
			}
		}
		while (cin.fail() || x < 0 || x >= 3 || y < 0 || y >=3 || check)
		{

			if (!check)
			{
				for (int j = 0; j < m; j++)
				{
					if ((get_x_move_sus(j) == x && get_y_move_sus(j) == y))
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
		}
		bool double_check = false;
		while (!check)
		{
			for (int j = 0; j < m; j++)
			{
				if (get_x_move_sus(j) == x && get_y_move_sus(j) == y)
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
			}

		}

		record_move_sus(x, y);
	}

	else if (player->get_type() == PlayerType::COMPUTER) {
		x = rand() % player->get_board_ptr()->get_rows();
		y = rand() % player->get_board_ptr()->get_columns();


		for (int i = 0; i < m; i++)
		{
			if (get_x_move_sus(i) == x && get_y_move_sus(i) == y)
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
					if ((get_x_move_sus(j) == x && get_y_move_sus(j) == y))
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
				if (get_x_move_sus(j) == x && get_y_move_sus(j) == y)
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

		record_move_sus(x, y);
	}


	moves_sus++;
	return new Move<char>(x, y, player->get_symbol());

}