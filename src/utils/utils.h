#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../globais/configuracao.h"
#include "../tipos/obra.h"
#include "../tipos/pagina.h"
#include "../tipos/registro.h"

Obra cria_obra_vazia();
Pagina cria_pagina_vazia();
Registro cria_registro_vazio();

Obra *le_obra_da_entrada();
void le_entrada_com_espacos(char *entrada);
