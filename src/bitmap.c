#include "ep3.h"

// Funções de manipulação de bitmap

Bitmap* inicializa_bitmap() {
  Bitmap* bitmap = (Bitmap*) malloc(sizeof(Bitmap));
  for (int i = 0; i < MAX_BLOCOS_INT32; i++) {
    bitmap->bit[i] = 0;
  }
  return bitmap;
}

/* bitmap->bit[i / 32] acessa o i-ésimo uint32_t
* 1 << (i % 32) cria uma máscara com o bit (i % 32) setado e os outros bits zerados
* |= faz um OR bit a bit entre o i-ésimo uint32_t e a máscara
* Isso seta o bit (i % 32) do i-ésimo uint32_t
*/
void seta_bit(Bitmap* bitmap, int i) {
  bitmap->bit[i / 32] |= 1 << (i % 32);
}

/* bitmap->bit[i / 32] acessa o i-ésimo uint32_t
 * ~(1 << (i % 32)) cria uma máscara com o bit (i % 32) zerado e os outros bits setados
 * &= faz um AND bit a bit entre o i-ésimo uint32_t e a máscara
 * Isso limpa o bit (i % 32) do i-ésimo uint32_t
 */
void limpa_bit(Bitmap* bitmap, int i) {
  bitmap->bit[i / 32] &= ~(1 << (i % 32));
}

/* bitmap->bit[i / 32] acessa o i-ésimo uint32_t
 * bitmap->bit[i / 32] >> (i % 32) move o bit (i % 32) para a posição mais à direita
 * & 1 retorna 1 se o bit mais à direita for 1 e 0 se for 0
 * Isso verifica o bit (i % 32) do i-ésimo uint32_t
 */
int verifica_bit(Bitmap* bitmap, int i) {
  return (bitmap->bit[i / 32] >> (i % 32)) & 1;
}





// Funções de escrita e leitura de bitmap em arquivo

void salva_bitmap_em_arquivo(Bitmap* bitmap, const char* arquivo_bitmap) {
  FILE* fp = fopen(arquivo_bitmap, "wb");
  if (fp == NULL) {
    printf("Erro ao abrir arquivo %s.\n", arquivo_bitmap);
    return;
  }
  fwrite(bitmap->bit, sizeof(uint32_t), MAX_BLOCOS / 32, fp);
  fclose(fp);
}

Bitmap* le_bitmap_do_arquivo(Bitmap* bitmap, const char* arquivo_bitmap) {
  FILE* fp = fopen(arquivo_bitmap, "rb");
  if (fp == NULL) {
    printf("Erro ao abrir arquivo %s.\n", arquivo_bitmap);
    return NULL;
  }
  fread(bitmap->bit, sizeof(uint32_t), MAX_BLOCOS / 32, fp);
  fclose(fp);
  return bitmap;
}

void imprime_bitmap(Bitmap* bitmap) {
  printf("\nBitmap: ");
  for (int i = 0; i < MAX_BLOCOS_INT32; i++) {
    for (int j = 0; j < 32; j++) {
      printf("%d", (bitmap->bit[i] >> j) & 1);
    }
  }
  printf("\n");
}




// Funções de verificação de espaço livre

int verifica_espaco_para_arquivo(Bitmap* bitmap, int tamanho) {
  // tamanho é o tamanho do arquivo em bytes
  int blocos_necessarios = ceil((float) tamanho / TAM_BLOCO);
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