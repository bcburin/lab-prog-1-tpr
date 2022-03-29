#ifndef LISTA_DISC_H
#define LISTA_DISC_H

#include <string.h>
#include "List.h"
#include "Aluno.h"
#include "Style.h"

typedef enum {
  CODIGO_D_INVALIDO = -1,
  METODO_D_INVALIDO = -2,
  DISCIPLINA_NAO_ENCONTRADA = -3,
  CREDITOS_INVALIDO = -4,
} ERRO_REGISTRO_DISCIPLINA;

typedef enum {
  POR_NOME_D = 1,
  POR_CODIGO_D,
} METODO_DE_BUSCA_D;

/* FUNCOES PRIVADAS */

int _disciplina_determinar_metodo_de_busca(); //ok

int _disciplina_validar_codigo(const char *codigo);//ok

int _disciplina_validar_creditos(const char *creditos);//ok

int _disciplina_cadastrar_nome(char*);//ok

int _disciplina_cadastrar_codigo(char*);//ok

int _disciplina_cadastrar_professor(char*);//ok

int _disciplina_cadastrar_creditos(char*);//ok

/* CADASTRAR disciplina */

int cadastrar_disciplina(List *disciplinas);//ok

/* REMOVER disciplina */

/* Remove o disciplina por meio de uma busca com o codigo fornecido pelo usuario
 */
int remover_disciplina(List *disciplinas);//ok


/* Consultar disciplina */

int consultar_disciplina(List *disciplinas);

#endif