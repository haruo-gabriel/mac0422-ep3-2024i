#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <readline/readline.h>
#include <math.h>

// FUNÇÕES DO PROMPT
#define MAX_ARGS 3

void parse_comando(const char *comando, char *args[], int *num_args);
int valida_comando(char* args[], int num_args);
void executa_comando(char* args[]);
void prompt();

// FAT
#define TAM_BLOCO 4000 // Tamanho de um bloco (4KB) em bytes
#define TAM_DISCO 1000000000  // Tamanho do disco (100MB) em bytes
// #define MAX_BLOCOS (TAM_DISCO / TAM_BLOCO) // Número máximo de blocos
#define MAX_BLOCOS 33
#define LIVRE -1 // Bloco livre
#define FIM -2 // Fim da cadeia de blocos de um arquivo

typedef struct {
  int prox;
} FATNode;

FATNode* inicializa_fat();
int aloca_arquivo(FATNode* fat, Bitmap* bitmap, int tamanho);
void salva_fat_em_arquivo(FATNode* fat);
FATNode* le_fat_do_arquivo(FATNode* fat, const char* arquivo_fat);

// BITMAP
#define MAX_BLOCOS_INT32 ((int) ceil((float) MAX_BLOCOS / (float) 32)) // Número máximo de uint32_t necessários para representar todos os blocos

typedef struct {
  uint32_t bit[MAX_BLOCOS / 32]; // Cada uint32_t possui 32 bits
} Bitmap;

Bitmap* inicializa_bitmap();
void seta_bit(Bitmap* bitmap, int i);
void limpa_bit(Bitmap* bitmap, int i);
int verifica_bit(Bitmap* bitmap, int i);
void salva_bitmap_em_arquivo(Bitmap* bitmap, const char* arquivo_bitmap);
Bitmap* le_bitmap_do_arquivo(Bitmap* bitmap, const char* arquivo_bitmap);
void imprime_bitmap(Bitmap* bitmap);
int verifica_espaco_para_arquivo(Bitmap* bitmap, int tamanho);

// COMANDOS
int monta(char dir);
// int criadir(char***);
// int apagadir(char***);
// int mostra(char***);
// int toca(char***);
// int apaga(char***);
// int lista(char***);
// int atualizadb(char***);
// int busca(char***);
// int status(char***);
// int desmonta(char***);
int sai();