#include "utils.h"

// cria a pagina e inicializa com registros vazios a quantidade maxima de registros
Pagina cria_pagina_vazia() {
    Pagina pagina;
    pagina.qtdRegistros = 0;
    pagina.proxima = -1;
    for (int i = 0; i < NREGSPORPAGINA; i++) {
        pagina.registros[i] = cria_registro_vazio();
    }
    return pagina;
}

Registro cria_registro_vazio() {
    Registro registro;
    registro.ocupado = false;
    registro.obra = cria_obra_vazia();
    return registro;
}

Obra cria_obra_vazia() {
    Obra obra;
    obra.autor[0] = '\0';
    obra.nome[0] = '\0';
    obra.ano = 0;
    obra.arquivo[0] = '\0';
    return obra;
}

void le_entrada_com_espacos(char *entrada) {

    fgets(entrada, TAMANHO_NOME, stdin);

    if (entrada[0] == '\n') {
        return le_entrada_com_espacos(entrada);
    }

    if ((strlen(entrada) > 0) && (entrada[strlen (entrada) - 1] == '\n')) {
        entrada[strlen (entrada) - 1] = '\0';
    }
}

// aloca o espaço na memória para a struct de obra e faz leitura de registros da entrada
Obra *le_obra_da_entrada() {
    Obra *obra = (Obra*) malloc(sizeof(Obra));
    le_entrada_com_espacos(obra->autor);
    le_entrada_com_espacos(obra->nome);
    scanf("%u", &obra->ano);
    scanf("%s", obra->arquivo);
    return obra;
}
