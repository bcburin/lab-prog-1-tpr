#include "Registro.h"

//função matricular no registro

int cadastrar_registro(List *registros) {
  char aluno_codigo[30];
  char disciplina_codigo[30];
  char periodo[10];

  imprimir_borda();

  int erro = 0;

  erro = _aluno_cadastrar_codigo(aluno_codigo);
  if(erro) return erro;

  erro = _disciplina_cadastrar_codigo(disciplina_codigo);
  if(erro) return erro;
  
  erro = _registro_cadastrar_periodo(periodo);
  if(erro) return erro;

  // Alocar memoria para o registro (apenas se nao houver erro)
  Registro *registro = (Registro*) malloc(sizeof(Registro)); 
  registro->aluno_codigo = (char*) malloc(sizeof(char) * CODIGO_A_SIZE);
  registro->disciplina_codigo = (char*) malloc(sizeof(char) * CODIGO_D_SIZE);
  registro->periodo = (char*) malloc(sizeof(char) * PERIODO_SIZE);

  // Setar valores de registro
  strcpy(registro->aluno_codigo, aluno_codigo);
  strcpy(registro->disciplina_codigo, disciplina_codigo);
  strcpy(registro->periodo, periodo);

  // Inserir registro na lista
  list_push(registros, registro);

  return 0;
}

/* Registro* criar_registro(char *aluno_codigo, char *disciplina_codigo, char *periodo) {
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
} */


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

int procurar_registro_por_periodo(void *registro, void *periodo) {
  char *registro_periodo = ((Registro*)registro)->periodo;

  return strcmp(registro_periodo, periodo) == 0;
}

void imprimir_atributo_registro(List *alunos, List *disciplinas,int chave_impressao, void *registro){
    Aluno *aluno;
    Disciplina *disciplina;
    switch (chave_impressao){
      case IMPRIME_DISCIPLINA:
        disciplina = list_search(alunos,procurar_disciplina_por_codigo,((Registro *)registro)->disciplina_codigo); 
        printf("%s\n", disciplina->nome); 
        break;
      case IMPRIME_ALUNO:
        aluno = list_search(alunos,procurar_aluno_por_codigo,((Registro *)registro)->aluno_codigo);
        printf("%s\n", aluno->nome); 
        break;
      default:
        break;
    }
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