#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "report.h"

#define N 512

double A[N][N], B[N][N], C[N][N];

struct time_report multiply_matrix_V1();

struct time_report multiply_matrix_V1_optimized();

struct time_report multiply_matrix_V2();

struct time_report multiply_matrix_V3();

void dot_product_V1();

void initialize_matrix();

int8_t dump_report_data_to_csv(struct time_report reportData);

float tdiff(struct timeval *start, struct timeval *end);

int main() {
    struct time_report reportData[4];
    initialize_matrix();
    reportData[0] = multiply_matrix_V1();
    reportData[1] = multiply_matrix_V1_optimized();
    reportData[2] = multiply_matrix_V2();
    reportData[3] = multiply_matrix_V3();
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


struct time_report __attribute__((optimize("O0"))) multiply_matrix_V1() {
    /*
     * Simple Matrix Multiplication
     * Forced to not be optimized by compiler
     * https://stackoverflow.com/questions/2219829/how-can-i-prevent-gcc-optimizing-some-statements-in-c
     */

    struct time_report reportData;
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

struct time_report multiply_matrix_V1_optimized() {
    /*
     * Simple Matrix Multiplication
     * Allowed to be optimized by the compiler
    */

    struct time_report report_data;
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

struct time_report multiply_matrix_V2() {
    /*
     * Improved localization in memory
     * Better use of caching - less cache misses
     * -O3 -- Even improves this
     */
    struct time_report report_data;
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
            "Version 2"
    );
    dump_report_data_to_csv(report_data);

    printf("%0.6f\n", report_data.time);
}

struct time_report multiply_matrix_V3() {
    /*
     * Improved localization in memory
     * Better use of caching - less cache misses
     * -O3 -- Even improves this
     */
    struct time_report report_data;
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
    report_data = create_time_report(
            tdiff(&start, &end),
            1,
            "Version 3"
    );
    dump_report_data_to_csv(report_data);
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

int8_t dump_report_data_to_csv(struct time_report reportData) {
    FILE *fp; // File pointer

    // Open a file named "output.txt" for writing
    fp = fopen("output.csv", "a+");

    if (fp == NULL) {
        printf("Error opening the file.\n");
        return -1; // Exiting the program with an error code
    }

    for (uint8_t i = 0; i < 3; i++)
        fprintf(fp, "%s,%d,%f\n", reportData.version_name, reportData.cores, reportData.time);

}

float tdiff(struct timeval *start, struct timeval *end) {
    return (end->tv_sec - start->tv_sec) + 1e-6 * (end->tv_usec - start->tv_usec);
}