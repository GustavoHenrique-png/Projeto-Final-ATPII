#include <stdio.h>
#include <stdlib.h>
#include "agenda.h"
#include "trataDados.h"

void ChamaMenuPrincipal();

int main()
{
    ChamaMenuPrincipal();
    return 0;
}

void ChamaMenuPrincipal()
{
    int acao;

    do
    {
        // Limpa a tela
        system("cls");

        // Gera menu
        printf("\n---------------------------------\nAcademico: %s\n---------------------------------\n", "Aluno");
        printf("1 - Cadastrar Disciplina\n2 - Grade\n3 - Historico Escolar\n4 - Agenda\n5 - Atividades Pendentes\n0 - Sair\n---------------------------------\n");
        printf("Informe a acao desejada: ");
        scanf("%d", &acao);

        // Limpa a tela
        system("cls");

        // Executa acao
        switch (acao)
        {
        case 1:
            printf("Cadastrar Disciplina\n");
            break;
        case 2:
            acessaGrade();
            break;
        case 3:
            printf("Historico Escolar\n");
            break;
        case 4:
            AcessaAgenda();
            break;
        case 5:
            ListaCompromissosPendentes();
            break;
        default:
            break;
        }

    } while (acao != 0);
}
