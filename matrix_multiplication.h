//
// Created by Franco Nicolas Merenda on 03/04/2024.
//

#ifndef HPC_MATRIX_MULTIPLICATION_H
#define HPC_MATRIX_MULTIPLICATION_H

#include "report.h"

time_report multiply_matrix_V1(double **matrix_A, double **matrix_B, double **matrix_C, uint32_t matrix_size);

time_report multiply_matrix_V1_optimized(double **matrix_A, double **matrix_B, double **matrix_C, uint32_t matrix_size);

time_report multiply_matrix_V2(double **matrix_A, double **matrix_B, double **matrix_C, uint32_t matrix_size);

time_report
multiply_matrix_V3(double **matrix_A, double **matrix_B, double **matrix_C, uint32_t matrix_size, uint8_t cores);

time_report
multiply_matrix_V4(double **matrix_A, double **matrix_B, double **matrix_C, uint32_t matrix_size, uint8_t cores,
                   uint32_t tile_size);
#endif //HPC_MATRIX_MULTIPLICATION_H
