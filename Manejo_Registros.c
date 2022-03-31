
#include "Manejo_Registros.h"

int _registro_determinar_metodo_de_busca() {
  imprimir_borda();
  printf("%d - Por aluno\n", POR_ALUNO_R);
  printf("%d - Por disciplina\n", POR_DISCIPLINA_R);
  imprimir_borda();

  printf("\nOpcao desejada: ");

  int metodo = 0;
  fflush(stdin);
  scanf("%d", &metodo);

  // Validar metodo

  return metodo;
}


int consultar_registro(List *registros, List *alunos, List *disciplinas){
  int metodo = _registro_determinar_metodo_de_busca();
  if(metodo < 0) return metodo; // Retornar erro

  imprimir_borda();
  fflush(stdin);

  List *resultados_busca_1;
  List *resultados_busca_2;
  Registro *registro;
  char key_aluno[50];
  char key_disciplina[50];
  char key_periodo[30];
  int erro = 0;

  printf("\nInsira o periodo sem tracos ou pontos (20181 20202): ");
  scanf("%[^\n]", &key_periodo);
  fflush(stdin);

  erro =_registro_validar_periodo(key_periodo);
  if(erro) return erro;

  resultados_busca_1 = list_search_all(registros, procurar_registro_por_periodo, key_periodo);
  
  switch (metodo) {
    case POR_ALUNO_R:
      printf("\nInsira o codigo do aluno: ");
      scanf("%[^\n]", &key_aluno);
      fflush(stdin);
      imprimir_borda();
      erro = _aluno_validar_codigo(key_aluno);
      if(erro == CODIGO_A_INVALIDO) return CODIGO_ALUNO_INVALIDO_R;
      resultados_busca_2 = list_search_all(resultados_busca_1,procurar_registro_por_aluno,key_aluno);      
      break;
    case POR_DISCIPLINA_R:
      printf("\nInsira o codigo da disciplina: ");
      scanf("%[^\n]", &key_disciplina);
      fflush(stdin);
      imprimir_borda();
      erro = _disciplina_validar_codigo(key_disciplina);
      if(erro == CODIGO_D_INVALIDO) return CODIGO_DISCIPLINA_INVALIDO_R;
      resultados_busca_2 = list_search_all(resultados_busca_1,procurar_registro_por_disciplina,key_disciplina);
      break;
  }

  //printf("RESULTADOS");
  for (Node *cur = resultados_busca_2->head; cur; cur = cur->next) {
        imprimir_atributo_registro(alunos, disciplinas, metodo, cur->data);
  }

  if(!registro) return REGISTRO_NAO_ENCONTRADO;

  list_destroy(resultados_busca_1);
  list_destroy(resultados_busca_2);
  imprimir_borda;
  
  return 0;
}

int _registro_validar_periodo(const char *periodo){
    if ((strlen(periodo) != PERIODO_SIZE-1) || (is_digit(periodo))) return PERIODO_INVALIDO_R;
    return 0;
}

int _registro_cadastrar_periodo(char* periodo) {

  printf("\nInsira o periodo do registro sem pontos (20181/20202): ");

  fflush(stdin);
  scanf("%s", periodo);

  int erro = _registro_validar_periodo(periodo);
  if (erro) return PERIODO_INVALIDO_R;

  return 0;
}