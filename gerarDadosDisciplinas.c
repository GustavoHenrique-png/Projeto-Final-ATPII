#include <stdio.h>
#define MAX_PREREQUISITOS 10 // Definimos o número máximo de pre-requisitos

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
    char codigo[11];
    char titulo[100];
    int cargaHoraria;
    int semestre;
    char prerequisitos[MAX_PREREQUISITOS][10];
    int numPrerequisitos;
    TipoDisciplina tipo;
    statusDisciplina status;
} Disciplina;

void adicionaDisciplinas()
{
    int numDisciplinas;
    printf("Informe o numero de disciplinas (0 para todas): ");
    scanf("%d", &numDisciplinas);

    Disciplina disciplinas[] = {
        {"DPAAIN.389", "Introducao a Engenharia de Software", 54, 1, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.390", "Fundamentos de Algebra e Calculo", 54, 1, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.391", "Logica e Pensamento Computacional", 54, 1, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.392", "Escrita Cientifica para Computacao", 27, 1, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.393", "Ingles Instrumental", 27, 1, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.394", "Engenharia de Requisitos", 54, 1, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.395", "Algoritmos e Tecnicas de Programacao I", 54, 2, {"DPAAIN.391"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.396", "Diversidade e Inclusao", 27, 2, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.397", "Analise e Projeto de Sistemas", 54, 2, {"DPAAIN.394"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.398", "Etica, Tecnologia e Sociedade", 27, 2, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.399", "Calculo I", 54, 2, {"DPAAIN.390"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.400", "Extensao Curricular I", 54, 2, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.401", "Algoritmos e Tecnicas de Programacao II", 54, 3, {"DPAAIN.395"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.402", "Sistemas Operacionais", 54, 3, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.403", "Algebra Linear", 54, 3, {"DPAAIN.390"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.404", "Banco de Dados I", 54, 3, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.405", "Extensao Curricular II", 54, 3, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.406", "Estruturas de Dados", 81, 4, {"DPAAIN.401"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.407", "Programacao Orientada a Objetos I", 54, 4, {"DPAAIN.401"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.408", "Banco de Dados II", 54, 4, {"DPAAIN.404"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.409", "Extensao Curricular III", 54, 4, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.410", "Administracao e Gestao Estrategica", 27, 4, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.411", "Inovacao e Empreendedorismo", 54, 5, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.412", "Interface Homem-Maquina", 54, 5, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.413", "Programacao Orientada a Objetos II", 54, 5, {"DPAAIN.407"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.414", "Redes de Computadores", 54, 5, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.415", "Extensao Curricular IV", 54, 5, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.416", "Sistemas Distribuidos", 54, 6, {"DPAAIN.414"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.417", "Projeto de Pesquisa e Inovacao I", 108, 6, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.418", "Relacoes Etnico-Raciais e Cultura Afrobrasileira e Indigena", 27, 6, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.419", "Governanca, Seguranca e Auditoria de Sistemas", 54, 6, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.420", "Engenharia da Experiencia do Usuario", 54, 6, {"DPAAIN.412"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.421", "Pratica de Fabrica de Software I", 54, 6, {"DPAAIN.404", "DPAAIN.407"}, 2, Obrigatoria, NaoCursada},
        {"DPAAIN.422", "Projeto de Pesquisa e Inovacao II", 108, 7, {"DPAAIN.417"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.423", "Testes de Software", 54, 7, {"DPAAIN.413"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.424", "Introducao a Inteligencia Artificial", 54, 7, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.425", "Economia Criativa", 27, 7, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.426", "Qualidade de Software", 27, 7, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.427", "Pratica de Fabrica de Software II", 54, 7, {"DPAAIN.421"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.428", "Redes Moveis", 54, 8, {"DPAAIN.414"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.429", "Estatistica Descritiva", 27, 8, {"DPAAIN.390"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.430", "Marketing Digital", 27, 8, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.431", "Extensao Curricular V", 54, 8, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.432", "Pratica de Fabrica de Software III", 54, 8, {"DPAAIN.427"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.433", "TCC I", 54, 8, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.434", "Software para Sistemas Ubiquos", 54, 9, {"DPAAIN.414"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.435", "Arquitetura de Software", 54, 9, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.436", "Extensao Curricular VI", 54, 9, {}, 0, Obrigatoria, NaoCursada},
        {"DPAAIN.437", "TCC II", 54, 9, {"DPAAIN.433"}, 1, Obrigatoria, NaoCursada},
        {"DPAAIN.438", "Lingua Brasileira de Sinais", 27, 9, {}, 0, Optativa, NaoCursada},
        {"DPAAIN.439", "Quimica, Meio Ambiente e Sociedade", 27, 9, {}, 0, Optativa, NaoCursada},
        {"DPAAIN.440", "Gestao de Custos", 27, 9, {}, 0, Optativa, NaoCursada},
        {"DPAAIN.441", "Comportamento Organizacional", 27, 9, {}, 0, Optativa, NaoCursada},
        {"DPAAIN.442", "Probabilidade", 27, 9, {}, 0, Optativa, NaoCursada},
        {"DPAAIN.443", "Desenvolvimento de Software para Dispositivos Moveis", 27, 9, {}, 0, Optativa, NaoCursada},
        {"DPAAIN.444", "Ciencia de Dados", 27, 9, {}, 0, Optativa, NaoCursada},
        {"DPAAIN.445", "Leitura e Producao de Generos Academicos", 27, 9, {}, 0, Optativa, NaoCursada},
        {"DPAAIN.446", "Introducao a Teoria da Computacao", 27, 9, {}, 0, Optativa, NaoCursada},
        {"DPAAIN.447", "Redes Neurais e Aprendizado Profundo", 27, 9, {}, 0, Optativa, NaoCursada},
        {"DPAAIN.448", "Tecnicas de Programacao para Middleware", 27, 9, {}, 0, Optativa, NaoCursada}};

    FILE *arquivo = fopen("disciplinas.bin", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve todas as disciplinas no arquivo binário
    int numDisciplinasMostrar = numDisciplinas == 0 ? sizeof(disciplinas) / sizeof(disciplinas[0]) : numDisciplinas;
    fwrite(disciplinas, sizeof(Disciplina), numDisciplinasMostrar, arquivo);

    fclose(arquivo);
    printf("Disciplinas salvas com sucesso em disciplinas.bin\n");
}

void imprimeDisciplinas()
{
    FILE *arquivo = fopen("disciplinas.bin", "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    printf("\n---------------------------------\n");

    Disciplina disciplina;

    while (fread(&disciplina, sizeof(Disciplina), 1, arquivo))
    {
        printf("Codigo: %s\n", disciplina.codigo);
        printf("Titulo: %s\n", disciplina.titulo);
        printf("Carga Horaria: %d\n", disciplina.cargaHoraria);
        printf("Semestre: %d\n", disciplina.semestre);
        printf("Pre-requisitos: ");
        for (int i = 0; i < disciplina.numPrerequisitos; i++)
        {
            printf("%s ", disciplina.prerequisitos[i]);
        }
        printf("\nTipo: %s\n", disciplina.tipo == Obrigatoria ? "Obrigatoria" : "Optativa");
        printf("Status: %s\n", disciplina.status == Cursando ? "Cursando" : disciplina.status == Cursada ? "Cursada"
                                                                                                         : "Nao Cursada");
        printf("---------------------------------\n");
    }

    fclose(arquivo);
}

int main()
{
    adicionaDisciplinas();
    imprimeDisciplinas();
    return 0;
}