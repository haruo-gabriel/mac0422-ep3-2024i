#include "ep3.h"

int monta(const char* arquivo) {
  printf("Entrei no monta.\n");

  FILE* fp = fopen(arquivo, "r");

  // Aqui, o arquivo já existe
  if (fp) {
    printf("O arquivo %s já existe.\n", arquivo);
    printf("Montando o sistema de arquivos.\n");
    fclose(fp);
    g_montado = true;
    g_arquivo_disco = strdup(arquivo);
  }
  // Aqui, o arquivo não existe
  else {
    printf("O arquivo %s não existe.\n", arquivo);
    printf("Montando novo sistema de arquivos.\n");

    // Cria um novo arquivo
    fp = fopen(arquivo, "w");
    if (fp) {
      // Aloca o espaço em disco para o novo arquivo
      uint8_t* buffer = calloc(TAM_DISCO, sizeof(uint8_t));
      if (buffer) {
        fwrite(buffer, sizeof(uint8_t), TAM_DISCO, fp);
        free(buffer);
      }
      fclose(fp);
    } else {
      printf("Falha ao montar o sistema.\n");
      return -1;
    }
    
    // Cria o bitmap e a tabela FAT
    Bitmap* bitmap = inicializa_bitmap();
    FATNode* fat = inicializa_fat();

    // Pega o diretório do arquivo de disco
    char* dir = dirname(strdup(arquivo));
    char bitmap_path[MAX_PATH];
    char fat_path[MAX_PATH];

    // Constrói os paths do bitmap e da FAT
    snprintf(bitmap_path, sizeof(bitmap_path), "%s/bitmap.bin", dir);
    snprintf(fat_path, sizeof(fat_path), "%s/fat.bin", dir);

    // Salva o bitmap e a tabela FAT no mesmo diretório que o arquivo do disco
    salva_bitmap_em_arquivo(bitmap, bitmap_path);
    salva_fat_em_arquivo(fat, fat_path);

    // Libera a memória alocada
    free(bitmap);
    free(fat);

    g_montado = true;
    g_arquivo_disco = strdup(arquivo);
  }

  return 0;
}

int desmonta() {
  printf("Entrei no desmonta.\n");
  if (remove(g_arquivo_disco) == 0) {
    printf("Sistema de arquivos desmontado.\n");
    g_montado = false;
    return 0;
  } else {
    printf("Falha ao desmontar o sistema de arquivos.\n");
    return -1;
  }
}

void lista_diretorio(const char* nome_diretorio) {
  printf("Entrei no lista_diretorio.\n");

  Diretorio* dir = acha_diretorio(nome_diretorio);
  if (!dir) {
    printf("Diretório não encontrado.\n");
    return;
  }

  printf("Nome | Tamanho | Criado | Modificado | Acessado\n");
  for (int i = 0; i < dir->num_arquivos; i++) {
    Arquivo arq = dir->arquivos[i];

    // O nome depende se o arquivo é um diretório ou não
    char* nome = arq.eh_diretorio ? strcat(arq.nome, "/") : arq.nome;

    // Converte as datas para strings
    char* criadoStr = ctime(&arq.criado);
    char* modificadoStr = ctime(&arq.modificado);
    char* acessadoStr = ctime(&arq.acessado);

    // Remove o caractere de nova linha do final das strings
    criadoStr[strcspn(criadoStr, "\n")] = 0;
    modificadoStr[strcspn(modificadoStr, "\n")] = 0;
    acessadoStr[strcspn(acessadoStr, "\n")] = 0;

    printf("%s | %d | %s | %s | %s\n",
      nome, arq.tamanho, criadoStr, modificadoStr, acessadoStr
    );
  }
}

int sai() {
  printf("Entrei no sai.\n");
  return 0;
}
