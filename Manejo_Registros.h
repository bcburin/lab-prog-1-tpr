#ifndef MANEJO_REGISTROS
#define MANEJO_REGISTROS

#include <stdio.h>

#include "Manejo_Alunos.h"
#include "Manejo_Disciplinas.h"
#include "List.h"
#include "Registro.h"
#include "Auxiliar.h"

typedef enum erro_registro_registro_{
  CODIGO_ALUNO_INVALIDO_R = -1,
  CODIGO_DISCIPLINA_INVALIDO_R = -2,
  PERIODO_INVALIDO_R = -3,
  REGISTRO_NAO_ENCONTRADO = -4
} ERRO_REGISTRO_REGISTRO;

typedef enum metodo_de_busca_r{
  POR_ALUNO_R = 1 ,
  POR_DISCIPLINA_R = 2,
} METODO_DE_BUSCA_R;

/* FUNCOES PRIVADAS */

int _registro_determinar_metodo_de_busca();

int _registro_validar_periodo(const char *periodo);

int _registro_cadastrar_periodo(char*);

/* REMOVER ALUNO */

/* TODO: Remove o registro 
 */
int remover_registro(List *registros);//IMPLEMENTAR

//TODO
/* IMPRIMIR O REGISTRO*/

/* CONSULTAR REGISTRO*/
//TODO: imprimir resultados
int consultar_registro(List *registros, List *alunos, List *disciplinas);





#endif