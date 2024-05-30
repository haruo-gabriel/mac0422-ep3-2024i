#include "ep3.h"

int conta_tokens(const char *str, const char *delimitadores) {
  char *str_copia = strdup(str);
  char *token;
  int num_args = 0;
  if (str_copia == NULL) {
    perror("strdup");
    return 1;
  }
  token = strtok(str_copia, delimitadores);
  while (token != NULL) {
    num_args++;
    token = strtok(NULL, delimitadores);
  }
  free(str_copia);
  return num_args;
}

int parse_comando(const char *comando, char *args[], int *num_args) {
  // Cria uma cópia da string comando
  char *comando_copia = strdup(comando);
  if (comando_copia == NULL) {
    perror("strdup");
    return 1;
  }
  
  char *token;
  char *delimitadores = " ";
  
  // Conta o número de tokens na string comando_copia
  int num_args = conta_tokens(comando_copia, delimitadores);
  
  // Aloca memória para o vetor de args
  *args = malloc((num_args + 1) * sizeof(char *));
  if (*args == NULL) {
    perror("malloc");
    free(comando_copia);
    return 1;
  }
  
  int i = 0;
  token = strtok(comando_copia, delimitadores);
  while (token != NULL) {
    // Aloca memória para cada token e copia o valor
    (*args)[i] = malloc(strlen(token) + 1);
    if ((*args)[i] == NULL) {
      free(comando_copia);
      return 1;
    }
    strcpy((*args)[i], token);
    i++;
    token = strtok(NULL, delimitadores);
  }
  
  // Define o último elemento do vetor de args como NULL
  (*args)[i] = NULL;
  
  // Libera a memória alocada para a cópia do comando
  free(comando_copia);
  
  return 0;
}

int valida_comando(char*** args) {
  char* arg0 = (*args)[0];
  // Lista de comandos válidos
  char* comandos_validos[NUM_COMANDOS_VALIDOS] = {
    "monta"
  };
  for (int i = 0; i < NUM_COMANDOS_VALIDOS; i++) {
    if (strcmp(arg0, comandos_validos[i]))
      return 0;
  }
  printf("Falhou no valida_comando\n");
  return 1;
}

void free_args(char** args, int num_args) {
  for (int i = 0; i < num_args; i++) {
    free(args[i]);
  }
  free(args);
}


/**
 * Executa o comando armazenado na string `*comando`.
 * Recebe a string `*comando` e a lista de args `args_ptr`.
 * Compara o argumento 0 de `args_ptr` (ou seja, o nome do programa)
 * com 
 * 
 * @param comando A string contendo o comando a ser executado.
 * @param args Um ponteiro para a lista de args do comando.
 * @return Retorna 0 se a operação foi bem sucedida e 1 caso contrário.
 */
int processa_comando(char ***args) {
  if (valida_comando(args)) {
    char* arg0 = (*args)[0];
    if (strcmp(arg0, "monta")) return monta(args);
  }
  return 1;
}

// void prompt(SistemaArquivos* sist) {
void prompt() {
  char* comando;
  char* args[MAX_ARGS];
  int num_args;

  while (1) {
    comando = readline("{ep3}: ");
    if (comando == NULL) {
      printf("Erro ao ler comando.\n");
      continue;
    }

    // Se o comando for vazio, ignora
    if (strlen(comando) == 0) {
      free(comando);
      continue;
    }

    parse_comando(comando, &args);

    free_args(args, num_args);
    free(comando);
  }
}