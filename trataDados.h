#ifndef TRATADADADOS_H
#define TRATADADADOS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_PREREQUISITOS 10
#define MAX_DISCIPLINAS 21

void menuGrade();
void leArquivos();

// Definição do enum para o tipo de disciplina
typedef enum {
    Obrigatoria,
    Optativa
} TipoDisciplina;

// Definição da struct para uma disciplina
typedef struct {
    char codigo[10];// Código alfanumérico da disciplina
    char titulo[100];// Título da disciplina
    int cargaHoraria;// Carga horária da disciplina
    int semestre;// Semestre em que a disciplina é oferecida
    char prerequisitos[MAX_PREREQUISITOS][10];  // Lista de códigos das disciplinas pré-requisito
    int numPrerequisitos;// Quantidade de pré-requisitos
    TipoDisciplina tipo;// Tipo da disciplina (Optativa ou Obrigatória)
} Disciplina;

// Definição da struct para a matriz curricular
typedef struct {
    Disciplina disciplinas[MAX_DISCIPLINAS];
    int numSemestres;                  // Número de semestres
} MatrizCurricular;

void acessaGrade(){
    menuGrade();
}

void menuGrade(){
    int acao;
    do {
        system("cls");
        printf("\n---------------------------------\nGrade\n---------------------------------\n");
        printf("1 - Lista Disciplina\n2 - Cadastra Disciplina\n3 - Excluir Disciplina\n4 - Voltar\n0 - Fechar\n---------------------------------\n");
        printf("Informe a acao desejada: ");
        scanf("%d", &acao);

        switch (acao) {
        case 1:
            leArquivos();
            break;
        case 2:
            printf("Cadastra Disciplina\n");
            break;
        case 3:
            printf("Exclui Disciplina\n");
            break;
        case 4:
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

    // Exibe as disciplinas lidas
    for (size_t i = 0; i < disciplinasLidas; i++) {
        printf("Título: %s\n", disciplina[i].titulo);
        printf("Semestre: %d\n", disciplina[i].semestre);
        printf("Carga Horária: %d\n", disciplina[i].cargaHoraria);
        printf("Tipo: %s\n", (disciplina[i].tipo == Obrigatoria) ? "Obrigatória" : "Optativa");
        printf("---------------------------------\n");
    }

    if (disciplinasLidas == 0) {
        printf("Nenhuma disciplina foi encontrada no arquivo.\n");
    }
}

#endif
