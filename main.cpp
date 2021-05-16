#include <iostream>
#include <vector>
#include <bitset>
#include <array>

bool Solve(std::vector<int> &board, int currentIndex, std::array<std::bitset<9>, 9> &rowValues, std::array<std::bitset<9>, 9> &columnValues, std::array<std::bitset<9>, 9> &cellValues);
int GetRow(int index);
int GetColumn(int index);
int GetCell(int index);

void print (std::vector<int> &board);

int main() {
//    std::vector<int> board {         // Easy Sudoku
//        0, 0, 1, 0, 2, 0, 0, 3, 0,
//        0, 0, 0, 4, 0, 0, 5, 0, 0,
//        2, 6, 0, 0, 3, 0, 7, 0, 8,
//        0, 8, 0, 0, 0, 3, 1, 0, 0,
//        7, 0, 0, 6, 0, 1, 0, 0, 9,
//        0, 0, 6, 5, 0, 0, 0, 4, 0,
//        8, 0, 9, 0, 7, 0, 0, 5, 1,
//        0, 0, 3, 0, 0, 8, 0, 0, 0,
//        0, 5, 0, 0, 6, 0, 2, 0, 0
//    };


    std::vector<int> board {            // Really hard Sudoku
            0, 0, 0, 0, 1, 0, 0, 0, 2,
            0, 0, 0, 0, 0, 3, 0, 1, 0,
            0, 0, 4, 0, 0, 5, 0, 0, 6,
            0, 0, 0, 6, 0, 0, 7, 5, 0,
            0, 0, 1, 0, 0, 0, 8, 0, 0,
            0, 8, 3, 0, 0, 9, 0, 0, 0,
            8, 0, 0, 7, 0, 0, 9, 0, 0,
            0, 2, 0, 5, 0, 0, 0, 0, 0,
            7, 0, 0, 0, 4, 0, 0, 0, 0,
    };

    std::cout << "Unsolved: \n";
    print(board);
    std::cout << "\n\n";

    auto rows = std::array<std::bitset<9>, 9>();
    auto cols = std::array<std::bitset<9>, 9>();
    auto cells = std::array<std::bitset<9>, 9>();

    // Store the existing numbers in the bitsets
    for (int i = 0; i < board.size(); ++i) {
        int row = GetRow(i);
        int column = GetColumn(i);
        int cell = GetCell(i);

        int value = board[i];

        if (value != 0) {
            rows[row].set(value - 1);
            cols[column].set(value - 1);
            cells[cell].set(value - 1);
        }
    }

    Solve(board, 0, rows, cols, cells);

    std::cout << "Solved: \n";
    print(board);
}

bool Solve(std::vector<int> &board,
           int currentIndex,
           std::array<std::bitset<9>, 9> &rowValues,
           std::array<std::bitset<9>, 9> &columnValues,
           std::array<std::bitset<9>, 9> &cellValues)
{
    if (currentIndex == 9 * 9) {
        return true;
    }

    while (board[currentIndex] != 0) {
        currentIndex += 1;
    }

    int row = GetRow(currentIndex);
    int column = GetColumn(currentIndex);
    int cell = GetCell(currentIndex);

    std::bitset<9> usedValues = rowValues[row] | columnValues[column] | cellValues[cell];

    if (usedValues.all()) {
        return false;
    }

    for (int i = 1; i < 10; ++i) {
        if (!usedValues[i - 1]) {
            board[currentIndex] = i;
            rowValues[row].set(i - 1);
            columnValues[column].set(i - 1);
            cellValues[cell].set(i - 1);

            if (Solve(board, currentIndex + 1, rowValues, columnValues, cellValues)) {
                // Sudoku was solved.
                return true;
            }

            rowValues[row].reset(i - 1);
            columnValues[column].reset(i - 1);
            cellValues[cell].reset(i - 1);
        }
    }

    // No number between 1-9 can be used. This path does not work.
    board[currentIndex] = 0;
    return false;
}

int GetRow(int index)
{
    return index / 9;
}

int GetColumn(int index)
{
    return index % 9;
}

int GetCell(int index)
{
    return (GetRow(index) / 3) * 3  + GetColumn(index) / 3;
}

void print(std::vector<int> &board)
{
    for (int i = 0; i < board.size(); ++i) {
        if (i % 9 == 0) {
            std::cout << "\n";
        }
        std::cout << board[i] << "  ";
    }
}