//
// Created by Franco Nicolas Merenda on 03/04/2024.
//
#include <string.h>
#include "report.h"

struct time_report create_time_report(float time,
                                      uint8_t cores,
                                      char *version_name) {
    struct time_report report_data;

    report_data.cores = cores;
    report_data.time = time;
    strcpy(report_data.version_name, version_name);
    return report_data;
};