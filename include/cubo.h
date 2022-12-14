#pragma once

#include "malha.h"

class Cubo {
public:
    Malha criarCubo(Vetor centroBase, double comprimentoAresta, Vetor Ka, Vetor Kd, Vetor Ke, double shininess);
};