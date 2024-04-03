//
// Created by Franco Nicolas Merenda on 03/04/2024.
//
#include <string.h>
#include <stdio.h>
#include "report.h"

time_report create_time_report(float time,
                               uint8_t cores,
                               char *version_name) {
    time_report report_data;

    report_data.cores = cores;
    report_data.time = time;
    char original_name[50];
    stpcpy(original_name, version_name);
    snprintf(report_data.version_name, 50, "%s - Cores: %d", original_name, cores);
    return report_data;
};