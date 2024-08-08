/* Алексеев Дмитрий Александрович*/

#ifndef TEMP_FUNCTIONS_H // Защита заголовка
#define TEMP_FUNCTIONS_H

#include <stdio.h>

// Структура данных для показаний температуры
typedef struct
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int temperature;
} TemperatureReading;

// Прототипы функций
void printHelp();
int readData(const char *filename, TemperatureReading *readings, int *maxReadings);
void processData(TemperatureReading readings[], int numReadings, int monthToProcess, int yearToProcess);
void printMonthlyStats(TemperatureReading readings[], int numReadings, int month, int year);
void printYearlyStats(TemperatureReading readings[], int numReadings, int year);

#endif