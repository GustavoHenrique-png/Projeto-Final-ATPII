#ifndef agenda_h
#define agenda_h
#include <stdio.h>
#include <unistd.h>

void AdicionaCompromisso();
void ListaCompromissos();
void MenuAgenda();

typedef struct Compromisso
{
    char descricao[100];
    char data[10];
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

    system("cls");
    printf("\n---------------------------------\nAdicionando Compromisso\n---------------------------------\n");
    printf("Informe a descricao do compromisso: ");
    scanf(" %[^\n]", compromisso.descricao);
    printf("Informe a data do compromisso: ");
    scanf(" %[^\n]", compromisso.data);

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

    printf("\n---------------------------------\n");
    printf("\nCompromisso adicionado com sucesso a sua agenda!\n");
    printf("\n---------------------------------\n");
    printf("\nVoltando para o menu da agenda\n");

    printf("o-\r");
    sleep(1);
    printf("-o\r");
    sleep(1);
    printf("o-\r");
    sleep(1);
    printf("-o\r");
    sleep(1);
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
                printf("%d - Descricao: %s\n", i, obj.descricao);
            }

            fclose(file);
        }

        printf("\n---------------------------------\n");
        printf("0 - Voltar\n");
        scanf("%d", &acao);
    } while (acao != 0);
}
#endif
