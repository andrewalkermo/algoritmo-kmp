#include "kmp.h"

int* cria_tabela_pi_de_palavra(char *palavra) {
  int *tabela_pi = (int*) malloc(sizeof(int) * strlen(palavra));
  int i;

  for (i = 0; i < strlen(palavra); i++) {
    tabela_pi[i] = -1;
  }

  for (i = 0; i < strlen(palavra); i++) {

    if (i == 0) {
      continue;
    }

    else if (palavra[i] == palavra[tabela_pi[i - 1] + 1]) {
      tabela_pi[i] = tabela_pi[i - 1] + 1;
    }

    else {
      int indice_pi = tabela_pi[i - 1];
      while (indice_pi >= 0 && palavra[i] != palavra[indice_pi + 1]) {
        indice_pi = tabela_pi[indice_pi];
        if (palavra[i] == palavra[indice_pi + 1]) {
          tabela_pi[i] = indice_pi + 1;
        }
      }
    }
  }
  for (i = 0; i < strlen(palavra); i++)
  {
    tabela_pi[i]++;
  }
  return tabela_pi;
}
