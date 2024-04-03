//
// Created by Franco Nicolas Merenda on 03/04/2024.
//

#include "report.h"
#include "utils.h"
#include <stdio.h>


int8_t dump_report_data_to_csv(time_report *time_data_reports, uint8_t report_data_size) {
    FILE *fp; // File pointer

    // Open a file named "output.txt" for writing
    fp = fopen("time_benchmarks.csv", "w");

    if (fp == NULL) {
        printf("Error opening the file.\n");
        return -1; // Exiting the program with an error code
    }

    for (uint8_t i = 0; i < report_data_size; i++)
        fprintf(fp, "%s,%d,%f\n", time_data_reports[i].version_name, time_data_reports[i].cores,
                time_data_reports[i].time);

    return 0;
}

float time_difference(struct timeval *start, struct timeval *end) {
    return (end->tv_sec - start->tv_sec) + 1e-6 * (end->tv_usec - start->tv_usec);
}
