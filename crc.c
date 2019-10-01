//
// Created by Artem Botnev on 26/09/2019.
//

#include "crc.h"

void convert_string_to_bytes(const char *ascii_str, unsigned char *bytes)
{
    int i = 0;
    while (ascii_str[i] != '\0')
    {
        bytes[i] = ascii_str[i];
        i++;
    }
}

int calculate_crc16_ccitt(const char *value)
{
    int crc = CRC;

    size_t len = strlen(value);
    unsigned char bytes[len];
    convert_string_to_bytes(value, bytes);

    for(size_t i = 0; i < len; i++)
    {
        for(int j = 0; j < BYTES_COUNT; j++)
        {
            int b = ((bytes[i] >> (BYTES_COUNT - j - 1) & 1) == 1);
            int c15 = ((crc >> ((BYTES_COUNT << 1) - 1) & 1) == 1);
            crc <<= 1;
            if (c15 ^ b) crc ^= POLYNOMIAL;
        }
    }

    crc &= CRC;

    return crc;
}

const char *build_answer(const char *inn, const char *factory_number)
{
    short source_size =
            sizeof(INN_SOURCE_PREFIX) + sizeof(FACTORY_NUMBER_SOURCE_PREFIX) + INN_SIZE + FACTORY_NUMBER_SIZE;

    char source[source_size + 1];
    strcpy(source, INN_SOURCE_PREFIX);
    strcat(source, inn);
    strcat(source, FACTORY_NUMBER_SOURCE_PREFIX);
    strcat(source, factory_number);

    int answer = calculate_crc16_ccitt(source);

    char str_answer[GEN_ANSWER_SIZE];
    char *result = calloc(sizeof(RESULT_PREFIX) + sizeof(str_answer), sizeof(char*));

    sprintf(str_answer, "%d", answer);
    strcpy(result, RESULT_PREFIX);
    strcat(result, str_answer);

    return result;
}
