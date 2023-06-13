#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 4

int board[BOARD_SIZE][BOARD_SIZE];
int score = 0;

void clear_screen() {
    system("cls || clear");
}

void print_board() {
    clear_screen();
    printf("\nScore: %d\n\n", score);
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%d\t", board[i][j]);
        }
        printf("\n");
    }
}

void init_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void add_random_tile() {
    int row, col;
    do {
        row = rand() % BOARD_SIZE;
        col = rand() % BOARD_SIZE;
    } while (board[row][col] != 0);
    board[row][col] = (rand() % 2 + 1) * 2;
}

void merge_tiles(int row, int col, int next_row, int next_col) {
    board[row][col] *= 2;
    score += board[row][col];
    board[next_row][next_col] = 0;
}

void move_tiles(int row, int col, int next_row, int next_col) {
    board[next_row][next_col] = board[row][col];
    board[row][col] = 0;
}

void move_up() {
    for (int col = 0; col < BOARD_SIZE; col++) {
        int last_merged_row = -1;
        for (int row = 1; row < BOARD_SIZE; row++) {
            if (board[row][col] == 0) {
                continue;
            }
            int next_row = row - 1;
            while (next_row >= 0 && board[next_row][col] == 0) {
                next_row--;
            }
            if (next_row == -1) {
                move_tiles(row, col, 0, col);
            } else if (board[next_row][col] == board[row][col] && last_merged_row != next_row) {
                merge_tiles(row, col, next_row, col);
                last_merged_row = next_row;
            } else if (next_row + 1 != row) {
                move_tiles(row, col, next_row + 1, col);
            }
        }
    }
}

void move_down() {
    for (int col = 0; col < BOARD_SIZE; col++) {
        int last_merged_row = BOARD_SIZE;
        for (int row = BOARD_SIZE - 2; row >= 0; row--) {
            if (board[row][col] == 0) {
                continue;
            }
            int next_row = row + 1;
            while (next_row < BOARD_SIZE && board[next_row][col] == 0) {
                next_row++;
            }
            if (next_row == BOARD_SIZE) {
                move_tiles(row, col, BOARD_SIZE - 1, col);
            } else if (board[next_row][col] == board[row][col] && last_merged_row != next_row) {
                merge_tiles(row, col, next_row, col);
                last_merged_row = next_row;
            } else if (next_row - 1 != row) {
                move_tiles(row, col, next_row - 1, col);
            }
        }
    }
}

void move_left() {
    for (int row = 0; row < BOARD_SIZE; row++) {
        int last_merged_col = -1;
        for (int col = 1; col < BOARD_SIZE; col++) {
            if (board[row][col] == 0) {
                continue;
            }
            int next_col = col - 1;
            while (next_col >= 0 && board[row][next_col] == 0) {
                next_col--;
            }
            if (next_col == -1) {
                move_tiles(row, col, row, 0);
            } else if (board[row][next_col] == board[row][col] && last_merged_col != next_col) {
                merge_tiles(row, col, row, next_col);
                last_merged_col = next_col;
            } else if (next_col + 1 != col) {
                move_tiles(row, col, row, next_col + 1);
            }
        }
    }
}

void move_right() {
    for (int row = 0; row < BOARD_SIZE; row++) {
        int last_merged_col = BOARD_SIZE;
        for (int col = BOARD_SIZE - 2; col >= 0; col--) {
            if (board[row][col] == 0) {
                continue;
            }
            int next_col = col + 1;
            while (next_col < BOARD_SIZE && board[row][next_col] == 0) {
                next_col++;
            }
            if (next_col == BOARD_SIZE) {
                move_tiles(row, col, row, BOARD_SIZE - 1);
            } else if (board[row][next_col] == board[row][col] && last_merged_col != next_col) {
                merge_tiles(row, col, row, next_col);
                last_merged_col = next_col;
            } else if (next_col - 1 != col) {
                move_tiles(row, col, row, next_col - 1);
            }
        }
    }
}

int check_game_over() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
            if (i < BOARD_SIZE - 1 && board[i][j] == board[i + 1][j]) {
                return 0;
            }
            if (j < BOARD_SIZE - 1 && board[i][j] == board[i][j + 1]) {
                return 0;
            }
        }
    }
    return 1;
}

int check_game_won() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 2048) {
                return 1;
            }
        }
    }
    return 0;
}

void game_loop() {
    init_board();
    add_random_tile();
    add_random_tile();
    print_board();
    while (1) {
        char input = getchar();
        if (input == 'w' || input == 'W') {
            move_up();
        } else if (input == 's' || input == 'S') {
            move_down();
        } else if (input == 'a' || input == 'A') {
            move_left();
        } else if (input == 'd' || input == 'D') {
            move_right();
        } else if (input == 'q' || input == 'Q') {
            break;
        }
        if (check_game_won()) {
            printf("\nYou won!\n");
            break;
        }
        if (check_game_over()) {
            printf("\nGame over!\n");
            break;
        }
        add_random_tile();
        print_board();
    }
}

int main() {
    srand(time(NULL));
    game_loop();
    return 0;
}