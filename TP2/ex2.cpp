#include "exercises.h"

Sudoku::Sudoku() {
    this->initialize();
}

Sudoku::Sudoku(int nums[9][9]): Sudoku() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (nums[i][j] != 0) {
                int n = nums[i][j];
                if (n < 1 || n > 9 || !accepts(i, j, n))
                    throw IllegalArgumentException;
                else
                    place(i, j, n);
            }
        }
    }
}

void Sudoku::initialize() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int n = 0; n < 10; n++) {
                numbers[i][j] = 0;
                lineHasNumber[i][n] = false;
                columnHasNumber[j][n] = false;
                block3x3HasNumber[i / 3][j / 3][n] = false;
            }
        }
    }
    this->countFilled = 0;
}

bool Sudoku::isComplete() const {
    return countFilled == 9 * 9;
}

bool Sudoku::containsInRow(int row, int number) {
    for (int i = 0; i < 9; i++) {
        if (numbers[row][i] == number) return true;
    }
    return false;
}

bool Sudoku::containsInColumn(int col, int number) {
    for (int i = 0; i < 9; i++) {
        if (numbers[i][col] == number) return true;
    }
    return false;
}

bool Sudoku::containsInBox(int row, int col, int number) {
    int r = row - (row % 3);
    int c = col - (col % 3);

    for (int i = r; i <= r + 2; i++) {
        for (int j = c; j <= c + 2; j++) {
            if (numbers[i][j] == number) return true;
        }
    }
    return false;
}

bool Sudoku::isSafe(int row, int col, int number) {
    return !(containsInRow(row, number) || containsInColumn(col, number) || containsInBox(row, col, number));
}

