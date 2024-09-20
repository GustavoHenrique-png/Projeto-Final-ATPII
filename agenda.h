#ifndef agenda_h
#define agenda_h
#include <stdio.h>
#include <unistd.h>
#include "data.h"

void AdicionaCompromisso();
void InsereCompromissoNoArquivo();
void ListaCompromissos();
void ImprimeInformacoes();
void ExcluirCompromisso();
void MenuAgenda();

// Definição do enum para o status do compromisso
typedef enum Status
{
    Pendente = 0,
    Concluido = 1
} Status;

// Definição da struct para um compromisso
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
        printf("1 - Adicionar Compromisso\n2 - Listar Compromissos\n0 - Voltar\n---------------------------------\n");
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
    scanf(" %[^\n]", compromisso.descricao); // Lê a descrição do compromisso
    printf("Informe a data do compromisso (formato dd-mm-AAAA): ");
    scanf(" %[^\n]", data); // Lê a data do compromisso
    printf("Informe o status do compromisso (0 - Pendente, 1 - Concluido): ");
    scanf("%d", &compromisso.status); // Lê o status do compromisso

    compromisso.data = ConverteStringToData(data); // Converte a string para data

    while (compromisso.data.dia == 0 && compromisso.data.mes == 0 && compromisso.data.ano == 0) // Garante que a data informada é válida
    {
        printf("Data informada invalida, por favor informe uma data valida (formato dd-mm-AAAA): ");
        scanf(" %[^\n]", data);
        compromisso.data = ConverteStringToData(data);
    }

    InsereCompromissoNoArquivo(compromisso); // Insere o compromisso no arquivo

    printf("\n---------------------------------\n");
    printf("\nCompromisso adicionado com sucesso a sua agenda!\n");
    printf("\n---------------------------------\n");
    printf("\nVoltando para o menu da agenda\n");

    sleep(2); // Aguarda 2 segundos e volta para o menu da agenda
}

// Função para inserir um compromisso no arquivo
void InsereCompromissoNoArquivo(Compromisso compromisso)
{
    FILE *file = fopen("agenda.bin", "ab"); // Abre arquivo para escrita no final
    if (file == NULL)
    {
        perror("Erro ao abrir arquivo.");
        return;
    }
    else
    {
        fwrite(&compromisso, sizeof(Compromisso), 1, file); // Escreve o compromisso no arquivo
        fclose(file);
    }
}

// Função para listar os compromissos
void ListaCompromissos()
{
    int acao;
    do
    {
        system("cls");
        printf("\n---------------------------------\nCompromissos\n---------------------------------\n");
        FILE *file = fopen("agenda.bin", "rb"); // Abre arquivo para leitura
        if (file == NULL)
        {
            perror("Erro ao abrir arquivo.");
            sleep(2);
            return;
        }
        else
        {
            Compromisso obj;
            for (int i = 1; fread(&obj, sizeof(Compromisso), 1, file); i++) // Lê o arquivo e imprime os compromissos
            {
                ImprimeInformacoes(i, obj);
            }

            fclose(file);
        }

        printf("\n---------------------------------\n");
        printf("1 - Excluir Compromisso\n2 - Proxima Pagina\n3 - Pagina Anterior\n0 - Voltar ao Menu\n");
        scanf("%d", &acao);
        switch (acao)
        {
        case 1:
            ExcluirCompromisso();
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
        }
    } while (acao != 0);
}

// Função para excluir um compromisso
void ExcluirCompromisso()
{
    int posicao;
    printf("Informe o id do compromisso que deseja excluir: ");
    scanf("%d", &posicao);

    FILE *file = fopen("agenda.bin", "rb"); // Abre arquivo para leitura
    if (file == NULL)
    {
        perror("Erro ao abrir arquivo.");
        return;
    }
    else
    {
        FILE *temp = fopen("temp.bin", "wb"); // Abre arquivo temporario para escrita
        if (temp == NULL)
        {
            perror("Erro ao abrir arquivo.");
            return;
        }
        else
        {
            Compromisso obj;
            for (int i = 1; fread(&obj, sizeof(Compromisso), 1, file); i++) // Le arquivo e escreve no arquivo temporario
            {
                if (i != posicao) // Verifica se a posicao atual é a posicao informada
                {
                    fwrite(&obj, sizeof(Compromisso), 1, temp); // Escreve no arquivo temporario
                }
            }

            // Fecha os arquivos
            fclose(file);
            fclose(temp);

            // Remove o arquivo original e renomeia o arquivo temporario
            remove("agenda.bin");
            rename("temp.bin", "agenda.bin");
        }
    }

    printf("Compromisso excluido com sucesso! Voltando para a listagem.\n");
    sleep(2);
    ListaCompromissos();
}

// Função para imprimir as informações de um compromisso na listagem
void ImprimeInformacoes(int i, Compromisso obj)
{
    printf("%d - %d/%d/%d - %s - %s\n", i, obj.data.dia, obj.data.mes, obj.data.ano, obj.descricao, obj.status == Pendente ? "Pendente" : "Concluido");
}

#endif
