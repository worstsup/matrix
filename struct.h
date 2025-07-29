#ifndef DATABASE_H
#define DATABASE_H

typedef struct {
    float **matrix;
    int rows;
    int cols;
    float determinant;
    float trace;
} Matrix;

void ShowMenu();

void InputMatrix(Matrix *m);
void PrintMatrix(const Matrix *m);
void FreeMatrix(Matrix *m);
void AllocateMatrix(Matrix *m, int rows, int cols);

Matrix MakeIdentMatrix(int n);
Matrix TransposeMatrix(const Matrix *m);
Matrix MinorMatrix(const Matrix *m, int row, int col);
Matrix CopyMatrix(const Matrix *m);
Matrix SumMatrix(const Matrix *m1, const Matrix *m2);
Matrix MultMatrix(const Matrix *m1, const Matrix *m2);
Matrix ExponentMatrix(const Matrix *m, int n);
Matrix InverseMatrix(const Matrix *m);

float TraceMatrix(Matrix *m);
float AlgebraicComplementMatrix(const Matrix *m, int row, int col);
float DeterminantMatrix1(const Matrix *m);
float DeterminantMatrix2(const Matrix *m);

int MakeUpperTriangularMatrix(Matrix *m, int *swap_count);

bool IsUpperTriangularMatrix(const Matrix *m);

void SimplifyUpperTriangularMatrix(Matrix *m);

#endif