
#include "Manejo_Registros.h"

int consultar_disciplinas_de_aluno(List *registros,List *alunos, List *disciplinas ){
    List *resultados_busca_1;// = (Registro*) malloc(sizeof(Registro)); 
    List *resultados_busca_2;

    imprimir_borda();
    fflush(stdin);

    char key_al[50];
    char key_per[30];

    printf("\nInsira o código do aluno: ");
    scanf("%[^\n]", &key_al);
    fflush(stdin);
    printf("\nInsira o periodo sem traços ou pontos (20181 20202): ");
    scanf("%[^\n]", &key_per);
    imprimir_borda();
    fflush(stdin);

    int erro = 0;
    erro = _aluno_validar_codigo(key_al);
    if(erro) return erro;
    erro =_registro_validar_periodo(key_per);
    if(erro) return erro;

    resultados_busca_1 = list_search_all(registros,procurar_registro_por_aluno,key_al);
    resultados_busca_2 = list_search_all(resultados_busca_1, procurar_registro_por_periodo, key_per);

    //como usar list_apply?
    //list_apply(resultados_busca_2, imprimir_atributo_registro(alunos,disciplinas, IMPRIME_ALUNO));
    //if(!registro) return CODIGO_INVALIDO;

    list_destroy(resultados_busca_1);
    list_destroy(resultados_busca_2);
    imprimir_borda;
  return 0;
}

/* consulta alunos de uma disciplina em um período */
int consultar_alunos_de_disciplina(List *registros, List *alunos, List *disciplinas){
    List *resultados_busca_1;// = (Registro*) malloc(sizeof(Registro)); 
    List *resultados_busca_2;

    imprimir_borda();
    fflush(stdin);

    char key_dis[50];
    char key_per[30];
    

    printf("\nInsira o código da disciplina: ");
    scanf("%[^\n]", &key_dis);
    fflush(stdin);
    printf("\nInsira o periodo sem traços ou pontos (20181 20202): ");
    scanf("%[^\n]", &key_per);
    imprimir_borda();
    fflush(stdin);

    int erro = 0;
    erro = _disciplina_validar_codigo(key_dis);
    if(erro) return erro;
    erro =_registro_validar_periodo(key_per);
    if(erro) return erro;

    resultados_busca_1 = list_search_all(registros,procurar_registro_por_aluno,key_dis);
    resultados_busca_2 = list_search_all(resultados_busca_1, procurar_registro_por_periodo, key_per);

    //como usar list_apply?
    //list_apply(resultados_busca_2, imprimir_atributo_registro(alunos,disciplinas, IMPRIME_DISCIPLINA));
    //if(!registro) return CODIGO_INVALIDO;

    list_destroy(resultados_busca_1);
    list_destroy(resultados_busca_2);
    imprimir_borda;
  return 0;
}

int _registro_validar_periodo(const char *periodo){
    if ((strlen(periodo) != PERIODO_SIZE-1) || (is_digit(periodo))) return PERIODO_INVALIDO;
    return 0;
}

int _registro_cadastrar_periodo(char* periodo) {

  printf("\nInsira o periodo do registro sem pontos (20181/20202): ");

  fflush(stdin);
  scanf("%s", periodo);

  int erro = _registro_validar_periodo(periodo);
  if (erro) return PERIODO_INVALIDO;

  return 0;
}