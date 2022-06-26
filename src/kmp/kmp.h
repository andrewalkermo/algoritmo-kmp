#pragma once

#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "../globais/configuracao.h"
#include "../operacoes_arquivo/operacoes_arquivo.h"

int* cria_tabela_pi_de_palavra(char *palavra);
bool arquivo_contem_palavra(char *nomeArquivo, char *palavra);
void compara_caractere_com_palavra(char caractere, const char *palavra, const int *tabelaPi, int *indicePalavra);