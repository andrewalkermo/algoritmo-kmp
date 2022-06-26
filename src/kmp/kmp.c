#include "kmp.h"

int* cria_tabela_pi_de_palavra(char *palavra) {
  int *tabelaPi = (int*) malloc(sizeof(int) * strlen(palavra));
  int i;

  for (i = 0; i < strlen(palavra); i++) {
    tabelaPi[i] = -1;
  }

  for (i = 0; i < strlen(palavra); i++) {

    if (i == 0) {
      continue;
    }

    else if (palavra[i] == palavra[tabelaPi[i - 1] + 1]) {
      tabelaPi[i] = tabelaPi[i - 1] + 1;
    }

    else {
      int indicePi = tabelaPi[i - 1];
      while (indicePi >= 0 && palavra[i] != palavra[indicePi + 1]) {
        indicePi = tabelaPi[indicePi];
        if (palavra[i] == palavra[indicePi + 1]) {
          tabelaPi[i] = indicePi + 1;
        }
      }
    }
  }

  return tabelaPi;
}

bool arquivo_contem_palavra(char *nomeArquivo, char *palavra) {
  FILE *arquivo = abre_arquivo(nomeArquivo, "r");

  char caractere;
  int *tabelaPi = cria_tabela_pi_de_palavra(palavra);

  int indicePalavra = 0;

  while ((caractere = (char) fgetc(arquivo)) != EOF) {
    compara_caractere_com_palavra(caractere, palavra, tabelaPi, &indicePalavra);
    if (indicePalavra == strlen(palavra)) {
      return true;
    }
  }
  return false;
}

void compara_caractere_com_palavra(char caractere, const char *palavra, const int *tabelaPi, int *indicePalavra) {
  if (caractere == palavra[*indicePalavra]) {
//    printf("LOG: Caractere %c corresponde a palavra %s - indice: %d\n", caractere, palavra, *indicePalavra);
    (*indicePalavra)++;
  }
  else if (*indicePalavra > 0) {
//    printf("LOG: Caractere %c não corresponde a palavra %s - indice: %d\n", caractere, palavra, *indicePalavra);
    *indicePalavra = tabelaPi[*indicePalavra - 1] + 1;
    compara_caractere_com_palavra(caractere, palavra, tabelaPi, indicePalavra);
  } else {
//    printf("LOG: Caractere %c não corresponde a palavra %s - indice: %d\n", caractere, palavra, *indicePalavra);
  }
}

void imprime_ocorrencia_da_palavra_na_obra(Obra *obra, char *palavra) {
  FILE *arquivo = abre_arquivo(obra->arquivo, "r");

  char caractere;
  int *tabelaPi = cria_tabela_pi_de_palavra(palavra);

  int indicePalavra = 0;
  int linha = 1;
  int posicao = 0;

  printf("ocorrencia(s) da palavra: %s:\n", palavra);
  while ((caractere = (char) fgetc(arquivo)) != EOF) {
    if (caractere == '\n') {
      linha++;
      posicao = 0;
      indicePalavra = 0;
    }
    else {
      posicao++;
    }
    compara_caractere_com_palavra(caractere, palavra, tabelaPi, &indicePalavra);
    if (indicePalavra == strlen(palavra)) {
      printf("linha: %d posicao: %lu\n", linha, (posicao - strlen(palavra) + 1));
      indicePalavra = tabelaPi[indicePalavra - 1] + 1;
    }
  }
}