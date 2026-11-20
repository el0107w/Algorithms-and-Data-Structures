#pragma once
#include <iostream>
#include <cmath>

using namespace std;

// Задача 1: Факториал
inline long long factorialRec(int n) {
    if (n <= 1) return 1;
    return n * factorialRec(n - 1);
}

inline long long factorialIter(int n) {
    long long res = 1;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

// Задача 2: Фибоначчи
inline long long fibRec(int n) {
    if (n <= 1) return n;
    return fibRec(n - 1) + fibRec(n - 2);
}

inline long long fibIter(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        long long c = a + b; a = b; b = c;
    }
    return b;
}

// Задача 3: Лабиринт 6x6
static const int MAZE_SIZE = 6;
static char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'S', '.', '#', '.', '.', '.'},
    {'.', '.', '#', '.', '#', '.'},
    {'.', '.', '.', '.', '#', '.'},
    {'#', '#', '.', '#', '.', '.'},
    {'.', '.', '.', '.', '.', '.'},
    {'.', '#', '#', '#', '#', 'F'}
};
static bool visited[MAZE_SIZE][MAZE_SIZE] = { false };

inline bool solveMaze(int x, int y) {
    if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE) return false;
    if (maze[x][y] == '#' || visited[x][y]) return false;
    if (maze[x][y] == 'F') { maze[x][y] = '*'; return true; }

    visited[x][y] = true;
    maze[x][y] = '*';

    if (solveMaze(x + 1, y)) return true;
    if (solveMaze(x - 1, y)) return true;
    if (solveMaze(x, y + 1)) return true;
    if (solveMaze(x, y - 1)) return true;

    maze[x][y] = '.';
    return false;
}

inline void printMaze() {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) cout << maze[i][j] << " ";
        cout << endl;
    }
}

// Задача 4: Ферзи 5x5
static const int N_QUEENS = 5;
static int board[N_QUEENS];

inline bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) return false;
    }
    return true;
}

inline bool solveNQueens(int row) {
    if (row == N_QUEENS) return true;
    for (int col = 0; col < N_QUEENS; col++) {
        if (isSafe(row, col)) {
            board[row] = col;
            if (solveNQueens(row + 1)) return true;
        }
    }
    return false;
}

inline void printQueens() {
    for (int i = 0; i < N_QUEENS; i++) {
        for (int j = 0; j < N_QUEENS; j++) {
            if (board[i] == j) cout << "Q ";
            else cout << ". ";
        }
        cout << endl;
    }
}