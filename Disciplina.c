#include "Disciplina.h"

void destruir_disciplina(void *disciplina) {
  free( ((Disciplina*)disciplina)->nome );
  free( ((Disciplina*)disciplina)->professor );
  free( ((Disciplina*)disciplina)->codigo );
  free( ((Disciplina*)disciplina)->creditos );
  free( ((Disciplina*)disciplina) );
}

void imprimir_disciplina(void *disciplina) {
  printf("\nDISCIPLINA: %s\n", ((Disciplina*)disciplina)->nome);
  printf("CODIGO: %s\n", ((Disciplina*)disciplina)->codigo);
  printf("PROFESSOR: %s\n", ((Disciplina*)disciplina)->professor);
  printf("CREDITOS: %s\n", ((Disciplina*)disciplina)->creditos);
}

int procurar_disciplina_por_codigo(void *disciplina, void *codigo) {
  char *codigo_disciplina = ((Disciplina*)disciplina)->codigo;

  // OBS: a funcao strcmp retorna zero se e so se seus parametros forem iguais
  return strcmp(codigo_disciplina, codigo) == 0;
}


int procurar_disciplina_por_nome(void *disciplina, void *nome) {
  char *disciplina_nome = ((Disciplina*)disciplina)->nome;

  return strstr(disciplina_nome, (char*) nome) != NULL; 
}



void fwrite_disciplina(FILE *fp, void* data) { fwrite(data, sizeof(Disciplina), 1, fp); }


void* fread_disciplina(FILE *fp) {
  void *data = malloc(sizeof(Disciplina));
  fread(data, sizeof(Disciplina), 1, fp);
  return data;
}