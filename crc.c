// RNM-Generator
// Copyright Artem Botnev 2019
// MIT License

#include "crc.h"

void convert_string_to_bytes(const char *ascii_str, unsigned char *bytes)
{
    int i = 0;
    while (ascii_str[i] != 0x00)
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
        for(int j = 0; j < BITES_COUNT; j++)
        {
            int b = ((bytes[i] >> (BITES_COUNT - j - 1) & 1) == 1);
            int c15 = ((crc >> ((BITES_COUNT << 1) - 1) & 1) == 1);
            crc <<= 1;
            if (c15 ^ b) crc ^= POLYNOMIAL;
        }
    }

    crc &= CRC;

    return crc;
}

char *add_spaces(const char *str, int size)
{
    int spaces_count = (size + 1) / CHARS_BETWEEN_SPACES;
    int answer_size = size + spaces_count;
    char *result = calloc(answer_size, sizeof(char*));

    int shift = 0;
    int next_space_index = CHARS_BETWEEN_SPACES;
    for(int i = 0; i < answer_size; i++)
    {
        if (i == next_space_index)
        {
            shift++;
            next_space_index += CHARS_BETWEEN_SPACES + 1;
            result[i] = 0x20;
        }
        else
        {
            result[i] = str[i - shift];
        }
    }

    return result;
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
    int full_answer_size = sizeof(RESULT_PREFIX) + sizeof(str_answer);
    char str_full_answer[full_answer_size];

    sprintf(str_answer, "%d", answer);

    // add lead zero
    if (str_answer[GEN_ANSWER_SIZE - 2] == 0x00)
    {
        for (int i = GEN_ANSWER_SIZE - 2; i > 0; i--)
        {
            str_answer[i] = str_answer[i - 1];
        }
        str_answer[0] = '0';
    }

    strcpy(str_full_answer, RESULT_PREFIX);
    strcat(str_full_answer, str_answer);

    return add_spaces(str_full_answer, full_answer_size);
}
