#pragma once

#include <iostream>
#include <cmath>
#include <limits>
#include "../include/algebraLinear.h"
#include "../include/objeto.h"

using namespace std;

class Cone : public Objeto{
public:
    double altura, raio;
    Vetor centroBase, direcao;

    //0 -> base
    //1 -> corpo
    int flagIntersecao;
    
    AlgebraLinear al;

    Cone();
    Cone(double altura, double raio, Vetor centroBase, Vetor direcao);

    bool verificarIntersecao(Vetor p0, Vetor dr) override;
    Vetor calcularNormal(Vetor posicao) override;
    void rotacionarX(double angulo) override;
    void rotacionarY(double angulo) override;
    void rotacionarZ(double angulo) override;
    void translacao(double x, double y, double z) override;
    void escala(double sx, double sy, double sz) override;
    void espelhamentoXY() override;
    void espelhamentoXZ() override;
    void espelhamentoYZ() override;
    void cisalhamentoYX(double angulo) override;
    void cisalhamentoXY(double angulo) override;
    void cisalhamentoXZ(double angulo) override;
    void cisalhamentoZX(double angulo) override;
    void cisalhamentoYZ(double angulo) override;
    void cisalhamentoZY(double angulo) override;
};