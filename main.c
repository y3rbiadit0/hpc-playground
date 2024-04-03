#include "report.h"
#include "utils.h"
#include "matrix_multiplication.h"
#include "matrix_utils.h"

#define MATRIX_SIZE 512
#define REPORT_DATA_SIZE 7

int main() {
    double **matrix_A = alloc_matrix_2D(MATRIX_SIZE);
    double **matrix_B = alloc_matrix_2D(MATRIX_SIZE);
    double **matrix_C = alloc_matrix_2D(MATRIX_SIZE);

    time_report time_data_reports[REPORT_DATA_SIZE];
    initialize_matrix(matrix_A, matrix_B, matrix_C, MATRIX_SIZE);

    time_data_reports[0] = multiply_matrix_V1(matrix_A, matrix_B, matrix_C, MATRIX_SIZE);
    time_data_reports[1] = multiply_matrix_V1_optimized(matrix_A, matrix_B, matrix_C, MATRIX_SIZE);
    time_data_reports[2] = multiply_matrix_V2(matrix_A, matrix_B, matrix_C, MATRIX_SIZE);
    time_data_reports[3] = multiply_matrix_V3(matrix_A, matrix_B, matrix_C, MATRIX_SIZE, 2);
    time_data_reports[4] = multiply_matrix_V3(matrix_A, matrix_B, matrix_C, MATRIX_SIZE, 4);
    time_data_reports[5] = multiply_matrix_V3(matrix_A, matrix_B, matrix_C, MATRIX_SIZE, 8);
    time_data_reports[6] = multiply_matrix_V3(matrix_A, matrix_B, matrix_C, MATRIX_SIZE, 16);

    dump_report_data_to_csv(time_data_reports, REPORT_DATA_SIZE);
    return 0;
}
