#include "kmp.h"

int* cria_tabela_pi_de_palavra(char *palavra) {
  int *tabelaPi = (int*) malloc(sizeof(int) * strlen(palavra));
  int i;

  // inicializa a tabela pi com -1 em todas as posicoes
  for (i = 0; i < strlen(palavra); i++) {
    tabelaPi[i] = -1;
  }

  for (i = 0; i < strlen(palavra); i++) {
    // se for o primeiro indice, mantem o valor da tabela
    // nao tem nenhum prefixo igual ao sufixo antes do primeiro elemento
    if (i == 0) {
      continue;
    }
    // confere se e possivel estender o maior prefixo igual a sufixo
    // verificando se o caracter na posicao do indice i da palavra corresponde ao caracter da palavra na posicao do valor do [indice i - 1] da tabela pi  +1
    // incrementa o valor da tabela pi na posicao i
    else if (palavra[i] == palavra[tabelaPi[i - 1] + 1]) {
      tabelaPi[i] = tabelaPi[i - 1] + 1;
    }

    else {
      int indicePi = tabelaPi[i - 1];
      // verifica se e possivel estender o proximo maior prefixo igual ao sufixo utilizando o valor da tabela pi para o valor da posicao i -1 na palavra
      // o processo e repetido no loop ate ser possivel estender um prefixo igual ao sufixo
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
  // abre o arquivo
  FILE *arquivo = abre_arquivo(nomeArquivo, "r");

  char caractere;
  // cria a tabela pi para a palavra digitada
  int *tabelaPi = cria_tabela_pi_de_palavra(palavra);

  int indicePalavra = 0;

  // faz a leitura do arquivo
  // compara os caracteres do arquivo com a palavra
  // verifica se o tamanho da palavra corresponde ao valor do indicePalavra, caso seja, retorna verdadeira pois a palavra esta no arquivo
  while ((caractere = (char) fgetc(arquivo)) != EOF) {
    compara_caractere_com_palavra(caractere, palavra, tabelaPi, &indicePalavra);
    if (indicePalavra == strlen(palavra)) {
      return true;
    }
  }
  return false;
}

void compara_caractere_com_palavra(char caractere, const char *palavra, const int *tabelaPi, int *indicePalavra) {
  // verifica se o caracterer do arquivo corresponde ao caracter da palavra na posicao indecePalavra, caso sim, incrementa o valor do indicePalavra
  // caso nao corresponda mas o indice seja > 0, atualiza o indice para o valor da [tabela pi no indice atual - 1] + 1 compara novamente recursivamente
  if (caractere == palavra[*indicePalavra]) {
    (*indicePalavra)++;
  }
  else if (*indicePalavra > 0) {
    *indicePalavra = tabelaPi[*indicePalavra - 1] + 1;
    compara_caractere_com_palavra(caractere, palavra, tabelaPi, indicePalavra);
  } else {
  }
}

void imprime_ocorrencia_da_palavra_na_obra(Obra *obra, char *palavra) {
  FILE *arquivo = abre_arquivo(obra->arquivo, "r");

  char caractere;
  // cria a tabela pi para a palavra digitada
  int *tabelaPi = cria_tabela_pi_de_palavra(palavra);

  int indicePalavra = 0;
  int linha = 1;
  int posicao = 0;

  printf("ocorrencia(s) da palavra: %s:\n", palavra);
  // faz a leitura do arquivo
  // verifica se a linha e vazia, caso seja a posicao e 0 porque nao caracteres
  // caso nao seja incrementa a posicao
  while ((caractere = (char) fgetc(arquivo)) != EOF) {
    if (caractere == '\n') {
      linha++;
      posicao = 0;
      indicePalavra = 0;
    }
    else {
      posicao++;
    }
  // compara os caracteres do arquivo com a palavra
  // verifica se o tamanho da palavra corresponde ao valor do indicePalavra, caso seja, imprime a linha e a posicao da palavra no arquivo
    compara_caractere_com_palavra(caractere, palavra, tabelaPi, &indicePalavra);
    if (indicePalavra == strlen(palavra)) {
      printf("linha: %d posicao: %lu\n", linha, (posicao - strlen(palavra) + 1));
      indicePalavra = tabelaPi[indicePalavra - 1] + 1;
    }
  }
}