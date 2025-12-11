/**
 * @file Infinity.h
 * @brief Header file for Infinity game classes.
 * @author Hamza Mohamed
 *
 * This file provides:
 * - `Infinity_Board`: A specialized board class for the Tic-Tac-Toe game.
 * - `Infinity_UI`: A user interface class tailored to This game setup and player interaction.
 */


#ifndef INFINITY_H
#define INFINITY_H

#include "BoardGame_Classes.h"
#include <vector>
#include <queue>
using namespace std;


/**
 * @class Infinity_ComputerPlayer
 * @brief Represents a computer player for the Infinity game.
 *
 * Inherits from the generic Player class and implements
 * move selection logic specific to the Infinity game.
 */
class Infinity_ComputerPlayer : public Player<char> {
public:
    /**
	* @brief Construct a computer player with a name and symbol.
	* @param name The name of the computer player.
	* @param symbol The symbol used by the computer player on the board.
	* @returns A pointer to the move chosen by the computer player.
    */
    Infinity_ComputerPlayer(string name, char symbol);
    
    /**
	* @brief Determine and return the computer player's move.
	* @returns A pointer to the move chosen by the computer player.
    */
    Move<char>* get_infinity_computer_move();
};



/**
 * @class Infinity_Board
 * @brief Specialized board class for the Infinity game.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for Infinity,
 * including move updates and win/loss/draw conditions.
 *
 * @see Board
 */
class Infinity_Board : public Board<char> {
private:
    /**
    * 
    */
    vector<pair<int, int>>all_moves;
    
    /**
    * @
    */
    int current_marks;
    
    /**
    * 
    */
    bool three_in_row(char s);

public:
    /**
    * @brief Default constructor that initializes a 3x3 X-O board.
    */
    Infinity_Board();

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
     * @return Always returns false as losing is not explicitly tracked in Infinity.
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
};


class Infinity_UI : public UI<char> {
public:
    
    /**
    * @brief Default constructor for the Infinity UI.
    */
    Infinity_UI();

    /**
    * @brief Display the game menu and get user choice.
    * @return The user's menu choice as an integer.
    */
    int show_menu();

    /**
    * @brief Sets up the players for the Infinity game.
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

