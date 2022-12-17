#pragma once

#include "vetor.h"

class AlgebraLinear {
public:
  AlgebraLinear();
  double produtoEscalar(Vetor v1, Vetor v2);
  Vetor vetorMultEscalar(Vetor v, double e);
  Vetor vetorDivEscalar(Vetor v, double e);
  Vetor arroba (Vetor i1, Vetor i2);
  Vetor soma (Vetor i1, Vetor i2);
  Vetor multEscalar (Vetor i, double e);
  Vetor vetorSomaVetor(Vetor v, Vetor p);
  Vetor vetorSubVetor(Vetor p1, Vetor p2);
  double norma (Vetor v);
  Vetor produtoVetorial(Vetor v1, Vetor v2);


  Vetor rotacionarX(Vetor a, double angulo);
  Vetor rotacionarY(Vetor a, double angulo);
  Vetor rotacionarZ(Vetor a, double angulo);
  Vetor translacao(Vetor a, double x, double y, double z);
  Vetor escala(Vetor a, double sx, double sy, double sz);
  Vetor espelhamentoXY(Vetor a);
  Vetor espelhamentoXZ(Vetor a);
  Vetor espelhamentoYZ(Vetor a);
  Vetor cisalhamentoYX(Vetor a, double angulo);
  Vetor cisalhamentoXY(Vetor a, double angulo);
  Vetor cisalhamentoXZ(Vetor a, double angulo);
  Vetor cisalhamentoZX(Vetor a, double angulo);
  Vetor cisalhamentoYZ(Vetor a, double angulo);
  Vetor cisalhamentoZY(Vetor a, double angulo);
};