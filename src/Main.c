#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Manejo_Alunos.h"
#include "Manejo_Disciplinas.h"
#include "Manejo_Registros.h"
#include "Style.h"


/* OPCOES DO MENU */

typedef enum opmenu { 
  MENU_ALUNO = 1,
  MENU_DISCIPLINA,
  MENU_MATRICULAS,
  SAIR,
  PRINCIPAL
} OPMENU;

typedef enum op_a { 
  CADASTRAR_ALUNO = 1, 
  REMOVER_ALUNO,
  MOSTRAR_ALUNOS,
  CONSULTAR_ALUNO, 
  CONSULTAR_MATRICULAS_ALUNO,
  DESFAZER_MATRICULAS_DE_ALUNO,
  VOLTAR_A
} OP_A;

typedef enum op_d {
  CADASTRAR_DISCIPLINA = 1, 
  REMOVER_DISCIPLINA,
  MOSTRAR_DISCIPLINAS,
  CONSULTAR_DISCIPLINA,
  CONSULTAR_ALUNOS_MATRICULADOS_DISCIPLINA,
  DESFAZER_MATRICULAS_DE_DISCIPLINA,
  VOLTAR_D
} OP_D;

typedef enum op_r {
  MATRICULAR_ALUNO_EM_DISCIPLINA=1,
  MOSTRAR_MATRICULAS,
  DESFAZER_MATRICULA,
  VOLTAR_R
} OP_R;

void imprimir_menu();

void menu_cabecalho();

void imprimir_submenu_aluno();

void imprimir_submenu_disciplina();

void imprimir_submenu_matriculas();

void imprimir_erro(int erro);


int main() {
  // Carregar listas
  List *alunos = list_load("data/alunos.bin", fread_aluno, destruir_aluno);
  List *disciplinas = list_load("data/disciplinas.bin", fread_disciplina, destruir_disciplina);
  List *registros = list_load("data/registros.bin", fread_registro, destruir_registro);


  int op;
  int sair = 0;
  int menu = PRINCIPAL;

  while(!sair) {

    // Imprimir menu atual
    switch(menu) {
      case PRINCIPAL:
        imprimir_menu();
        break;

      case MENU_ALUNO:
        imprimir_submenu_aluno();
        break;

      case MENU_DISCIPLINA:
        imprimir_submenu_disciplina();
        break;

      case MENU_MATRICULAS:
        imprimir_submenu_matriculas();
        break;
    }
    
    printf("\nOpcao desejada: ");

    fflush(stdin);
    scanf("%d", &op);

    int erro = 0;

    // Determinar acao a ser feita
    switch(menu) {

      // Se no menu principal
      case PRINCIPAL:
        if (MENU_ALUNO <= op && op <= MENU_MATRICULAS) menu = op;
        if (op == SAIR) sair = 1;
        menu = op;
        break;

      // Se no submenu de aluno
      case MENU_ALUNO:
        switch(op) {
          case CADASTRAR_ALUNO:
            erro = cadastrar_aluno(alunos);
            imprimir_erro(erro);
            break;

          case REMOVER_ALUNO:
            erro = remover_aluno(alunos);
            imprimir_erro(erro);
            break;

          case MOSTRAR_ALUNOS:
            list_apply(alunos, imprimir_aluno);
            pressione_para_continuar();
            break;

          case CONSULTAR_ALUNO:
            erro = consultar_aluno(alunos);
            imprimir_erro(erro);
            pressione_para_continuar();
            break;

          case CONSULTAR_MATRICULAS_ALUNO:
            erro = consultar_registro_por_aluno(registros, alunos);
            imprimir_erro(erro);
            break;

          case DESFAZER_MATRICULAS_DE_ALUNO:
            erro = remover_registros_por_aluno(registros);
            imprimir_erro(erro);
            break;

          case VOLTAR_A:
            menu = PRINCIPAL;
            break;

          default:
            printf("\nOpcao invalida!\n");
        }
        break;

      // Se em submenu de disciplinas
      case MENU_DISCIPLINA:
        switch(op) {
          case CADASTRAR_DISCIPLINA:
            erro = cadastrar_disciplina(disciplinas);
            imprimir_erro(erro);
            break;

          case REMOVER_DISCIPLINA:
            erro = remover_disciplina(disciplinas);
            imprimir_erro(erro);
            break;

          case MOSTRAR_DISCIPLINAS:
            list_apply(disciplinas, imprimir_disciplina);
            pressione_para_continuar();
            break;

          case CONSULTAR_DISCIPLINA:
            erro = consultar_disciplina(disciplinas);
            imprimir_erro(erro);
            pressione_para_continuar();
            break;

          case CONSULTAR_ALUNOS_MATRICULADOS_DISCIPLINA:
            erro = consultar_registro_por_disciplina(registros, disciplinas);
            imprimir_erro(erro);
            break;

          case DESFAZER_MATRICULAS_DE_DISCIPLINA:
            erro = remover_registros_por_disciplina(registros);
            imprimir_erro(erro);
            break;

          case VOLTAR_D:
            menu = PRINCIPAL;
            break;
          
          default:
            printf("\nOpcao invalida!\n");
        }
        break;

      // Se em submenu de matriculas
      case MENU_MATRICULAS:
        switch(op) {
          case MOSTRAR_MATRICULAS:
            list_apply(registros, imprimir_registro);
            pressione_para_continuar();
            break;

          case MATRICULAR_ALUNO_EM_DISCIPLINA:
            erro = cadastrar_registro(registros, alunos, disciplinas);
            imprimir_erro(erro);
            break;

          case DESFAZER_MATRICULA:
            erro = remover_registro(registros);
            imprimir_erro(erro);
            break;

          case VOLTAR_R:
            menu = PRINCIPAL;
            break;
          
          default:
            printf("\nOpcao invalida!\n");
        }
        break;
    }
  } 

  imprimir_borda();
  printf("\nSalvando alteracoes...\n");
  imprimir_borda();
  
  // Persistir memoria
  list_save(alunos, "data/alunos.bin", fwrite_aluno);
  list_save(disciplinas, "data/disciplinas.bin", fwrite_disciplina);
  list_save(registros, "data/registros.bin", fwrite_registro);

  // Liberar memoria utilizada para as listas
  list_destroy(alunos);
  list_destroy(disciplinas);
  list_destroy(registros);

  return 0;
}


