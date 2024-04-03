//
// Created by Franco Nicolas Merenda on 03/04/2024.
//

#ifndef HPC_REPORT_H
#define HPC_REPORT_H

#include <stdint.h>

typedef struct {
    float time;
    uint8_t cores;
    char version_name[50];
} time_report;

time_report create_time_report(float time,
                                      uint8_t cores,
                                      char *version_name);
#endif //HPC_REPORT_H
