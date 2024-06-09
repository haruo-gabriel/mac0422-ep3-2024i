#include "minunit.h"
#include "../src/ep3.h"

MU_TEST(test_inicializa_bitmap) {
  Bitmap* bitmap = inicializa_bitmap();
  int blocos = ceil((float) MAX_BLOCOS / 8);
  for (int i = 0; i < blocos; i++) {
    mu_check(bitmap->bit[i] == 0);
  }
  imprime_bitmap(bitmap);
  free(bitmap);
}

MU_TEST(test_seta_bit) {
  Bitmap* bitmap = inicializa_bitmap();
  seta_bit(bitmap, 10);
  mu_check(verifica_bit(bitmap, 10) == 1);
  free(bitmap);
}

MU_TEST(test_limpa_bit) {
  Bitmap* bitmap = inicializa_bitmap();
  seta_bit(bitmap, 10);
  limpa_bit(bitmap, 10);
  mu_check(verifica_bit(bitmap, 10) == 0);
  free(bitmap);
}

MU_TEST(test_salva_le_bitmap) {
  Bitmap* bitmap1 = inicializa_bitmap();
  seta_bit(bitmap1, 10);
  salva_bitmap_em_arquivo(bitmap1, "./testes/test_bitmap.bin");

  Bitmap* bitmap2 = inicializa_bitmap();
  le_bitmap_do_arquivo(bitmap2, "./testes/test_bitmap.bin");

  int blocos = ceil((float) MAX_BLOCOS / 8);

  mu_check(memcmp(bitmap1->bit, bitmap2->bit, sizeof(uint8_t) * blocos) == 0);

  free(bitmap1);
  free(bitmap2);
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_inicializa_bitmap);
  MU_RUN_TEST(test_seta_bit);
  MU_RUN_TEST(test_limpa_bit);
  MU_RUN_TEST(test_salva_le_bitmap);
}

int main() {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}