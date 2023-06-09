#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 9

// Функция за проверка на валидността на поставеното число на дадена позиция
int isValid(int puzzle[SIZE][SIZE], int row, int col, int num) {
    // Проверка за валидност по реда и колоната
    for (int i = 0; i < SIZE; i++) {
        if (puzzle[row][i] == num || puzzle[i][col] == num) {
            return 0;
        }
    }

    // Проверка за валидност във вътрешния квадрат 3x3
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[startRow + i][startCol + j] == num) {
                return 0;
            }
        }
    }

    return 1;
}

// Функция за решаване на судоку
int solveSudoku(int puzzle[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            // Търсене на непопълнена клетка
            if (puzzle[row][col] == 0) {
                for (int num = 1; num <= SIZE; num++) {
                    // Проверка на възможността да се постави число
                    if (isValid(puzzle, row, col, num)) {
                        // Поставяне на числото
                        puzzle[row][col] = num;

                        // Рекурсивно решаване на останалата част от судоку
                        if (solveSudoku(puzzle)) {
                            return 1;
                        }

                        // Връщане на нула, ако се достигне невалидна конфигурация
                        puzzle[row][col] = 0;
                    }
                }

                // Връщане на нула, ако не се намери валидно число
                return 0;
            }
        }
    }

    // Връщане на едно, ако судокуто е решено
    return 1;
}

// Функция за извличане на судоку от .ss файл
void extractSudokuFromSSFile(const char* filename, int puzzle[SIZE][SIZE]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    char line[20];
    int row = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '-') {
            continue;
        }

        int col = 0;
        for (int i = 0; i < strlen(line); i++) {
            if (line[i] >= '1' && line[i] <= '9') {
                puzzle[row][col] = line[i] - '0';
                col++;
            } else if (line[i] == '.' || line[i] == ' ') {
                puzzle[row][col] = 0;
                col++;
            }
        }

        row++;
    }

    fclose(file);
}

// Функция за запис на судоку в .ss файл
void saveSudokuToSSFile(const char* filename, int puzzle[SIZE][SIZE]) {
    FILE* file = fopen(filename, "a"); // Отваряне на файла за дописване
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    fprintf(file, "\n"); // Нов ред преди записването на решението

    for (int row = 0; row < SIZE; row++) {
        if (row % 3 == 0 && row != 0) {
            fprintf(file, "---+---+---\n");
        }
        for (int col = 0; col < SIZE; col++) {
            if (col % 3 == 0 && col != 0) {
                fprintf(file, "|");
            }
            if (puzzle[row][col] == 0) {
                fprintf(file, ".");
            } else {
                fprintf(file, "%d", puzzle[row][col]);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Функция за извеждане на судоку на екрана
void printSudoku(int puzzle[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        if (row % 3 == 0 && row != 0) {
            printf("-----------\n");
        }
        for (int col = 0; col < SIZE; col++) {
            if (col % 3 == 0 && col != 0) {
                printf("|");
            }
            if (puzzle[row][col] == 0) {
                printf(" .");
            } else {
                printf("%2d", puzzle[row][col]);
            }
        }
        printf("\n");
    }
}

// Главна функция
int main() {
    char filename[100];
    printf("Enter the filename: ");
    scanf("%s", filename);

    int puzzle[SIZE][SIZE];

    // Извличане на судоку от .ss файла
    extractSudokuFromSSFile(filename, puzzle);

    // Решаване на судоку
    if (solveSudoku(puzzle)) {
        // Извеждане на решението на екрана
        printf("Sudoku solved successfully:\n");
        printSudoku(puzzle);

        // Запис на решението в .ss файл
        char outputFilename[100];
        strcpy(outputFilename, "sudoku_solution.ss");
        saveSudokuToSSFile(outputFilename, puzzle);
        printf("Solution saved in %s\n", outputFilename);
    } else {
        printf("Unable to solve the sudoku.\n");
    }

    return 0;
}