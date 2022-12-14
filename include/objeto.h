#pragma once

#include <iostream>
#include <vector>
#include "vetor.h"
#include "iluminacao.h"

using namespace std;

class Objeto {

private:
  Vetor Ke;
  Vetor Kd;
  Vetor Ka;
  double shininess;

  double distancia;
  Vetor pontoIntersecao;
  
  bool temIntersecao;

public:
  virtual bool verificarIntersecao(Vetor p0, Vetor dr) = 0;
  virtual Vetor calcularNormal(Vetor posicao) = 0;

  void setKe(Vetor Ke);
  Vetor getKe();

  void setKd(Vetor Kd);
  Vetor getKd();

  void setKa(Vetor Ka);
  Vetor getKa();

  void setShininess(double shininess);
  double getShininess();

  void setDistancia(double distancia);
  double getDistancia();

  void setPontoIntersecao(Vetor pontoIntersecao);
  Vetor getPontoIntersecao();

  void setTemIntersecao(bool temIntersecao);
  bool getTemIntersecao();
  
  // void setDistanciaSombra(double distanciaSombra);
  // double getDistanciaSombra();

  // virtual Vetor buscarCor(Vetor pi, vector<Iluminacao*> luzes, vector<Objeto*> objetos, Vetor p0, Vetor dr, Vetor luzAmbiente, int index) = 0;

  //virtual Vetor verificarCor(Vetor p0, Vetor dr, Vetor pi, vector<Iluminacao*> Luzes, vector<Objeto*> Objetos, Vetor luzAmbiente) = 0;

};
