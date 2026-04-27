//define 3
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int** createMatrix(size_t rows, size_t cols);
int fillingMatrix(int** matrix, size_t rows, size_t cols, int min_g, int max_g);
int** transpositionMatrix(int** matrix, size_t rows, size_t cols);
int printMatrix(int** matrix, size_t rows, size_t cols);
int cleanMatrix(int*** matrix, size_t rows);
int** multiplyMatrixs(int** matrix11, size_t rows1, size_t cols1, int** matrix22, size_t rows2, size_t cols2);

int main() {
    int** M = createMatrix(2, 3);

    if (M) {
        printf("createMatrix\n");
        cleanMatrix(&M, 2);
        if (M == NULL) {
            printf("cleanMatrix yes\n");
        }
        else {
            printf("cleanMatrix no\n");
        }
    } else {
        printf("cleanMatrix no\n");
    }

    size_t rows = 3, cols = 4;

    if (rows <= 0 || cols <= 0) {
        printf("Error with size\n");
        return 0;
    }

    int start = 5, end = 100;
    int** A = createMatrix(rows, cols);
    if (!A) {
        printf("Error with mx\n");
        return 0;
    }
    fillingMatrix(A, rows, cols, start, end);

    printf("Matrix A:\n");
    printMatrix(A, rows, cols);

    int** C = transpositionMatrix(A, rows, cols);
    if (C) {
        printf("------------------------\n");
        printf("Transposition:\n");
        printMatrix(C, cols, rows);
        cleanMatrix(&C, cols);
    } else {
        printf("------------------------\n");
        printf("Error with transposition\n");
    }

    cleanMatrix(&A, rows);
    printf("\n_____________________________________\n");

    // Тест умножения матриц
    size_t rows1 = 2, cols1 = 3, rows2 = 3, cols2 = 4;
    int A1[] = {1, 2, 3, 4, 5, 6};
    int B1[] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};

    size_t data1 = sizeof(A1) / sizeof(A1[0]);
    size_t data2 = sizeof(B1) / sizeof(B1[0]);

    if (data1 != rows1 * cols1) {
        printf("Error: matrix X size\n");
        return 0;
    }
    if (data2 != rows2 * cols2) {
        printf("Error: matrix Y size\n");
        return 0;
    }

    if (rows1 > 0 && cols1 > 0 && rows2 > 0 && cols2 > 0 && cols1 == rows2) {
        int** X = createMatrix(rows1, cols1);
        int** Y = createMatrix(rows2, cols2);

        if (X && Y) {
            for (size_t i = 0, k = 0; i < rows1; i++)
                for (size_t j = 0; j < cols1; j++)
                    X[i][j] = A1[k++];
            for (size_t i = 0, k = 0; i < rows2; i++)
                for (size_t j = 0; j < cols2; j++)
                    Y[i][j] = B1[k++];

            printf("Matrix X:\n");
            printMatrix(X, rows1, cols1);
            printf("Matrix Y:\n");
            printMatrix(Y, rows2, cols2);

            int** R = multiplyMatrixs(X, rows1, cols1, Y, rows2, cols2);
            if (R) {
                printf("------------------------\n");
                printf("Multiplication:\n");
                printMatrix(R, rows1, cols2);
                cleanMatrix(&R, rows1);
            }
            else {
                printf("------------------------\n");
                printf("Error with multiplication\n");
            }

            cleanMatrix(&X, rows1);
            cleanMatrix(&Y, rows2);
        }
        else {
            if (X) cleanMatrix(&X, rows1);
            if (Y) cleanMatrix(&Y, rows2);
        }
    }
    else {
        printf("Error with size for multiplication\n");
    }

    return 0;
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

int** transpositionMatrix(int** matrix, size_t rows, size_t cols) {
    if (matrix == NULL || rows == 0 || cols == 0) {
        return NULL;
    }

    int** result = createMatrix(cols, rows);
    if (result == NULL) {
        return NULL;
    }

    // Транспонируем
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

int printMatrix(int** matrix, size_t rows, size_t cols) {
    if (matrix == NULL || rows == 0 || cols == 0)
        return 1;

    for (size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL){
            continue;
        }
        for (size_t j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int cleanMatrix(int*** matrix_ptr, size_t rows) {
    if (matrix_ptr == NULL || *matrix_ptr == NULL || rows == 0)
        return 1;

    // освобождаем строки
    for (size_t i = 0; i < rows; i++) {
        if ((*matrix_ptr)[i] != NULL) {
            free((*matrix_ptr)[i]);
            (*matrix_ptr)[i] = NULL;
        }
    }

    // освобождаем массив указателей
    free(*matrix_ptr);
    // обнуляем указатель
    *matrix_ptr = NULL;

    return 0;
}

int** multiplyMatrixs(int** matrix11, size_t rows1, size_t cols1, int** matrix22, size_t rows2, size_t cols2) {
    if (matrix11 == NULL || matrix22 == NULL) {
        return NULL;
    }

    if (rows1 == 0 || cols1 == 0 || rows2 == 0 || cols2 == 0) {
        return NULL;
    }

    if (cols1 != rows2) {
        return NULL;
    }

    int** result = createMatrix(rows1, cols2);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < rows1; i++) {
        if (matrix11[i] == NULL) {
            continue;
        }

        for (size_t j = 0; j < cols2; j++) {
            long long sum = 0;

            for (size_t k = 0; k < cols1; k++) {
                if (matrix22[k] == NULL) {
                    continue;
                }

                long long mul = (long long)matrix11[i][k] * (long long)matrix22[k][j];

                if (mul > 0 && sum > LLONG_MAX - mul) {
                    cleanMatrix(&result, rows1);
                    return NULL;
                }
                if (mul < 0 && sum < LLONG_MIN - mul) {
                    cleanMatrix(&result, rows1);
                    return NULL;
                }
                sum += mul;
            }

            if (sum > INT_MAX || sum < INT_MIN) {
                cleanMatrix(&result, rows1);
                return NULL;
            }
            result[i][j] = (int)sum;
        }
    }

    return result;
}