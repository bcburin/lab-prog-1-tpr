#ifndef REGISTRO_H
#define REGISTRO_H

#define PERIODO_SIZE 6

#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Aluno.h"
#include "Disciplina.h"
#include "Manejo_Disciplinas.h"
#include "Manejo_Alunos.h"


typedef struct Registro_ {
  char* aluno_codigo;
  char* disciplina_codigo;
  char* periodo;
} Registro;

typedef enum {
    IMPRIME_ALUNO=-1,
    IMPRIME_DISCIPLINA=-2
} CHAVE_IMPRESSAO;

/* FUNCAO CONSTRUTORA */

/* - Cria uma  instancia de Registro e a retorna
 * - Aloca memoria para criar copias de todos os parametros enviados
 */
//Registro* criar_registro(char *aluno_codigo, char *disciplina_codigo, char *periodo);
int cadastrar_registro(List *registros);

/* FUNCAO DESTRUTORA */

void destruir_registro(void *registro);

/* FUNCOES DE PROCURA */

int procurar_registro_por_aluno(void *registro, void *aluno_codigo);

int procurar_registro_por_disciplina(void *registro, void *disciplina_codigo);

int procurar_registro_por_registro(void *registro, void *registro_chave);

int procurar_registro_por_periodo(void *registro, void *periodo);

/*FUNÇÕES DE IMPRESSÃO*/

//acessa listas, busca por código e imprime nome do atributo
void imprimir_atributo_registro(List *alunos, List *disciplinas,int chave_impressao, void *registro);

void imprimir_registro(void *registro);

/* FUNCOES DE MANIPULACAO DE ARQUIVOS */

void fwrite_registro(FILE *fp, void* registro);

void* fread_registro(FILE *fp);

#endif