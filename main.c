#include "report.h"
#include "utils.h"
#include "matrix_multiplication.h"
#include "matrix_utils.h"

#define MATRIX_SIZE 512
#define REPORT_DATA_SIZE 7

void dot_product_V1();

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





//
//void dot_product_V1() {
//    struct timeval start, end;
//    gettimeofday(&start, NULL);
//
//#pragma omp parallel for num_threads(2)
//    for (int i = 0; i < MATRIX_SIZE; i++) {
//        for (int k = 0; k < MATRIX_SIZE; k++) {
//            for (int j = 0; j < MATRIX_SIZE; j++) {
//                C[i][j] += A[i][k] * B[k][j];
//            }
//        }
//    }
//    gettimeofday(&end, NULL);
//    printf("%0.6f\n", tdiff(&start, &end));
//}
