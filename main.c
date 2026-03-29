#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** createMatrix(int rows, int cols);
int fillingMatrix(int** matrix, int rows, int cols);
int checkingCorrectMatrix(int** matrix, int rows, int cols);
int transpositionMatrix(int** matrix, int** matrix2, int rows, int cols);
int printMatrix(int** matrix, int rows, int cols);
void cleanMatrix(int** matrix, int rows);

int main() {
    int rows = 3, cols = 4;
    int** matrix = NULL;
    int** matrix2 = NULL;

    matrix = createMatrix(rows, cols);
    if (matrix == NULL) {
        printf("error1");
        return 1;
    }

    matrix2 = createMatrix(cols, rows);
    if (matrix2 == NULL) {
        printf("error2");
        cleanMatrix(matrix, rows);
        matrix = NULL;
        return 1;
    }

    if (fillingMatrix(matrix, rows, cols) != 0) {
        printf("error3");
        cleanMatrix(matrix, rows);
        cleanMatrix(matrix2, cols);
        matrix = NULL;
        matrix2 = NULL;
        return 1;
    }

    if (checkingCorrectMatrix(matrix, rows, cols) != 0) {
        printf("error4");
        cleanMatrix(matrix, rows);
        cleanMatrix(matrix2, cols);
        matrix = NULL;
        matrix2 = NULL;
        return 1;
    }

    if (checkingCorrectMatrix(matrix2, cols, rows) != 0) {
        printf("error5");
        cleanMatrix(matrix, rows);
        cleanMatrix(matrix2, cols);
        matrix = NULL;
        matrix2 = NULL;
        return 1;
    }

    if (transpositionMatrix(matrix, matrix2, rows, cols) != 0) {
        printf("error6");
        cleanMatrix(matrix, rows);
        cleanMatrix(matrix2, cols);
        matrix = NULL;
        matrix2 = NULL;
        return 1;
    }

    // Выводим исходную матрицу
    if (printMatrix(matrix, rows, cols) != 0) {
        printf("error7");
        cleanMatrix(matrix, rows);
        cleanMatrix(matrix2, cols);
        matrix = NULL;   // Обнуляем указатели после очистки
        matrix2 = NULL;
        return 1;
    }

    if (printMatrix(matrix2, cols, rows) != 0) {
        printf("error8");
        cleanMatrix(matrix, rows);
        cleanMatrix(matrix2, cols);
        matrix = NULL;   // Обнуляем указатели после очистки
        matrix2 = NULL;
        return 1;
    }

    cleanMatrix(matrix, rows);
    cleanMatrix(matrix2, cols);
    matrix = NULL;   // Обнуляем указатели после очистки
    matrix2 = NULL;

    return 0;
}

int** createMatrix(int rows, int cols) {
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

int fillingMatrix(int** matrix, int rows, int cols) {
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

int checkingCorrectMatrix(int** matrix, int rows, int cols) {
    if (matrix == NULL) {
        return 1;
    }

    if (rows <= 0 || cols <= 0) {
        return 2;
    }

    int f = 0;
    for (int i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            f++;
        }
    }
    if (f == rows)
        return 3;

    return 0;
}

int transpositionMatrix(int** matrix, int** matrix2, int rows, int cols) {
    if (rows <= 0 || cols <= 0)
        return 1;

    if (matrix == NULL || matrix2 == NULL)
        return 2;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix2[j][i] = matrix[i][j];
        }
    }
    return 0;
}

int printMatrix(int** matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0)
        return 1;

    for (int i = 0; i < rows; i++) {
        if (matrix[i] == NULL)
            return 2;

        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

void cleanMatrix(int** matrix, int rows) {
    if (matrix == NULL)
        return;

    if (rows <= 0) {
        free(matrix);
        return;
    }

    for (int i = 0; i < rows; i++) {
        if (matrix[i] != NULL) {
            free(matrix[i]);
        }
    }

    free(matrix);
}