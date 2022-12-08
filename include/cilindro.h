#pragma once

#include <cmath>
#include "objeto.h"
#include "algebraLinear.h"

using namespace std

class Cilindro : public Objeto {
public:
  double raio, altura;
  Vetor centroBase, centroTopo;
  Vetor dr;

  Cilindro();
  Cilindro(double raio, double altura, Vetor centroBase, Vetor centroTopo, Vetor dr, Vetor Ke, Vetor Kd, Vetor Ka, double shininess);

  Vetor calcularNormal(Vetor posicao) override;

  bool verificarIntersecao(Vetor p0, Vetor dr) override;
}
