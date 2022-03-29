#ifndef MANEJO_REGISTROS
#define MANEJO_REGISTROS

#include <stdio.h>

#include "Manejo_Alunos.h"
#include "Manejo_Disciplinas.h"
#include "List.h"
#include "Registro.h"
#include "Auxiliar.h"

typedef enum erro_registro_registro_{
  CODIGO_INVALIDO = -1,
  PERIODO_INVALIDO = -2,
} ERRO_REGISTRO_REGISTRO;

/* consulta e imprime todas as disciplinas de um aluno em um período */
int consultar_disciplinas_de_aluno(List *registros, List *alunos, List *disciplinas );

/* consulta e imprime alunos de uma disciplina em um período */
int consultar_alunos_de_disciplina(List *registro, List *alunos, List *disciplinas);

int _registro_validar_periodo(const char *periodo);

int _registro_cadastrar_periodo(char*);

#endif