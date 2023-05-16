#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 9;

bool isValid(vector < vector < int >> & board, int row, int col, int num) {
    // Check if the number is already in the row
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }
    // Check if the number is already in the column
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[j][col] == num) {
            return false;
        }
    }
    // Check if the number is already in the 3x3 box
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (int i = boxRow; i < boxRow + 3; i++) {
        for (int j = boxCol; j < boxCol + 3; j++) {
            if (board[i][j] == num) {
                return false;
            }
        }
    }
    return true;
}

bool solveSudoku(vector < vector < int >> & board) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            // Find the first empty cell
            if (board[row][col] == 0) {
                // Try all possible numbers for this cell
                for (int num = 1; num <= BOARD_SIZE; num++) {
                    if (isValid(board, row, col, num)) {
                        // If the number is valid, place it in the cell
                        board[row][col] = num;
                        // Recursively solve the rest of the puzzle
                        if (solveSudoku(board)) {
                            return true;
                        }
                        // If we can't solve the puzzle, backtrack and try a different number
                        board[row][col] = 0;
                    }
                }
                // If we can't place any number in this cell, backtrack to the previous cell
                return false;
            }
        }
    }
    // If there are no empty cells, the puzzle is solved
    return true;
}

void printBoard(vector < vector < int >> & board) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    ifstream inFile(argv[1]);
    if (!inFile) {
        cout << "Error opening file " << argv[1] << endl;
        return 1;
    }
    // Read in the Sudoku board from the file
    vector < vector < int >> board(BOARD_SIZE, vector < int > (BOARD_SIZE));
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            inFile >> board[row][col];
        }
    }
    // Solve the Sudoku puzzle
    if (solveSudoku(board)) {
        // Print the solved board
        printBoard(board);
        // Write the solved board to
        // Write the solved board to the output file
        ofstream outFile("solved_" + string(argv[1]));
        if (!outFile) {
            cout << "Error creating file solved_" << argv[1] << endl;
            return 1;
        }
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                outFile << board[row][col] << " ";
            }
            outFile << endl;
        }
        outFile.close();
    } else {
        cout << "No solution found for the Sudoku puzzle" << endl;
    }
    return 0;
}