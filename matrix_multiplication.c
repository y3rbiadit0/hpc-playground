//
// Created by Franco Nicolas Merenda on 03/04/2024.
//

#include "matrix_multiplication.h"
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include "report.h"
#include "utils.h"

__attribute__((optnone)) time_report
multiply_matrix_V1(double **matrix_A, double **matrix_B, double **matrix_C, uint32_t matrix_size) {
    /*
     * Simple Matrix Multiplication
     * Forced to not be optimized by compiler
     * https://stackoverflow.com/questions/2219829/how-can-i-prevent-gcc-optimizing-some-statements-in-c
     */

    time_report reportData;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            for (int k = 0; k < matrix_size; k++) {
                matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }

    gettimeofday(&end, NULL);
    reportData = create_time_report(
            time_difference(&start, &end),
            1,
            "Version 1"
    );
    printf("%0.6f\n", reportData.time);
    return reportData;
}

time_report
multiply_matrix_V1_optimized(double **matrix_A, double **matrix_B, double **matrix_C, uint32_t matrix_size) {
    /*
     * Simple Matrix Multiplication
     * Allowed to be optimized by the compiler
    */

    time_report report_data;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            for (int k = 0; k < matrix_size; k++) {
                matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }

    gettimeofday(&end, NULL);
    report_data = create_time_report(
            time_difference(&start, &end),
            1,
            "Version 1 - Compiler Optimized"
    );
    printf("%0.6f\n", report_data.time);
    return report_data;
}

time_report multiply_matrix_V2(double **matrix_A, double **matrix_B, double **matrix_C, uint32_t matrix_size) {
    /*
     * Improved localization in memory
     * Better use of caching - less cache misses
     * -O3 -- Even improves this
     */
    time_report report_data;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < matrix_size; i++) {
        for (int k = 0; k < matrix_size; k++) {
            for (int j = 0; j < matrix_size; j++) {
                matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }
    gettimeofday(&end, NULL);
    report_data = create_time_report(
            time_difference(&start, &end),
            1,
            "Version 2 - Improved localization"
    );

    printf("%0.6f\n", report_data.time);
    return report_data;
}

time_report
multiply_matrix_V3(double **matrix_A, double **matrix_B, double **matrix_C, uint32_t matrix_size, uint8_t cores) {
    /*
     * Improved using OpenMP - Threading
     * Better use of caching - less cache misses
     * -O3 -- Even improves this
     */
    time_report report_data;
    struct timeval start, end;
    gettimeofday(&start, NULL);
#pragma omp parallel for num_threads(cores)
    for (int i = 0; i < matrix_size; i++) {
        for (int k = 0; k < matrix_size; k++) {
            for (int j = 0; j < matrix_size; j++) {
                matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }
    gettimeofday(&end, NULL);
    report_data = create_time_report(
            time_difference(&start, &end),
            cores,
            "Version 3 - OpenMP"
    );
    printf("%0.6f\n", report_data.time);
    return report_data;
}

time_report
multiply_matrix_V4(double **matrix_A, double **matrix_B, double **matrix_C, uint32_t matrix_size, uint8_t cores,
                   uint32_t tile_size) {
    time_report report_data;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    //Process the entire matrix
#pragma omp parallel for num_threads(cores)
    for (int i_matrix = 0; i_matrix < matrix_size; i_matrix += tile_size)
#pragma omp parallel for num_threads(cores)
            for (int j_matrix = 0; j_matrix < matrix_size; j_matrix += tile_size)
                for (int k_matrix = 0; k_matrix < matrix_size; k_matrix += tile_size)
                    // Process Tile matrix
                    for (int i_tile = 0; i_tile < tile_size; i_tile++)
                        for (int k_tile = 0; k_tile < tile_size; k_tile++)
                            for (int j_tile = 0; j_tile < tile_size; j_tile++)
                                matrix_C[i_matrix + i_tile][j_matrix + j_tile] +=
                                        matrix_A[i_matrix + i_tile][k_matrix + k_tile] *
                                        matrix_B[k_matrix + k_tile][j_matrix + j_tile];

    gettimeofday(&end, NULL);
    report_data = create_time_report(
            time_difference(&start, &end),
            cores,
            "Version 4 - Tiling - OpenMP"
    );
    printf("%0.6f\n", report_data.time);
    return report_data;
}