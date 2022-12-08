#ifndef ALGEBRALINEAR_H
#define ALGEBRALINEAR_H

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
};

#endif