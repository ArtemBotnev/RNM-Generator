// RNM-Generator
// Copyright Artem Botnev 2019
// MIT License

#define WIN "windows"
#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_NAME WIN
    #define INN_MESSAGE "Enter organization INN and press Enter"
    #define INN_ERROR_MESSAGE "INN must contain 12 digits. Example: 009715225506"
    #define FACTORY_NUMBER_MESSAGE "Enter factory number and press Enter"
    #define FACTORY_NUMBER_ERROR_MESSAGE "Factory number must contain 14 digits. Example: 00308300087104"
    #define RNM "RNM"
#else
    #define PLATFORM_NAME "not_bad_system_:)"
    #define INN_MESSAGE "Введите ИНН организации и нажмите ввод"
    #define INN_ERROR_MESSAGE "ИНН должен быть из 12 цифр. Например: 009715225506"
    #define FACTORY_NUMBER_MESSAGE "Введите заводской номер и нажмите ввод"
    #define FACTORY_NUMBER_ERROR_MESSAGE "Заводской номер кассы должен быть из 14 цифр. Например: 00308300087104"
    #define RNM "РНМ"
#endif

#include "crc.h"

char inn[INN_SIZE];
char factory_number[FACTORY_NUMBER_SIZE];

void ask_and_validate(char *src, short size, char *message, const char *error_message)
{
    char input[size + 2];
    printf("%s\n", message);
    fgets(input, size + 2, stdin);

    if (input[size] != '\n')
    {
        fseek(stdin, 0, SEEK_END);
        printf("%s\n", error_message);
        ask_and_validate(src, size, message, error_message);
    }

    for (int i = 0; i < size; i++)
    {
        src[i] = input[i];
    }
}

int main()
{
    ask_and_validate(inn, INN_SIZE, INN_MESSAGE, INN_ERROR_MESSAGE);
    ask_and_validate(factory_number, FACTORY_NUMBER_SIZE, FACTORY_NUMBER_MESSAGE, FACTORY_NUMBER_ERROR_MESSAGE);

    const char *answer = build_answer(inn, factory_number);
    printf("%s: %s\n", RNM,  answer);

    if (PLATFORM_NAME == WIN) system("pause");

    return 0;
}