#ifndef agenda_h
#define agenda_h
#include <stdio.h>
#include <unistd.h>
#include "data.h"

void AdicionaCompromisso();
void InsereCompromissoNoArquivo();
void ListaCompromissos();
void ImprimeInformacoes();
void MenuAgenda();

typedef enum Status
{
    Pendente = 0,
    Concluido = 1
} Status;

typedef struct Compromisso
{
    char descricao[100];
    Data data;
    Status status;
} Compromisso;

void AcessaAgenda()
{
    MenuAgenda();
}

void MenuAgenda()
{
    int acao;

    do
    {
        system("cls");
        printf("\n---------------------------------\nAgenda\n---------------------------------\n");
        printf("1 - Adicionar Compromisso\n2 - Listar Compromissos\n3 - Excluir Compromisso\n0 - Voltar\n---------------------------------\n");
        printf("Informe a acao desejada: ");
        scanf("%d", &acao);

        switch (acao)
        {
        case 1:
            AdicionaCompromisso();
            break;
        case 2:
            ListaCompromissos();
            break;
        case 3:
            printf("Excluir Compromisso\n");
            break;
        default:
            break;
        }
    } while (acao != 0);
}

void AdicionaCompromisso()
{
    Compromisso compromisso;
    char data[11];

    system("cls");
    printf("\n---------------------------------\nAdicionando Compromisso\n---------------------------------\n");
    printf("Informe a descricao do compromisso: ");
    scanf(" %[^\n]", compromisso.descricao);
    printf("Informe a data do compromisso (formato dd-mm-AAAA): ");
    scanf(" %[^\n]", data);
    printf("Informe o status do compromisso (0 - Pendente, 1 - Concluido): ");
    scanf("%d", &compromisso.status);

    compromisso.data = ConverteStringToData(data);

    while (compromisso.data.dia == 0 && compromisso.data.mes == 0 && compromisso.data.ano == 0)
    {
        printf("Data informada invalida, por favor informe uma data valida (formato dd-mm-AAAA): ");
        scanf(" %[^\n]", data);
        compromisso.data = ConverteStringToData(data);
    }

    InsereCompromissoNoArquivo(compromisso);

    printf("\n---------------------------------\n");
    printf("\nCompromisso adicionado com sucesso a sua agenda!\n");
    printf("\n---------------------------------\n");
    printf("\nVoltando para o menu da agenda\n");

    sleep(2);
}

void InsereCompromissoNoArquivo(Compromisso compromisso)
{
    FILE *file = fopen("agenda.bin", "ab");
    if (file == NULL)
    {
        perror("Erro ao abrir arquivo.");
        return;
    }
    else
    {
        fwrite(&compromisso, sizeof(Compromisso), 1, file);
        fclose(file);
    }
}

void ListaCompromissos()
{
    int acao;
    do
    {
        system("cls");
        printf("\n---------------------------------\nCompromissos\n---------------------------------\n");
        FILE *file = fopen("agenda.bin", "rb");
        if (file == NULL)
        {
            perror("Erro ao abrir arquivo.");
            return;
        }
        else
        {
            Compromisso obj;
            for (int i = 1; fread(&obj, sizeof(Compromisso), 1, file); i++)
            {
                ImprimeInformacoes(i, obj);
            }

            fclose(file);
        }

        printf("\n---------------------------------\n");
        printf("0 - Voltar\n");
        scanf("%d", &acao);
    } while (acao != 0);
}

void ImprimeInformacoes(int i, Compromisso obj)
{
    printf("%d - %d/%d/%d - %s - %s\n", i, obj.data.dia, obj.data.mes, obj.data.ano, obj.descricao, obj.status == Pendente ? "Pendente" : "Concluido");
}

#endif
