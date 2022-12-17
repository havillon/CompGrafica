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

  virtual void verificarIntersecaoTextura(Vetor p0);

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


  virtual void rotacionarX(double angulo) = 0;
  virtual void rotacionarY(double angulo) = 0;
  virtual void rotacionarZ(double angulo) = 0;
  virtual void translacao(double x, double y, double z) = 0;
  virtual void escala(double sx, double sy, double sz) = 0;
  virtual void espelhamentoXY() = 0;
  virtual void espelhamentoXZ() = 0;
  virtual void espelhamentoYZ() = 0;
  virtual void cisalhamentoYX(double angulo) = 0;
  virtual void cisalhamentoXY(double angulo) = 0;
  virtual void cisalhamentoXZ(double angulo) = 0;
  virtual void cisalhamentoZX(double angulo) = 0;
  virtual void cisalhamentoYZ(double angulo) = 0;
  virtual void cisalhamentoZY(double angulo) = 0;
};
