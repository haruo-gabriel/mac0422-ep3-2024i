#include "ep3.h"

FATNode* inicializa_fat() {
  FATNode* fat = (FATNode*) malloc(MAX_BLOCOS * sizeof(FATNode));
  for (int i = 0; i < MAX_BLOCOS; i++) {
    fat[i].prox = LIVRE;
  }
  return fat;
}

int aloca_arquivo(FATNode* fat, Bitmap* bitmap, int tamanho) {
  // O tamanho do arquivo é dado em bytes

  // Verifica se há espaço o suficiente para armazenar o arquivo
  if (verifica_espaco_para_arquivo(bitmap, tamanho) == 0) {
    printf("Espaço insuficiente para armazenar o arquivo.\n");
    return 0;
  }

  // Encontra o primeiro bloco livre
  int primeiro_bloco_livre = encontra_primeiro_bloco_livre(bitmap);

  // Aloca o arquivo na FAT e no bitmap
  int bloco_atual = primeiro_bloco_livre;
  int blocos_necessarios = ceil((float) tamanho / TAM_BLOCO);
  for (int i = 0; i < blocos_necessarios; i++) {
    int prox_bloco = encontra_primeiro_bloco_livre(bitmap);
    fat[bloco_atual].prox = prox_bloco;
    bloco_atual = prox_bloco;
  }
  fat[bloco_atual].prox = FIM;
  
  return 1;
}

void salva_fat_em_arquivo(FATNode* fat) {
  return;
}

FATNode* le_fat_do_arquivo(FATNode* fat, const char* arquivo_fat) {
  return;
}