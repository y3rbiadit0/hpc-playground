//
// Created by Franco Nicolas Merenda on 03/04/2024.
//

#ifndef HPC_MATRIX_UTILS_H
#define HPC_MATRIX_UTILS_H

#include <stdint.h>

void initialize_matrix(double **matrix_A, double **matrix_B, double **matrix_C, uint32_t matrix_size);

double **alloc_matrix_2D(uint32_t size);

#endif //HPC_MATRIX_UTILS_H
