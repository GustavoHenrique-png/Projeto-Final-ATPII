#ifndef TRATADADADOS_H
#define TRATADADOS_H

void leArquivos(){

    FILE *file;
    file = fopen("disciplinas.bin","rb");

    //Tratando erros
    if(file == NULL){
        printf("Não foi possível abrir o arquivo\n");
    }else{
        
    }

}

#endif