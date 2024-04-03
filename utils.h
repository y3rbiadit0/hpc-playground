//
// Created by Franco Nicolas Merenda on 03/04/2024.
//

#ifndef HPC_UTILS_H
#define HPC_UTILS_H


#include "report.h"
#include <sys/time.h>

float time_difference(struct timeval *start, struct timeval *end);

int8_t dump_report_data_to_csv(time_report *time_data_reports, uint8_t report_data_size);


#endif //HPC_UTILS_H
