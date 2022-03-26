#include "Registro.h"

Registro* criar_registro(char *aluno_codigo, char *disciplina_codigo, char *periodo) {
  Registro *registro = malloc(sizeof(Registro));

  char *new_aluno_codigo = malloc(CODIGO_A_SIZE);
  char *new_disciplina_codigo = malloc(CODIGO_D_SIZE);
  char *new_periodo = malloc(PERIODO_SIZE);

  strcpy(new_aluno_codigo, aluno_codigo);
  strcpy(new_disciplina_codigo, disciplina_codigo);
  strcpy(new_periodo, periodo);

  registro->aluno_codigo = new_aluno_codigo;
  registro->disciplina_codigo = new_disciplina_codigo;
  registro->periodo = new_periodo;

  return registro;
}


void destruir_registro(void *registro) {
  free( ((Registro*)registro)->aluno_codigo );
  free( ((Registro*)registro)->disciplina_codigo );
  free( ((Registro*)registro)->periodo );
  free( ((Registro*)registro) );
}


int procurar_registro_por_aluno(void *registro, void *aluno_codigo) {
  char *registro_aluno_codigo = ((Registro*)registro)->aluno_codigo;

  return strcmp(registro_aluno_codigo, aluno_codigo) == 0;
}


int procurar_registro_por_disciplina(void *registro, void *disciplina_codigo) {
  char *registro_disciplina_codigo = ((Registro*)registro)->disciplina_codigo;

  return strcmp(registro_disciplina_codigo, disciplina_codigo) == 0;
}


void fwrite_registro(FILE *fp, void* registro) {
  char *aluno_codigo = ((Registro*)registro)->aluno_codigo;
  char *disciplina_codigo = ((Registro*)registro)->disciplina_codigo;
  char *periodo = ((Registro*)registro)->periodo;

  fwrite(aluno_codigo, sizeof(char), CODIGO_A_SIZE, fp);
  fwrite(disciplina_codigo, sizeof(char), CODIGO_D_SIZE, fp);
  fwrite(periodo, sizeof(char), PERIODO_SIZE, fp);
}


void* fread_registro(FILE *fp) {
  Registro *registro = malloc(sizeof(Registro));

  char *aluno_codigo = malloc(sizeof(char) * CODIGO_A_SIZE);
  char *disciplina_codigo = malloc(sizeof(char) * CODIGO_D_SIZE);
  char *periodo = malloc(sizeof(char) * PERIODO_SIZE);

  fread(aluno_codigo, sizeof(char), CODIGO_A_SIZE, fp);
  fread(disciplina_codigo, sizeof(char), CODIGO_D_SIZE, fp);
  fread(periodo, sizeof(char), PERIODO_SIZE, fp);

  registro->aluno_codigo = aluno_codigo;
  registro->disciplina_codigo = disciplina_codigo;
  registro->periodo = periodo;

  return (void*) registro;
}