#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Manejo_Alunos.h"
#include "Manejo_Disciplinas.h"
#include "Manejo_Registros.h"
#include "Style.h"


/* OPCOES DO MENU */


typedef enum opcao {CADASTRAR_ALUNO = 1, 
                    REMOVER_ALUNO, 
                    CADASTRAR_DISCIPLINA, 
                    REMOVER_DISCIPLINA,
                    MOSTRAR_ALUNOS, 
                    MOSTRAR_DISCIPLINAS,
                    CONSULTAR_ALUNO, 
                    CONSULTAR_DISCIPLINA,
                    MATRICULAR_ALUNO_EM_DISCIPLINA,
                    MOSTRAR_MATRICULAS,
                    CONSULTAR_MATRICULAS_ALUNO,
                    CONSULTAR_ALUNOS_MATRICULADOS_DISCIPLINA,
                    DESFAZER_MATRICULA,
                    DESFAZER_MATRICULAS_DE_ALUNO,
                    DESFAZER_MATRICULAS_DE_DISCIPLINA,
                    SAIR
              } Opcao;

void imprimir_menu();

void imprimir_erro(int erro);


int main() {
  // Carregar listas
  List *alunos = list_load("alunos.bin", fread_aluno, destruir_aluno);
  List *disciplinas = list_load("disciplinas.bin", fread_disciplina, destruir_disciplina);
  List *registros = list_load("registros.bin", fread_registro, destruir_registro);


  Opcao op;
  int sair = 0;

  while(!sair) {
    imprimir_menu();
    printf("\nOpcao desejada: ");

    fflush(stdin);
    scanf("%d", &op);

    int erro = 0;
    switch(op) {
      case CADASTRAR_ALUNO:
        erro = cadastrar_aluno(alunos);
        imprimir_erro(erro);
        break;

      case REMOVER_ALUNO:
        erro = remover_aluno(alunos);
        imprimir_erro(erro);
        break;

      case CADASTRAR_DISCIPLINA:
        erro = cadastrar_disciplina(disciplinas);
        imprimir_erro(erro);
        break;

      case REMOVER_DISCIPLINA:
        erro = remover_disciplina(disciplinas);
        imprimir_erro(erro);
        break;

      case MOSTRAR_ALUNOS:
        list_apply(alunos, imprimir_aluno);
        pressione_para_continuar();
        break;

      case MOSTRAR_DISCIPLINAS:
        list_apply(disciplinas, imprimir_disciplina);
        pressione_para_continuar();
        break;

      case CONSULTAR_ALUNO:
        erro = consultar_aluno(alunos);
        imprimir_erro(erro);
        pressione_para_continuar();
        break;

      case MOSTRAR_MATRICULAS:
        list_apply(registros, imprimir_registro);
        pressione_para_continuar();
        break;

      case CONSULTAR_DISCIPLINA:
        erro = consultar_disciplina(disciplinas);
        imprimir_erro(erro);
        pressione_para_continuar();
        break;

      case MATRICULAR_ALUNO_EM_DISCIPLINA:
        erro = cadastrar_registro(registros, alunos, disciplinas);
        imprimir_erro(erro);
        break;

      case CONSULTAR_MATRICULAS_ALUNO:
        erro = consultar_registro_por_aluno(registros, alunos);
        imprimir_erro(erro);
        break;

      case CONSULTAR_ALUNOS_MATRICULADOS_DISCIPLINA:
        erro = consultar_registro_por_disciplina(registros, disciplinas);
        imprimir_erro(erro);
        break;

      case DESFAZER_MATRICULA:
        erro = remover_registro(registros);
        imprimir_erro(erro);
        break;

      case DESFAZER_MATRICULAS_DE_ALUNO:
        erro = remover_registros_por_aluno(registros);
        imprimir_erro(erro);
        break;

      case DESFAZER_MATRICULAS_DE_DISCIPLINA:
        erro = remover_registros_por_disciplina(registros);
        imprimir_erro(erro);
        break;

      case SAIR:
        sair = 1;
        break;

      default:
        printf("\nOpcao invalida!\n");
        break;
    }
  } 

  imprimir_borda();
  printf("\nSalvando alteracoes...\n");
  imprimir_borda();
  
  // Persistir memoria
  list_save(alunos, "alunos.bin", fwrite_aluno);
  list_save(disciplinas, "disciplinas.bin", fwrite_disciplina);
  list_save(registros, "registros.bin", fwrite_registro);

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
}


void imprimir_menu() {
  imprimir_borda();
  printf("-------------------     MENU    ---------------------");
  imprimir_borda();
  printf("\n%d - Cadastrar aluno\n", CADASTRAR_ALUNO);
  printf("%d - Remover aluno\n", REMOVER_ALUNO);
  printf("%d - Cadastrar disciplina\n", CADASTRAR_DISCIPLINA);
  printf("%d - Remover disciplina\n", REMOVER_DISCIPLINA);
  printf("%d - Mostrar alunos cadastrados\n", MOSTRAR_ALUNOS);
  printf("%d - Mostrar disciplinas cadastradas\n", MOSTRAR_DISCIPLINAS);
  printf("%d - Consultar aluno\n", CONSULTAR_ALUNO);
  printf("%d - Consultar disciplina\n", CONSULTAR_DISCIPLINA);
  printf("%d - Matricular aluno em disciplina\n", MATRICULAR_ALUNO_EM_DISCIPLINA);
  printf("%d - Mostrar matriculas vigentes\n", MOSTRAR_MATRICULAS);
  printf("%d - Consultar disciplinas nas quais um aluno esta cadastrado\n", CONSULTAR_MATRICULAS_ALUNO);
  printf("%d - Consultar alunos matriculados em disciplina\n", CONSULTAR_ALUNOS_MATRICULADOS_DISCIPLINA);
  printf("%d - Desfazer matricula\n", DESFAZER_MATRICULA);
  printf("%d - Desfazer matriculas de aluno\n", DESFAZER_MATRICULAS_DE_ALUNO);
  printf("%d - Desfazer matriculas de disciplina\n", DESFAZER_MATRICULAS_DE_DISCIPLINA);
  printf("%d - Sair\n", SAIR);
  imprimir_borda();
}
