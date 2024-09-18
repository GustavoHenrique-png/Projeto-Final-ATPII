#ifndef TRATADADADOS_H
#define TRATADADADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define MAX_PREREQUISITOS 10
#define MAX_DISCIPLINAS 21

void menuGrade();
void leArquivos();
void cadastraDisciplina();
void excluiDisciplina();

// Definição do enum para o tipo de disciplina
typedef enum {
    Obrigatoria,
    Optativa
} TipoDisciplina;

//Definição de status da disciplina
typedef enum{
    Cursando,
    Cursada,
    NaoCursada
} statusDisciplina;

// Definição da struct para uma disciplina
typedef struct {
    char codigo[10];// Código alfanumérico da disciplina
    char titulo[100];// Título da disciplina
    int cargaHoraria;// Carga horária da disciplina
    int semestre;// Semestre em que a disciplina é oferecida
    char prerequisitos[MAX_PREREQUISITOS][10];  // Lista de códigos das disciplinas pré-requisito
    int numPrerequisitos;// Quantidade de pré-requisitos
    TipoDisciplina tipo;// Tipo da disciplina (Optativa ou Obrigatória)
    statusDisciplina status;//mantém os status de uma disciplina
} Disciplina;

typedef struct{
    char codigo[10];
    char titulo [100];
    int semestre;
    char preRequisitos[MAX_PREREQUISITOS][10];
    int numPrerequisitos;
    statusDisciplina status;
}minhasDisciplinas;

// Definição da struct para a matriz curricular
typedef struct {
    Disciplina disciplinas[MAX_DISCIPLINAS];
    int numSemestres;// Número de semestres
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
            cadastraDisciplina();
            break;
        case 3:
            excluiDisciplina();
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
        sleep(10);
    }

    if (disciplinasLidas == 0) {
        printf("Nenhuma disciplina foi encontrada no arquivo.\n");
    }

}

void cadastraDisciplina(){
    FILE * fileAluno = fopen("fileAluno.bin","wb");
    minhasDisciplinas minhasdisciplinas[MAX_DISCIPLINAS];
    int escolha;
    size_t minhasdisciplinasLidas = fwrite(minhasdisciplinas,sizeof(minhasDisciplinas),MAX_DISCIPLINAS,fileAluno);

    for(size_t i = 0; i<minhasdisciplinasLidas;i++){
        printf("Código da disciplina:\n");
        scanf("^\n[]",minhasdisciplinas[i].codigo);
        printf("Titulo da disciplina:\n");
        scanf("^\n[]",minhasdisciplinas[i].titulo);
        printf("Necessita pre-requisitos?\n 1 - Sim\n2 - Não");
        scanf("%d",&escolha);
        if(escolha == 1){
            printf("Digite o numero de pre requisitos necessários");
            scanf("^\n[]",minhasdisciplinas[i].numPrerequisitos);
            size_t minhasdisciplinasLidas = fwrite(minhasdisciplinas,sizeof(minhasDisciplinas),MAX_DISCIPLINAS,fileAluno);
        }
        else{
            size_t minhasdisciplinasLidas = fwrite(minhasdisciplinas,sizeof(minhasDisciplinas),MAX_DISCIPLINAS,fileAluno);
        }
        printf("Disciplina cadastrada com sucesso!");
    }

}

void excluiDisciplina(){

}

#endif
