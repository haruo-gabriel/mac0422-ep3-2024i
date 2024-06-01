#include "minunit.h"
#include "src/ep3.h"

MU_TEST(test_inicializa_fat) {
  printf("\n\n\nOn test_inicializa_fat\n");
  FATNode* fat = inicializa_fat();
  mu_assert(fat != NULL, "Error: FAT initialization failed.");
  for (int i = 0; i < MAX_BLOCOS; i++) {
    mu_assert(fat[i].prox == LIVRE, "Error: FAT block not initialized correctly.");
  }
  free(fat);
}

MU_TEST(test_aloca_arquivo) {
  printf("\n\n\nOn test_aloca_arquivo\n");

  FATNode* fat = inicializa_fat();
  Bitmap* bitmap = inicializa_bitmap();
  int tamanho_arquivo = TAM_BLOCO * 5;  // 5 blocks

  // Alocate the first file
  int result = aloca_arquivo(fat, bitmap, tamanho_arquivo);
  mu_assert(result >= 0, "Error: File allocation failed.");
  int blocos_alocados = 0;
  for (int i = 0; i < MAX_BLOCOS; i++) {
    if (verifica_bit(bitmap, i) == 1) {
      blocos_alocados++;
    }
  }
  mu_assert(blocos_alocados == 5, "Error: Incorrect number of blocks allocated.");
  // imprime_fat_bitmap(fat, bitmap);

  // Alocate a second file that is too big
  result = aloca_arquivo(fat, bitmap, TAM_BLOCO * 30);  // 30 blocks
  mu_assert(result == -1, "Error: File allocation succeeded when it should have failed.");

  // Allocate a second file that fits
  result = aloca_arquivo(fat, bitmap, TAM_BLOCO * 10);  // 10 blocks
  mu_assert(result >= 0, "Error: File allocation failed.");
  int blocos_alocados2 = 0;
  for (int i = 0; i < MAX_BLOCOS; i++) {
    if (verifica_bit(bitmap, i) == 1) {
      blocos_alocados2++;
    }
  }
  mu_assert(blocos_alocados2 == 15, "Error: Incorrect number of blocks allocated.");

  // imprime_fat_bitmap(fat, bitmap);

  free(fat);
  free(bitmap);
}

MU_TEST(test_deleta_arquivo) {
  printf("\n\n\nOn test_deleta_arquivo\n");

  FATNode* fat = inicializa_fat();
  Bitmap* bitmap = inicializa_bitmap();
  int tamanho_arquivo = TAM_BLOCO * 5;  // 5 blocks

  // Allocate a file
  int bloco_inicial = aloca_arquivo(fat, bitmap, tamanho_arquivo);
  mu_assert(bloco_inicial >= 0, "Error: File allocation failed.");

  // imprime_fat_bitmap(fat, bitmap);

  // Delete the file
  int result = deleta_arquivo(fat, bitmap, bloco_inicial);
  mu_assert(result >= 0, "Error: File deletion failed.");

  // imprime_fat_bitmap(fat, bitmap);

  // Check that the blocks are free
  for (int i = bloco_inicial; i < bloco_inicial + 5; i++) {
    mu_assert(verifica_bit(bitmap, i) == 0, "Error: Block not freed.");
    mu_assert(fat[i].prox == LIVRE, "Error: FAT node not freed.");
  }

  free(fat);
  free(bitmap);
}

MU_TEST(test_salva_le_fat) {
  printf("\n\n\nOn test_salva_le_fat\n");

  FATNode* fat1 = inicializa_fat();
  Bitmap* bitmap = inicializa_bitmap();
  int tamanho_arquivo = TAM_BLOCO * 5;  // 5 blocks

  // Allocate a file
  int bloco_inicial = aloca_arquivo(fat1, bitmap, tamanho_arquivo);
  mu_assert(bloco_inicial >= 0, "Error: File allocation failed.");

  // Save the FAT to a file
  salva_fat_em_arquivo(fat1, "./testes/test_fat.bin");

  // Load the FAT from the file
  FATNode* fat2 = le_fat_do_arquivo("./testes/test_fat.bin");
  mu_assert(fat2 != NULL, "Error: FAT loading failed.");

  // Check that the FATs are equal
  mu_assert(memcmp(fat1, fat2, sizeof(FATNode) * MAX_BLOCOS) == 0, "Error: FATs are not equal.");

  // Print the FATs
  // imprime_fat(fat1, "FAT 1");
  // imprime_fat(fat2, "FAT 2");

  free(fat1);
  free(fat2);
  free(bitmap);
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_inicializa_fat);
  MU_RUN_TEST(test_aloca_arquivo);
  MU_RUN_TEST(test_deleta_arquivo);
  MU_RUN_TEST(test_salva_le_fat);
}

int main() {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}