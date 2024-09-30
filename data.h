#ifndef data_h
#define data_h
#include <stdio.h>

// Definição do structa de data
typedef struct Data
{
    int dia; // Armazena dia
    int mes; // Armazena mês
    int ano; // Armazena ano
} Data;

// Converte string "dd-mm-aa" para struct
Data ConverteStringToData(char *dateStr)
{
    Data data;

    //Captura e separação de dias e meses (%2d) e ano (%4d)
    if (sscanf(dateStr, "%2d-%2d-%4d", &data.dia, &data.mes, &data.ano) != 3)
    {
        return (Data){0, 0, 0};
    }

    return data;
}

#endif