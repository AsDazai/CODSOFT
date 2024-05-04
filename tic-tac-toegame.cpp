#include <iostream>
#include <vector>

using namespace std;

const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = '-';

// Function to print the current game board
void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a player has won
bool checkWinner(const vector<vector<char>>& board, char player) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }

    return false;
}

// Function to check if the board is full (no empty spaces)
bool isBoardFull(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

// Function to get a valid player move
int getValidMove(const vector<vector<char>>& board, char player) {
    int move;
    do {
        cout << player << "'s turn, enter a move (1-9): ";
        cin >> move;
    } while (move < 1 || move > 9 || board[(move - 1) / 3][(move - 1) % 3] != EMPTY);

    return move - 1; // Convert move index to 0-based index
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, EMPTY)); // Initialize empty board

    char currentPlayer = PLAYER_X;
    bool gameOver = false;

    while (!gameOver) {
        // Print the current board
        printBoard(board);

        // Get player move
        int move = getValidMove(board, currentPlayer);

        // Update the board
        board[move / 3][move % 3] = currentPlayer;

        // Check for winner
        if (checkWinner(board, currentPlayer)) {
            cout << currentPlayer << " wins!" << endl;
            gameOver = true;
        } else if (isBoardFull(board)) {
            cout << "It's a tie!" << endl;
            gameOver = true;
        }

        // Switch players
        currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
    }

    return 0;
}
