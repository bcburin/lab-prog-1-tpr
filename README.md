# lab-prog-1-tpr

## Trabalho prático de revisão para a disciplina de Laboratório de Programação I (IME), ao final da UD 1 (revisão de C)

Autores:

- Bruno Camacho Burin
- Mateus Lima Silveira

Programa implementa um banco de dados de alunos e disciplinas usando listas duplamente encadeadas. A inserção de novos alunos ou disciplinas é sempre feita no fim da lista. A remoção desses dados, claro, ocorre em qualquer posição da lista. A busca é linear, atravessando cada nó da lista até encontrar, ou não, o valor desejado. O salvamento e carregamento das listas (persistência de dados), é feito por meio de escrita e leitura em arquivos binários. A listas foram todas implementadas usando os arquivos List.h e List.c, que implementam uma lista duplamente encadeada de dados genéricos (ponteiros void\*).

As buscas nessas listas, por comidade, podem tanto ser feita pelo nome ou parte do nome do aluno ou disciplina, quanto por codigo ou, se for o caso, CPF. Ademais, implementou-se uma lista de matrículas (registros), que explicita quais alunos estiveram matriculados em cada materia em cada semestre. Isso é feito armazenando elementos contendo um codigo de aluno, um codigo de matricula e um semestre na lista de registros. Como resultado, também é possível descobrir todas as matérias nas quais um aluno está matriculado, ou todos os alunos que estão matriculados em determinada disciplina. O filtro por período, em ambos casos, é opcional.

A remoção nas listas de alunos e disciplinas mostra o elemento que foi removido, caso isso tenha ocorrido, ou mostra uma mensagem caso a remoção não tenha se dado. No geral, implementaram-se os tratamentos de diversos tipos de erro gerados pelo input do usuário.

Todos os arquivos fonte estão dentro da pasta "src/" e a função main() está no arquivo Main.c. Eles podem ser compilados simultaneamente com o comando:

'''
gcc src/\*.c -o main.exe
'''

O qual foi testado no prompt git bash para o SO Windows, com sucesso. A versão do gcc usada foi 9.2.0.

Os dados de persistência de memória estão, por sua vez, no diretório "data/", contendo os arquivos: "alunos.bin", "disciplinas.bin" e "registros.bin", que armazenam, respectivamente, a lista de alunos, disciplinas e matrículas. Observação importante: o executável gerado na compilação deve, necessariamente, estar no mesmo diretório que a pasta "data".
