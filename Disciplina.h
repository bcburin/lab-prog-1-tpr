#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <stdio.h>
#include <stdlib.h>

#define CODIGO_D_SIZE 5
#define CREDITOS_D_SIZE 2

typedef struct {
  char* codigo;
  char* nome;
  char* professor;
  char*  creditos;
} Disciplina;

/* FUNCAO DESTRUTORA */
void destruir_disciplina(void *disciplina); //ok

/* IMPRESSAO DE DISCIPLINA */

void imprimir_disciplina(void *disciplina);//ok

/* FUNCAO DE PROCURA */

/* - Recebe como parametros um ponteiro para o disciplina, alem do codigo em questao
 * - Retorna 1 se o disciplina tem o codigo fornecido, 0 caso contrario
 */
int procurar_disciplina_por_codigo(void *disciplina, void *codigo);//ok

/* - Recebe como parametros um ponteiro para o disciplina, alem de uma string (nome)
 * - Retorna 1 se o nome do disciplina contem a string fornecida, 0 caso contrario
 */
int procurar_disciplina_por_nome(void *disciplina, void *nome);//ok

/* - Recebe como parametros um ponteiro para o disciplina, alem de uma string (cpf)
 * - Retorna 1 se o disciplina tem o cpf em questao, 0 caso contrario
 */


/* MANIPULACAO DE ARQUIVOS *///ok

void fwrite_disciplina(FILE *fp, void* data);

void* fread_disciplina(FILE *fp);


#endif