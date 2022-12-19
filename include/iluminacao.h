#pragma once

#include <limits>
#include <cmath>
#include "vetor.h"
#include "algebraLinear.h"

using namespace std;

class Iluminacao {
public:
  Vetor intensidadeOriginal;
  Vetor intensidade;
  AlgebraLinear al;
  // Vetor dr;

  //0: pontual
  //1: direcional
  //2: spot
  int tipo;
  bool ligada;

  virtual double calcularDistancia(Vetor p, Vetor *l) = 0;

  // Iluminacao();
  // Iluminacao(Vetor intensidade, Vetor posicao, int tipo);

};

class LuzPontual : public Iluminacao{
public:
  Vetor posicao;

  LuzPontual(Vetor intensidade, Vetor posicao);
  double calcularDistancia(Vetor p, Vetor* l) override;
};

class LuzDirecional : public Iluminacao{
public:
  Vetor direcao;

  LuzDirecional(Vetor intensidade, Vetor direcao);
  double calcularDistancia(Vetor p, Vetor* l) override;
};

class LuzSpot : public Iluminacao {
public:
  Vetor direcao;
  Vetor posicao;
  double angulo;

  LuzSpot(Vetor intensidade, Vetor direcao, Vetor posicao, double angulo);
  double calcularDistancia(Vetor p, Vetor* l) override;
};