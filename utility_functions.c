#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "struct.h"

void AllocateMatrix(Matrix *m, int rows, int cols) {
    m->rows = rows;
    m->cols = cols;
    m->matrix = malloc(rows * sizeof(float*));
    if (!m->matrix) exit(EXIT_FAILURE);
    for (int i = 0; i < rows; i++) {
        m->matrix[i] = malloc(cols * sizeof(float));
        if (!m->matrix[i]) {
            for (int j = 0; j < i; j++) {
                free(m->matrix[j]);
            }
            free(m->matrix);
            exit(EXIT_FAILURE);
        }
    }
}

void FreeMatrix(Matrix *m) {
    for(int i = 0; i < m->rows; i++) {
        free(m->matrix[i]);
    }
    free(m->matrix);
}

void InputMatrix(Matrix *m) {
    printf("Введите размер матрицы (n x m): ");
    int rows, cols;
    while (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        printf("Неправильный ввод, введите натуральные числа для размера матрицы: ");
        while(getchar() != '\n');
    }
    AllocateMatrix(m, rows, cols);
    printf("Введите элементы матрицы размера %dx%d:\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            while (scanf("%f", &m->matrix[i][j]) != 1) {
                printf("Неправильный ввод, введитте вещественное число для ячейки [%d][%d]: ", i, j);
                while(getchar() != '\n');
            }
        }
    }
}

void PrintMatrix(const Matrix *m) {
    int rows, cols;
    rows = m->rows;
    cols = m->cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++){
            if (j == 0){
                printf("| ");
            }
            printf("%.1f ", m->matrix[i][j]);
            if (j == cols - 1) {
                printf("|\n");
            }
        }
    }
}

float TraceMatrix(Matrix *m) {
    float trace = 0.0;
    if (m->rows != m->cols) {
        printf("След может быть вычислен только для квадратных матриц.\n");
        return 0.0f;
    }
    int n;
    n = m->rows;
    for (int i = 0; i < n; i++) {
        trace += m->matrix[i][i];
    }
    m->trace = trace;
    return trace;
}

Matrix MinorMatrix(const Matrix *m, int row, int col) {
    Matrix minor;
    AllocateMatrix(&minor, m->rows - 1, m->cols - 1);
    for (int i = 0, mi = 0; i < m->rows; i++) {
        if (i == row) continue;
        for (int j = 0, mj = 0; j < m->cols; j++) {
            if (j == col) continue;
            minor.matrix[mi][mj++] = m->matrix[i][j];
        }
        mi++;
    }
    return minor;
}

float AlgebraicComplementMatrix(const Matrix *m, int row, int col) {
    Matrix minor = MinorMatrix(m, row, col);
    float det_minor = DeterminantMatrix1(&minor);
    FreeMatrix(&minor);
    if ((row + col) % 2 == 0) return det_minor;
    return -det_minor;
}

// Вычисление определителя матрицы с помощью разложения по первой строке (O(n!))
float DeterminantMatrix1(const Matrix *m) {
    if (m->rows != m->cols) {
        printf("Определитель может быть вычислен только для квадратных матриц.\n");
        return 0.0f;
    }
    int n = m->rows;
    if (n <= 0) return 0;
    if (n == 1) return m->matrix[0][0];
    if (n == 2) {
        return (m->matrix[0][0] * m->matrix[1][1] - m->matrix[0][1] * m->matrix[1][0]);
    }
    float det = 0;
    for (int j = 0; j < n; j++) {
        det += m->matrix[0][j] * AlgebraicComplementMatrix(m, 0, j);
    }
    return det;
}

bool IsUpperTriangularMatrix(const Matrix *m) {
    int n = m->rows;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (m->matrix[i][j] != 0.0f) {
                return false;
            }
        }
    }
    return true;
}

int MakeUpperTriangularMatrix(Matrix *m, int *swap_count) {
    if (swap_count) *swap_count = 0;
    int rank = 0;
    for (int c = 0, r = 0; c < m->cols && r < m->rows; c++) {
        int max_row = r;
        for (int i = r + 1; i < m->rows; i++) {
            if (fabsf(m->matrix[i][c]) > fabsf(m->matrix[max_row][c])) {
                max_row = i;
            }
        }
        if (fabsf(m->matrix[max_row][c]) == 0.0f) {
            continue;
        }
        if (max_row != r) {
            float *tmp = m->matrix[r];
            m->matrix[r] = m->matrix[max_row];
            m->matrix[max_row] = tmp;
            if (swap_count) (*swap_count)++;
        }
        for (int i = r + 1; i < m->rows; i++) {
            float factor = m->matrix[i][c] / m->matrix[r][c];
            for (int j = c; j < m->cols; j++) {
                m->matrix[i][j] -= factor * m->matrix[r][j];
            }
            m->matrix[i][c] = 0.0f;
        }
        r++;
        rank++;
    }
    return rank;
}

