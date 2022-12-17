#include "../include/esfera.h"

Esfera::Esfera(){};

Esfera::Esfera(double raio, Vetor centro, Vetor Ke, Vetor Kd, Vetor Ka, double shininess){
  this->raio = raio;
  this->centro = centro;
  this->setKe(Ke);
  this->setKd(Kd);
  this->setKa(Ka);
  this->setShininess(shininess);
};

Vetor Esfera::calcularNormal(Vetor posicao){
  AlgebraLinear al;
  return al.vetorDivEscalar(al.vetorSubVetor(posicao,this->centro), (this->raio));
}

bool Esfera::verificarIntersecao(Vetor p0, Vetor dr){
  
  AlgebraLinear al;

  Vetor w = al.vetorSubVetor(p0, centro);

  double a = al.produtoEscalar(dr,dr);
  double b = 2*al.produtoEscalar(w, dr);
  double c = al.produtoEscalar(w,w) - (this->raio*this->raio);
  
  double delta = (b*b) - (4*a*c);
  if(delta < 0){
    return false;
  }else{
    double t1 = (-b - sqrt(delta)) / (2*a);
    double t2 = (-b + sqrt(delta)) / (2*a);
    
    double t = max(min(t1,t2),0.0);

    if(t < 0.0001){
      return false;
    }
    
    Vetor pi = al.vetorSomaVetor(al.vetorMultEscalar(dr, t), p0);
    
    this->setDistancia(t);
    this->setPontoIntersecao(pi);

    return true;
    
  }
}

void Esfera::rotacionarX(double angulo){
  centro = al.rotacionarX(centro, angulo);
}

void Esfera::rotacionarY(double angulo){
  centro = al.rotacionarY(centro, angulo);
}

void Esfera::rotacionarZ(double angulo){
  centro = al.rotacionarZ(centro, angulo);
}

void Esfera::translacao(double x, double y, double z){
  centro = al.translacao(centro, x, y, z);
}

void Esfera::escala(double sx, double sy, double sz){
  centro = al.escala(centro, sx, sy, sz);
  raio = raio * max(sx,(max(sy,sz)));
}

void Esfera::espelhamentoXY(){
  centro = al.espelhamentoXY(centro);
}

void Esfera::espelhamentoXZ(){
  centro = al.espelhamentoXZ(centro);
}

void Esfera::espelhamentoYZ(){
  centro = al.espelhamentoYZ(centro);
}


//nada acontece aqui
void Esfera::cisalhamentoYX(double angulo){}
void Esfera::cisalhamentoXY(double angulo){}
void Esfera::cisalhamentoXZ(double angulo){}
void Esfera::cisalhamentoZX(double angulo){}
void Esfera::cisalhamentoYZ(double angulo){}
void Esfera::cisalhamentoZY(double angulo){}