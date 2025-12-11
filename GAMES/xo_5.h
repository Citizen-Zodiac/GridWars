/**
 * @file xo_5.h
 * @brief Header file for Tic-Tac-Toe 5x5 game classes.
 * @author Mustafa Mahmoud
 *
 * This file provides:
 * - `XO_5_Board`: A specialized board class for the Tic-Tac-Toe game.
 * - `XO_5_UI`: A user interface class tailored to This game setup and player interaction.
 */


#ifndef _XO_5_H
#define _XO_5_H

#include"BoardGame_Classes.h"
#include<vector>
#include<set>
#include<utility>
using namespace std;

/**
* @brief Max moves and counter moves
*/
const int MAX_MOVES_XO_5 = 24;
static int moves_XO_5 = 0;

/*
@brief Vectors to record moves in XO (5x5) game.
*/
static vector< int> xV;
static vector< int> yV;


/*
@brief Record a move in XO (5x5) game.
@param row The row index of the move.
@param col The column index of the move.
*/
void record_move(int row, int col);

/*
@brief Get the x-coordinate of a recorded move in XO (5x5) game.
@param index The index of the move to retrieve.
@return The x-coordinate of the move.
*/
int get_x_move(int index);
/*
@brief Get the y-coordinate of a recorded move in XO (5x5) game.
@param index The index of the move to retrieve.
@return The y-coordinate of the move.
*/
int get_y_move(int index);



/**
* @brief numbers of wins for player onw
*/
static set<pair<int, int>> count1_rows;
static set<pair<int, int>> count1_columns;
static set<pair<int, int>> count1_diags;

/**
* @brief numbers of wins for player two
*/
static set<pair<int, int>> count2_rows;
static set<pair<int, int>> count2_columns;
static set<pair<int, int>> count2_diags;



/**
 * @class XO_5_Board
 * @brief Specialized board class for the XO (5x5) game.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for XO (5x5),
 * including move updates and win/loss/draw conditions.
 *
 * @see Board
 */
class XO_5_Board : public Board<char> {
private:
	char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
	/**
	 * @brief Default constructor initializing a XO (5x5) board.
	*/
	XO_5_Board();

	/**
	* @brief Updates the board with a player's move.
	* @param move Pointer to a Move<char> object containing move coordinates and symbol.
	* @return true if the move is valid and successfully applied, false otherwise.
	*/
	bool update_board(Move<char>* move) override;

	/**
	* @brief Checks if the given player has won the game.
	* @param player Pointer to the player being checked.
	* @return true if the player has a winning line, false otherwise.
	*/
	bool is_win(Player<char>* player) override;

	/**
	* @brief Checks if the given player has lost the game.
	* @param player Pointer to the player being checked.
	* @return Always returns false as losing is not explicitly tracked in XO (5x5).
	*/
	bool is_lose(Player<char>* player) override;

	/**
	* @brief Checks if the game has ended in a draw.
	* @param player Pointer to the player being checked.
	* @return true if the board is full and no player has won, false otherwise.
	*/
	bool is_draw(Player<char>* player) override;

	/**
   * @brief Determines if the game is over (win or draw).
   * @param player Pointer to the player to evaluate.
   * @return true if the game has ended, false otherwise.
   */
	bool game_is_over(Player<char>* player) override;
};


/**
 * @class XO_5_UI
 * @brief User interface class for the XO (5x5) game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * XO (5x5)-specific implementations for player setup and move retrieval.
 *
 * @see UI
 */
class XO_5_UI : public UI<char> {
public:
	/**
	 * @brief Default constructor for the XO (5x5) UI.
	*/
	XO_5_UI();

	/**
	* @brief Retrieves the next move from a player.
	* @param player Pointer to the player whose move is being requested.
	* @return A pointer to a new `Move<char>` object representing the player's action.
	*/
	Move<char>* get_move(Player<char>* player) override;

	/**
	 * @brief Creates a player of the specified type.
	 * @param name Name of the player.
	 * @param symbol Character symbol ('X' or 'O') assigned to the player.
	 * @param type The type of the player (Human or Computer).
	 * @return Pointer to the newly created Player<char> instance.
	 */
	Player<char>* create_player(string& name, char symbol, PlayerType type) override;

	/*
	@brief Sets up the players for the XO (5x5) game.
	@return An array of pointers to the created Player<char> instances.
	*/
	Player<char>** setup_players() override;
};



#endif