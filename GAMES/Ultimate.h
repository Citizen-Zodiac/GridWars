/**
 * @class Ultimate_SubBoard
 * @brief Represents a 3x3 sub-board in Ultimate Tic-Tac-Toe.
 *
 * This class manages the state of a single sub-board, including placement of marks,
 * checking for wins, and returning the current board state.
 */
class Ultimate_SubBoard {
private:
    char cells[3][3]; /**< 3x3 grid of cells for this sub-board */
    bool finished;    /**< Whether this sub-board has finished */
    char winner;      /**< Winner of this sub-board ('X', 'O', or '\0' if none) */

    /**
     * @brief Checks if the given symbol has three in a row on this sub-board.
     * @param s Symbol to check ('X' or 'O')
     * @return True if three in a row exists, false otherwise
     */
    bool three_in_row(char s);

public:
    /** @brief Default constructor initializes the sub-board to empty and unfinished */
    Ultimate_SubBoard();

    /**
     * @brief Places a mark on the sub-board.
     * @param r Row index (0-2)
     * @param c Column index (0-2)
     * @param s Symbol to place ('X' or 'O')
     * @return True if placement succeeded, false if the cell was occupied
     */
    bool place_mark(int r, int c, char s);

    /** @brief Checks if the sub-board is full.
     *  @return True if all cells are filled, false otherwise
     */
    bool is_full() const;

    /** @brief Checks if the sub-board has finished.
     *  @return True if finished, false otherwise
     */
    bool is_finished() const;

    /** @brief Returns the winner of the sub-board.
     *  @return Symbol of the winner ('X' or 'O') or '\0' if none
     */
    char get_winner() const;

    /** @brief Returns the current state of the sub-board as a 2D vector.
     *  @return 3x3 vector of chars representing the sub-board
     */
    vector<vector<char>> get_matrix() const;
};


/**
 * @class Ultimate_MainBoard
 * @brief Represents the main 9x9 board of Ultimate Tic-Tac-Toe.
 *
 * Manages 3x3 sub-boards and checks for overall game state, wins, draws, and losses.
 */
class Ultimate_MainBoard : public Board<char> {
private:
    Ultimate_SubBoard sub[3][3]; /**< 3x3 grid of sub-boards */

    /**
     * @brief Checks if the given symbol has three in a row in the main board.
     * @param s Symbol to check ('X' or 'O')
     * @return True if three sub-boards in a row are won by s, false otherwise
     */
    bool main_three_in_row(char s);

public:
    /** @brief Default constructor initializes all sub-boards */
    Ultimate_MainBoard();

    /**
     * @brief Updates the main board with a move.
     * @param move Pointer to the Move object
     * @return True if the move was successful
     */
    bool update_board(Move<char>* move) override;

    /** @brief Checks if the given player has won the game */
    bool is_win(Player<char>* p) override;

    /** @brief Checks if the given player has lost the game */
    bool is_lose(Player<char>* p) override;

    /** @brief Checks if the game is a draw */
    bool is_draw(Player<char>* p) override;

    /** @brief Checks if the game is over (win, lose, or draw) */
    bool game_is_over(Player<char>* p) override;

    /** @brief Access a sub-board
     *  @param r Row index of sub-board (0-2)
     *  @param c Column index of sub-board (0-2)
     *  @return Reference to the sub-board
     */
    Ultimate_SubBoard& get_sub(int r, int c);
};


/**
 * @class Ultimate_ComputerPlayer
 * @brief Represents a computer player in Ultimate Tic-Tac-Toe.
 */
class Ultimate_ComputerPlayer : public Player<char> {
public:
    /**
     * @brief Constructor to initialize computer player with name and symbol
     * @param name Player's name
     * @param symbol Player's symbol ('X' or 'O')
     */
    Ultimate_ComputerPlayer(string name, char symbol);

    /**
     * @brief Generates a move for the computer player
     * @return Pointer to the Move object chosen by AI
     */
    Move<char>* get_ultimate_computer_move();
};


/**
 * @class Ultimate_UI
 * @brief Handles user interaction for Ultimate Tic-Tac-Toe.
 */
class Ultimate_UI : public UI<char> {
public:
    /** @brief Default constructor */
    Ultimate_UI();

    /**
     * @brief Gets a move from a player
     * @param p Pointer to the player
     * @return Pointer to the Move object
     */
    Move<char>* get_move(Player<char>* p) override;

    /**
     * @brief Creates a player
     * @param name Player's name
     * @param symbol Player's symbol
     * @param type Player type (human or computer)
     * @return Pointer to the created player
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Displays the full main board including all sub-boards
     * @param board Pointer to the Ultimate_MainBoard
     */
    void display_ultimate_board(Ultimate_MainBoard* board);

    /** @brief Shows the menu options to the player
     *  @return The selected menu option
     */
    int show_menu();

    /** @brief Sets up the two players
     *  @return Array of two Player pointers
     */
    Player<char>** setup_players();
};


/**
 * @class Ultimate_GameManager
 * @brief Manages the game loop for Ultimate Tic-Tac-Toe.
 */
class Ultimate_GameManager {
private:
    Ultimate_MainBoard* board; /**< Pointer to the main board */
    Player<char>* players[2];  /**< Array of two players */
    Ultimate_UI* ui;            /**< Pointer to the UI */

public:
    /**
     * @brief Constructor initializes game manager with board, players, and UI
     * @param b Pointer to the main board
     * @param p Array of two Player pointers
     * @param u Pointer to the UI
     */
    Ultimate_GameManager(Ultimate_MainBoard* b, Player<char>* p[2], Ultimate_UI* u);

    /** @brief Runs the game loop until completion */
    void run();
};
