#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** createMatrix(int rows, int cols);
int fillingMatrix(int** matrix, int rows, int cols);
int checkingCorrectMatrix(int** matrix, int rows, int cols);
int transpositionMatrix(int** matrix, int rows, int cols);
int printMatrix(int** matrix, int rows, int cols);
int cleanMatrix(int** matrix, int rows);


int main() {
    int rows = 2, cols = 3;
    int** matrix = NULL;
    matrix = createMatrix(rows, cols);

    if (matrix != NULL) {
        // используем

        // освобождаем
        cleanMatrix(matrix, rows);
    }
    return 0;
}


int** createMatrix(int rows, int cols){
    int** matrix = (int**)calloc(rows, sizeof(int*));

    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)calloc(cols, sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    return matrix;
}


int fillingMatrix(int** matrix, int rows, int cols){
    srand(time(NULL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100 + 1;
        }
    }
    return 0;
}


int checkingCorrectMatrix(int** matrix, int rows, int cols){
    return 0;
}


int transpositionMatrix(int** matrix, int rows, int cols){
    return 0;
}


int printMatrix(int** matrix, int rows, int cols){
    return 0;
}


int cleanMatrix(int** matrix, int rows){
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}



