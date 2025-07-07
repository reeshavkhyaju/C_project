#include <stdio.h>
void initializeBoard();
void printBoard();
int isBoardFull();
int checkWin(char);
void makeMove(char);
void computerMove(char);
int minimax(char player);
char board[3][3];
int main() {
    char currentPlayer = 'X'; 
    initializeBoard();
    printf("TIC TAC TOE\n");
    printf("You are playing against the computer.\n");

    while (1) {
        printBoard();
        if (currentPlayer == 'X') {
            makeMove(currentPlayer);
        } else {
            computerMove(currentPlayer);
        }

        if (checkWin(currentPlayer)) {
            printBoard();
            if (currentPlayer == 'X') {
                printf("Congratulations! You win!\n");
            } else {
                printf("Computer wins!\n");
            }
            break;
        } else if (isBoardFull()) {
            printBoard();
            printf("It's a draw!\n");
            break;
        }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}
void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("\n");
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

int checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1;
    }
    return 0;
}

void makeMove(char player) {
    int row, col;
    do {
        printf("Player %c, enter row (0-2) and column (0-2) separated by space: ", player);
        scanf("%d %d", &row, &col);
        //row--;
        //col--;
    } while (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ');

    board[row][col] = player;
}

void computerMove(char player) {
    int bestScore = -10;
    int bestMoveRow = -1;
    int bestMoveCol = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = player;
                int score = minimax(player == 'X' ? 'O' : 'X');
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestMoveRow = i;
                    bestMoveCol = j;
                }
            }
        }
    }

    printf("Computer chooses row %d, column %d.\n", bestMoveRow, bestMoveCol);
    board[bestMoveRow][bestMoveCol] = player;
}

int minimax(char player) {
    if (checkWin('X')) return -1;
    if (checkWin('O')) return 1;
    if (isBoardFull()) return 0;
    if (player == 'X') {
        int maxScore = -1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax('O');
                    board[i][j] = ' ';
                    if (score > maxScore) {
                        maxScore = score;
                    }
                }
            }
        }
        return maxScore;
    } else {
        int minScore = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax('X');
                    board[i][j] = ' ';
                    if (score < minScore) {
                        minScore = score;
                    }
                }
            }
        }
        return minScore;
    }
}





