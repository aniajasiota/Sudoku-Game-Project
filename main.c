#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define EMPTY 0
int** board = NULL;
int size = 4;
int block_size = 2;
int** solution_board = NULL;
time_t start_time, end_time;

void init_board(int size) {
	board = calloc(size, sizeof(int*));
	if (board == NULL) {
		printf("Memory allocation error.\n");
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		board[i] = calloc(size, sizeof(int));
		if (board[i] == NULL) {
			printf("Memory allocation error.\n");
			exit(1);
		}
	}
}
void clear_solution_board() {
	for (int i = 0; i < size; i++)
		free(solution_board[i]);
	free(solution_board);
}
void clear_board() {
	for (int i = 0; i < size; i++)
		free(board[i]);
	free(board);
}

void save(const char* filename) {
	FILE* file;
	fopen_s(&file, filename, "w");
	if (file == NULL) {
		printf("Cannot open file for saving.\n");
		return;
	}
	fprintf(file, "%d %d\n", size, block_size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fprintf(file, "%d ", board[i][j]);
		}
		fprintf(file, "\n");
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fprintf(file, "%d ", solution_board[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
	printf("The game has been saved to file '%s'.\n", filename);
}

void load_previous_game(const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "r");
    if (file == NULL) {
        printf("ERROR: Cannot open file '%s' to load game.\n", filename);
        return;
    }

    if (fscanf(file, "%d %d", &size, &block_size) != 2) {
        printf("ERROR: Corrupted save file.\n");
        fclose(file);
        return;
    }

    init_board(size);
    solution_board = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        solution_board[i] = (int*)malloc(size * sizeof(int));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (fscanf(file, "%d", &board[i][j]) != 1) {
                printf("ERROR: Corrupted board data.\n");
                fclose(file);
                return;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (fscanf(file, "%d", &solution_board[i][j]) != 1) {
                printf("ERROR: Corrupted solution data.\n");
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
    printf("Previous game loaded successfully from '%s'.\n", filename);
}


int is_valid(int r, int c, int num) {
	for (int i = 0; i < size; i++) {
		if (board[r][i] == num || board[i][c] == num)
			return 0;
	}

	int startRow = r - r % block_size;
	int startCol = c - c % block_size;

	for (int i = startRow; i < startRow + block_size; i++) {
		for (int j = startCol; j < startCol + block_size; j++) {
			if (board[i][j] == num)
				return 0;
		}
	}
	return 1;
}

int check() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] != solution_board[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

void shuffle(int* array, int n) {
	for (int i = 0; i < n - 1; i++) {
		int j = i + rand() / (RAND_MAX / (n - i) + 1);
		int tmp = array[j];
		array[j] = array[i];
		array[i] = tmp;
	}
}

int fill(int r, int c) {
	if (r == size)
		return 1;

	int nextRow = (c == size - 1) ? r + 1 : r;
	int nextCol = (c + 1) % size;

	int* nums = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) nums[i] = i + 1;
	shuffle(nums, size);

	for (int i = 0; i < size; i++) {
		if (is_valid(r, c, nums[i])) {
			board[r][c] = nums[i];
			if (fill(nextRow, nextCol)) {
				free(nums);
				return 1;
			}
			board[r][c] = EMPTY;
		}
	}
	free(nums);
	return 0;
}

void show_board() {
	printf("    ");
	for (int j = 0; j < size; j++) {
		if (j % block_size == 0 && j != 0)
			printf("*");
		printf("%2d ", j + 1);
	}
	printf("\n");

	printf("   ");
	for (int j = 0; j < size + (size - 1) / block_size; j++) {
		printf("***");
	}
	printf("\n");

	for (int i = 0; i < size; i++) {
		if (i % block_size == 0 && i != 0) {
			printf("   ");
			for (int k = 0; k < size + (size - 1) / block_size; k++) {
				printf("***");
			}
			printf("\n");
		}

		printf("%2d *", i + 1);

		for (int j = 0; j < size; j++) {
			if (j % block_size == 0 && j != 0)
				printf("*");

			if (board[i][j] == EMPTY)
				printf(" _ ");
			else if (size == 16 && board[i][j] < 10)
				printf(" %d ", board[i][j]);
			else
				printf("%2d ", board[i][j]);
		}
		printf("\n");
	}
}

int count_solutions(int r, int c, int* count) {
	if (r == size) {
		(*count)++;
		return *count > 1 ? 1 : 0;
	}

	int nextRow = (c == size - 1) ? r + 1 : r;
	int nextCol = (c + 1) % size;

	if (board[r][c] != EMPTY)
		return count_solutions(nextRow, nextCol, count);

	for (int num = 1; num <= size; num++) {
		if (is_valid(r, c, num)) {
			board[r][c] = num;
			if (count_solutions(nextRow, nextCol, count))
				return 1;
			board[r][c] = EMPTY;
		}
	}
	return 0;
}

void remove_numbers(int clues) {
	solution_board = (int**)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		solution_board[i] = (int*)malloc(size * sizeof(int));
		for (int j = 0; j < size; j++) {
			solution_board[i][j] = board[i][j];
		}
	}

	int total = size * size;
	int attempts = total - clues;

	while (attempts > 0) {
		int r = rand() % size;
		int c = rand() % size;

		if (board[r][c] == EMPTY)
			continue;

		int backup = board[r][c];
		board[r][c] = EMPTY;

		int count = 0;
		count_solutions(0, 0, &count);

		if (count != 1) {
			board[r][c] = backup;
		}
		else {
			attempts--;
		}
	}
}

void show_game_guide() {
    printf("QUICK HOW TO PLAY TUTORIAL\n");
    printf("GAMEPLAY GUIDE\n");
    printf("Enter coordinates like '13 2' to place into row 1 column 2 a value 1.\n");
    printf("To remove a value, enter '13 0'.\n");
    printf("To end the game, type '000'.\n");
}

void game() {
	int row_col, value;

	printf("\nEnter coordinates like '13 2' to place into row 1 column 3 a value 2.\n");
	printf("To remove a value, enter '13 0'.\n");
    printf("To end the game, type '000'.\n");

	start_time = time(NULL);
	while (1) {
		printf("\n");
		show_board();
        printf("\nEnter coordinates like '13 2' to place into row 1 column 3 a value 2.\n");
		while (scanf_s("%d %d", &row_col, &value) != 2) {
			while (getchar() != '\n');
			printf("ERROR. Enter coordinates like '13 2' to place into row 1 column 3 a value 2.\n");
		}

		if (row_col == 0 && value == 0) {
			int choice;
			end_time = time(NULL);
			double elapsed_time = difftime(end_time, start_time);
			int minutes = (int)(elapsed_time / 60);
			int seconds = (int)((int)elapsed_time % 60);
			printf("Do you want to save the game before exiting? 1 - yes, 0 - no: ");
			while (scanf_s("%d", &choice) != 1 || (choice != 0 && choice != 1)) {
				while (getchar() != '\n');
				printf("Invalid input. Enter 1 for yes or 0 for no: ");
			}
			if (choice == 1) {
				save("save.txt");
			}
			printf("You solved this in: %d minutes, %d seconds.\n", minutes, seconds);
			printf("END. Thank you for playing\n");
			break;
		}

		int r = row_col / 10;
		int c = row_col % 10;

		if (r < 1 || r > size || c < 1 || c > size || value < 0 || value > size) {
			printf("ERROR. Please try again.\n");
			continue;
		}

		int i = r - 1;
		int j = c - 1;

		if (value == 0) {
			if (board[i][j] == EMPTY) {
				printf("This cell is empty.\n");
				continue;
			}
			board[i][j] = EMPTY;
			printf("Removed value from (%d, %d).\n", r, c);
		} else {
			if (board[i][j] != EMPTY) {
				printf("You cant insert value here. Remove to insert new one (enter %d 0).\n", row_col);
				continue;
			}
			board[i][j] = value;
		}

		if (check()) {
			printf("Congratulations :)) You solved it!!!\n");
			end_time = time(NULL);
			double elapsed_time = difftime(end_time, start_time);
			int minutes = (int)(elapsed_time / 60);
			int seconds = (int)((int)elapsed_time % 60);
			printf("Game time: %d minutes, %d seconds.\n", minutes, seconds);
			break;
		}
	}
}

void select_game_parameters() {
	int how_difficult;
	printf("\nChoose your game difficulty level:\n");
	printf("1| Easy, 2| Medium, 3| Hard. Your choice: ");
	while (scanf_s("%d", &how_difficult) != 1 || (how_difficult < 1 || how_difficult > 3)) {
		while (getchar() != '\n');
		printf("ERROR!!! Please choose number 1-3 ");
	}

    printf("\nChoose size of your sudoku:\n");
	printf("1| 4x4, 2| 9x9, 3| 16x16. Your choice: ");
	int what_size;
	while (scanf_s("%d", &what_size) != 1 || (what_size < 1 || what_size > 3)) {
		while (getchar() != '\n');
		printf("ERROR!!! Please choose number 1-3 :");
	}
    if (what_size == 1) {
        size = 4;
        block_size = 2;
    } else if (what_size == 2) {
        size = 9;
        block_size = 3;
    } else if (what_size == 3) {
        size = 16;
        block_size = 4;
    } else {
        printf("Invalid choice, defaulting to 4x4.\n");
        size = 4;
        block_size = 2;
    }

	int clues;
	int total_cells = size * size;
	if (how_difficult == 1) {
        clues = total_cells * 0.6;
    } else if (how_difficult == 2) {
        clues = total_cells * 0.45;
    } else if (how_difficult == 3) {
        clues = total_cells * 0.35;
    } else {
        printf("Invalid choice, defaulting to easy.\n");
        clues = total_cells * 0.6;
    }

	init_board(size);
	fill(0, 0);
	remove_numbers(clues);
	game();
	clear_board();
}
    void menu() {
	int choice;
	while (1) {
        printf("WELCOME TO SUDOKU GAME :))\n");
        printf("Choose an option to start:\n");
		printf("1| INSTRUCTION\n");
		printf("2| NEW GAME\n");
		printf("3| LOAD A PREVIOUS GAME\n");
		printf("4| EXIT\n");
		printf("Your choice: ");
		while (scanf_s("%d", &choice) != 1 || (choice < 1 || choice > 4)) {
			while (getchar() != '\n');
			printf("ERROR!!! Please choose number 1-4 :\n");
		}

		if (choice == 1) {
            show_game_guide();
        } else if (choice == 2) {
            select_game_parameters();
        } else if (choice == 3) {
            load_previous_game("previousgame.txt");
        } else if (choice == 4) {
            printf("Thank you for playing our game. Bye!!!\n");
            return;
        } else {
            printf("ERROR!!! Please choose number 1-4 :\n");
        }
        printf("\n");
	}
}
int main() {
	srand((unsigned int)time(NULL));
	menu();
	return 0;
}

