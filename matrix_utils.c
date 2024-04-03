//
// Created by Franco Nicolas Merenda on 03/04/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include "matrix_utils.h"

void initialize_matrix(double **matrix_A, double **matrix_B, double **matrix_C, uint32_t matrix_size) {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            matrix_A[i][j] = (double) rand() / (double) RAND_MAX;
            matrix_B[i][j] = (double) rand() / (double) RAND_MAX;
            matrix_C[i][j] = 0;
        }
    }
}

double **alloc_matrix_2D(uint32_t size) {
    double **A = (double **) malloc(size * sizeof(double *));
    if (A == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Allocate memory for each row
    for (int i = 0; i < size; i++) {
        A[i] = (double *) malloc(size * sizeof(double));
        if (A[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");

            //Deallocate memory allocated in case of error to avoid memory leaks.
            for (int index = 0; index < i; index++)free(A[index]);
            free(A);
            return NULL;
        }
    }
    return A;
}