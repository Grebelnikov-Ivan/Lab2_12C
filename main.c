
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define EMPTY INT_MIN  // для пустой ячейки

int** createMatrix(size_t rows, size_t cols);
int fillingMatrix(int** matrix, size_t rows, size_t cols, int min_g, int max_g);
int checkingCorrectMatrix(int** matrix, size_t rows, size_t cols);
int** transpositionMatrix(int** matrix, size_t rows, size_t cols);
int printMatrix(int** matrix, size_t rows, size_t cols);
int cleanMatrix(int** matrix, size_t rows);
int empty(int n);

int main(){
    size_t rows = 3, cols = 4;
    int** matrix = NULL;
    int** matrix2 = NULL;

    matrix = createMatrix(rows, cols);
    if (matrix == NULL) {
        printf("error1");
        return 1;
    }

    /*int test_data[] = {5, 6, 7, 8, EMPTY, EMPTY, EMPTY, EMPTY, 9, 10, 11, 12};
    for(size_t i = 0, k = 0; i < rows; i++)
        for(size_t j = 0; j < cols; j++) {
            matrix[i][j] = test_data[k];
            k++;
        }*/
    int min_g = -100;
    int max_g = 100;
    if (fillingMatrix(matrix, rows, cols, min_g, max_g) != 0) {
        printf("error10");
        cleanMatrix(matrix, rows);
        return 1;
    }

    if (checkingCorrectMatrix(matrix, rows, cols) != 0) {
        printf("error4");
        cleanMatrix(matrix, rows);
        return 1;
    }

    if (printMatrix(matrix, rows, cols) != 0) {
        printf("error7");
        cleanMatrix(matrix, rows);
        return 1;
    }

    matrix2 = transpositionMatrix(matrix, rows, cols);
    if (matrix2 == NULL) {
        printf("error6");
        return 1;
    }

    if (printMatrix(matrix2, cols, rows) != 0) {
        printf("error8");
        cleanMatrix(matrix2, cols);
        return 1;
    }

    cleanMatrix(matrix2, cols);

    matrix = NULL;
    matrix2 = NULL;

    return 0;
}

int empty(int n) {
    return n == EMPTY;
}

int** createMatrix(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0)
        return NULL;

    int** matrix = (int**)calloc(rows, sizeof(int*));
    if (matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        matrix[i] = (int*)calloc(cols, sizeof(int));
        if (matrix[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = EMPTY;
        }
    }
    return matrix;
}

int fillingMatrix(int** matrix, size_t rows, size_t cols, int min_g, int max_g){
    if (matrix == NULL || rows == 0 || cols == 0)
        return 1;

    if (min_g > max_g) {
        return 2;
    }

    srand(time(NULL));

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = min_g + rand() % (max_g - min_g + 1);
        }
    }
    return 0;
}

int checkingCorrectMatrix(int** matrix, size_t rows, size_t cols) {
    if (matrix == NULL) {
        return 1;
    }
    if (rows == 0 || cols == 0) {
        return 2;
    }
    for (size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL)
            return 3;
    }
    return 0;
}

int** transpositionMatrix(int** matrix, size_t rows, size_t cols) {
    if (matrix == NULL || rows == 0 || cols == 0) {
        return NULL;
    }

    // проверка, что все строки матрицы существуют
    for ( size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            cleanMatrix(matrix, rows);
            return NULL;
        }
    }

    int** result = NULL;
    result = createMatrix(cols, rows);
    if (result == NULL) {
        cleanMatrix(matrix, rows);
        return NULL;
    }

    // Проверка, что все строки результирующей матрицы созданы корректно
    for (size_t i = 0; i < cols; i++) {
        if (result[i] == NULL) {
            cleanMatrix(result, cols);
            cleanMatrix(matrix, rows);
            return NULL;
        }
    }

    // Транспонируем только непустые элементы
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (!empty(matrix[i][j])) {
                result[j][i] = matrix[i][j];
            }
        }
    }

    cleanMatrix(matrix, rows);

    return result;
}

int printMatrix(int** matrix, size_t rows, size_t cols) {
    if (matrix == NULL || rows == 0 || cols == 0)
        return 1;

    for (size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL)
            return 2;

        for (size_t j = 0; j < cols; j++) {
            if (!empty(matrix[i][j])) {
                printf("%d\t", matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int cleanMatrix(int** matrix, size_t rows) {
    if (matrix == NULL)
        return 0;

    if (rows == 0) {
        free(matrix);
        return 1;
    }

    for (size_t i = 0; i < rows; i++) {
        if (matrix[i] != NULL) {
            free(matrix[i]);
            matrix[i] = NULL;
        }
    }

    free(matrix);
    return 0;
}