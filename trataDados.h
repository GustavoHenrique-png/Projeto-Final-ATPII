#ifndef TRATADADADOS_H
#define TRATADADOS_H

#include <stdio.h>

#define TAMANHO_MAXIMO 100



void leArquivos(){

    FILE *file;
    file = fopen("disciplinas.bin","rb");
    int tamanho,linhas,colunas;

    //Tratando erros
    if(file == NULL){
        printf("Não foi possível abrir o arquivo\n");
        return;
    }else{

        fread(&linhas,sizeof(int),1,file);
        fread(&colunas,sizeof(int),1,file);
        int dados[TAMANHO_MAXIMO] [TAMANHO_MAXIMO];

        //Lendo os dados do arquivo
        fread(dados,sizeof(int),linhas*colunas,file);

        //Fechando o arquivo
        fclose(file);

        //Exibindo os dados
        for (int i = 0; i < linhas; i++)
        {
            for(int j = 0; j<colunas; j++){
                printf("%d",dados[i][j]);
            }
        }
    }
}

#endif