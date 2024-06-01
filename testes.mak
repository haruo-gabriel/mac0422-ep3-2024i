CC=g++
CFLAGS=-I. -Wall -Wextra -std=c++11
DEPS = src/ep3.h minunit.h
OBJ_BITMAP = testes/testes-bitmap.o src/bitmap.o src/utils.o
OBJ_FAT = testes/testes-fat.o src/fat.o src/bitmap.o src/utils.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

testes/testa-bitmap: $(OBJ_BITMAP)
	$(CC) -o $@ $^ $(CFLAGS)

testes/testa-fat: $(OBJ_FAT)
	$(CC) -o $@ $^ $(CFLAGS)

run-bitmap: testes/testa-bitmap
	./testes/testa-bitmap

run-fat: testes/testa-fat
	./testes/testa-fat

clean:
	rm -f src/*.o testes/*.o testes/testa-bitmap testes/testa-fat
	rm -f testes/test_bitmap.bin testes/test_fat.bin