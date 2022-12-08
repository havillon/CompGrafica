#pragma once

#include "algebraLinear/vetor.h"

class Janela {
public:
    int wJanela, hJanela, nLinhas, nColunas;
    Vetor centro;
    double distancia;

    Janela(Vetor centro, int wJanela, int hJanela, int nLinhas, int nColunas, double distancia);
};