bool Sudoku::solve() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (numbers[row][col] == 0) {
                for (int number = 1; number <= 9; number++) {
                    if (isSafe(row, col, number)) {
                        numbers[row][col] = number;

                        if (solve()) return true;
                        else numbers[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int Sudoku::countSolutions() {
    //TODO
    return 0;
}

void Sudoku::generate() {
	//TODO
}

int** Sudoku::getNumbers() {
    int** ret = new int*[9];
    for (int i = 0; i < 9; i++) {
        ret[i] = new int[9];
        for (int a = 0; a < 9; a++)
            ret[i][a] = numbers[i][a];
    }
    return ret;
}

#include <iostream>

void Sudoku::print() const {
    for (int i = 0; i < 9; i++) {
        for (int a = 0; a < 9; a++)
            std::cout << this->numbers[i][a] << " ";
        std::cout << std::endl;
    }
}

bool Sudoku::accepts(int i, int j, int n) {
	//TODO
    return false;
}

void Sudoku::place(int i, int j, int n) {
    if (numbers[i][j] != 0)
        return;

    numbers[i][j] = n;
    lineHasNumber[i][n] = true;
    columnHasNumber[j][n] = true;
    block3x3HasNumber[i / 3][j / 3][n] = true;
    countFilled++;
}

int Sudoku::clear(int i, int j) {
    int n = numbers[i][j];

    numbers[i][j] = 0;
    lineHasNumber[i][n] = false;
    columnHasNumber[j][n] = false;
    block3x3HasNumber[i / 3][j / 3][n] = false;
    countFilled--;

    return n;
}

void Sudoku::clear() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (numbers[i][j] != 0)
                clear(i, j);
}

/// TESTS ///
#include <gtest/gtest.h>

void compareSudokus(int in[9][9], int out[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int a = 0; a < 9; a++)
            ASSERT_EQ(in[i][a], out[i][a]);
    }
}

TEST(TP2_Ex2, testSudokuAlreadySolved) {
    int in[9][9] =
            {{8, 6, 2, 3, 4, 1, 7, 9, 5},
             {1, 5, 4, 9, 7, 6, 3, 8, 2},
             {9, 3, 7, 8, 2, 5, 1, 4, 6},
             {5, 7, 6, 1, 3, 8, 9, 2, 4},
             {2, 1, 8, 5, 9, 4, 6, 3, 7},
             {3, 4, 9, 7, 6, 2, 8, 5, 1},
             {6, 2, 3, 4, 8, 7, 5, 1, 9},
             {7, 8, 5, 2, 1, 9, 4, 6, 3},
             {4, 9, 1, 6, 5, 3, 2, 7, 8}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);

    int out[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            out[i][a] = res[i][a];

    compareSudokus(in, out);
}

TEST(TP2_Ex2, testSudokuNoneBackStepsRequired) {
    int in[9][9] =
            {{8, 6, 0, 0, 0, 0, 0, 9, 0},
             {0, 0, 4, 0, 7, 6, 3, 0, 0},
             {9, 0, 0, 0, 2, 5, 1, 0, 0},
             {0, 7, 6, 1, 3, 0, 0, 2, 0},
             {2, 1, 0, 0, 0, 0, 0, 3, 7},
             {0, 4, 0, 0, 6, 2, 8, 5, 0},
             {0, 0, 3, 4, 8, 0, 0, 0, 9},
             {0, 0, 5, 2, 1, 0, 4, 0, 0},
             {0, 9, 0, 0, 0, 0, 0, 7, 8}};

    int out[9][9] =
            {{8, 6, 2, 3, 4, 1, 7, 9, 5},
             {1, 5, 4, 9, 7, 6, 3, 8, 2},
             {9, 3, 7, 8, 2, 5, 1, 4, 6},
             {5, 7, 6, 1, 3, 8, 9, 2, 4},
             {2, 1, 8, 5, 9, 4, 6, 3, 7},
             {3, 4, 9, 7, 6, 2, 8, 5, 1},
             {6, 2, 3, 4, 8, 7, 5, 1, 9},
             {7, 8, 5, 2, 1, 9, 4, 6, 3},
             {4, 9, 1, 6, 5, 3, 2, 7, 8}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);

    int sout[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            sout[i][a] = res[i][a];

    compareSudokus(out, sout);
}

TEST(TP2_Ex2, testSudokuSomeBackStepsRequired) {
    int in[9][9] =
            {{7, 0, 5, 2, 6, 3, 4, 0, 9},
             {0, 0, 0, 0, 0, 0, 0, 3, 0},
             {0, 0, 0, 0, 8, 0, 0, 0, 0},
             {0, 0, 9, 5, 0, 4, 0, 0, 2},
             {5, 0, 6, 0, 0, 0, 7, 0, 8},
             {2, 0, 0, 8, 0, 0, 1, 0, 0},
             {0, 0, 0, 0, 1, 0, 0, 0, 0},
             {0, 2, 0, 0, 0, 0, 0, 0, 0},
             {3, 0, 8, 7, 2, 9, 6, 0, 4}};

    int out[9][9] =
            {{7, 1, 5, 2, 6, 3, 4, 8, 9},
             {8, 6, 4, 9, 5, 7, 2, 3, 1},
             {9, 3, 2, 4, 8, 1, 5, 7, 6},
             {1, 8, 9, 5, 7, 4, 3, 6, 2},
             {5, 4, 6, 1, 3, 2, 7, 9, 8},
             {2, 7, 3, 8, 9, 6, 1, 4, 5},
             {4, 9, 7, 6, 1, 5, 8, 2, 3},
             {6, 2, 1, 3, 4, 8, 9, 5, 7},
             {3, 5, 8, 7, 2, 9, 6, 1, 4}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);

    int sout[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            sout[i][a] = res[i][a];

    compareSudokus(out, sout);
}

TEST(TP2_Ex2, testSudokuManyBackStepsRequired) {
    int in[9][9] =
            {{1, 0, 0, 0, 0, 7, 0, 0, 0},
             {0, 7, 0, 0, 6, 0, 8, 0, 0},
             {2, 0, 0, 0, 4, 0, 6, 0, 0},
             {7, 6, 4, 0, 0, 0, 9, 0, 0},
             {0, 0, 0, 0, 2, 0, 5, 6, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 1, 0, 0, 3, 0, 0, 0, 0},
             {4, 0, 0, 1, 0, 0, 0, 0, 5},
             {0, 5, 0, 0, 0, 4, 0, 9, 0}};

    int out[9][9] =
            {{1, 4, 6, 8, 5, 7, 2, 3, 9},
             {3, 7, 9, 2, 6, 1, 8, 5, 4},
             {2, 8, 5, 9, 4, 3, 6, 7, 1},
             {7, 6, 4, 3, 1, 5, 9, 2, 8},
             {8, 3, 1, 4, 2, 9, 5, 6, 7},
             {5, 9, 2, 6, 7, 8, 4, 1, 3},
             {9, 1, 8, 5, 3, 2, 7, 4, 6},
             {4, 2, 7, 1, 9, 6, 3, 8, 5},
             {6, 5, 3, 7, 8, 4, 1, 9, 2}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);

    int sout[9][9];
    int **res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            sout[i][a] = res[i][a];

    compareSudokus(out, sout);
}

TEST(TP2_Ex2, testSudokuWithMinimalClues) {
    int in[9][9] =
            {{7, 0, 0, 1, 0, 8, 0, 0, 0},
             {0, 9, 0, 0, 0, 0, 0, 3, 2},
             {0, 0, 0, 0, 0, 5, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 1, 0, 0},
             {9, 6, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 8, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 5, 0, 0, 1, 0, 0, 0},
             {3, 2, 0, 0, 0, 0, 0, 0, 6}};

    int out[9][9] =
            {{7, 5, 2, 1, 3, 8, 6, 9, 4},
             {1, 9, 8, 7, 4, 6, 5, 3, 2},
             {4, 3, 6, 2, 9, 5, 7, 8, 1},
             {2, 8, 3, 4, 5, 9, 1, 6, 7},
             {9, 6, 1, 8, 2, 7, 3, 4, 5},
             {5, 7, 4, 6, 1, 3, 8, 2, 9},
             {6, 1, 9, 3, 7, 2, 4, 5, 8},
             {8, 4, 5, 9, 6, 1, 2, 7, 3},
             {3, 2, 7, 5, 8, 4, 9, 1, 6}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);

    int sout[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            sout[i][a] = res[i][a];

    compareSudokus(out, sout);
}

TEST(TP2_Ex2, testSudokuWithMultipleSolutions) {
    int in[9][9] =
            {{0/*7*/, 0, 0, 1, 0, 8, 0, 0, 0},
             {0, 9, 0, 0, 0, 0, 0, 3, 2},
             {0, 0, 0, 0, 0, 5, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 1, 0, 0},
             {9, 6, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 8, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 5, 0, 0, 1, 0, 0, 0},
             {3, 2, 0, 0, 0, 0, 0, 0, 6}};

    Sudoku s(in);
    EXPECT_EQ(s.solve() && s.isComplete(), true);
    int** out = s.getNumbers();
    for (int i=0; i<9; i++)
        for (int j=0; j<9; j++)
            if (in[i][j] != 0)
                EXPECT_EQ(in[i][j], out[i][j]);
}

TEST(TP2_Ex2, testSudokuEmpty) {
    int in[9][9] =
            {{0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);
    EXPECT_EQ(s.isComplete(), true);
}

TEST(TP2_Ex2, testSudokuImpossible) {
    int in[9][9] =
            {{7, 0, 0, 1, 0, 8, 0, 0, 0},
             {4/*0*/, 9, 0, 0, 0, 0, 0, 3, 2},
             {0, 0, 0, 0, 0, 5, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 1, 0, 0},
             {9, 6, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 8, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 5, 0, 0, 1, 0, 0, 0},
             {3, 2, 0, 0, 0, 0, 0, 0, 6}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), false);

    int out[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            out[i][a] = res[i][a];

    compareSudokus(in, out);
}