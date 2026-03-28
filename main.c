#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char** createMatrix(int rows, int cols);
int fillingMatrix(char** matrix);
int checkingCorrectMatrix(char** matrix);
int transpositionMatrix(char** matrix);
int printMatrix(char** matrix);
int cleanMatrix(char** matrix);


int main() {
    int rows = 2, cols = 3;
    char** matrix = NULL;
    matrix = createMatrix(rows, cols);

    if (matrix != NULL) {
        // используем

        // освобождаем
        cleanMatrix(matrix);
    }
    return 0;
}


char** createMatrix(int rows, int cols){
    char** matrix = (char**)calloc(rows, sizeof(char*));

    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (char*)calloc(cols + 1, sizeof(char));
        matrix[i][cols] = '\n';

        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    matrix[rows] = NULL;

    return matrix;
}


int fillingMatrix(char** matrix){
    return 0;
}


int checkingCorrectMatrix(char** matrix){
    return 0;
}


int transpositionMatrix(char** matrix){
    return 0;
}


int printMatrix(char** matrix){
    return 0;
}


int cleanMatrix(char** matrix){
    for (int i = 0; matrix[i] != NULL; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}



