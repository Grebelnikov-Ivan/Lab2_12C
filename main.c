#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int** createMatrix(size_t rows, size_t cols);
int fillingMatrix(int** matrix, size_t rows, size_t cols, int min_g, int max_g);
int** transpositionMatrix(int** matrix, size_t rows, size_t cols);
int printMatrix(int** matrix, size_t rows, size_t cols);
int cleanMatrix(int** matrix, size_t rows);
int** multiplyMatrixs(int** matrix11, size_t rows1, size_t cols1, int** matrix22, size_t rows2, size_t cols2);

int main() {
    // rows = 2, cols = 4;
    // rows = 3, cols = 3;
    // rows = 1, cols = 5;
    // rows = 5, cols = 1;
    // rows = 10, cols = 22;
    size_t rows = 3, cols = 4;

    if (rows <= 0 || cols <= 0) {
        printf("Error with size\n"); return 0;
    }

    int start = 5, end = 100;
    int** A = createMatrix(rows, cols);
    if (!A) {
        printf("Error with mx\n");
        cleanMatrix(A, rows);
        A = NULL;
        return 0;
    }
    fillingMatrix(A, rows, cols, start, end);
    // fillingMatrix(NULL, rows, cols, start, end);

    printf("Matrix A:\n");
    printMatrix(A, rows, cols);

    // free(A[0]); A[0] = NULL;
    // free(A[1]); A[1] = NULL;

    int** C = transpositionMatrix(A, rows, cols);
    if (C) {
        printf("------------------------\n");
        printf("Transposition:\n");
        printMatrix(C, cols, rows);
        cleanMatrix(C, cols);
        C = NULL;
    } else {
        printf("------------------------\n");
        printf("Error with transposition\n");
    }

    cleanMatrix(A, rows);
    A = NULL;
    printf("\n_____________________________________\n");

    // size_t rows1 = 2, cols1 = 3, rows2 = 3, cols2 = 4;
    // int A1[] = {1,2,3,4,5,6};
    // int B1[] = {7,8,9,10,11,12,13,14,15,16,17,18};
    // // ожидаемо: [74,80,86,92; 173,188,203,218]

    // size_t rows1 = 2, cols1 = 3, rows2 = 3, cols2 = 4;
    // int A1[] = {1,1,3,1,5,6};
    // int B1[] = {7,8,9,10,11,12,13,14,15,16,17,18};
    // // ожидаемо: [52,56,60,64; 145,156,167,178]

    // size_t rows1 = 2, cols1 = 3, rows2 = 3, cols2 = 4;
    // int A1[] = {-1,-2,-3,-4,-5,-6};
    // int B1[] = {-7,-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-18};
    // // ожидаемо: [74,80,86,92; 173,188,203,218]

    // size_t rows1 = 3, cols1 = 2, rows2 = 2, cols2 = 4;
    // int A1[] = {1,2,3,4,5,6};
    // int B1[] = {7,8,9,10,11,12,13,14};
    // // ожидаемо: [29,32,35,38; 65,72,79,86; 101,112,123,134]

    // size_t rows1 = 1, cols1 = 3, rows2 = 3, cols2 = 1;
    // int A1[] = {1,2,3};
    // int B1[] = {4,5,6};
    // // ожидаемо: [32]

    // size_t rows1 = 3, cols1 = 1, rows2 = 1, cols2 = 3;
    // int A1[] = {1,2,3};
    // int B1[] = {4,5,6};
    // // ожидаемо: [4,5,6; 8,10,12; 12,15,18]

    // size_t rows1 = 3, cols1 = 3, rows2 = 3, cols2 = 3;
    // int A1[] = {1,0,0,0,1,0,0,0,1};
    // int B1[] = {5,6,7,8,9,10,11,12,13};
    // // ожидаемо: [5,6,7; 8,9,10; 11,12,13]

    // size_t rows1 = 2, cols1 = 3, rows2 = 3, cols2 = 4;
    // int A1[] = {0,0,0,0,0,0};
    // int B1[] = {7,8,9,10,11,12,13,14,15,16,17,18};
    // // ожидаемо: [0,0,0,0; 0,0,0,0]

    // size_t rows1 = 2, cols1 = 3, rows2 = 3, cols2 = 4;
    // int A1[] = {2000000000,2000000000,2000000000,0,0,0};
    // int B1[] = {2,0,0,0,2,0,0,0,2,0,0,0};
    // // ожидаемо: overflow -> NULL

    // size_t rows1 = 2, cols1 = 4, rows2 = 3, cols2 = 4;
    // // cols1(4) != rows2(3) -> NULL

    size_t rows1 = 2, cols1 = 3, rows2 = 3, cols2 = 4;
    int A1[] = {1, 2, 3, 4, 5, 6};
    int B1[] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};

    if (rows1 > 0 && cols1 > 0 && rows2 > 0 && cols2 > 0 && cols1 == rows2) {
        int** X = createMatrix(rows1, cols1);
        int** Y = createMatrix(rows2, cols2);
        if (X && Y) {
            for (size_t i = 0, k = 0; i < rows1; i++)
                for (size_t j = 0; j < cols1; j++) X[i][j] = A1[k++];
            for (size_t i = 0, k = 0; i < rows2; i++)
                for (size_t j = 0; j < cols2; j++) Y[i][j] = B1[k++];

            // free(X[1]); X[1] = NULL;
            // free(Y[2]); Y[2] = NULL;

            printf("Matrix X:\n");
            printMatrix(X, rows1, cols1);
            printf("Matrix Y:\n");
            printMatrix(Y, rows2, cols2);

            int** R = multiplyMatrixs(X, rows1, cols1, Y, rows2, cols2);
            if (R) {
                printf("------------------------\n");
                printf("Multiplication:\n");
                printMatrix(R, rows1, cols2);
                cleanMatrix(R, rows1);
                R = NULL;
            }
            else {
                printf("------------------------\n");
                printf("Error with multiplication\n");
            }
            cleanMatrix(X, rows1);
            X = NULL;
            cleanMatrix(Y, rows2);
            Y = NULL;
        }
        else {
            if (X) {
                cleanMatrix(X, rows1);
                X = NULL;
            }
            if (Y) {
                cleanMatrix(Y, rows2); Y = NULL;
            }
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

    // проверка, что все строки матрицы существуют
    /*for ( size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            cleanMatrix(matrix, rows);
            matrix = NULL;
            return 1;
        }
    } */

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

    // проверка, что все строки матрицы существуют
    /*for ( size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            cleanMatrix(matrix, rows);
            matrix = NULL;
            return NULL;
        }
    }*/

    int** result = NULL;
    result = createMatrix(cols, rows);
    if (result == NULL) {
        cleanMatrix(matrix, rows);
        matrix = NULL;
        return NULL;
    }

    // проверка, что все строки созданы корректно
    for (size_t i = 0; i < cols; i++) {
        if (result[i] == NULL) {
            cleanMatrix(result, cols);
            result = NULL;
            return NULL;
        }
    }

    // транспонируем
    for (size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            continue;
        }
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

int cleanMatrix(int** matrix, size_t rows) {
    if (matrix == NULL || rows == 0)
        return 1;

    for (size_t i = 0; i < rows; i++) {
        if (matrix[i] != NULL) {
            free(matrix[i]);
            matrix[i] = NULL;
        }
    }

    free(matrix);
    return 0;
}


/*int check_overflow(long long sum, long long mul) {
    if (mul > 0 && sum > LLONG_MAX - mul)
        return 1;
    if (mul < 0 && sum < LLONG_MIN - mul)
        return 1;
    return 0;
}*/


int** multiplyMatrixs(int** matrix11, size_t rows1, size_t cols1, int** matrix22, size_t rows2, size_t cols2) {
    if (matrix11 == NULL || matrix22 == NULL) {
        return NULL;
    }

    if (rows1 == 0 || cols1 == 0 || rows2 == 0 || cols2 == 0) {
        return NULL;
    }

    // количество столбцов первой матрицы должно равняться количеству строк второй
    if (cols1 != rows2) {
        return NULL;
    }

    int** result = createMatrix(rows1, cols2);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < rows1; i++) {
        // если строка первой матрицы NULL, пропускаем
        if (matrix11[i] == NULL) {
            continue;
        }

        for (size_t j = 0; j < cols2; j++) {
            long long sum = 0;

            for (size_t k = 0; k < cols1; k++) {
                // проверяем, вторую матрицу NULL
                if (matrix22[k] == NULL) {
                    continue;
                }

                long long mul = (long long)matrix11[i][k] * (long long)matrix22[k][j];

                // проверка переполнения при сложении
                if (mul > 0 && sum > LLONG_MAX - mul)
                    return NULL;
                if (mul < 0 && sum < LLONG_MIN - mul){
                    return NULL;}
                /*if (check_overflow(sum, mul) != 0)
                    return NULL;*/
                sum += mul;
            }


            // можно ли в int
            if (sum > INT_MAX || sum < INT_MIN) {
                cleanMatrix(result, rows1);
                result = NULL;
                return NULL;
            }
            result[i][j] = (int)sum;
        }
    }

    return result;
}