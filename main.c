#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "report.h"

#define N 512
#define REPORT_DATA_SIZE 7

double A[N][N], B[N][N], C[N][N];

time_report multiply_matrix_V1();

time_report multiply_matrix_V1_optimized();

time_report multiply_matrix_V2();

time_report multiply_matrix_V3(uint8_t cores);

void dot_product_V1();

void initialize_matrix();

int8_t dump_report_data_to_csv(time_report time_data_reports[REPORT_DATA_SIZE]);

float tdiff(struct timeval *start, struct timeval *end);

int main() {
    time_report time_data_reports[REPORT_DATA_SIZE];
    initialize_matrix();
    time_data_reports[0] = multiply_matrix_V1();
    time_data_reports[1] = multiply_matrix_V1_optimized();
    time_data_reports[2] = multiply_matrix_V2();
    time_data_reports[3] = multiply_matrix_V3(2);
    time_data_reports[4] = multiply_matrix_V3(4);
    time_data_reports[5] = multiply_matrix_V3(8);
    time_data_reports[6] = multiply_matrix_V3(16);
    dump_report_data_to_csv(time_data_reports);
    return 0;
}

void initialize_matrix() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (double) rand() / (double) RAND_MAX;
            B[i][j] = (double) rand() / (double) RAND_MAX;
            C[i][j] = 0;
        }
    }
}


__attribute__((optnone)) time_report multiply_matrix_V1() {
    /*
     * Simple Matrix Multiplication
     * Forced to not be optimized by compiler
     * https://stackoverflow.com/questions/2219829/how-can-i-prevent-gcc-optimizing-some-statements-in-c
     */

    time_report reportData;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    gettimeofday(&end, NULL);
    reportData = create_time_report(
            tdiff(&start, &end),
            1,
            "Version 1"
    );
    printf("%0.6f\n", reportData.time);
    return reportData;
}

time_report multiply_matrix_V1_optimized() {
    /*
     * Simple Matrix Multiplication
     * Allowed to be optimized by the compiler
    */

    time_report report_data;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    gettimeofday(&end, NULL);
    report_data = create_time_report(
            tdiff(&start, &end),
            1,
            "Version 1 - Compiler Optimized"
    );
    printf("%0.6f\n", report_data.time);
    return report_data;
}

time_report multiply_matrix_V2() {
    /*
     * Improved localization in memory
     * Better use of caching - less cache misses
     * -O3 -- Even improves this
     */
    time_report report_data;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    gettimeofday(&end, NULL);
    report_data = create_time_report(
            tdiff(&start, &end),
            1,
            "Version 2 - Improved localization"
    );

    printf("%0.6f\n", report_data.time);
    return report_data;
}

time_report multiply_matrix_V3(uint8_t cores) {
    /*
     * Improved using OpenMP - Threading
     * Better use of caching - less cache misses
     * -O3 -- Even improves this
     */
    time_report report_data;
    struct timeval start, end;
    gettimeofday(&start, NULL);
#pragma omp parallel for num_threads(cores)
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    gettimeofday(&end, NULL);
    report_data = create_time_report(
            tdiff(&start, &end),
            cores,
            "Version 3 - OpenMP"
    );
    printf("%0.6f\n", report_data.time);
    return report_data;
}

void dot_product_V1() {
    struct timeval start, end;
    gettimeofday(&start, NULL);

#pragma omp parallel for num_threads(2)
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    gettimeofday(&end, NULL);
    printf("%0.6f\n", tdiff(&start, &end));
}

int8_t dump_report_data_to_csv(time_report time_data_reports[REPORT_DATA_SIZE]) {
    FILE *fp; // File pointer

    // Open a file named "output.txt" for writing
    fp = fopen("time_benchmarks.csv", "w");

    if (fp == NULL) {
        printf("Error opening the file.\n");
        return -1; // Exiting the program with an error code
    }

    for (uint8_t i = 0; i < REPORT_DATA_SIZE; i++)
        fprintf(fp, "%s,%d,%f\n", time_data_reports[i].version_name, time_data_reports[i].cores,
                time_data_reports[i].time);

    return 0;
}

float tdiff(struct timeval *start, struct timeval *end) {
    return (end->tv_sec - start->tv_sec) + 1e-6 * (end->tv_usec - start->tv_usec);
}