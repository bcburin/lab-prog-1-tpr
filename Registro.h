#ifndef REGISTRO_H
#define REGISTRO_H

#define PERIODO_SIZE 7

#include <stdlib.h>
#include <string.h>

#include "Aluno.h"
#include "Disciplina.h"

typedef struct Registro_ {
  char* aluno_codigo;
  char* disciplina_codigo;
  char* periodo;
} Registro;

/* FUNCAO CONSTRUTORA */

/* - Cria uma  instancia de Registro e a retorna
 * - Aloca memoria para criar copias de todos os parametros enviados
 */
Registro* criar_registro(char *aluno_codigo, char *disciplina_codigo, char *periodo);

/* FUNCAO DESTRUTORA */

void destruir_registro(void *registro);

/* FUNCOES DE PROCURA */

int procurar_registro_por_aluno(void *registro, void *aluno_codigo);

int procurar_registro_por_disciplina(void *registro, void *disciplina_codigo);


/* FUNCOES DE MANIPULACAO DE ARQUIVOS */

void fwrite_registro(FILE *fp, void* registro);

void* fread_registro(FILE *fp);

#endif