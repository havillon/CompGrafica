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

//1 - ponto
//0 - vetor
//transformações

Vetor AlgebraLinear::rotacionarX(Vetor a, double angulo) {
    return Vetor(
        a.x,
        a.y*cos(angulo) - a.z*sin(angulo),
        a.y*sin(angulo) + a.z*cos(angulo),
        a.w
    );
}

Vetor AlgebraLinear::rotacionarZ(Vetor a, double angulo) {
    return Vetor(
        a.x*cos(angulo) - a.y*sin(angulo),
        a.x*sin(angulo) + a.y*cos(angulo),
        a.z,
        a.w
    );
}

Vetor AlgebraLinear::rotacionarY(Vetor a, double angulo) {
    return Vetor(
        a.x*cos(angulo) + a.z*sin(angulo),
        a.y,
        -a.x*sin(angulo) + a.z*cos(angulo),
        a.w
    );
}

Vetor AlgebraLinear::translacao(Vetor a, double x, double y, double z) {
    return Vetor(
        a.x + x,
        a.y + y,
        a.z + z,
        a.w
    );
}

Vetor AlgebraLinear::escala(Vetor a, double sx, double sy, double sz) {
    return Vetor(
        a.x * sx,
        a.y * sy,
        a.z * sz,
        a.w
    );
}

Vetor AlgebraLinear::espelhamentoXY(Vetor a) {
    return Vetor(
        a.x,
        a.y,
        -a.z,
        a.w
    );
}

Vetor AlgebraLinear::espelhamentoXZ(Vetor a) {
    return Vetor(
        a.x,
        -a.y,
        a.z,
        a.w
    );
}

Vetor AlgebraLinear::espelhamentoYZ(Vetor a) {
    return Vetor(
        -a.x,
        a.y,
        a.z,
        a.w
    );
}

Vetor AlgebraLinear::cisalhamentoYX(Vetor a, double angulo) {
    return Vetor(
        a.x + a.y * tan(angulo),
        a.y,
        a.z,
        a.w
    );
}

Vetor AlgebraLinear::cisalhamentoXY(Vetor a, double angulo) {
    return Vetor(
        a.x,
        a.y + a.x * tan(angulo),
        a.z,
        a.w
    );
}

Vetor AlgebraLinear::cisalhamentoXZ(Vetor a, double angulo) {
    return Vetor(
        a.x,
        a.y,
        a.z + a.x * tan(angulo),
        a.w
    );
}

Vetor AlgebraLinear::cisalhamentoZX(Vetor a, double angulo) {
    return Vetor(
       a.x + a.z * tan(angulo),
       a.y,
       a.z,
       a.w
    );
}

Vetor AlgebraLinear::cisalhamentoYZ(Vetor a, double angulo) {
    return Vetor(
        a.x,
        a.y,
        a.z + a.y * tan(angulo),
        a.w
    );
}

Vetor AlgebraLinear::cisalhamentoZY(Vetor a, double angulo) {
    return Vetor(
        a.x,
        a.y + a.z * tan(angulo),
        a.z,
        a.w
    );
}