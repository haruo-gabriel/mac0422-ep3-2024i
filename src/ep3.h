#ifndef EP3_H
#define EP3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <readline/readline.h>
#include <math.h>
#include <libgen.h>
#include <time.h>
#include <stdbool.h>

// CONSTANTES

#define MAX_ARGS 3
#define TAM_BLOCO 4096 // Tamanho de um bloco (4KB) em bytes
// #define TAM_DISCO 104857600   // Tamanho do disco (100MB) em bytes
#define TAM_DISCO 1048576 // Tamanho do disco (1MB) em bytes
#define MAX_BLOCOS (TAM_DISCO / TAM_BLOCO) // Número máximo de blocos
// #define MAX_BLOCOS 33
#define LIVRE -1 // Bloco livre
#define FIM_ARQUIVO -2 // FIM_ARQUIVO da cadeia de blocos de um arquivo
#define MAX_PATH 255
#define MAX_NOME 100

// VARIÁVEIS GLOBAIS

extern bool g_montado;
extern char* g_arquivo_disco;

// STRUCTS

typedef struct {
  uint8_t* bit;
} Bitmap;

typedef struct {
  int prox;
} FATNode;

typedef struct Arquivo Arquivo;
typedef struct Diretorio Diretorio;

struct Arquivo {
  char nome[MAX_NOME];
  int tamanho; // Tamanho do arquivo em bytes
  time_t criado;
  time_t modificado;
  time_t acessado;
  bool eh_diretorio;
  Diretorio* conteudo;
};

struct Diretorio {
  Arquivo* arquivos;
  int num_arquivos;
  Diretorio* pai;
};


// UTILS

int converte_bytes_para_blocos(int bytes);
int converte_blocos_para_bytes(int blocos);
void imprime_bitmap(Bitmap* bitmap);
void imprime_fat(FATNode* fat, const char* nome_fat);
void imprime_fat_bitmap(FATNode* fat, Bitmap* bitmap);

// PROMPT

void parse_comando(const char *comando, char *args[], int *num_args);
int valida_comando(char* args[], int num_args);
void executa_comando(char* args[]);
void prompt();

// COMANDOS

int monta(const char* arquivo);
// int criadir(char***);
// int apagadir(char***);
// int mostra(char***);
// int toca(char***);
// int apaga(char***);
// int lista(char***);
// int atualizadb(char***);
// int busca(char***);
// int status(char***);
int desmonta();
int sai();

// BITMAP

Bitmap* inicializa_bitmap();
void seta_bit(Bitmap* bitmap, int i);
void limpa_bit(Bitmap* bitmap, int i);
int verifica_bit(Bitmap* bitmap, int i);
void salva_bitmap_em_arquivo(Bitmap* bitmap, const char* arquivo_bitmap);
Bitmap* le_bitmap_do_arquivo(Bitmap* bitmap, const char* arquivo_bitmap);
int possui_espaco_para_arquivo(Bitmap* bitmap, int tamanho);
int encontra_primeiro_bloco_livre(Bitmap* bitmap);

// FAT

FATNode* inicializa_fat();
int aloca_arquivo(FATNode* fat, Bitmap* bitmap, int tamanho);
int deleta_arquivo(FATNode* fat, Bitmap* bitmap, int bloco_inicial);
void salva_fat_em_arquivo(FATNode* fat, const char* arquivo_fat);
FATNode* le_fat_do_arquivo(const char* arquivo_fat);

// ARQUIVOS
Diretorio* acha_diretorio(const char* nome_diretorio);

#endif