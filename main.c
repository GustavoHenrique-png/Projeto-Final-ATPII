#include <stdio.h>
#include <stdlib.h>
#include "agenda.h"
#include "trataDados.h"

// Declaração da função que chama o menu principal
void ChamaMenuPrincipal();

int main()
{
    // Chamada da função
    ChamaMenuPrincipal();
    return 0;
}

// Função que cria e exibe o menu
void ChamaMenuPrincipal()
{
    int acao;// Variavel para navegação do menu

    do
    {
        // Limpa a tela
        system("cls");

        // Gera menu
        printf("\n---------------------------------\nAcademico: %s\n---------------------------------\n", "Aluno");
        printf("1 - Acessar grade curricular\n2 - Acessar agenda do aluno\n0 - Sair\n---------------------------------\n");
        printf("Informe a acao desejada: ");
        scanf("%d", &acao);

        // Limpa a tela
        system("cls");

        // Executa acao
        switch (acao)
        {
        case 1:
            acessaGrade(); // Chama a função da grade curricular
            break;
        case 2:
            AcessaAgenda(); // Chama a função da agenda do aluno
            break;
        default:
            break;
        }

    } while (acao != 0); //Condição de parada do loop
}
