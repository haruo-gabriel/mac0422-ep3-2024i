#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

// #define MAX_TOKENS 3
#define NUM_COMANDOS_VALIDOS 1
#define MAX_ARGS 3

// typedef struct {
//   char* arg0, arg1, arg2;
// } comando;


int conta_tokens(const char *, const char *);
int parse_comando(const char *, char ***);
int valida_comando(char***);
int processa_comando(char***);

int monta(char***);
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
// int sai(char***);