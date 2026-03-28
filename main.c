#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** createMatrix(int rows, int cols);
int fillingMatrix(int** matrix, int rows, int cols);
int checkingCorrectMatrix(int** matrix, int rows, int cols);
int transpositionMatrix(int** matrix, int** matrix2, int rows, int cols);
int printMatrix(int** matrix, int rows, int cols);
int cleanMatrix(int** matrix, int rows);


int main() {
    int rows = 3, cols = 4;
    int** matrix = NULL;
    int** matrix2 = NULL;
    matrix = createMatrix(rows, cols);
    matrix2 = createMatrix(cols, rows);

    if (matrix != NULL && matrix2 != NULL) {
        // используем
        fillingMatrix(matrix, rows, cols);

        transpositionMatrix(matrix, matrix2, rows, cols);

        printMatrix(matrix, rows, cols);
        printMatrix(matrix2, cols, rows);

        // освобождаем
        cleanMatrix(matrix, rows);
        matrix = NULL;

        cleanMatrix(matrix2, cols);
        matrix2 = NULL;
    }
    else {
        if (matrix != NULL) {
            cleanMatrix(matrix, rows);
            matrix = NULL;
        }
        if (matrix2 != NULL) {
            cleanMatrix(matrix2, cols);
            matrix2 = NULL;
        }
        return 1;
    }
    return 0;
}


int** createMatrix(int rows, int cols){
    if (rows <= 0 || cols <= 0)
        return NULL;
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
    if (matrix == NULL || rows <= 0 || cols <= 0)
        return 1;

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


int transpositionMatrix(int** matrix, int** matrix2, int rows, int cols){
    if (matrix == NULL || matrix2 == NULL || rows <= 0 || cols <= 0)
        return 1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix2[j][i] = matrix[i][j];
        }
    }
    return 0;
}


int printMatrix(int** matrix, int rows, int cols){
    if (matrix == NULL|| rows <= 0 || cols <= 0)
        return 1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}


int cleanMatrix(int** matrix, int rows){
    if (matrix == NULL || rows <= 0)
        return 1;

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}



