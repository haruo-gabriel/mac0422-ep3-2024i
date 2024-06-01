#include "ep3.h"

int converte_bytes_para_blocos(int bytes) {
  return (int) ceil((float) bytes / (float) TAM_BLOCO);
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

void imprime_fat(FATNode* fat, const char* nome_fat) {
  printf("\n%s:\n", nome_fat);
  for (int i = 0; i < MAX_BLOCOS; i++) {
    printf("%2d -> %2d\n", i, fat[i].prox);
  }
}

void imprime_fat_bitmap(FATNode* fat, Bitmap* bitmap) {
  printf("\nBITMAP | FAT:\n");
  for (int i = 0; i < MAX_BLOCOS; i++) {
    printf("%6d | %2d -> %2d\n", verifica_bit(bitmap, i), i, fat[i].prox);
  }
}