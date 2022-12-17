#pragma once

#include <cmath>
#include "objeto.h"
#include "algebraLinear.h"

using namespace std

;class Esfera : public Objeto {
public:
  double raio;
  Vetor centro;

  AlgebraLinear al;

  Esfera();
  Esfera(double raio, Vetor centro, Vetor Ke, Vetor Kd, Vetor Ka, double shininess);

  Vetor calcularNormal(Vetor posicao) override;

  bool verificarIntersecao(Vetor p0, Vetor dr) override;
  // Vetor buscarCor(Vetor pi, vector<Iluminacao*> luzes, vector<Objeto*> objetos, Vetor p0, Vetor dr, Vetor luzAmbiente, int index) override;

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
