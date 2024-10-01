#ifndef TRATADADADOS_H
#define TRATADADADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define MAX_PREREQUISITOS 10     // Definimos o número máximo de pre-requisitos
#define MAX_DISCIPLINAS 21       // Definimos o número máximo de disciplinas
#define DISCIPLINAS_POR_PAGINA 5 // Definimos o número de disciplinas por página

// Declaração das funções do sistema
void menuGrade();
void leArquivos();
void cadastraDisciplina();
void excluiDisciplina();
void listaDisciplinaCadastrada();

// Definição do enum para o tipo de disciplina
typedef enum
{
    Obrigatoria,
    Optativa
} TipoDisciplina;

// Definição de status da disciplina
typedef enum
{
    Cursando,
    Cursada,
    NaoCursada
} statusDisciplina;

// Definição da struct para uma disciplina
typedef struct
{
    char codigo[11];                           // Código alfanumérico da disciplina
    char titulo[100];                          // Título da disciplina
    int cargaHoraria;                          // Carga horária da disciplina
    int semestre;                              // Semestre em que a disciplina é oferecida
    char prerequisitos[MAX_PREREQUISITOS][10]; // Lista de códigos das disciplinas pré-requisito
    int numPrerequisitos;                      // Quantidade de pré-requisitos
    TipoDisciplina tipo;                       // Tipo da disciplina (Optativa ou Obrigatória)
    statusDisciplina status;                   // Status da disciplina
} Disciplina;

// Struct que representa a disciplina
typedef struct
{
    char codigo[10];
    char titulo[100];
    int semestre;
    int cargaHoraria;
    char preRequisitos[MAX_PREREQUISITOS][10];
    int numPrerequisitos;
    statusDisciplina status;
    TipoDisciplina tipo;
} minhasDisciplinas;

// Função que acessa o menu de grade
void acessaGrade()
{
    menuGrade();
}

// Função que exibe o menu de grade curricular
void menuGrade()
{
    int acao;
    do
    {
        system("cls"); // Limpa a tela com "cls"
        printf("\n---------------------------------\nGrade\n---------------------------------\n");
        printf("1 - Lista Disciplina\n2 - Cadastra Disciplina\n3 - Excluir Disciplina\n4 - Lista Disciplina Cadastrada\n0 - Voltar\n---------------------------------\n");
        printf("Informe a acao desejada: ");
        scanf("%d", &acao);

        // Escolhas para navegar pelos menus
        switch (acao)
        {
        case 1:
            leArquivos(); // Chamada da função que lista as disciplinas do arquivo
            break;
        case 2:
            cadastraDisciplina(); // Chamada da função que cadastra as disciplinas no arquivo novo
            break;
        case 3:
            excluiDisciplina(); // Chamada da função que exclui uma disciplina do arquivo do aluno
            break;
        case 4:
            listaDisciplinaCadastrada(); // Chamada da função que lista as disciplinas cadastradas
            break;
        default:
            break;
        }
    } while (acao != 0); // Condição de parada do loop
}

