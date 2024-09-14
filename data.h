#ifndef data_h
#define data_h
#include <stdio.h>

typedef struct Data
{
    int dia;
    int mes;
    int ano;
} Data;

Data ConverteStringToData(char *dateStr)
{
    Data data;

    if (sscanf(dateStr, "%2d-%2d-%4d", &data.dia, &data.mes, &data.ano) != 3)
    {
        return (Data){0, 0, 0};
    }

    return data;
}

#endif