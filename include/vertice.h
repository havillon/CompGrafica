#pragma once

#include "algebraLinear.h"

class Vertice {
public:
    Vetor ponto;
    Vetor normal;

    Vertice();
    Vertice(Vetor ponto, Vetor normal);
};