#include "ep3.h"

int main() {
  char* comando = NULL;
  char **argumentos = NULL;

  while (1) {
    // Imprime o prompt
    comando = readline("{ep3}: ");
    if (comando == NULL) {  
      printf("\n");
      break;
    }
    
    // Tokeniza o comando
    if (parse_comando(comando, &argumentos) == 1) {
      printf("Falhou no parse_comando.\n");
      return 1;
    }

    // Executa o comando
    if (processa_comando(&argumentos) != 0) {
      printf("Falhou no processa_comando.\n");
      return 1;
    }

    // Libera memória para receber o próximo comando
    free(comando);
    for (int i=0; argumentos[i] != NULL; i++) {
      free(argumentos[i]);
    }
    free(argumentos);
  }

  return 0;
}