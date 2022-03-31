
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


int cadastrar_registro(List *registros, List *alunos, List *disciplinas) {
  char aluno_codigo[30];
  char disciplina_codigo[30];
  char periodo[30];

  imprimir_borda();

  printf("Insira o codigo do aluno a ser matriculado e o da disciplina de cadastro\n");

  pressione_para_continuar();

  imprimir_borda();

  int erro = 0;

  // Validar aluno
  erro = _aluno_cadastrar_codigo(aluno_codigo);
  if(erro) return erro;
  if(!list_search(alunos, procurar_aluno_por_codigo, aluno_codigo)) return ALUNO_NAO_ENCONTRADO;

  // Validar disciplina
  erro = _disciplina_cadastrar_codigo(disciplina_codigo);
  if(erro) return erro;
  if(!list_search(disciplinas, procurar_disciplina_por_codigo, disciplina_codigo)) return DISCIPLINA_NAO_ENCONTRADA;

  // Validar periodo
  erro = _registro_cadastrar_periodo(periodo);
  if (erro) return erro;

  Registro *novo_registro = criar_registro(aluno_codigo, disciplina_codigo, periodo);

  list_push(registros, novo_registro);

  return 0;
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

  erro =_registro_cadastrar_periodo(key_periodo);

  if(erro) return erro;

  //printf("cadastrei o periodo\n");
  resultados_busca_1 = list_search_all(registros, procurar_registro_por_periodo, key_periodo);
  
  imprimir_borda();

  switch (metodo) {
    case POR_ALUNO_R:
      erro = _aluno_cadastrar_codigo(key_aluno);
      if(erro) return erro;
      resultados_busca_2 = list_search_all(resultados_busca_1,procurar_registro_por_aluno,key_aluno);  
      metodo = IMPRIME_DISCIPLINA;  
      break;

    case POR_DISCIPLINA_R:
      erro = _disciplina_cadastrar_codigo(key_disciplina);
      if(erro) return erro;
      resultados_busca_2 = list_search_all(resultados_busca_1,procurar_registro_por_disciplina,key_disciplina);
      metodo = IMPRIME_ALUNO;

      break;
  }

  imprimir_borda();
  //printf("%d\n", resultados_busca_2->size);
  if(!(resultados_busca_2->size)) return REGISTRO_NAO_ENCONTRADO;
  printf("--------------------- RESULTADOS --------------------");
  imprimir_borda();
  for(Node *cur = resultados_busca_2->head; cur ; cur=cur->next) {
        imprimir_atributo_registro(alunos, disciplinas, metodo, cur->data);
  }
  
  pressione_para_continuar();

  list_destroy(resultados_busca_1);
  list_destroy(resultados_busca_2);


  imprimir_borda();
  
  return 0;
}


int remover_registro(List *registros) {
  char aluno_codigo[30];
  char disciplina_codigo[30];
  char periodo[10];

  imprimir_borda();

  printf("INSIRA DADOS DA MATRICULA A SER REMOVIDA\n");

  pressione_para_continuar();

  imprimir_borda();

  int erro = 0;

  erro = _aluno_cadastrar_codigo(aluno_codigo);
  if(erro) return erro;

  erro = _disciplina_cadastrar_codigo(disciplina_codigo);
  if(erro) return erro;

  erro = _registro_cadastrar_periodo(periodo);
  if(erro) return erro;

  Registro registro_chave = (Registro) {aluno_codigo, disciplina_codigo, periodo};

  Registro *removido = list_retrieve_first(registros, procurar_registro_por_registro, &registro_chave);

  if (removido) {
    imprimir_borda();
    printf("Matricula ambaixo removida com sucesso: \n");
    imprimir_registro(removido);
  }

  destruir_registro(removido);
}


int remover_registros_por_aluno(List *registros) {
  char aluno_codigo[30];

  imprimir_borda();

  int erro = 0;

  erro = _aluno_cadastrar_codigo(aluno_codigo);
  if(erro) return erro;

  List *removidos = list_retrieve_all(registros, procurar_registro_por_aluno, aluno_codigo);

  imprimir_borda();
  if( removidos->size != 0 ) {
    printf("Matriculas removidas com sucesso: \n");
    list_apply(removidos, imprimir_registro);
  } else {
    printf("Nao ha registros para esse aluno!\n");
  }

  list_destroy(removidos);

  return 0;
}


int remover_registros_por_disciplina(List *registros) {
  char disciplina_codigo[30];

  imprimir_borda();

  int erro = 0;

  erro = _disciplina_cadastrar_codigo(disciplina_codigo);
  if(erro) return erro;

  List *removidos = list_retrieve_all(registros, procurar_registro_por_disciplina, disciplina_codigo);

  imprimir_borda();
  if( removidos->size != 0 ) {
    printf("Matriculas removidas com sucesso: \n");
    list_apply(removidos, imprimir_registro);
  } else {
    printf("Nao ha registros para essa disciplina!\n");
  }

  list_destroy(removidos);

  return 0;
}


int _registro_validar_periodo(const char *periodo){
    if ((strlen(periodo) != PERIODO_SIZE-1) || !(is_digit(periodo))) return PERIODO_INVALIDO;
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