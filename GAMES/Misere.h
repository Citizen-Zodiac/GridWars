/**
 * @file Misere.h
 * @brief Header file for Misere Tic-Tac-Toe game classes.
 * @author Hamza Mohamed
 *
 * This file provides:
 * - `MisereBoard`: A specialized board class for the Tic-Tac-Toe game.
 * - `MisereUI`: A user interface class tailored to This game setup and player interaction.
 */


#ifndef MISERE_UI_H
#define MISERE_UI_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
using namespace std;


/**
* @class RandomMiserePlayer
* @brief player class for the Misere game.
*/
class RandomMiserePlayer : public Player<char> {
public:
    /**
    * @brief Construct a Misere player with name and symbol.
    * @param name The name of the player.
    * @param symbol The symbol used by the  player on the board.
    * @returns A pointer to the move chosen by the player.
    */
    RandomMiserePlayer(string name, char symbol);

    /**
    * @brief Generate a move for the player.
    * @return A pointer to the Move<char> object representing the player's move.
    */
    Move<char>* get_random_move();

};



/**
 * @class MisereBoard
 * @brief Specialized board class for the Misere game.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for Misere,
 * including move updates and win/loss/draw conditions.
 *
 * @see Board
 */
class MisereBoard : public Board<char> {
public:

    /**
    * @brief Construct a Misere board with predefined dimensions.
    */
    MisereBoard();

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
    * @return Always returns false as losing is not explicitly tracked in Misere.
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
     * @brief Checks if there are three consecutive cells containing the same symbol.
     * @param s The symbol to check for (e.g., player's piece).
     * @return True if there are three in a row, otherwise false.
     */
    bool three_in_row(char s);

};

/**
 * @class MisereUI
 * @brief User interface class for the Misere game.
 *
 * This class inherits from the generic `UI<char>` class and implements
 * methods for player setup and move retrieval specific to the Misere game.
 *
 * @see UI
 */
class MisereUI : public UI<char> {
public:
    /**
    * @brief Default constructor for the Misere UI.
    */
    MisereUI();

    /**
    * @brief Display the game menu and get user choice.
    * @return The user's menu choice as an integer.
    */
    int show_menu();

    /**
    * @brief Sets up the players for the Misere game.
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
