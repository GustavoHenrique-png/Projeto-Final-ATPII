#ifndef agenda_h
#define agenda_h
#include <stdio.h>
#include <unistd.h>
#include "data.h"

#define MAX_PAGINA 5
#define SLEEP_TIME 2

void AdicionaCompromisso();
void InsereCompromissoNoArquivo();
void ListaCompromissos();
void ListaCompromissosPendentes();
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

    sleep(SLEEP_TIME);
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

// region ListaCompromissos
//  Função para listar os compromissos
void ListaCompromissos()
{
    system("cls");
    FILE *file = fopen("agenda.bin", "rb"); // Abre arquivo para leitura
    if (file == NULL)
    {
        perror("Erro ao abrir arquivo.");
        sleep(SLEEP_TIME);
        return;
    }
    else
    {
        Compromisso obj;
        int pagina = 0;
        int totalCompromissos = 0;

        // Conta o total de compromissos
        while (fread(&obj, sizeof(Compromisso), 1, file))
        {
            if (obj.status == Pendente)
                totalCompromissos++;
        }

        fseek(file, 0, SEEK_SET); // Reseta o ponteiro do arquivo para o inicio

        if (totalCompromissos == 0) // Verifica se existem compromissos pendentes
        {
            printf("Nenhum compromisso encontrado.\n");
            fclose(file);
            return;
        }

        int acao;
        do
        {
            system("cls");
            printf("\n---------------------------------\nCompromissos - Pagina %d\n---------------------------------\n", pagina + 1);

            int inicio = pagina * MAX_PAGINA; // Define o inicio da pagina
            int fim = inicio + MAX_PAGINA;    // Define o fim da pagina
            int compromissoAtual = 0;         // Contador de compromissos

            while (fread(&obj, sizeof(Compromisso), 1, file)) // Le o arquivo e imprime os compromissos
            {
                if (obj.status == Pendente)
                {
                    if (compromissoAtual >= inicio && compromissoAtual < fim) // Verifica se o compromisso atual esta na pagina
                        ImprimeInformacoes(compromissoAtual + 1, obj);
                    compromissoAtual++;
                }
            }

            // Reseta o ponteiro do arquivo para o inicio
            fseek(file, 0, SEEK_SET);

            // Imprime as opcoes do menu
            printf("\n---------------------------------\n");
            if (fim < totalCompromissos)
                printf("1 - Proxima Pagina\n");
            if (pagina > 0)
                printf("2 - Pagina Anterior\n");
            printf("3 - Excluir Compromisso\n");
            printf("4 - Mudar Status\n");
            printf("0 - Voltar ao Menu\n");
            scanf("%d", &acao);

            if (acao == 1 && fim < totalCompromissos)
                pagina++;
            else if (acao == 2 && pagina > 0)
                pagina--;

            if (acao == 3)
            {
                fclose(file);
                ExcluirCompromisso();
            }
        } while (acao != 0 && acao != 3);

        fclose(file);
    }
}

// Função para listar os compromissos pendentes
void ListaCompromissosPendentes()
{
    system("cls");
    printf("\n---------------------------------\nCompromissos Pendentes\n---------------------------------\n");

    FILE *file = fopen("agenda.bin", "rb"); // Abre arquivo para leitura
    if (file == NULL)
    {
        perror("Erro ao abrir arquivo.");
        fclose(file);
        return;
    }
    else
    {
        Compromisso obj;
        int pagina = 0;
        int totalCompromissos = 0;

        // Conta o total de compromissos pendentes
        while (fread(&obj, sizeof(Compromisso), 1, file))
        {
            if (obj.status == Pendente)
                totalCompromissos++;
        }

        fseek(file, 0, SEEK_SET); // Reseta o ponteiro do arquivo para o inicio

        if (totalCompromissos == 0) // Verifica se existem compromissos pendentes
        {
            printf("Nenhum compromisso pendente encontrado.\n");
            fclose(file);
            return;
        }

        int acao;
        do
        {
            system("cls");
            printf("\n---------------------------------\nCompromissos Pendentes - Pagina %d\n---------------------------------\n", pagina + 1);

            int inicio = pagina * MAX_PAGINA; // Define o inicio da pagina
            int fim = inicio + MAX_PAGINA;    // Define o fim da pagina
            int compromissoAtual = 0;         // Contador de compromissos

            while (fread(&obj, sizeof(Compromisso), 1, file)) // Le o arquivo e imprime os compromissos pendentes
            {
                if (obj.status == Pendente)
                {
                    if (compromissoAtual >= inicio && compromissoAtual < fim) // Verifica se o compromisso atual esta na pagina
                        ImprimeInformacoes(compromissoAtual + 1, obj);
                    compromissoAtual++;
                }
            }

            // Reseta o ponteiro do arquivo para o inicio
            fseek(file, 0, SEEK_SET);

            // Imprime as opcoes do menu
            printf("\n---------------------------------\n");
            if (fim < totalCompromissos)
                printf("1 - Proxima Pagina\n");
            if (pagina > 0)
                printf("2 - Pagina Anterior\n");
            printf("3 - Excluir Compromisso\n");
            printf("0 - Voltar ao Menu\n");
            scanf("%d", &acao);

            if (acao == 1 && fim < totalCompromissos)
                pagina++;
            else if (acao == 2 && pagina > 0)
                pagina--;

            if (acao == 3)
            {
                fclose(file);
                ExcluirCompromisso();
            }
        } while (acao != 0 && acao != 3);

        if (file != NULL)
            fclose(file);
    }
}
// endregion ListaCompromissos

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
            int totalCompromissos = 0;

            while (fread(&obj, sizeof(Compromisso), 1, file))
            {
                if (obj.status == Pendente)
                    totalCompromissos++;
            }

            // Reseta o ponteiro do arquivo para o inicio
            fseek(file, 0, SEEK_SET);

            if (totalCompromissos == 0)
            {
                printf("Nenhum compromisso encontrado. Voltando para o menu da agenda.\n");
                sleep(SLEEP_TIME);
                return;
            }

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

    printf("\n---------------------------------\n");
    printf("Compromisso excluido com sucesso!\n");
    printf("\n---------------------------------\n");
    printf("\nVoltando para o menu\n");
    sleep(SLEEP_TIME);
}

// Função para imprimir as informações de um compromisso na listagem
void ImprimeInformacoes(int i, Compromisso obj)
{
    printf("Id: %d \nData: %d/%d/%d \nDescricao: %s \nStatus: %s\n---------------------------------\n", i, obj.data.dia, obj.data.mes, obj.data.ano, obj.descricao, obj.status == Pendente ? "Pendente" : "Concluido");
}

#endif
