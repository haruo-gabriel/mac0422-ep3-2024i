CC=g++
CFLAGS=-I. -Wall -Wextra -std=c++11
DEPS = src/ep3.h minunit.h
OBJ = testes/testes-bitmap.o src/bitmap.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

testes/testa-bitmap: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: testes/testa-bitmap
	./testes/testa-bitmap

clean:
	rm -f src/*.o testes/*.o testes/testa-bitmap /testes/test_bitmap.bin