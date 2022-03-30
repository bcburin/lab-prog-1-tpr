#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Disciplina.h"
#include "Manejo_Alunos.h"
#include "Manejo_Disciplinas.h"
#include "Style.h"


/* OPCOES DO MENU */

typedef enum opcao {CADASTRAR_ALUNO = 1, REMOVER_ALUNO, 
              CADASTRAR_DISCIPLINA, REMOVER_DISCIPLINA,
              MOSTRAR_ALUNOS, MOSTRAR_DISCIPLINAS,
              CONSULTAR_ALUNO, CONSULTAR_DISCIPLINA,
              CONSULTAR_DISCIPLINAS_ALUNO, CONSULTAR_ALUNOS_DISCIPLINA,
              SAIR
              } Opcao;

void imprimir_menu();


int main() {
  List *alunos = list_load("alunos.bin", fread_aluno, destruir_aluno);
  List *disciplinas = list_load("disciplinas.bin", fread_disciplina, destruir_disciplina);

  list_shift(disciplinas);

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
        if (erro == CODIGO_A_INVALIDO) printf("\nCodigo invalido!\n");
        if (erro == CPF_INVALIDO) printf("\nCPF invalido!\n");
        break;
      case REMOVER_ALUNO:
        erro = remover_aluno(alunos);
        if (erro == CODIGO_A_INVALIDO) printf("\nCodigo invalido!\n");
        if (erro == CPF_INVALIDO) printf("\nCPF invalido!\n");
        if (erro == ALUNO_NAO_ENCONTRADO) printf("\nAluno nao encontrado!\n");
        break;
      case CADASTRAR_DISCIPLINA:
        erro = cadastrar_disciplina(disciplinas);
        if (erro == CODIGO_D_INVALIDO) printf("\nCodigo invalido!\n");
        if (erro == DISCIPLINA_NAO_ENCONTRADA) printf("\nDisciplina nao encontrada!\n");
        break;
      case REMOVER_DISCIPLINA:
        erro = remover_disciplina(disciplinas);
        if (erro == CODIGO_D_INVALIDO) printf("\nCodigo invalido!\n");
        if (erro == DISCIPLINA_NAO_ENCONTRADA) printf("\nDisciplina nao encontrada!\n");
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
        if (erro == CODIGO_A_INVALIDO) printf("\nCodigo invalido!\n");
        if (erro == CPF_INVALIDO) printf("\nCPF invalido!\n");
        if (erro == ALUNO_NAO_ENCONTRADO) printf("\nAluno nao encontrado!\n");
        pressione_para_continuar();
        break;
      case CONSULTAR_DISCIPLINA:
        erro = consultar_disciplina(disciplinas);
        if (erro == CODIGO_D_INVALIDO) printf("\nCodigo invalido!\n");
        if (erro == DISCIPLINA_NAO_ENCONTRADA) printf("\nDisciplina nao encontrada!\n");
        if (erro == CREDITOS_INVALIDO) printf("\nCreditos invalidos!\n");
        pressione_para_continuar();
        break;
      case CONSULTAR_ALUNOS_DISCIPLINA:
        printf("cAD");
        break;
      case CONSULTAR_DISCIPLINAS_ALUNO:
        printf("cda");
        break;  
      case SAIR:
        sair = 1;
        break;
      default:
        printf("def");
    }
  } 

  imprimir_borda();
  printf("\nSalvando alteracoes...\n");
  imprimir_borda();
  
  // Persistir memoria
  list_save(alunos, "alunos.bin", fwrite_aluno);
  list_save(disciplinas, "disciplinas.bin", fwrite_disciplina);


  // Liberar memoria utilizada para as listas
  list_destroy(alunos);
  list_destroy(disciplinas);
  
  return 0;
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
  printf("%d - Consultar alunos em uma disciplina e periodo\n", CONSULTAR_ALUNOS_DISCIPLINA);
  printf("%d - Consultar disciplinas de um aluno e periodo\n", CONSULTAR_DISCIPLINAS_ALUNO);
  printf("%d - Sair\n", SAIR);
  imprimir_borda();
}
