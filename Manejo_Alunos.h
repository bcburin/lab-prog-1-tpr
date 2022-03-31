#ifndef MANEJO_ALUNOS_H
#define MANEJO_ALUNOS_H

#include <string.h>
#include "List.h"
#include "Aluno.h"
#include "Style.h"

typedef enum {
  CODIGO_A_INVALIDO = 11,
  CPF_INVALIDO = 12,
  METODO_INVALIDO = 13,
  ALUNO_NAO_ENCONTRADO = 14
} ERRO_REGISTRO_ALUNO;

typedef enum metodo_de_busca_a_{
  POR_NOME_A = 1,
  POR_CODIGO_A,
  POR_CPF,
} METODO_DE_BUSCA_A;

/* FUNCOES PRIVADAS */

int _aluno_determinar_metodo_de_busca();

int _aluno_validar_codigo(const char *codigo);

int _aluno_validar_cpf(const char *cpf);

int _aluno_cadastrar_nome(char*);

int _aluno_cadastrar_codigo(char*);

int _aluno_cadastrar_cpf(char*);


/* CADASTRAR ALUNO */

int cadastrar_aluno(List *alunos);

/* REMOVER ALUNO */

/* Remove o aluno por meio de uma busca com o codigo fornecido pelo usuario
 */
int remover_aluno(List *alunos);


/* Consultar Aluno */

int consultar_aluno(List *alunos);

#endif