#ifndef agenda_h
#define agenda_h
#include <stdio.h>

void AcessaAgenda()
{
    int acao = 0;

    printf("\n---------------------------------\nAgenda\n---------------------------------\n");
    printf("1 - Adicionar Compromisso\n2 - Listar Compromissos\n3 - Excluir Compromisso\n4 - Voltar\n---------------------------------\n");
    printf("Informe a acao desejada: ");
    scanf("%d", &acao);

    switch (acao)
    {
    case 1:
        printf("Adicionar Compromisso\n");
        break;
    case 2:
        printf("Listar Compromissos\n");
        break;
    case 3:
        printf("Excluir Compromisso\n");
        break;
    default:
        break;
    }
}

#endif
