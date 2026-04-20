#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define EMPTY INT_MIN  // для пустой ячейки

int** createMatrix(size_t rows, size_t cols);
int fillingMatrix(int** matrix, size_t rows, size_t cols, int min_g, int max_g);
int** transpositionMatrix(int** matrix, size_t rows, size_t cols);
int printMatrix(int** matrix, size_t rows, size_t cols);
int cleanMatrix(int** matrix, size_t rows);
int empty(int n);
int** multiplyMatrixs(int** matrix11, size_t rows1, size_t cols1, int** matrix22, size_t rows2, size_t cols2);

int main(){
    size_t rows = 3, cols = 4;
    int** matrix = NULL;
    int** matrix2 = NULL;

    matrix = createMatrix(rows, cols);
    if (matrix == NULL) {
        printf("error1");
        return 1;
    }

    int test_data[] = {13, 27, -5, 42, -18, 99, 0, -77, 56, 33, -91};

    // int test_data[] = {53, 32, 1, 12, EMPTY, EMPTY, EMPTY, EMPTY, 65, 34, -11, 0};

    // int test_data[] = {1, 2, 3, 4, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};

    // int test_data[] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 9, 10, 11, 12};

    // int test_data[] = {1, EMPTY, EMPTY, 4, 5, EMPTY, EMPTY, 8, 9, EMPTY, EMPTY, 12};

    // int test_data[] = {INT_MAX, INT_MIN + 1, 0, -1, EMPTY, EMPTY, EMPTY, EMPTY, 100, -100, 50, -50};

    // int test_data[] = {42, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};

    // int test_data[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // int test_data[] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};

    size_t data_size = sizeof(test_data) / sizeof(test_data[0]);
    for(size_t i = 0, k = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (k < data_size) {
                matrix[i][j] = test_data[k];
            } else {
                matrix[i][j] = EMPTY;  // недостающие элементы = empty
            }
            k++;
        }
    }
    /*int min_g = -100;
    int max_g = 100;
    if (fillingMatrix(matrix, rows, cols, min_g, max_g) != 0) {
        printf("error10");
        cleanMatrix(matrix, rows);
        matrix = NULL;
        return 1;
    }*/


    if (printMatrix(matrix, rows, cols) != 0) {
        printf("error7");
        cleanMatrix(matrix, rows);
        matrix = NULL;
        return 1;
    }

    // free(matrix[1]);      // освобождаем вторую строку
    // matrix[1] = NULL;

    matrix2 = transpositionMatrix(matrix, rows, cols);
    if (matrix2 == NULL) {
        printf("error6");
        return 1;
    }

    if (printMatrix(matrix2, cols, rows) != 0) {
        printf("error8");
        cleanMatrix(matrix2, cols);
        matrix2 = NULL;
        return 1;
    }

    cleanMatrix(matrix2, cols);
    matrix2 = NULL;


    printf("____________________________________\n");

    int** matrix11 = NULL;
    int** matrix22 = NULL;
    // количество столбцов первой матрицы должно равняться количеству строк второй
    // первая матрица 2x3
    size_t rows1 = 2, cols1 = 3;
    matrix11 = createMatrix(rows1, cols1);
    if (matrix11 == NULL) {
        cleanMatrix(matrix11, rows1);
        matrix11 = NULL;
        return 1;
    }

    // вторая матрица 3x4
    size_t rows2 = 3, cols2 = 4;
    matrix22 = createMatrix(rows2, cols2);
    if (matrix22 == NULL) {
        cleanMatrix(matrix11, rows1);
        matrix11 = NULL;
        cleanMatrix(matrix22, rows2);
        matrix22 = NULL;
        return 1;
    }

    int test_data_A[] = {1, 2, 3, 4, 5, 6};
    int test_data_B[] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    // {{74, 80, 86, 92}, {173, 188, 203, 218}}

    // int test_data_A[] = {1, EMPTY, 3, EMPTY, 5, 6};
    // int test_data_B[] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    //{{52, 56, 60, 64}, {145, 156, 167, 178}}

    // int test_data_A[] = {1, 2, 3, 4, 5, 6};
    // int test_data_B[] = {7, EMPTY, 9, 10, 11, 12, EMPTY, 14, 15, 16, 17, EMPTY};
    // {{74, 72, 60, 38}, {173, 156, 138, 110}}

    // int test_data_A[] = {1, EMPTY, 3, 4, 5, EMPTY};
    // int test_data_B[] = {7, 8, EMPTY, 10, EMPTY, 12, 13, 14, 15, EMPTY, 17, 18};
    // {{52, 50, 51, 10}, {28, 92, 65, 40}}

    // int test_data_A[] = {1, EMPTY, EMPTY, EMPTY, EMPTY, 6};
    // int test_data_B[] = {7, EMPTY, EMPTY, 10, EMPTY, 12, EMPTY, EMPTY, 15, EMPTY, 17, EMPTY};
    //{{7, EMPTY, EMPTY, 10}, {90, EMPTY, 102, EMPTY}}

    // int test_data_A[] = {-1, -2, -3, -4, -5, -6};
    // int test_data_B[] = {-7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18};
    // {{74, 80, 86, 92}, {173, 188, 203, 218}}

    // int test_data_A[] = {-1, 2, -3, 4, -5, 6};
    // int test_data_B[] = {7, -8, 9, -10, 11, -12, 13, -14, 15, -16, 17, -18};
    // {{-30, 26, -34, 32}, {63, -56, 73, -68}}

    // int test_data_A[] = {0, 0, 0, 0, 0, 0};
    // int test_data_B[] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    // // {{0, 0, 0, 0}, {0, 0, 0, 0}}

    // int test_data_A[] = {INT_MAX, INT_MIN + 1, 1, 1, 1, 1};
    // int test_data_B[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    // {{1, 1, 1, 1}, {3, 3, 3, 3}}

    // int test_data_A[] = {1, 2, 3, EMPTY, EMPTY, EMPTY};
    // int test_data_B[] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    // {{74, 80, 86, 92}, {...}}

    // int test_data_A[] = {10000, 20000, 30000, 40000, 50000, 60000};
    // int test_data_B[] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    //{{740000, 800000, 860000, 920000}, {1730000, 1880000, 2030000, 2180000}}


    // int test_data_A[] = {INT_MAX, INT_MAX, INT_MAX, 0, 0, 0};
    // int test_data_B[] = {INT_MAX, 0, 0, 0, INT_MAX, 0, 0, 0, INT_MAX, 0, 0, 0};
    // ...err

    // int test_data_A[] = {INT_MAX, INT_MAX, INT_MAX, 0, 0, 0};
    // int test_data_B[] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
    // ...err

    // int test_data_A[] = {2000000000, 2000000000, 2000000000, 0, 0, 0};
    // int test_data_B[] = {2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0};
    //...err


    for(size_t i = 0, k = 0; i < rows1; i++)
        for(size_t j = 0; j < cols1; j++) {
            matrix11[i][j] = test_data_A[k];
            k++;
        }
    for(size_t i = 0, k = 0; i < rows2; i++)
        for(size_t j = 0; j < cols2; j++) {
            matrix22[i][j] = test_data_B[k];
            k++;
        }

    printMatrix(matrix11, rows1, cols1);
    printMatrix(matrix22, rows2, cols2);

    int** result = NULL;
    result = multiplyMatrixs(matrix11, rows1, cols1, matrix22, rows2, cols2);
    if (result != NULL) {
        printMatrix(result, rows1, cols2);
        cleanMatrix(result, rows1);
        result = NULL;

    }
    else {
        printf("err");
        return 1;
    }

    cleanMatrix(matrix11, rows1);
    matrix11 = NULL;
    cleanMatrix(matrix22, rows2);
    matrix22 = NULL;

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

    // проверка, что все строки матрицы существуют
    for ( size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            cleanMatrix(matrix, rows);
            matrix = NULL;
            return 1;
        }
    }

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
    for ( size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            cleanMatrix(matrix, rows);
            matrix = NULL;
            return NULL;
        }
    }

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
            cleanMatrix(matrix, rows);
            matrix = NULL;
            return NULL;
        }
    }

    // транспонируем только непустые
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (!empty(matrix[i][j])) {
                result[j][i] = matrix[i][j];
            }
        }
    }

    cleanMatrix(matrix, rows);
    matrix = NULL;

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

    for (size_t i = 0; i < rows1; i++) {
        if (matrix11[i] == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < rows2; i++) {
        if (matrix22[i] == NULL) {
            return NULL;
        }
    }

    int** result = createMatrix(rows1, cols2);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < rows1; i++) {
        for (size_t j = 0; j < cols2; j++) {
            long long sum = 0;
            int f_no_empty = 0; // флаг

            for (size_t k = 0; k < cols1; k++) {
                // проверяем что оба элемента не пустые
                if (!empty(matrix11[i][k]) && !empty(matrix22[k][j])) {

                    long long mul = (long long)matrix11[i][k] * (long long)matrix22[k][j];

                    // проверка переполнения при сложении
                    if (mul > 0 && sum > LLONG_MAX - mul)
                        return NULL;
                    if (mul < 0 && sum < LLONG_MIN - mul)
                        return NULL;
                    /*if (check_overflow(sum, mul) != 0)
                        return NULL;*/

                    sum += mul;
                    f_no_empty = 1;
                }
            }


            if (f_no_empty == 1) { // если есть не нулевой
                // можно ли в int
                if (sum > INT_MAX || sum < INT_MIN) {
                    cleanMatrix(result, rows1);
                    result = NULL;
                    return NULL;
                }
                result[i][j] = (int)sum;
            }
        }
    }

    return result;
}