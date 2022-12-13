#include "../include/algebraLinear.h"
#include <cmath>

AlgebraLinear::AlgebraLinear(){}

double AlgebraLinear::produtoEscalar(Vetor v1, Vetor v2){
  return ((v1.v[0]*v2.v[0]) + (v1.v[1]*v2.v[1]) + (v1.v[2]*v2.v[2]));
}
 
Vetor AlgebraLinear::vetorMultEscalar(Vetor v, double e){
  return Vetor(v.v[0] * e, v.v[1] * e, v.v[2] * e, 1);
}

Vetor AlgebraLinear::vetorDivEscalar(Vetor v, double e){
  return Vetor(v.v[0]/e, v.v[1]/e, v.v[2]/e, 1);
}

Vetor AlgebraLinear::arroba(Vetor i1, Vetor i2){
  return Vetor(i1.v[0] * i2.v[0], i1.v[1] * i2.v[1], i1.v[2] * i2.v[2], 1);
}

Vetor AlgebraLinear::soma(Vetor i1, Vetor i2){
  return Vetor(i1.v[0] + i2.v[0], i1.v[1] + i2.v[1], i1.v[2] + i2.v[2], 1);
}

Vetor AlgebraLinear::multEscalar(Vetor i, double e){
  return Vetor(i.v[0] * e, i.v[1] * e, i.v[2] * e, 1);
}

Vetor AlgebraLinear::vetorSomaVetor(Vetor v, Vetor p){
  return Vetor(v.v[0] + p.v[0], v.v[1] + p.v[1], v.v[2] + p.v[2], 1);
}

Vetor AlgebraLinear::vetorSubVetor(Vetor p1, Vetor p2){
  return Vetor(p1.v[0] - p2.v[0], p1.v[1] - p2.v[1], p1.v[2] - p2.v[2], 1);
  }

double AlgebraLinear::norma(Vetor v){
  return sqrt(this->produtoEscalar(v,v));
}

Vetor AlgebraLinear::produtoVetorial(Vetor v1, Vetor v2){
  return Vetor(
    (v1.y * v2.z) - (v1.z * v2.y),
    (v1.z * v2.x) - (v1.x * v2.z),
    (v1.x * v2.y) - (v1.y * v2.x),
    0
  );
}

