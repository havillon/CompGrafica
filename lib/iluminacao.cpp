#include "../include/iluminacao.h"

LuzPontual::LuzPontual(Vetor intensidade, Vetor posicao){
  this->intensidade = intensidade;
  this->intensidadeOriginal = intensidade;
  this->posicao = posicao;
  this->tipo = 0;
  this->ligada = true; 
}

double LuzPontual::calcularDistancia(Vetor p, Vetor* l){
  Vetor pfMenosPi = al.vetorSubVetor(this->posicao, p);
  double normaPfMenosPi = al.norma(pfMenosPi);
  *l = al.vetorDivEscalar(pfMenosPi, normaPfMenosPi);
  return normaPfMenosPi;
}

LuzDirecional::LuzDirecional(Vetor intensidade, Vetor direcao){
  this->intensidade = intensidade;
  this->intensidadeOriginal = intensidade;
  this->direcao = direcao;
  this->tipo = 1;
  this->ligada = true;
}

double LuzDirecional::calcularDistancia(Vetor p, Vetor* l){
  *l = al.vetorDivEscalar(
    al.vetorMultEscalar(direcao, -1),
    al.norma(al.vetorMultEscalar(direcao, -1))
  );

  return (numeric_limits <double>::infinity());
}

LuzSpot::LuzSpot(Vetor intensidade, Vetor direcao, Vetor posicao, double angulo){
  this->intensidade = intensidade;
  this->intensidadeOriginal = intensidade;
  this->direcao = direcao;
  this->posicao = posicao;
  this->angulo = angulo;
  this->tipo = 2;
  this->ligada = true;
}

double LuzSpot::calcularDistancia(Vetor p, Vetor* l){
  *l = al.vetorDivEscalar(
    al.vetorSubVetor(posicao, p),
    al.norma(al.vetorSubVetor(posicao, p))
  );

  double auxAng = al.produtoEscalar(
    *l,
    al.vetorMultEscalar(direcao, -1)
  );

  if(auxAng < cos(angulo)){
    this->intensidade = Vetor(0,0,0,0);
  }else{
    this->intensidade = al.vetorMultEscalar(intensidadeOriginal, auxAng);
  }

  return al.norma(al.vetorSubVetor(posicao, p));
}