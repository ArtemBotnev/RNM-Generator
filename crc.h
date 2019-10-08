//
// Created by Artem Botnev on 26/09/2019.
//

#ifndef RNM_GENERATOR_CRC_H
#define RNM_GENERATOR_CRC_H

#define INN_SIZE 12
#define FACTORY_NUMBER_SIZE 14
#define GEN_ANSWER_SIZE 6
#define BITES_COUNT 8
#define CHARS_BETWEEN_SPACES 4

#define CRC 0xffff
#define POLYNOMIAL 0x1021

#define INN_SOURCE_PREFIX "0000000001"
#define FACTORY_NUMBER_SOURCE_PREFIX "000000"
#define RESULT_PREFIX "00000000010"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *build_answer(const char *inn, const char *factory_number);

#endif //RNM_GENERATOR_CRC_H
