#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define EMPTY INT_MIN  // для пустой ячейки

int** createMatrix(int rows, int cols);
int fillingMatrix(int** matrix, int rows, int cols);
int checkingCorrectMatrix(int** matrix, int rows, int cols);
int transpositionMatrix(int** matrix, int** matrix2, int rows, int cols);
int printMatrix(int** matrix, int rows, int cols);
void cleanMatrix(int** matrix, int rows);
int isEmpty(int value);

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
        return 1;
    }

    int test_data[] = {5, 6, 7, 8,EMPTY, EMPTY, EMPTY, EMPTY, 9, 10, 11, 12};
    for(int i = 0, k = 0; i < rows; i++)
        for(int j = 0; j < cols; j++) {
            matrix[i][j] = test_data[k];
            k++;
        }

    // fillingMatrix(matrix, rows, cols);

    if (checkingCorrectMatrix(matrix, rows, cols) != 0) {
        printf("error4");
        cleanMatrix(matrix, rows);
        cleanMatrix(matrix2, cols);
        return 1;
    }

    if (checkingCorrectMatrix(matrix2, cols, rows) != 0) {
        printf("error5");
        cleanMatrix(matrix, rows);
        cleanMatrix(matrix2, cols);
        return 1;
    }

    if (transpositionMatrix(matrix, matrix2, rows, cols) != 0) {
        printf("error6");
        cleanMatrix(matrix, rows);
        cleanMatrix(matrix2, cols);
        return 1;
    }

    if (printMatrix(matrix, rows, cols) != 0) {
        printf("error7");
        cleanMatrix(matrix, rows);
        cleanMatrix(matrix2, cols);
        return 1;
    }

    if (printMatrix(matrix2, cols, rows) != 0) {
        printf("error8");
        cleanMatrix(matrix, rows);
        cleanMatrix(matrix2, cols);
        return 1;
    }

    cleanMatrix(matrix, rows);
    cleanMatrix(matrix2, cols);

    return 0;
}

int empty(int n) {
    return n == EMPTY;
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
        // заполним пустыми
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = EMPTY;
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
    for (int i = 0; i < rows; i++) {
        if (matrix[i] == NULL)
            return 3;
    }
    return 0;
}

int transpositionMatrix(int** matrix, int** matrix2, int rows, int cols) {
    if (rows <= 0 || cols <= 0)
        return 1;

    if (matrix == NULL || matrix2 == NULL)
        return 2;

    // Сначала заполняем результат пустыми значениями
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            matrix2[i][j] = EMPTY;
        }
    }

    // Транспонируем только непустые элементы
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!empty(matrix[i][j])) {
                matrix2[j][i] = matrix[i][j];
            }
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
            if (!empty(matrix[i][j])) {
                printf("%d\t", matrix[i][j]);}
            /*if (empty(matrix[i][j])) {
                printf(".\t");  // для пустой
            }
            else {
                printf("%d\t", matrix[i][j]);
            }*/
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