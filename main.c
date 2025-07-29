#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <math.h>
#include "struct.h"

int main() {
    setlocale(LC_ALL, "Russian");
    Matrix A;
    bool hasMatrix = false;
    int option;
    do {
        ShowMenu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                if (hasMatrix) {
                    FreeMatrix(&A);
                }
                InputMatrix(&A);
                hasMatrix = true;
                break;

            case 2:
                if (hasMatrix) {
                    PrintMatrix(&A);
                } else {
                    printf("Матрица ещё не введена.\n");
                }
                break;

            case 3:
                if (hasMatrix) {
                    float tr = TraceMatrix(&A);
                    printf("След матрицы: %.2f\n", tr);
                } else {
                    printf("Матрица ещё не введена.\n");
                }
                break;

            case 4:
                if (hasMatrix) {
                    float det = DeterminantMatrix2(&A);
                    printf("Определитель: %.2f\n", det);
                } else {
                    printf("Матрица ещё не введена.\n");
                }
                break;

            case 5:
                if (hasMatrix) {
                    Matrix T = TransposeMatrix(&A);
                    printf("Транспонированная матрица:\n");
                    PrintMatrix(&T);
                    FreeMatrix(&T);
                } else {
                    printf("Матрица ещё не введена.\n");
                }
                break;

            case 6:
                if (hasMatrix) {
                    Matrix Inv = InverseMatrix(&A);
                    printf("Обратная матрица:\n");
                    PrintMatrix(&Inv);
                    FreeMatrix(&Inv);
                } else {
                    printf("Матрица ещё не введена.\n");
                }
                break;

            case 7:
                if (hasMatrix) {
                    printf("Введите вторую матрицу для умножения:\n");
                    Matrix B;
                    InputMatrix(&B);
                    Matrix R = MultMatrix(&A, &B);
                    printf("Результат умножения:\n");
                    PrintMatrix(&R);
                    FreeMatrix(&B);
                    FreeMatrix(&R);
                } else {
                    printf("Матрица ещё не введена.\n");
                }
                break;

            case 8:
                if (hasMatrix) {
                    int n;
                    printf("Введите степень: ");
                    scanf("%d", &n);
                    Matrix P = ExponentMatrix(&A, n);
                    printf("Результат возведения в степень %d:\n", n);
                    PrintMatrix(&P);
                    FreeMatrix(&P);
                } else {
                    printf("Матрица ещё не введена.\n");
                }
                break;

            case 0:
                printf("Выход из программы.\n");
                break;

            default:
                printf("Неверная опция.\n");
        }

    } while (option != 0);

    if (hasMatrix) {
        FreeMatrix(&A);
    }

    return 0;
}