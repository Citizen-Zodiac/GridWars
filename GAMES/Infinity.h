/**
 * @file Infinity.h
 * @brief Header file for Infinity game classes.
 * 
 * This file provides:
 * - `Infinity_Board`: Specialized board class for the Infinity game logic.
 * - `Infinity_UI`: User interface class for managing player interaction.
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
 * Implements automatic move selection logic.
 */
class Infinity_ComputerPlayer : public Player<char> {
public:
    /**
     * @brief Construct a computer player with a name and symbol.
     * @param name The name of the computer player.
     * @param symbol The symbol used by the computer player on the board.
     */
    Infinity_ComputerPlayer(string name, char symbol);
    
    /**
     * @brief Determine and return the computer player's move.
     * @return A pointer to the move chosen by the computer player.
     */
    Move<char>* get_infinity_computer_move();
};


/**
 * @class Infinity_Board
 * @brief Specialized board class for the Infinity game.
 *
 * Handles move validation, win checking, and game progression.
 */
class Infinity_Board : public Board<char> {
private:
    /**
     * @brief Stores all moves played in the game as (row, column) pairs.
     */
    vector<pair<int, int>> all_moves;
    
    /**
     * @brief Tracks the number of marks currently on the board.
     */
    int current_marks;
    
    /**
     * @brief Checks if there are three identical symbols in a row.
     * @param s The symbol to check for (e.g., 'X' or 'O').
     * @return True if there are three consecutive marks, false otherwise.
     */
    bool three_in_row(char s);

public:
    /**
     * @brief Default constructor initializing Infinity board settings.
     */
    Infinity_Board();

    /**
     * @brief Updates the board with a new move.
     * @param move The move object containing the position and symbol.
     * @return True if the move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks whether the given player has won the game.
     * @param p Pointer to the player being checked.
     * @return True if the player meets the win condition.
     */
    bool is_win(Player<char>* p) override;
    
    /**
     * @brief Checks if the player has lost the game.
     * @details Always returns false because Infinity does not track losing explicitly.
     * @param p Pointer to the player being checked.
     * @return False in all cases.
     */
    bool is_lose(Player<char>* p) override;
    
    /**
     * @brief Determines if the game ended in a draw.
     * @param p Pointer to the player (not used directly).
     * @return True if the board is full and no one has won.
     */
    bool is_draw(Player<char>* p) override;

    /**
     * @brief Checks whether the game is over for the given player.
     * @param p Pointer to the player being checked.
     * @return True if win or draw conditions are met.
     */
    bool game_is_over(Player<char>* p) override;
};


/**
 * @class Infinity_UI
 * @brief User interface class for the Infinity game.
 *
 * Handles player input, menu display, and game setup.
 */
class Infinity_UI : public UI<char> {
public:
    /**
     * @brief Default constructor for the Infinity UI.
     */
    Infinity_UI();

    /**
     * @brief Displays the game menu and retrieves the user's choice.
     * @return The selected menu option.
     */
    int show_menu();

    /**
     * @brief Sets up the players for the Infinity game.
     * @return An array of pointers to the created Player objects.
     */
    Player<char>** setup_players() override;

    /**
     * @brief Retrieves the next move from the specified player.
     * @param p Pointer to the player making the move.
     * @return A pointer to the new Move<char> object.
     */
    Move<char>* get_move(Player<char>* p) override;

    /**
     * @brief Creates a player based on the given type.
     * @param name Player's name.
     * @param symbol Player's assigned symbol (typically 'X' or 'O').
     * @param type Player type: Human or Computer.
     * @return Pointer to the newly created player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif
