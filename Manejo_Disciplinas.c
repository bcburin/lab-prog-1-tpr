#include "Manejo_Disciplinas.h"
#include "Disciplina.h"
#include "Auxiliar.h"

int _disciplina_determinar_metodo_de_busca() {
  imprimir_borda();
  printf("%d - Por nome\n", POR_NOME_D);
  printf("%d - Por codigo\n", POR_CODIGO_D);

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
  if (strlen(codigo) != CODIGO_D_SIZE-1) return CODIGO_D_INVALIDO;
  if(!is_digit(codigo)) return CODIGO_D_INVALIDO;
  return 0;
}

int _disciplina_validar_creditos(const char *creditos){
  // if (strlen(creditos) != CREDITOS_D_SIZE) return CREDITOS_INVALIDO;
  if(!is_digit(creditos)) return CREDITOS_INVALIDO;
  return 0;
}

int _disciplina_cadastrar_nome(char *nome) {

  printf("\nInsira o nome da disciplina: ");

  fflush(stdin);
  scanf("%[^\n]", nome);

  // TODO: validar nome

  return 0;
}


int _disciplina_cadastrar_codigo(char *codigo) {

  printf("\nInsira o codigo da disciplina: ");

  fflush(stdin);
  scanf("%s", codigo);

  int erro = _disciplina_validar_codigo(codigo);
  if (erro) return CODIGO_D_INVALIDO;

  return 0;
}

int _disciplina_cadastrar_professor(char *professor) {

  printf("\nInsira o nome do professor da disciplina: ");

  fflush(stdin);
  scanf("%[^\n]", professor);

  // TODO: validar nome

  return 0;
}

int _disciplina_cadastrar_creditos(char *creditos){

    printf("\nInsira os creditos da disciplina: ");

    fflush(stdin);
    scanf("%s", creditos);

    int erro = _disciplina_validar_creditos(creditos);
    if (erro) return CREDITOS_INVALIDO;

    return 0;
}

int cadastrar_disciplina(List *disciplinas) {
  char nome[30];
  char codigo[10];
  char professor[50];
  char creditos[10];

  imprimir_borda();
  
  int erro = 0;

  erro = _disciplina_cadastrar_nome(nome);
  if(erro){
    //printf("\nErro: %d\n", erro);
    return erro;
  }

  erro = _disciplina_cadastrar_codigo(codigo);
  
  if(erro){
    //printf("\nErro: %d\n", erro);
    return erro;
  }

  erro = _disciplina_cadastrar_professor(professor);
  if(erro){
    //printf("\nErro: %d\n", erro);
    return erro;
  }

  erro = _disciplina_cadastrar_creditos(creditos);
  if(erro){
    //printf("\nErro: %d\n", erro);
    return erro;
  }

  // Alocar memoria para a disciplina (apenas se nao houver erro)
  Disciplina *disciplina = (Disciplina*) malloc(sizeof(Disciplina)); 
  disciplina->nome = (char*) malloc( sizeof(char) * (strlen(nome) + 1) );
  disciplina->codigo = (char*) malloc( sizeof(char) * CODIGO_D_SIZE );
  disciplina->professor = (char*) malloc( sizeof(char) * (strlen(professor) + 1) );
  disciplina->creditos = (char*) malloc( sizeof(char) * (strlen(creditos) + 1) );

  // Setar dados da disciplina
  strcpy(disciplina->nome, nome);
  strcpy(disciplina->codigo, codigo);
  strcpy(disciplina->professor, professor);
  strcpy(disciplina->creditos, creditos);

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
    case POR_NOME_D:
      printf("\nInsira o nome ou parte do nome da disciplina: ");
      scanf("%[^\n]", &key);
      if ( list_remove_first(disciplinas, procurar_disciplina_por_nome, key) )
        return DISCIPLINA_NAO_ENCONTRADA;
      break;

    case POR_CODIGO_D:
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
    case POR_NOME_D:
      printf("\nInsira o nome ou parte do nome: ");
      scanf("%[^\n]", &key);
      disciplina = list_search(disciplinas, procurar_disciplina_por_nome, key);
      break;
    case POR_CODIGO_D:
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
