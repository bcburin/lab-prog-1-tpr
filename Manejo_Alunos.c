#include "Manejo_Alunos.h"
#include "Auxiliar.h"

int _aluno_determinar_metodo_de_busca() {
  imprimir_borda();
  printf("\n%d - Por nome\n", POR_NOME_A);
  printf("%d - Por codigo\n", POR_CODIGO_A);
  printf("%d - Por CPF\n", POR_CPF);
  imprimir_borda();

  printf("\nOpcao desejada: ");

  int metodo = 0;
  fflush(stdin);
  scanf("%d", &metodo);

  // Validar metodo

  return metodo;
}

int _aluno_validar_codigo(const char *codigo) {
  if ((strlen(codigo) != CODIGO_A_SIZE-1) || (!is_digit(codigo))) return CODIGO_A_INVALIDO;
  return 0;
}

int _aluno_validar_cpf(const char *cpf) {
  if ((strlen(cpf) != CPF_SIZE-1)||(!is_digit(cpf))) return CPF_INVALIDO;
  return 0;
}

int _aluno_cadastrar_nome(char *nome, int cadastro) {
  if (cadastro) printf("\nInsira o nome do aluno: ");
  else printf("Insira o nome ou parte do nome do aluno: ");

  fflush(stdin);
  scanf("%[^\n]", nome);

  // TODO: validar nome

  return 0;
}


int _aluno_cadastrar_codigo(char *codigo) {

  printf("\nInsira o codigo do aluno: ");

  fflush(stdin);
  scanf("%s", codigo);

  int erro = _aluno_validar_codigo(codigo);
  if (erro) return CODIGO_A_INVALIDO;


  return 0;
}


int _aluno_cadastrar_cpf(char *cpf) {

  printf("\nInsira o CPF do aluno (sem pontos e tracos): ");

  fflush(stdin);
  scanf("%s", cpf);

  int erro = _aluno_validar_cpf(cpf);
  if(erro) return CPF_INVALIDO;

  return 0;
}


int cadastrar_aluno(List *alunos) {

  // Declarar variaveis de buffer
  char nome[30];
  char codigo[10];
  char cpf[20];

  imprimir_borda();

  int erro = 0;

  erro = _aluno_cadastrar_nome(nome, 1);
  if(erro) return erro;
  
  erro = _aluno_cadastrar_codigo(codigo);
  if(erro) return erro;
  
  erro = _aluno_cadastrar_cpf(cpf);
  if(erro) return erro;

  // Alocar memoria para aluno (apenas se nao houver erros)
  Aluno *aluno = (Aluno*) malloc(sizeof(Aluno)); 
  aluno->nome = malloc( sizeof(char) * (strlen(nome) + 1) );
  aluno->codigo = malloc( sizeof(char) * CODIGO_A_SIZE );
  aluno->cpf = malloc( sizeof(char) * CPF_SIZE );

  // Setar dados do aluno
  strcpy(aluno->nome, nome);
  strcpy(aluno->codigo, codigo);
  strcpy(aluno->cpf, cpf);
  
  // Adicionar aluno ao fim da lista
  list_push(alunos, aluno);

  return 0;
}


int remover_aluno(List *alunos) {
  int metodo = _aluno_determinar_metodo_de_busca();
  if(metodo < 0) return metodo; // Retorna erro

  imprimir_borda();
  fflush(stdin);

  char key[50];
  int erro = 0;
  Aluno *removido = NULL;

  switch (metodo) {
    case POR_NOME_A:
      erro = _aluno_cadastrar_nome(key, 0);
      if(erro) return erro;
      removido = list_retrieve_first(alunos, procurar_aluno_por_nome, key);
      if (!removido) return ALUNO_NAO_ENCONTRADO;
      break;

    case POR_CODIGO_A:
      erro = _aluno_cadastrar_codigo(key);
      if (erro) return erro;
      removido = list_retrieve_first(alunos, procurar_aluno_por_codigo, key);
      if (!removido) return ALUNO_NAO_ENCONTRADO;
      break;

    case POR_CPF:
      erro = _aluno_cadastrar_cpf(key);
      if (erro) return erro;
      removido = list_retrieve_first(alunos, procurar_aluno_por_cpf, key);
      if (!removido) return ALUNO_NAO_ENCONTRADO;
      break;
  }

  // Mostrar aluno removido
  imprimir_borda();
  printf("\nAluno abaixo removido com sucesso: \n");
  imprimir_aluno(removido);
  destruir_aluno(removido);
  pressione_para_continuar();

  return 0;
}


int consultar_aluno(List *alunos) {
  int metodo = _aluno_determinar_metodo_de_busca();
  if(metodo < 0) return metodo; // Retornar erro

  imprimir_borda();
  fflush(stdin);

  Aluno *aluno;
  char key[50];
  int erro = 0;

  switch (metodo) {
    case POR_NOME_A:
      erro = _aluno_cadastrar_nome(key, 0);
      if(erro) return erro;
      aluno = list_search(alunos, procurar_aluno_por_nome, key);
      break;
    case POR_CODIGO_A:
      erro = _aluno_cadastrar_codigo(key);
      if(erro) return erro;
      aluno = list_search(alunos,procurar_aluno_por_codigo,key);
      break;
    case POR_CPF:
      erro = _aluno_cadastrar_cpf(key);
      if(erro) return erro;
      aluno = list_search(alunos,procurar_aluno_por_cpf,key);
      break;
  }

  if(!aluno) return ALUNO_NAO_ENCONTRADO;

  imprimir_borda();
  imprimir_aluno(aluno);

  return 0;
}
