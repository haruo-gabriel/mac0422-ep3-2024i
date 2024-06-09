#include "ep3.h"

// Funções de manipulação de bitmap

Bitmap* inicializa_bitmap() {
  Bitmap* bitmap = (Bitmap*) malloc(sizeof(Bitmap));
  bitmap->bit = (uint8_t*) malloc(converte_blocos_para_bytes(MAX_BLOCOS) * sizeof(uint8_t));
  return bitmap;
}

/* bitmap->bit[i / 8] acessa o i-ésimo uint8_t
 * 1 << (i % 8) cria uma máscara com o bit (i % 8) setado e os outros bits zerados
 * |= faz um OR bit a bit entre o i-ésimo uint8_t e a máscara
 * Isso seta o bit (i % 8) do i-ésimo uint8_t
 */
void seta_bit(Bitmap* bitmap, int i) {
  bitmap->bit[i / 8] |= 1 << (i % 8);
}

/* bitmap->bit[i / 8] acessa o i-ésimo uint8_t
 * ~(1 << (i % 8)) cria uma máscara com o bit (i % 8) zerado e os outros bits setados
 * &= faz um AND bit a bit entre o i-ésimo uint8_t e a máscara
 * Isso limpa o bit (i % 8) do i-ésimo uint8_t
 */
void limpa_bit(Bitmap* bitmap, int i) {
  bitmap->bit[i / 8] &= ~(1 << (i % 8));
}

/* bitmap->bit[i / 8] acessa o i-ésimo uint8_t
 * bitmap->bit[i / 8] >> (i % 8) move o bit (i % 8) para a posição mais à direita
 * & 1 retorna 1 se o bit mais à direita for 1 e 0 se for 0
 * Isso verifica o bit (i % 8) do i-ésimo uint8_t
 */
int verifica_bit(Bitmap* bitmap, int i) {
  return (bitmap->bit[i / 8] >> (i % 8)) & 1;
}





// Funções de escrita e leitura de bitmap em arquivo

void salva_bitmap_em_arquivo(Bitmap* bitmap, const char* arquivo_bitmap) {
  FILE* fp = fopen(arquivo_bitmap, "wb");
  if (fp == NULL) {
    printf("Erro ao abrir arquivo %s.\n", arquivo_bitmap);
    return;
  }
  fwrite(bitmap->bit, sizeof(uint8_t), converte_blocos_para_bytes(MAX_BLOCOS), fp);
  fclose(fp);
}

Bitmap* le_bitmap_do_arquivo(Bitmap* bitmap, const char* arquivo_bitmap) {
  FILE* fp = fopen(arquivo_bitmap, "rb");
  if (fp == NULL) {
    printf("Erro ao abrir arquivo %s.\n", arquivo_bitmap);
    return NULL;
  }
  fread(bitmap->bit, sizeof(uint8_t), converte_blocos_para_bytes(MAX_BLOCOS), fp);
  fclose(fp);
  return bitmap;
}




// Funções de verificação de espaço livre

int possui_espaco_para_arquivo(Bitmap* bitmap, int tamanho_arquivo) {
  // tamanho é o tamanho do arquivo em bytes
  int blocos_necessarios = converte_bytes_para_blocos(tamanho_arquivo);
  int blocos_livres = 0;
  for (int i = 0; i < MAX_BLOCOS; i++) {
    if (!verifica_bit(bitmap, i)) {
      blocos_livres++;
    }
  }
  // Retorna 1 se houver espaço suficiente para o arquivo e 0 caso contrário
  return blocos_livres >= blocos_necessarios;
}

int encontra_primeiro_bloco_livre(Bitmap* bitmap) {
  for (int i = 0; i < MAX_BLOCOS; i++) {
    if (!verifica_bit(bitmap, i)) {
      return i;
    }
  }
  return -1;
}