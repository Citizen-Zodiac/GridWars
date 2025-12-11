/**
 * @file Diamond.h
 * @brief Header file for Diamond game classes.
 * @author Hamza Mohamed
 *
 * This file provides:
 * - `Diamond_Board`: A specialized board class for the Tic-Tac-Toe game.
 * - `Diamond_UI`: A user interface class tailored to This game setup and player interaction.
 */


#ifndef DIAMOND_H
#define DIAMOND_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
using namespace std;


/**
* @class Diamond_ComputerPlayer
* @brief Computer player class for the Diamond game.
*/
class Diamond_ComputerPlayer : public Player<char> {
public:
    /**
	* @brief Construct a Diamond computer player with name and symbol.
	* @param name The name of the computer player.
	* @param symbol The symbol used by the computer player on the board.
	* @returns A pointer to the move chosen by the computer player.
    */
    Diamond_ComputerPlayer(string name, char symbol);
    
    /**
	* @brief Generate a move for the computer player.
	* @return A pointer to the Move<char> object representing the computer's move.
    */
    Move<char>* get_diamond_computer_move();
};


/**
 * @class Diamond_Board
 * @brief Specialized board class for the Diamond game.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for Diamond,
 * including move updates and win/loss/draw conditions.
 *
 * @see Board
 */
class Diamond_Board : public Board<char> {

public:

	/**
	* @brief Construct a Diamond board with predefined dimensions.
    */
    Diamond_Board();

	/**
	* @brief Update the board with a new move.
	* @param move The move object containing position and symbol.
	* @return true if the move is valid and applied, false otherwise.
    */
    bool update_board(Move<char>* move) override;
    

   /**
   * @brief Checks if the given player has won the game.
   * @param player Pointer to the player being checked.
   * @return true if the player has a winning line, false otherwise.
   */
    bool is_win(Player<char>* p) override;
    
   /**
   * @brief Checks if the given player has lost the game.
   * @param p Pointer to the player being checked.
   * @return Always returns false as losing is not explicitly tracked in Diamond.
   */
    bool is_lose(Player<char>* p) override;
    
    /**
	* @brief Checks if the game ended in a draw.
	* @param p Pointer to the player being checked.
	* @return true if the game is a draw, false otherwise.
    */
    bool is_draw(Player<char>* p) override;

	/**
	* @brief Checks if the game is over for the given player.
	* @param p Pointer to the player being checked.
	* @return true if the game is over, false otherwise.
    */
    bool game_is_over(Player<char>* p) override;

private:
    /**
	* @brief Check if a cell is valid within the diamond shape.
	* @param r Row index.
	* @param c Column index.
	* @return true if the cell is valid, false otherwise.
    */
    bool diamond_cell_valid(int r, int c);
    
    /**
	* @brief Get all lines of a given length in the diamond shape.
	* @param length The length of the lines to retrieve.
	* @return A vector of lines, each line being a vector of (row, column) pairs.
    */
    vector<vector<pair<int, int>>> diamond_get_lines(int length);
    
    /**
	* @brief Check if a line is fully occupied by the given symbol.
	* @param line A vector of (row, column) pairs representing the line.
	* @param s The symbol to check for.
	* @return true if the line is fully occupied by the symbol, false otherwise.
    */
    bool diamond_line_full(const vector<pair<int, int>>& line, char s);

	/**
	* @brief Find all lines of a given length occupied by the player's symbol.
	* @param p Pointer to the player.
	* @param length The length of the lines to find.
	* @param outLines Reference to a vector to store the found lines.
	* @return true if any lines are found, false otherwise.
    */
    bool find_lines(Player<char>* p, int length,
        vector<vector<pair<int, int>>>& outLines);
};



/**
 * @class Diamond_UI
 * @brief User interface class for the Diamond game.
 *
 * This class inherits from the generic `UI<char>` class and implements
 * methods for player setup and move retrieval specific to the Diamond game.
 *
 * @see UI
 */
class Diamond_UI : public UI<char> {
public:
	/**
	* @brief Default constructor for the Diamond UI.
    */
    Diamond_UI();

	/**
	* @brief Display the game menu and get user choice.
	* @return The user's menu choice as an integer.
    */
	int show_menu();

	/**
	* @brief Sets up the players for the Diamond game.
	* @return An array of pointers to the created players.
	*/
	Player<char>** setup_players() override;
 
	/**
	* @brief Retrieves the next move from a player.
	* @param p Pointer to the player whose move is being requested.
	* @return A pointer to a new `Move<char>` object representing the player's action.
	*/
	Move<char>* get_move(Player<char>* p) override;
    
	/**
	* @brief Creates a player of the specified type.
	* @param name Name of the player.
	* @param symbol Character symbol ('X' or 'O') assigned to the player.
	* @param type The type of the player (Human or Computer).
	* @return Pointer to the newly created Player<char> instance.
	*/
	Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif
