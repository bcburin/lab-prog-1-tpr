#include "Manejo_Disciplinas.h"
#include "Disciplina.h"
#include "Auxiliar.h"

int _disciplina_determinar_metodo_de_busca() {
  imprimir_borda();
  printf("%d - Por nome\n", POR_NOME);
  printf("%d - Por codigo\n", POR_CODIGO);

  imprimir_borda();

  printf("\nOpcao desejada: ");

  int metodo = 0;
  fflush(stdin);
  scanf("%d", &metodo);

  // Validar metodo
  if (metodo >= 1 && metodo <= 2)
    return metodo;

  return 0;
}


int _disciplina_validar_codigo(const char *codigo) {
  if (strlen(codigo) != CODIGO_D_SIZE-1) return CODIGO_INVALIDO;
  if(!is_digit(codigo)) return CODIGO_INVALIDO;
  return 0;
}

int _disciplina_validar_creditos(const char *creditos){
  if (strlen(creditos) != CREDITOS_D_SIZE-1) return CREDITOS_INVALIDO;
  if(!is_digit(creditos)) return CREDITOS_INVALIDO;
  return 0;
}

char* _disciplina_cadastrar_nome() {
  char buffer[50];

  printf("\nInsira o nome da disciplina: ");

  fflush(stdin);
  scanf("%[^\n]", buffer);

  // TODO: validar nome

  char *nome = (char*) malloc( (strlen(buffer) + 1) * sizeof(char));

  strcpy(nome, buffer);

  return nome;
}


char* _disciplina_cadastrar_codigo() {
  char buffer[20];

  printf("\nInsira o codigo da disciplina: ");

  fflush(stdin);
  scanf("%s", buffer);

  int erro = _disciplina_validar_codigo(buffer);
  if (erro) return NULL;

  char *codigo = (char*) malloc( CODIGO_D_SIZE * sizeof(char));

  strcpy(codigo, buffer);

  return codigo;
}

char* _disciplina_cadastrar_professor() {
  char buffer[50];

  printf("\nInsira o nome do professor da disciplina: ");

  fflush(stdin);
  scanf("%[^\n]", buffer);

  // TODO: validar nome

  char *professor = (char*) malloc( (strlen(buffer) + 1) * sizeof(char));

  strcpy(professor, buffer);

  return professor;
}

char* _disciplina_cadastrar_creditos(){
    char buffer[10];

    printf("\nInsira os creditos da disciplina: ");

    fflush(stdin);
    scanf("%s", buffer);

    int erro = _disciplina_validar_creditos(buffer);
    if (erro) return NULL;

    char *creditos = (char*) malloc( CREDITOS_D_SIZE * sizeof(char));

    strcpy(creditos, buffer);

    return creditos;
}

int cadastrar_disciplina(List *disciplinas) {
  char *nome = NULL;
  char *codigo = NULL;
  char *professor = NULL;
  char *creditos = NULL;

  imprimir_borda();

  nome = _disciplina_cadastrar_nome();
  // if(!nome) return NOME_INVALIDO;

  codigo = _disciplina_cadastrar_codigo();
  if(!codigo) return CODIGO_INVALIDO;

  professor = _disciplina_cadastrar_professor();
  // if(!professor) return NOME_INVALIDO

  creditos = _disciplina_cadastrar_creditos();
  if(!creditos) return CREDITOS_INVALIDO;
  
  Disciplina *disciplina = (Disciplina*) malloc(sizeof(Disciplina)); 
  disciplina->nome = nome;
  disciplina->codigo = codigo;
  disciplina->professor = professor;
  disciplina->creditos = creditos;

  list_push(disciplinas, disciplina);

  imprimir_borda();

  return 0;
}


int remover_disciplina(List *disciplinas) {
  int metodo = _disciplina_determinar_metodo_de_busca();
  if(metodo < 0) return metodo; // Retorna erro

  imprimir_borda();
  fflush(stdin);

  char key[50];
  int erro = 0;

  switch (metodo) {
    case POR_NOME:
      printf("\nInsira o nome ou parte do nome da disciplina: ");
      scanf("%[^\n]", &key);
      if ( list_remove_first(disciplinas, procurar_disciplina_por_nome, key) )
        return DISCIPLINA_NAO_ENCONTRADA;
      break;

    case POR_CODIGO:
      printf("\nInsira o codigo: ");
      scanf("%[^\n]", &key);
      erro = _disciplina_validar_codigo(key);
      if (erro) 
        return erro;
      if ( list_remove_first(disciplinas, procurar_disciplina_por_codigo, key) )
        return DISCIPLINA_NAO_ENCONTRADA;
      break;

    default:
      break;
  }

  return 0;
}


int consultar_disciplina(List *disciplinas) {
  int metodo = _disciplina_determinar_metodo_de_busca();
  if(metodo < 0) return metodo; // Retornar erro

  imprimir_borda();
  fflush(stdin);

  Disciplina *disciplina;
  char key[50];
  int erro = 0;

  switch (metodo) {
    case POR_NOME:
      printf("\nInsira o nome ou parte do nome: ");
      scanf("%[^\n]", &key);
      disciplina = list_search(disciplinas, procurar_disciplina_por_nome, key);
      break;
    case POR_CODIGO:
      printf("\nInsira o codigo: ");
      scanf("%[^\n]", &key);
      erro = _disciplina_validar_codigo(key);
      if(erro) return erro;
      disciplina = list_search(disciplinas,procurar_disciplina_por_codigo,key);
      break;
    default:
      break;
  }

  if(!disciplina) return DISCIPLINA_NAO_ENCONTRADA;

  imprimir_borda();
  imprimir_disciplina(disciplina);

  return 0;
}
