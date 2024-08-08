/* Алексеев Дмитрий Александрович*/

#include "temp_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> // Добавлено для `realloc`.
#include "temp_functions.h"

void processData(TemperatureReading readings[], int numReadings, int monthToProcess, int yearToProcess)
{
    if (monthToProcess > 0 && yearToProcess > 0)
    {
        printMonthlyStats(readings, numReadings, monthToProcess, yearToProcess); // Передаем год в printMonthlyStats
    }
    else if (monthToProcess > 0)
    {
        printMonthlyStats(readings, numReadings, monthToProcess, 0);
    }
    else if (yearToProcess > 0)
    {
        printYearlyStats(readings, numReadings, yearToProcess); // Передаем год в printYearlyStats
    }
    else
    {
        printYearlyStats(readings, numReadings, 0);
    }
}

void printMonthlyStats(TemperatureReading readings[], int numReadings, int month, int year)
{
    int count = 0;
    int minTemp = 99;
    int maxTemp = -99;
    int totalTemp = 0;
    for (int i = 0; i < numReadings; i++)
    {
        if (readings[i].month == month && (year == 0 || readings[i].year == year))
        {
            count++;
            totalTemp += readings[i].temperature;
            if (readings[i].temperature < minTemp)
            {
                minTemp = readings[i].temperature;
            }
            if (readings[i].temperature > maxTemp)
            {
                maxTemp = readings[i].temperature;
            }
        }
    }
    if (count > 0)
    {
        double averageTemp = (double)totalTemp / count;
        if (year > 0)
        {
            printf("Статистика за месяц %d года %d:\n", month, year);
        }
        else
        {
            printf("Статистика за месяц %d:\n", month);
        }
        printf("  Средняя температура: %.2f\n", averageTemp);
        printf("  Минимальная температура: %d\n", minTemp);
        printf("  Максимальная температура: %d\n", maxTemp);
    }
    else
    {
        if (year > 0)
        {
            printf("Данные по месяцу %d и году %d не найдены.\n", month, year);
        }
        else
        {
            printf("Данные по месяцу не найдены %d.\n", month);
        }
    }
}

void printYearlyStats(TemperatureReading readings[], int numReadings, int year)
{
    int count = 0;
    int minTemp = 99;
    int maxTemp = -99;
    int totalTemp = 0;
    for (int i = 0; i < numReadings; i++)
    {
        if (year == 0 || readings[i].year == year)
        {
            count++;
            totalTemp += readings[i].temperature;
            if (readings[i].temperature < minTemp)
            {
                minTemp = readings[i].temperature;
            }
            if (readings[i].temperature > maxTemp)
            {
                maxTemp = readings[i].temperature;
            }
        }
    }
    if (count > 0)
    {
        double averageTemp = (double)totalTemp / count;
        if (year > 0)
        {
            printf("Статистика за года %d:\n", year);
        }
        else
        {
            printf("Статистика за все года и месяца:\n");
        }
        printf("  Средняя температура: %.2f\n", averageTemp);
        printf("  Минимальная температура: %d\n", minTemp);
        printf("  Максимальная температура: %d\n", maxTemp);
    }
    else
    {
        if (year > 0)
        {
            printf("Данные для года не найдены %d.\n", year);
        }
        else
        {
            printf("Данные не найдены.\n");
        }
    }
}

void printHelp()
{
    printf("Использование: temp_stats [-h] [-f <filename.csv>] [-m <month>] [-g <year>]\n");
    printf("\n Опции:\n");
    printf("  -h  Информации о возможных ключах запуска с кратким описанием их назначения\n");
    printf("  -f  <filename.csv>  Входной CSV-файл\n");
    printf("  -m  <month>  Вывод статистики за определенный месяц\n");
    printf("  -g  <year>  Вывод статистики за определенный год\n");
}

int readData(const char *filename, TemperatureReading *readings, int *maxReadings)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return -1;
    }

    int numReadings = 0;
    char line[1024]; // Буфер для хранения строки из файла CSV

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Разбираем строку и сохраняем значения в структуре TemperatureReading
        int year, month, day, hour, minute, temperature;
        if (sscanf(line, "%d;%d;%d;%d;%d;%d", &year, &month, &day, &hour, &minute, &temperature) != 6)
        {
            printf("Ошибка в строке %d: Неправильный формат CSV.\n", ++numReadings);
            continue;
        }

        if (numReadings >= *maxReadings)
        {
            *maxReadings *= 2;
            TemperatureReading *temp = realloc(readings, *maxReadings * sizeof(TemperatureReading));
            if (temp == NULL)
            {
                fclose(fp);
                return -1;
            }
            readings = temp;
        }

        readings[numReadings].year = year;
        readings[numReadings].month = month;
        readings[numReadings].day = day;
        readings[numReadings].hour = hour;
        readings[numReadings].minute = minute;
        readings[numReadings].temperature = temperature;

        numReadings++;
    }

    fclose(fp);
    return numReadings;
}