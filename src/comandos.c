#include "ep3.h"

int monta(const char* arquivo) {
  printf("Entrei no monta.\n");

  FILE* fp = fopen(arquivo, "r");
  if (fp) {
    // Aqui, o arquivo já existe
    printf("O arquivo %s já existe. Montando o sistema de arquivos.\n", arquivo);
    // TODO: Implement file system loading
    fclose(fp);
  } else {
    // Aqui, o arquivo não existe
    printf("O arquivo %s não existe. Montando novo sistema de arquivos.\n", arquivo);
    // Cria um novo arquivo
    fp = fopen(arquivo, "w");
    if (fp) {
      fseek(fp, TAM_DISCO - 1, SEEK_SET);
      fputc('\0', fp);
      // TODO: Implement file system creation
      fclose(fp);
    } else {
      printf("Falha ao montar o sistema.\n");
      return -1;
    }
  }

  return 0;
}

int sai() {
  printf("Entrei no sai.\n");
  return 0;
}
