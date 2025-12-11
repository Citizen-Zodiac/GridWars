/**
 * @file word_tic.h
 * @brief Header file for Word Tic-Tac-Toe game classes.
 * @author Mustafa Mahmoud
 *
 * This file provides:
 * - `Word_Board`: A specialized board class for the Tic-Tac-Toe game.
 * - `Word_UI`: A user interface class tailored to This game setup and player interaction.
 */


#ifndef _WORD_TIC_H
#define _WORD_TIC_H

#include"BoardGame_Classes.h"
#include<vector>
#include<set>
#include<unordered_set>
#include<fstream>

using namespace std;

/*
@brief Vectors to record moves in Word game.
*/
static vector< int> xV_word;
static vector< int> yV_word;


/*
@brief Record a move in Word game.
@param row The row index of the move.
@param col The column index of the move.
*/
void record_move_four(int row, int col);

/*
@brief Get the x-coordinate of a recorded move in Word game.
@param index The index of the move to retrieve.
@return The x-coordinate of the move.
*/
int get_x_move_four(int index);
/*
@brief Get the y-coordinate of a recorded move in Word game.
@param index The index of the move to retrieve.
@return The y-coordinate of the move.
*/
int get_y_move_four(int index);

/**
* @brief The dicionary which contain all words
*/
static unordered_set<std::string> dictionary;

/**
* @brief Load dic.txt in dictionary
*/
void load_dictionary();

/**
* @brief Check if the word valid (in dic) or no
* @param const string the word (w)
* @return true if the word (w) valid (in dic)
*/
bool is_valid_word(const std::string& w);

/**
* @brief select a random letter for computer player
* @return character for computer
*/
char random_letter();


/**
 * @class Word_Board
 * @brief Specialized board class for the Word game.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for Word,
 * including move updates and win/loss/draw conditions.
 *
 * @see Board
 */

class Word_Board : public Board<char> {
private:
	char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
	/**
	 * @brief Default constructor initializing a Word board.
	*/
	Word_Board();

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
	* @return Always returns false as losing is not explicitly tracked in Word.
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
 * @class Word_UI
 * @brief User interface class for the Word game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * Word-specific implementations for player setup and move retrieval.
 *
 * @see UI
 */


class Word_UI : public UI<char> {
public:

	/**
	 * @brief Default constructor for the Word UI.
	*/
	Word_UI();

	/**
	* @brief Retrieves the next move from a player.
	* @param player Pointer to the player whose move is being requested.
	* @return A pointer to a new `Move<char>` object representing the player's action.
	*/
	Move<char>* get_move(Player<char>* player) override;

	/**
	 * @brief Creates a player of the specified type.
	 * @param name Name of the player.
	 * @param symbol Character symbol (Character) assigned to the player.
	 * @param type The type of the player (Human or Computer).
	 * @return Pointer to the newly created Player<char> instance.
	 */
	Player<char>* create_player(string& name, char symbol, PlayerType type) override;

	/*
	@brief Sets up the players for the Word game.
	@return An array of pointers to the created Player<char> instances.
	*/
	Player<char>** setup_players() override;
};


#endif
