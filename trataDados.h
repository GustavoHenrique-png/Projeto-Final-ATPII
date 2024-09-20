#ifndef TRATADADADOS_H
#define TRATADADADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>  // Para Sleep e system("cls")

#define MAX_PREREQUISITOS 10
#define MAX_DISCIPLINAS 21
#define DISCIPLINAS_POR_PAGINA 5  // Definimos o número de disciplinas por página

void menuGrade();
void leArquivos();
void cadastraDisciplina();
void excluiDisciplina();
void listaDisciplinaCadastrada();

// Definição do enum para o tipo de disciplina
typedef enum {
    Obrigatoria,
    Optativa
} TipoDisciplina;

// Definição de status da disciplina
typedef enum {
    Cursando,
    Cursada,
    NaoCursada
} statusDisciplina;

// Definição da struct para uma disciplina
typedef struct {
    char codigo[10]; // Código alfanumérico da disciplina
    char titulo[100]; // Título da disciplina
    int cargaHoraria; // Carga horária da disciplina
    int semestre; // Semestre em que a disciplina é oferecida
    char prerequisitos[MAX_PREREQUISITOS][10]; // Lista de códigos das disciplinas pré-requisito
    int numPrerequisitos; // Quantidade de pré-requisitos
    TipoDisciplina tipo; // Tipo da disciplina (Optativa ou Obrigatória)
    statusDisciplina status; // Status da disciplina
} Disciplina;

typedef struct {
    char codigo[10];
    char titulo[100];
    int semestre;
    char preRequisitos[MAX_PREREQUISITOS][10];
    int numPrerequisitos;
    statusDisciplina status;
} minhasDisciplinas;

// Definição da struct para a matriz curricular
typedef struct {
    Disciplina disciplinas[MAX_DISCIPLINAS];
    int numSemestres; // Número de semestres
} MatrizCurricular;

void acessaGrade() {
    menuGrade();
}

void menuGrade() {
    int acao;
    do {
        system("cls");  // Usa "cls" para limpar a tela no Windows
        printf("\n---------------------------------\nGrade\n---------------------------------\n");
        printf("1 - Lista Disciplina\n2 - Cadastra Disciplina\n3 - Excluir Disciplina\n4 - Voltar\n0 - Fechar\n---------------------------------\n");
        printf("Informe a acao desejada: ");
        scanf("%d", &acao);

        switch (acao) {
            case 1:
                leArquivos();
                break;
            case 2:
                cadastraDisciplina();
                break;
            case 3:
                excluiDisciplina();
                break;
            case 4:
                listaDisciplinaCadastrada();
                break;
            default:
                break;
        }
    } while (acao != 0);
}

void leArquivos() {
    FILE *file = fopen("disciplinas.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Disciplina disciplina[MAX_DISCIPLINAS];

    // Lê todas as disciplinas do arquivo
    size_t disciplinasLidas = fread(disciplina, sizeof(Disciplina), MAX_DISCIPLINAS, file);
    fclose(file);  // Fecha o arquivo após a leitura

    if (disciplinasLidas == 0) {
        printf("Nenhuma disciplina foi encontrada no arquivo.\n");
        return;
    }

    int pagina = 0;
    int continuar = 1;

    while (pagina * DISCIPLINAS_POR_PAGINA < disciplinasLidas && continuar == 1) {
        system("cls");  // Limpa a tela antes de exibir cada página
        printf("\n---------------------------------\nDisciplinas - Página %d\n---------------------------------\n", pagina + 1);

        // Exibe até 5 disciplinas por página
        for (int i = pagina * DISCIPLINAS_POR_PAGINA; i < (pagina + 1) * DISCIPLINAS_POR_PAGINA && i < disciplinasLidas; i++) {
            printf("Título: %s\n", disciplina[i].titulo);
            printf("Semestre: %d\n", disciplina[i].semestre);
            printf("Carga Horária: %d\n", disciplina[i].cargaHoraria);
            printf("Tipo: %s\n", (disciplina[i].tipo == Obrigatoria) ? "Obrigatória" : "Optativa");
            printf("---------------------------------\n");
        }

        // Se houver mais disciplinas a exibir, pergunte se o usuário quer continuar
        if ((pagina + 1) * DISCIPLINAS_POR_PAGINA < disciplinasLidas) {
            printf("Deseja ir para a próxima página? (1 - Sim, 0 - Não): ");
            scanf("%d", &continuar);
        } else {
            printf("Você chegou ao final da lista.\n");
            continuar = 0;
        }

        pagina++;  // Incrementa a página
    }
}

void cadastraDisciplina() {
    FILE *fileAluno = fopen("fileAluno.bin", "ab");  // Modo "ab" para adicionar sem apagar o conteúdo anterior
    if (fileAluno == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    minhasDisciplinas novaDisciplina;
    int escolha;

    printf("Código da disciplina:\n");
    scanf("%s", novaDisciplina.codigo);
    printf("Título da disciplina:\n");
    scanf("%s", novaDisciplina.titulo);
    printf("Semestre da disciplina:\n");
    scanf("%d", &novaDisciplina.semestre);

    printf("Necessita pré-requisitos?\n1 - Sim\n2 - Não\n");
    scanf("%d", &escolha);

    if (escolha == 1) {
        printf("Digite o número de pré-requisitos necessários:\n");
        scanf("%d", &novaDisciplina.numPrerequisitos);

        for (int j = 0; j < novaDisciplina.numPrerequisitos; j++) {
            printf("Digite o código do pré-requisito %d:\n", j + 1);
            scanf("%s", novaDisciplina.preRequisitos[j]);
        }
    } else {
        novaDisciplina.numPrerequisitos = 0;
    }

    // Salvando a nova disciplina no arquivo sem alterar as outras
    fwrite(&novaDisciplina, sizeof(minhasDisciplinas), 1, fileAluno);
    printf("Disciplina cadastrada com sucesso!\n");

    fclose(fileAluno);
}

void listaDisciplinaCadastrada() {
    
}

void excluiDisciplina() {
    
}

#endif
