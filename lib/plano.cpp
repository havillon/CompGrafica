#include "../include/plano.h"

Plano::Plano(){}

Plano::Plano(Vetor p_pi, Vetor n_pi, Vetor Ke, Vetor Kd, Vetor Ka, double shininess){
  this->p_pi = p_pi;
  this->n_pi = n_pi;
  this->setKe(Ke);
  this->setKd(Kd);
  this->setKa(Ka);
  this->setShininess(shininess);
}

bool Plano::verificarIntersecao(Vetor p0, Vetor dr){
  AlgebraLinear al;
  Vetor w = al.vetorSubVetor(p0, this->p_pi);
  double drEscalarN = al.produtoEscalar(dr, this->n_pi);

  if(drEscalarN == 0){
    return false;
  }

  double wEscalarN = al.produtoEscalar(w, this->n_pi);

  double t = (-wEscalarN)/drEscalarN;

  if(t < 0.0001){
    return false;
  }

  Vetor pi = al.soma(p0, al.vetorMultEscalar(dr, t));

  double distancia = al.norma(al.vetorSubVetor(pi, p0));

  this->setDistancia(distancia);
  this->setPontoIntersecao(pi);

  return true;
  
}

Vetor Plano::calcularNormal(Vetor posicao){
  return this->n_pi;
}

void Plano::rotacionarX(double angulo){
  p_pi = al.rotacionarX(p_pi, angulo);
  n_pi = al.rotacionarX(n_pi, angulo);
}

void Plano::rotacionarY(double angulo){
  p_pi = al.rotacionarY(p_pi, angulo);
  n_pi = al.rotacionarY(n_pi, angulo);
}

void Plano::rotacionarZ(double angulo){
  p_pi = al.rotacionarZ(p_pi, angulo);
  n_pi = al.rotacionarZ(n_pi, angulo);
}

void Plano::translacao(double x, double y, double z){
  p_pi = al.translacao(p_pi, x, y, z);
}

void Plano::escala(double sx, double sy, double sz){
  p_pi = al.escala(p_pi, sx, sy, sz);
}

void Plano::espelhamentoXY(){
  p_pi = al.espelhamentoXY(p_pi);
  n_pi = al.espelhamentoXY(n_pi);
}

void Plano::espelhamentoXZ(){
  p_pi = al.espelhamentoXZ(p_pi);
  n_pi = al.espelhamentoXZ(n_pi);
}

void Plano::espelhamentoYZ(){
  p_pi = al.espelhamentoYZ(p_pi);
  n_pi = al.espelhamentoYZ(n_pi);
}

//nada acontece aqui
void Plano::cisalhamentoYX(double angulo){}
void Plano::cisalhamentoXY(double angulo){}
void Plano::cisalhamentoXZ(double angulo){}
void Plano::cisalhamentoZX(double angulo){}
void Plano::cisalhamentoYZ(double angulo){}
void Plano::cisalhamentoZY(double angulo){}