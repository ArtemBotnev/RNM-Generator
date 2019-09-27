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
    int crc = 0xffff;
    int polynomial = 0x1021;

    size_t len = strlen(value);
    unsigned char bytes[len];
    convert_string_to_bytes(value, bytes);

    for(size_t i = 0; i < len; i++)
    {
        for(int j = 0; j < CHAR_BIT; j++)
        {
            int b = ((bytes[i] >> (7 - j) & 1) == 1);
            int c15 = ((crc >> 15 & 1) == 1);
            crc <<= 1;
            if (c15 ^ b) crc ^= polynomial;
        }
    }

    crc &= 0xffff;

    return crc;
}

const char *build_answer(const char *inn, const char *factory_number)
{
    if (strlen(inn) != 12) return "ИНН должен быть из 12 цифр. Например: 009715225506";
    if (strlen(factory_number) != 14) return "Заводской номер кассы должен быть из 14 цифр. Например: 00308300087104\0";

    char source[43];
    strcpy(source, "0000000001");
    strcat(source, inn);
    strcat(source, "000000");
    strcat(source, factory_number);

    int answer = calculate_crc16_ccitt(source);

    char *prefix = "00000000010";
    char str_answer[6];
    char *result = calloc(sizeof(*prefix) + sizeof(str_answer), sizeof(char*));

    sprintf(str_answer, "%d", answer);
    strcpy(result, prefix);
    strcat(result, str_answer);

    return result;
}
