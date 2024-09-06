

#include <stdio.h>

int main()
{
    int acao = 0;
    printf("\n---------------------------------\nAcademico: %s\n---------------------------------\n", "Aluno");
    printf("1 - Cadastrar Disciplina\n2 - Grade\n3 - Historico Escolar\n4 - Agenda\n5 - Atividades Pendentes\n---------------------------------\n");
    printf("Informe a acao desejada: ");
    scanf("%d", &acao);

    switch (acao)
    {
    case 1:
        printf("Cadastrar Disciplina\n");
        break;
    case 2:
        printf("Grade\n");
        break;
    case 3:
        printf("Historico Escolar\n");
        break;
    case 4:
        printf("Agenda\n");
        break;
    case 5:
        printf("Atividades Pendentes\n");
        break;
    }

    return 0;
}
