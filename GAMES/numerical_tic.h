/**
 * @file numerical_tic.h
 * @brief Header file for the Numerical Tic-Tac-Toe game classes.
 * 
 * This file provides:
 * - `NumericalTicBoard`: A specialized board class for Numerical Tic-Tac-Toe, 
 *    handling game logic and win/draw detection based on number combinations.
 * - `NumericalTicUI`: A user interface class tailored to the numerical version 
 *    of Tic-Tac-Toe, responsible for input handling and player setup.
 */

#ifndef NUMERICAL_TIC_H
#define NUMERICAL_TIC_H

#include "BoardGame_Classes.h"
#include <vector>

/**
 * @class NumericalTicBoard
 * @brief Logic handler for the Numerical Tic-Tac-Toe board.
 * 
 * This class manages:
 * - Tracking used numbers.
 * - Updating the board after valid moves.
 * - Determining win/lose/draw conditions.
 */
class NumericalTicBoard : public Board<int> {
private:
    /** 
     * @brief Stores all numbers that have already been played to prevent repetition. 
     */
    std::vector<int> used_numbers;

public:
    /**
     * @brief Constructs an empty Numerical Tic-Tac-Toe board.
     */
    NumericalTicBoard();

    /**
     * @brief Updates the board with the player's move.
     * @param move Pointer to the move object containing the chosen cell and value.
     * @return True if the move is valid and applied, otherwise false.
     */
    bool update_board(Move<int>* move) override;

    /**
     * @brief Checks if the given player has won.
     * @param player Pointer to the current player.
     * @return True if a winning condition is met.
     */
    bool is_win(Player<int>* player) override;

    /**
     * @brief Checks if the given player has lost.
     * @param player Pointer to the current player.
     * @return True if the opponent's win condition is achieved.
     */
    bool is_lose(Player<int>* player) override;

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player (unused but follows interface signature).
     * @return True if no moves remain and no one has won.
     */
    bool is_draw(Player<int>* player) override;

    /**
     * @brief Determines whether the game is over.
     * @param player Pointer to the current player.
     * @return True if win/lose/draw conditions are met.
     */
    bool game_is_over(Player<int>* player) override;
};

/**
 * @class NumericalTicUI
 * @brief User interface class for player interaction in Numerical Tic-Tac-Toe.
 */
class NumericalTicUI : public UI<int> {
public:
    /**
     * @brief Constructs the UI for the game.
     * @param message Message displayed before the UI prints the board.
     * @param cell_display_width Width of each printed cell.
     */
    NumericalTicUI(string message, int cell_display_width) 
        : UI<int>(message, cell_display_width) {}

    /**
     * @brief Gets a move from the given player.
     * @param player Pointer to the current player.
     * @return A pointer to a newly created Move object.
     */
    Move<int>* get_move(Player<int>* player) override;

    /**
     * @brief Creates a player object for the game.
     * @param name Reference to the player's name.
     * @param symbol Player's numerical symbol (odd/even).
     * @param type Whether the player is human or computer.
     * @return Pointer to the newly created player.
     */
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;

    /**
     * @brief Sets up the two players for the game.
     * @return Pointer to an array of two Player pointers.
     */
    Player<int>** setup_players() override;
};

#endif
