// 2048.cpp: Definuje vstupní bod pro aplikaci.
//

#include "2048.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define SIZE 4

int board[SIZE][SIZE];
int score = 0;

void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void printBoard() {
    system("cls");
    printf("Vitej ve hre 2048\nHra se ovlada klavesami W (nahoru) - A (doleva) - S (dolu) - D (doprava)\n");
    printf("Score: %d\n", score);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                printf("  . ");
            }
            else {
                printf("%4d", board[i][j]);
            }
        }
        printf("\n");
    }
}

int getRandomEmptyCell() {
    int emptyCells[SIZE * SIZE];
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                emptyCells[count] = i * SIZE + j;
                count++;
            }
        }
    }
    if (count == 0) return -1;
    int randomIndex = rand() % count;
    return emptyCells[randomIndex];
}

void addRandomTile() {
    int cell = getRandomEmptyCell();
    if (cell != -1) {
        int value = (rand() % 2 + 1) * 2;
        int row = cell / SIZE;
        int col = cell % SIZE;
        board[row][col] = value;
    }
}

int isGameOver() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
            if ((i < SIZE - 1 && board[i][j] == board[i + 1][j]) ||
                (j < SIZE - 1 && board[i][j] == board[i][j + 1])) {
                return 0;
            }
        }
    }
    return 1;
}

void moveLeft() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            if (board[i][j] != 0) {
                int k = j - 1;
                while (k >= 0) {
                    if (board[i][k] == 0) {
                        board[i][k] = board[i][k + 1];
                        board[i][k + 1] = 0;
                        k--;
                    }
                    else if (board[i][k] == board[i][k + 1]) {
                        board[i][k] *= 2;
                        score += board[i][k];
                        board[i][k + 1] = 0;
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
}

void moveRight() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE - 2; j >= 0; j--) {
            if (board[i][j] != 0) {
                int k = j + 1;
                while (k < SIZE) {
                    if (board[i][k] == 0) {
                        board[i][k] = board[i][k - 1];
                        board[i][k - 1] = 0;
                        k++;
                    }
                    else if (board[i][k] == board[i][k - 1]) {
                        board[i][k] *= 2;
                        score += board[i][k];
                        board[i][k - 1] = 0;
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
}

void moveUp() {
    for (int j = 0; j < SIZE; j++) {
        for (int i = 1; i < SIZE; i++) {
            if (board[i][j] != 0) {
                int k = i - 1;
                while (k >= 0) {
                    if (board[k][j] == 0) {
                        board[k][j] = board[k + 1][j];
                        board[k + 1][j] = 0;
                        k--;
                    }
                    else if (board[k][j] == board[k + 1][j]) {
                        board[k][j] *= 2;
                        score += board[k][j];
                        board[k + 1][j] = 0;
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
}

void moveDown() {
    for (int j = 0; j < SIZE; j++) {
        for (int i = SIZE - 2; i >= 0; i--) {
            if (board[i][j] != 0) {
                int k = i + 1;
                while (k < SIZE) {
                    if (board[k][j] == 0) {
                        board[k][j] = board[k - 1][j];
                        board[k - 1][j] = 0;
                        k++;
                    }
                    else if (board[k][j] == board[k - 1][j]) {
                        board[k][j] *= 2;
                        score += board[k][j];
                        board[k - 1][j] = 0;
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    initializeBoard();
    addRandomTile();
    addRandomTile();
    printBoard();

    int key;
    while (1) {
        key = _getch();
        switch (key) {
        case 'a':
            moveLeft();
            break;
        case 'd':
            moveRight();
            break;
        case 'w':
            moveUp();
            break;
        case 's':
            moveDown();
            break;
        case 27:
            exit(0);
            break;
        }
        if (isGameOver()) {
            printf("Hra skoncila, neexistuje dalsi platny tah.\n");
            break;
        }
        if (key == 'a' || key == 'd' || key == 'w' || key == 's') {
            addRandomTile();
        }
        printBoard();
    }
    return 0;
}

