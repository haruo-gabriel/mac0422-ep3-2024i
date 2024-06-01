#include "ep3.h"

FATNode* inicializa_fat() {
  FATNode* fat = (FATNode*) malloc(MAX_BLOCOS * sizeof(FATNode));
  for (int i = 0; i < MAX_BLOCOS; i++) {
    fat[i].prox = LIVRE;
  }
  return fat;
}

/**
 * Retorna -1 caso não haja espaço suficiente para armazenar o arquivo.
 * Caso contrário, retorna o índice do primeiro bloco alocado para o arquivo. 
 */
int aloca_arquivo(FATNode* fat, Bitmap* bitmap, int tamanho_arquivo) {
  // O tamanho do arquivo é dado em bytes

  // Verifica se há espaço o suficiente para armazenar o arquivo
  if (!possui_espaco_para_arquivo(bitmap, tamanho_arquivo)) {
    printf("Espaço insuficiente para armazenar o arquivo.\n");
    return -1;
  }

  int blocos_necessarios = converte_bytes_para_blocos(tamanho_arquivo);
  int primeiro_bloco_livre = encontra_primeiro_bloco_livre(bitmap);
  int bloco_atual = primeiro_bloco_livre;
  int bloco_prox = -1;
  seta_bit(bitmap, bloco_atual);
  blocos_necessarios--;
  for (int i = 0; i < blocos_necessarios; i++) {
    bloco_prox = encontra_primeiro_bloco_livre(bitmap);
    seta_bit(bitmap, bloco_prox);
    fat[bloco_atual].prox = bloco_prox;
    bloco_atual = bloco_prox;
  }
  fat[bloco_atual].prox = FIM_ARQUIVO;
  
  return primeiro_bloco_livre;
}

int deleta_arquivo(FATNode* fat, Bitmap* bitmap, int bloco_inicial) {
  int bloco_atual = bloco_inicial;
  int bloco_prox = fat[bloco_atual].prox;
  while (bloco_prox != FIM_ARQUIVO) {
    // Marca o bloco atual como livre
    limpa_bit(bitmap, bloco_atual);
    fat[bloco_atual].prox = LIVRE;
    // Atualiza os ponteiros
    bloco_atual = bloco_prox;
    bloco_prox = fat[bloco_atual].prox;
  }
  limpa_bit(bitmap, bloco_atual);
  fat[bloco_atual].prox = LIVRE;
  return 1;
}

void salva_fat_em_arquivo(FATNode* fat, const char* arquivo_fat) {
  FILE* file = fopen(arquivo_fat, "wb");
  if (!file) {
    fprintf(stderr, "Error opening file: %s\n", arquivo_fat);
    return;
  }
  fwrite(fat, sizeof(FATNode), MAX_BLOCOS, file);
  fclose(file);
}

FATNode* le_fat_do_arquivo(const char* arquivo_fat) {
  FATNode* fat = inicializa_fat();
  FILE* file = fopen(arquivo_fat, "rb");
  if (!file) {
    fprintf(stderr, "Error opening file: %s\n", arquivo_fat);
    free(fat);
    return NULL;
  }
  size_t items_read = fread(fat, sizeof(FATNode), MAX_BLOCOS, file);
  if (items_read < MAX_BLOCOS) {
    fprintf(stderr, "Error reading file: %s\n", arquivo_fat);
    free(fat);
    fclose(file);
    return NULL;
  }
  fclose(file);
  return fat;
}