// Вычисление определителя методом Гаусса (O(n^3))
float DeterminantMatrix2(const Matrix *m) {
    if (m->rows != m->cols) {
        printf("Определитель может быть вычислен только для квадратных матриц.\n");
        return 0.0f;
    }
    if (m->rows <= 0) return 0.0f;
    if (m->rows == 1) return m->matrix[0][0];
    if (m->rows == 2) {
        return (m->matrix[0][0] * m->matrix[1][1] - m->matrix[0][1] * m->matrix[1][0]);
    }
    Matrix tmp = CopyMatrix(m);
    int swap_count = 0;
    if (MakeUpperTriangularMatrix(&tmp, &swap_count) == 0) {
        FreeMatrix(&tmp);
        return 0.0f;
    }
    float det = 1.0;
    for (int i = 0; i < tmp.rows; i++){
        det *= tmp.matrix[i][i];
    }
    FreeMatrix(&tmp);
    if (swap_count % 2 != 0) return -det;
    return det;
}

Matrix CopyMatrix(const Matrix *m) {
    Matrix copy;
    AllocateMatrix(&copy, m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            copy.matrix[i][j] = m->matrix[i][j];
        }
    }
    return copy;
}

void SimplifyUpperTriangularMatrix(Matrix *m) {
    if (!IsUpperTriangularMatrix(m)) {
        printf("Матрица не верхняя треугольная\n");
        return;
    }
    for (int i = 0; i < m->rows; i++) {
        if (m->matrix[i][i] != 0.0f) {
            float diag = m->matrix[i][i];
            for (int k = i; k < m->cols; k++) {
                if (m->matrix[i][k] != 0.0f) m->matrix[i][k] /= diag;
            }
        }
    }
}

Matrix SumMatrix(const Matrix *m1, const Matrix *m2) {
    if (m1->cols != m2->cols || m1->rows != m2->rows) {
        printf("Матрицы должны быть одного размера для суммирования\n");
        exit(EXIT_FAILURE);
    }
    Matrix sum;
    AllocateMatrix(&sum, m1->rows, m1->cols);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            sum.matrix[i][j] = m1->matrix[i][j] + m2->matrix[i][j];
        }
    }
    return sum;
}

Matrix MultMatrix(const Matrix *m1, const Matrix *m2) {
    if (m1->cols != m2->rows) {
        printf("Неподходящие размеры матриц для умножения\n");
        exit(EXIT_FAILURE);
    }
    Matrix mult;
    AllocateMatrix(&mult, m1->rows, m2->cols);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m2->cols; j++) {
            mult.matrix[i][j] = 0.0f;
            for (int k = 0; k < m1->cols; k++) {
                mult.matrix[i][j] += m1->matrix[i][k] * m2->matrix[k][j];
            }
        }
    }
    return mult;
}

Matrix ExponentMatrix(const Matrix *m, int n) {
    if (n < 0) {
        printf("Неверно введена степень\n");
        exit(EXIT_FAILURE);
    }
    if (m->rows != m->cols) {
        printf("Возведение в степень возможно только для квадратных матриц\n");
        exit(EXIT_FAILURE);
    }
    Matrix result = MakeIdentMatrix(m->rows);

    for (int i = 0; i < n; i++) {
        Matrix temp = MultMatrix(&result, m);
        FreeMatrix(&result);
        result = temp;
    }
    return result;
}

Matrix MakeIdentMatrix(int n) {
    Matrix m;
    AllocateMatrix(&m, n, n);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if (i == j) {
                m.matrix[i][j] = 1.0f;
            } else {
                m.matrix[i][j] = 0.0f;
            }
        }
    }
    return m;
}

Matrix TransposeMatrix(const Matrix *m) {
    Matrix transpose;
    AllocateMatrix(&transpose, m->cols, m->rows);
    for (int i = 0; i < m->cols; i++) {
        for (int j = 0; j < m->rows; j++) {
            transpose.matrix[i][j] = m->matrix[j][i];
        }
    }
    return transpose;
}

Matrix InverseMatrix(const Matrix *m) {
    float det = DeterminantMatrix2(m);
    if (det == 0.0f) {
        printf("Matrix is singular, no inverse\n");
        exit(EXIT_FAILURE);
    }
    Matrix inverse;
    int n = m->rows;
    AllocateMatrix(&inverse, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse.matrix[i][j] = AlgebraicComplementMatrix(m, i, j) / det;
        }
    }
    Matrix result = TransposeMatrix(&inverse);
    FreeMatrix(&inverse);
    return result;
}


void ShowMenu() {
    printf("\n====== МАТРИЧНЫЙ КАЛЬКУЛЯТОР ======\n");
    printf("1. Ввести матрицу\n");
    printf("2. Вывести матрицу\n");
    printf("3. След матрицы\n");
    printf("4. Определитель матрицы\n");
    printf("5. Транспонирование\n");
    printf("6. Обратная матрица\n");
    printf("7. Умножение на другую матрицу\n");
    printf("8. Возведение в степень\n");
    printf("0. Выход\n");
    printf("Выберите опцию: ");
}