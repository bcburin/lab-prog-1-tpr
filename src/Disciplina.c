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



void fwrite_disciplina(FILE *fp, void* disciplina) { 
  char* codigo = ((Disciplina*)disciplina)->codigo;
  char* nome = ((Disciplina*)disciplina)->nome;
  char* professor = ((Disciplina*)disciplina)->professor;
  char* creditos = ((Disciplina*)disciplina)->creditos;

  // Determinar tamanhos das strings nao padronizadas
  int nome_size = strlen(nome)+1;
  int professor_size = strlen(professor)+1;
  //int creditos_size = strlen(creditos)+1;

  //Escrever dados no arquivo
  fwrite(&nome_size, sizeof(int), 1, fp);
  fwrite(&professor_size, sizeof(int), 1, fp);
  //fwrite(&creditos_size, sizeof(int), 1, fp);
  fwrite(nome, sizeof(char), nome_size, fp);
  fwrite(professor, sizeof(char), professor_size, fp);
  fwrite(creditos, sizeof(char), CREDITOS_D_SIZE, fp);
  fwrite(codigo, sizeof(char), CODIGO_D_SIZE, fp);
 }


void* fread_disciplina(FILE *fp) {
  Disciplina *disciplina = malloc(sizeof(Disciplina));
  
  // Ler tamanhos das strings nao padronizadas
  int nome_size = 0;
  int professor_size = 0;
  fread(&nome_size, sizeof(int), 1, fp);
  fread(&professor_size, sizeof(int), 1, fp);

  // Alocar espaco para campos a serem lidos do arquivo
  char *nome = malloc( sizeof(char) * nome_size );
  char *professor = malloc( sizeof(char) * professor_size );
  char *creditos = malloc( sizeof(char) * CREDITOS_D_SIZE );
  char *codigo = malloc ( sizeof(char) * CODIGO_D_SIZE );

  // Ler entradas do arquivo
  fread(nome, sizeof(char), nome_size, fp);
  fread(professor, sizeof(char), professor_size, fp);
  fread(creditos, sizeof(char), CREDITOS_D_SIZE, fp);
  fread(codigo, sizeof(char), CODIGO_D_SIZE, fp);

  // Colocar dados lidos na estrutura
  disciplina->nome = nome;
  disciplina->professor = professor;
  disciplina->creditos = creditos;
  disciplina->codigo = codigo;

  return (void*) disciplina;
}