#pragma once

#include <cmath>
#include "objeto.h"
#include "../algebraLinear/algebraLinear.h"

using namespace std

;class Esfera : public Objeto {
public:
  double raio;
  Vetor centro;  

  Esfera();
  Esfera(double raio, Vetor centro, Vetor Ke, Vetor Kd, Vetor Ka, double shininess);

  Vetor calcularNormal(Vetor posicao) override;

  bool verificarIntersecao(Vetor p0, Vetor dr) override;
  // Vetor buscarCor(Vetor pi, vector<Iluminacao*> luzes, vector<Objeto*> objetos, Vetor p0, Vetor dr, Vetor luzAmbiente, int index) override;

};