// Função que lê o arquivo
void leArquivos()
{
    FILE *file = fopen("disciplinas.bin", "rb"); // Abre o arquivo
    if (file == NULL)
    { // Verifica se o arquivo abriu corretamente
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Disciplina disciplina[MAX_DISCIPLINAS]; // Array que armazena as disciplinas

    // Lê todas as disciplinas do arquivo
    size_t disciplinasLidas = fread(disciplina, sizeof(Disciplina), MAX_DISCIPLINAS, file);
    fclose(file); // Fecha o arquivo após a leitura

    if (disciplinasLidas == 0)
    { // Verifica se há disciplinas no arquivo
        printf("Nenhuma disciplina foi encontrada no arquivo.\n");
        return;
    }

    int pagina = 0;
    int continuar = 1;

    while (pagina * DISCIPLINAS_POR_PAGINA < disciplinasLidas && continuar == 1)
    {
        system("cls"); // Limpa a tela antes de exibir cada página
        printf("\n---------------------------------\nDisciplinas - Pagina %d\n---------------------------------\n", pagina + 1);

        // Exibe até 5 disciplinas por página
        for (int i = pagina * DISCIPLINAS_POR_PAGINA; i < (pagina + 1) * DISCIPLINAS_POR_PAGINA && i < disciplinasLidas; i++)
        {
            printf("Titulo: %s\n", disciplina[i].titulo);
            printf("Semestre: %d\n", disciplina[i].semestre);
            printf("Carga Horaria: %d\n", disciplina[i].cargaHoraria);
            printf("Tipo: %s\n", (disciplina[i].tipo == Obrigatoria) ? "Obrigatoria" : "Optativa");
            printf("---------------------------------\n");
        }

        // Se houver mais disciplinas, mudar a pagina
        if ((pagina + 1) * DISCIPLINAS_POR_PAGINA < disciplinasLidas)
        {
            printf("Deseja ir para a proxima pagina? (1 - Sim, 0 - Não): ");
            scanf("%d", &continuar);
        }
        else
        {
            printf("Voce chegou ao final da lista.\n");
            continuar = 0;
        }

        pagina++; // Incrementa a página
    }
}

// Função que cadastra uma nova disciplina
void cadastraDisciplina()
{
    FILE *fileAluno = fopen("fileAluno.bin", "ab"); // Abre o arquivo
    if (fileAluno == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    minhasDisciplinas novaDisciplina; // Cria uma nova disciplina a ser cadastrada
    int escolha;

    // Dados da disciplina a ser cadastrada
    printf("Codigo da disciplina:\n");
    scanf("%s", novaDisciplina.codigo);
    printf("Titulo da disciplina:\n");
    scanf("%s", novaDisciplina.titulo);
    printf("Semestre da disciplina:\n");
    scanf("%d", &novaDisciplina.semestre);
    printf("Carga horaria da disciplina:\n");
    scanf("%d", &novaDisciplina.cargaHoraria);

    printf("Necessita de pre-requisitos?\n1 - Sim\n2 - Não\n");
    scanf("%d", &escolha);

    if (escolha == 1)
    { // Se tiver pre-requisitos informar os códigos
        printf("Digite o número de pre-requisitos necessarios:\n");
        scanf("%d", &novaDisciplina.numPrerequisitos);

        for (int j = 0; j < novaDisciplina.numPrerequisitos; j++)
        {
            printf("Digite o codigo do pre-requisito %d:\n", j + 1);
            scanf("%s", novaDisciplina.preRequisitos[j]);
        }
    }
    else
    {
        novaDisciplina.numPrerequisitos = 0;
    }

    // Salvando a nova disciplina no arquivo
    fwrite(&novaDisciplina, sizeof(minhasDisciplinas), 1, fileAluno);
    printf("Disciplina cadastrada com sucesso!\n");
    Sleep(5000);

    fclose(fileAluno);
}

void listaDisciplinaCadastrada()
{
    FILE *fileAluno = fopen("fileAluno.bin", "rb");
    if (fileAluno == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    minhasDisciplinas disciplinas[MAX_DISCIPLINAS];

    size_t disciplinasLidas = fread(disciplinas, sizeof(minhasDisciplinas), MAX_DISCIPLINAS, fileAluno);
    fclose(fileAluno);

    if (disciplinasLidas == 0)
    {
        printf("Nenhuma disciplina foi encontrada no arquivo.\n");
        return;
    }

    int pagina = 0;
    int continuar = 1;

    while (pagina * DISCIPLINAS_POR_PAGINA < disciplinasLidas && continuar == 1)
    {
        system("cls");
        printf("\n---------------------------------\nDisciplinas - Pagina %d\n---------------------------------\n", pagina + 1);

        for (int i = pagina * DISCIPLINAS_POR_PAGINA; i < (pagina + 1) * DISCIPLINAS_POR_PAGINA && i < disciplinasLidas; i++)
        {
            printf("Codigo: %s\n", disciplinas[i].codigo);
            printf("Titulo: %s\n", disciplinas[i].titulo);
            printf("Semestre: %d\n", disciplinas[i].semestre);
            printf("Carga Horaria: %d\n", disciplinas[i].cargaHoraria);
            printf("Pre-requisitos: ");
            for (int j = 0; j < disciplinas[i].numPrerequisitos; j++)
            {
                printf("%s ", disciplinas[i].preRequisitos[j]);
            }
            printf("\nTipo: %s\n", (disciplinas[i].tipo == Obrigatoria) ? "Obrigatoria" : "Optativa");
            printf("---------------------------------\n");
        }

        Sleep(5000);

        if ((pagina + 1) * DISCIPLINAS_POR_PAGINA < disciplinasLidas)
        {
            printf("Deseja ir para a próxima pagina? (1 - Sim, 0 - Não): ");
            scanf("%d", &continuar);
        }
        else
        {
            printf("Voce chegou ao final da lista.\n");
            continuar = 0;
        }

        pagina++;
    }
}

// Função que exclui uma disciplina
void excluiDisciplina()
{

    FILE *fileAluno = fopen("fileAluno.bin", "rb"); // Abre o arquivo em modo leitura
    if (fileAluno == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    minhasDisciplinas disciplinas[MAX_DISCIPLINAS];
    size_t disciplinasLidas = fread(disciplinas, sizeof(minhasDisciplinas), MAX_DISCIPLINAS, fileAluno);
    fclose(fileAluno);

    if (disciplinasLidas == 0)
    {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }

    char codigo[10]; // Armazena o código da disciplina a ser excluida
    printf("Digite o codigo da disciplina que deseja excluir:\n");
    scanf("%s", codigo);

    // Arquivo temporário para armazenar o que não vai ser excluido
    FILE *fileTemp = fopen("temp.bin", "wb");
    if (fileTemp == NULL)
    {
        printf("Erro ao criar o arquivo temporário.\n");
        return;
    }

    int encontrado = 0; // Variavel para verificar se a disciplina foi encontrada

    for (size_t i = 0; i < disciplinasLidas; i++)
    {
        // Verifica se o código da disciplina atual é diferente do código que queremos excluir
        if (strcmp(disciplinas[i].codigo, codigo) != 0)
        {
            fwrite(&disciplinas[i], sizeof(minhasDisciplinas), 1, fileTemp);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(fileTemp);

    // Se o código for igual, substitue o original pelo temporario
    if (encontrado)
    {
        remove("fileAluno.bin");             // Remove o original
        rename("temp.bin", "fileAluno.bin"); // Renomeia o temporário para o original
        printf("Disciplina com codigo '%s' excluida com sucesso!\n", codigo);
    }
    else
    {
        printf("Disciplina com codigo '%s' nao encontrada.\n", codigo);
    }

    // Limpa o arquivo temporário se não foi usado
    if (encontrado == 0)
    {
        remove("temp.bin"); // Remove o temporario se n foi usado
    }
}

#endif