void imprimir_erro(int erro) {
  if (erro == CODIGO_A_INVALIDO) printf("\nCodigo invalido!\n");
  if (erro == CPF_INVALIDO) printf("\nCPF invalido!\n");
  if (erro == ALUNO_NAO_ENCONTRADO) printf("\nAluno nao encontrado!\n");
  if (erro == CODIGO_D_INVALIDO) printf("\nCodigo invalido!\n");
  if (erro == CREDITOS_INVALIDO) printf("\nCreditos invalidos!\n");
  if (erro == DISCIPLINA_NAO_ENCONTRADA) printf("\nDisciplina nao encontrada!\n");
  if (erro == CODIGO_ALUNO_INVALIDO_R) printf("\nCodigo de aluno invalido!\n");
  if (erro == CODIGO_DISCIPLINA_INVALIDO_R) printf("\nCodigo de disciplina invalido!\n");
  if (erro == PERIODO_INVALIDO) printf("\nPeriodo invalido!\n");
  if (erro == REGISTRO_NAO_ENCONTRADO) printf("\nRegistro nao encontrado!\n");
  if (erro == OPCAO_INVALIDA) printf("\nEntrada invalida!\n");
  if (erro == METODO_INVALIDO) printf("\nMetodo invalido!\n");
  if (erro == METODO_D_INVALIDO) printf("\nMetodo invalido!\n");
}


void menu_cabecalho() {
  imprimir_borda();
  printf("-------------------     MENU    ---------------------");
  imprimir_borda();
}


void imprimir_menu() {
  menu_cabecalho();
  printf("\n(%d) Ir ao menu de alunos\n", MENU_ALUNO);
  printf("(%d) Ir ao menu de disciplinas\n", MENU_DISCIPLINA);
  printf("(%d) Ir ao menu de matriculas\n", MENU_MATRICULAS);
  printf("(%d) Sair\n", SAIR);
  imprimir_borda();
}

void imprimir_submenu_aluno() {
  menu_cabecalho();
  printf("\n(%d) Cadastrar aluno\n", CADASTRAR_ALUNO);
  printf("(%d) Remover aluno\n", REMOVER_ALUNO);
  printf("(%d) Mostrar alunos cadastrados\n", MOSTRAR_ALUNOS);
  printf("(%d) Consultar aluno\n", CONSULTAR_ALUNO);
  printf("(%d) Consultar disciplinas nas quais um aluno esta cadastrado\n", CONSULTAR_MATRICULAS_ALUNO);
  printf("(%d) Desfazer matriculas de aluno\n", DESFAZER_MATRICULAS_DE_ALUNO);
  printf("(%d) Voltar", VOLTAR_A);
  imprimir_borda();
}

void imprimir_submenu_disciplina() {
  menu_cabecalho();
  printf("\n(%d) Cadastrar disciplina\n", CADASTRAR_DISCIPLINA);
  printf("(%d) Remover disciplina\n", REMOVER_DISCIPLINA);
  printf("(%d) Mostrar disciplinas cadastradas\n", MOSTRAR_DISCIPLINAS);
  printf("(%d) Consultar disciplina\n", CONSULTAR_DISCIPLINA);
  printf("(%d) Consultar alunos matriculados em disciplina\n", CONSULTAR_ALUNOS_MATRICULADOS_DISCIPLINA);
  printf("(%d) Desfazer matriculas de disciplina\n", DESFAZER_MATRICULAS_DE_DISCIPLINA);
  printf("(%d) Voltar\n", VOLTAR_D);
  imprimir_borda();
}

void imprimir_submenu_matriculas() {
  menu_cabecalho();
  printf("\n(%d) Matricular aluno em disciplina\n", MATRICULAR_ALUNO_EM_DISCIPLINA);
  printf("(%d) Mostrar matriculas vigentes\n", MOSTRAR_MATRICULAS);
  printf("(%d) Desfazer matricula\n", DESFAZER_MATRICULA);
  printf("(%d) Voltar\n", VOLTAR_R);
  imprimir_borda();
}