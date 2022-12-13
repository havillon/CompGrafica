#pragma once

#include <iostream>
#include <cmath>
#include <limits>
#include "../include/algebraLinear.h"
#include "../include/objeto.h"

using namespace std;

class Cilindro : public Objeto{
public:
    double altura, raio;
    Vetor centroBase, direcao;

    //0 -> base
    //1 -> corpo
    //2 -> topo
    int flagIntersecao;
    
    AlgebraLinear al;

    Cilindro();
    Cilindro(double altura, double raio, Vetor centroBase, Vetor direcao);

    bool verificarIntersecao(Vetor p0, Vetor dr) override;
    Vetor calcularNormal(Vetor posicao) override;
};