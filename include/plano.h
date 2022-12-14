#pragma once

#include <cmath>
#include "objeto.h"
#include "algebraLinear.h"
#include "iluminacao.h"

using namespace std;

class Plano : public Objeto {

public:
  Vetor p_pi;
  Vetor n_pi;
  Plano();
  Plano(Vetor p_pi, Vetor n_pi, Vetor Ke, Vetor Kd, Vetor Ka, double shininess);

  Vetor calcularNormal(Vetor posicao) override;
  bool verificarIntersecao(Vetor p0, Vetor dr) override;
  // Vetor buscarCor(Vetor pi, vector<Iluminacao*> luzes, vector<Objeto*> objetos, Vetor p0, Vetor dr, Vetor luzAmbiente, int index) override;
};