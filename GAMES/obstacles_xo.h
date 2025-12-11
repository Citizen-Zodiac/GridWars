/**
 * @file obstacles_xo.h
 * @brief Header file for Obstacles Tic-Tac-Toe game classes.
 * @author Mustafa Mahmoud
 *
 * This file provides:
 * - `Obstacles_XO_Board`: A specialized board class for the Tic-Tac-Toe game.
 * - `Obstacles_XO_UI`: A user interface class tailored to This game setup and player interaction.
 */


#ifndef _OBSTACLES_XO_H
#define _OBSTACLES_XO_H

#include"BoardGame_Classes.h"
#include<vector>
using namespace std;


/*
@brief Vectors to record moves in Obstacles game.
*/
static vector< int> xV_obs;
static vector< int> yV_obs;

/*
@brief Record a move in Obstacles game.
@param row The row index of the move.
@param col The column index of the move.
*/
void record_move_obs(int row, int col);

/*
@brief Get the x-coordinate of a recorded move in Obstacles game.
@param index The index of the move to retrieve.
@return The x-coordinate of the move.
*/
int get_x_move_obs(int index);
/*
@brief Get the y-coordinate of a recorded move in Obstacles game.
@param index The index of the move to retrieve.
@return The y-coordinate of the move.
*/
int get_y_move_obs(int index);


/**
* @brief Count rounds
*/
static int rounds_obstacles = 0;



/**
 * @class Obstacles_XO_Board
 * @brief Specialized board class for the Obstacles game.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for Obstacles,
 * including move updates and win/loss/draw conditions.
 *
 * @see Board
 */

class Obstacles_XO_Board : public Board<char> {
private:
	char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
	/**
	 * @brief Default constructor initializing a Obstacles board.
	*/
	Obstacles_XO_Board();

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
	* @return Always returns false as losing is not explicitly tracked in Obstacles.
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
 * @class Obstacles_XO_UI
 * @brief User interface class for the Obstacles game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * Obstacles-specific implementations for player setup and move retrieval.
 *
 * @see UI
 */
class Obstacles_XO_UI : public UI<char> {
public:
	/**
	 * @brief Default constructor for the Obstacles UI.
	*/
	Obstacles_XO_UI();

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
	@brief Sets up the players for the Obstacles game.
	@return An array of pointers to the created Player<char> instances.
	*/
	Player<char>** setup_players() override;
};

#endif // !_OBSTACLES_XO_H