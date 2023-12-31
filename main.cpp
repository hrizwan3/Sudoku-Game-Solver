#include <iostream>
#include "sudoku.hpp"
#include "utilities.hpp"

using namespace std;


int main(int argc, char* argv[]) {
    // Instructions for the game
    cout << endl <<"Hello! Welcome to Fraudulent Sudoku (with a solver)" << endl;
    cout << "This is a game of Sudoku, where you can play a game, or have the computer solve it for you (by entering -2 -2 -2)" << endl;
    cout << "You can also save your game and load it later" << endl << endl;

    // Game options
    string choices[] = {"Load last game", "Start new game"};
    string boards[] = {"easy1", "easy2", "easy3", "grid1", "grid2"};

    // Game selection
    cout << "Please select an option:" << endl;
    displayGameOptions(choices);
    int val;
    cin >> val;
    cout << "You selected: " << choices[val - 1] << endl;

    // Load game
    Sudoku sudoku;
    if (val == 1) {
        if (!loadSudoku(sudoku, "saves/save.txt")) {
            cout << "Game not found, loading a preset" << endl;
            loadSudoku(sudoku, "preset-games/easy1.txt");
        }
    } else {
        cout << "Please select a game:" << endl;
        displayBoardOptions(boards);
        cin >> val;
        loadSudoku(sudoku, ("preset-games/" + boards[val - 1] + ".txt").c_str());
    }

    // Play game
    bool player{true}; // true if player is playing, false if computer is solving

    while (!sudoku.checkSolved()) {
        sudoku.printBoard();
        cout << "Please enter a row, column, and value (separated by spaces), or type \"-1 -1 -1\" to stop, or \"-2 -2 -2\" to solve: ";
        int row, col, value;
        cin >> row >> col >> value;
        if (row == -1 && col == -1 && value == -1) {
            cout << "Would you like to save your game? (y/n) ";
            char save;
            cin >> save;
            if (save == 'y') {
                saveSudoku(sudoku, "saves/save.txt");
            }
            break;
        } else if (row == -2 && col == -2 && value == -2) { // doesn't work if you modify the board
            sudoku.solve();
            player = false;
            break;
        } else if (val < 1 || val > 9 || row < 1 || row > 9 || col < 1 || col > 9) {
            cout << "Invalid move!" << endl;
        } else if (sudoku.isValidMove(row - 1, col - 1, value)) {
            sudoku.setCell(row - 1, col - 1, value);
        } else {
            cout << "Invalid move!" << endl;
        }
    }

    // End game
    if (player && sudoku.checkSolved()) {
        cout << "Congratulations! You solved the puzzle!" << endl;
    } else if (sudoku.checkSolved()) {
        cout << "Here's the answer:" << endl;
        sudoku.printBoard();
    }
    return 0;
}