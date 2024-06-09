#include "ep3.h"

void parse_comando(const char* comando, char* args[], int* num_args) {
  // Cria uma cópia da string comando
  char* comando_copia = strdup(comando);
  char* token = strtok(comando_copia, " ");
  int i = 0;

  while (token != NULL && i < MAX_ARGS) {
    // strdup aloca memória e copia o conteúdo para a nova string
    args[i] = strdup(token);
    token = strtok(NULL, " ");
    i++;
  }
  args[i] = NULL;
  *num_args = i;

  free(comando_copia);
}

int valida_comando(char* args[], int num_args) {
  // Se o sistema de arquivos não estiver montado, apenas monta e sai são comandos válidos
  if (!g_montado) {
    if (strcmp(args[0], "monta") == 0 && num_args == 2) {
      return 0;
    }
    if (strcmp(args[0], "sai") == 0 && num_args == 1) {
      return -1;
    }
  }
  // Os comandos a seguir precisam que o sistema de arquivos esteja montado
  else {
    if (strcmp(args[0], "copia") == 0 && num_args == 3) {
      return 0;
    }
    if (strcmp(args[0], "criadir") == 0 && num_args == 2) {
      return 0;
    }
    if (strcmp(args[0], "apagadir") == 0 && num_args == 2) {
      return 0;
    }
    if (strcmp(args[0], "mostra") == 0 && num_args == 2) {
      return 0;
    }
    if (strcmp(args[0], "toca") == 0 && num_args == 2) {
      return 0;
    }
    if (strcmp(args[0], "apaga") == 0 && num_args == 2) {
      return 0;
    }
    if (strcmp(args[0], "lista") == 0 && num_args == 2) {
      return 0;
    }
    if (strcmp(args[0], "atualizadb") == 0 && num_args == 2) {
      return 0;
    }
    if (strcmp(args[0], "busca") == 0 && num_args == 2) {
      return 0;
    }
    if (strcmp(args[0], "status") == 0 && num_args == 1) {
      return 0;
    }
    if (strcmp(args[0], "desmonta") == 0 && num_args == 1) {
      return 0;
    }
    if (strcmp(args[0], "sai") == 0 && num_args == 1) {
      return -1;
    }
  }
  return 1;
}

void executa_comando(char* args[]) {
  if (strcmp(args[0], "monta") == 0) {
    monta(args[1]);
  }
  if (strcmp(args[0], "desmonta") == 0) {
    desmonta();
  }
  if (strcmp(args[0], "sai") == 0) {
    sai();
  }
}

// void prompt(SistemaArquivos* sist) {
void prompt() {
  char* comando;
  char* args[MAX_ARGS+1]; // O último elemento é NULL para indicar o fim do array
  int num_args;
  int valida;

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

    // Separa o comando em um array de args
    // args[0] é o comando, args[1] é o primeiro argumento, e assim por diante
    parse_comando(comando, args, &num_args);

    // Valida e executa o comando
    valida = valida_comando(args, num_args);
    if (valida <= 0) {
      executa_comando(args);
    } else {
      printf("Comando inválido.\n");
    }

    // Libera memória
    for (int i = 0; i < num_args; i++) {
      free(args[i]);
    }
    free(comando);

    // Se o comando for sai(), sai do loop
    if (valida == -1) {
      break;
    }
  }
}