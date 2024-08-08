/* Алексеев Дмитрий Александрович*/

#include "temp_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <locale.h>

int main(int argc, char *argv[])
{
 //   setlocale(LC_ALL, "Russian");
    int opt;
    const char *filename = NULL;
    int monthToProcess = 0;
    int yearToProcess = 0;
    while ((opt = getopt(argc, argv, "hf:m:g:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            printHelp();
            return 0;
        case 'f':
            filename = optarg;
            break;
        case 'm':
            monthToProcess = atoi(optarg);
            break;
        case 'g':
            yearToProcess = atoi(optarg);
            break;
        default:
            printHelp();
            return 1;
        }
    }
    if (filename == NULL)
    {
        printHelp();
        return 1;
    }
    // Динамическое выделение памяти для чтения
    TemperatureReading *readings = NULL;
    int numReadings = 0;
    int maxReadings = 1000000; // выделяемое число строк
    readings = malloc(maxReadings * sizeof(TemperatureReading));
    if (readings == NULL)
    {
        fprintf(stderr, "Ошибка выделения памяти.\n");
        return 1;
    }
    // Считывание данных из CSV-файла
    numReadings = readData(filename, readings, &maxReadings);
    if (numReadings == -1)
    {
        free(readings); // Освобождение выделенной памяти при ошибке
        return 1;       // Возникла ошибка при чтении файла
    }
    // Обработка и печать данных
    if (monthToProcess > 0 && yearToProcess > 0)
    {                                                                      // Указаны оба значения -m и -g
        processData(readings, numReadings, monthToProcess, yearToProcess); // месяц и год
    }
    else if (monthToProcess > 0)
    {
        processData(readings, numReadings, monthToProcess, 0); // только месяц
    }
    else if (yearToProcess > 0)
    {
        processData(readings, numReadings, 0, yearToProcess); // только год
    }
    else
    {
        processData(readings, numReadings, 0, 0); // Не указаны ни -m, ни -g
    }

    free(readings); // Освободите выделенную память
    return 0;
}