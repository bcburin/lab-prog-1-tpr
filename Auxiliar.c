#include "Auxiliar.h"

//verifica se a string é composta só de numero
//retorna 1 se for só digito
int is_digit(const char *codigo){
    const char *dig=codigo;
    for(int i=0; *(dig+i)!='\0'; i++){
        if ( !('0' <= *(dig+i) && *(dig+i) <= '9') )
            return 0;
    }
  return 1;
}