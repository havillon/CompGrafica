#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include "iluminacao.h"
#include "vetor.h"
#include "algebraLinear.h"
#include "objeto.h"
#include "canvas.h"
#include "observador.h"
#include "janela.h"
#include "esfera.h"
#include "plano.h"
#include "setup.h"

using namespace std;

class Cenario {
public:
  vector<Objeto*> objetos;
  vector<Iluminacao*> luzes;
  Vetor luzAmbiente;
  Vetor fundo;
  Canvas *canvas;
  Janela *janela;
  Observador observador;
  AlgebraLinear al;
  
  Cenario();
  Cenario(vector<Objeto*> objetos, vector<Iluminacao*> luzes, Vetor fundo, Canvas &canvas, Janela &janela, Vetor luzAmbiente, Observador observador);
  Cenario(Vetor fundo, Canvas &canvas, Janela &janela, Vetor luzAmbiente, Observador observador);
  void picking();
  void menuPicking(int indice);

  vector<Objeto*> getObjetos();
  void setObjetos(vector<Objeto*> objetos);

  vector<Iluminacao*> getLuzes();
  void setLuzes(vector<Iluminacao*> luzes);

  Vetor getLuzAmbiente();
  void setLuzAmbiente(Vetor luzAmbiente);

  Vetor getFundo();
  void setFundo(Vetor fundo);

  Canvas getCanvas();
  void setCanvas(Canvas canvas);

  Janela getJanela();
  void setJanela(Janela janela);

  Observador getObservador();
  void setObservador(Observador observador);
  
  void pintarCanvas();

  Vetor buscarCor(Vetor pi, Vetor dr, int index);

  void adicionarObjeto(Objeto *obj);
  void adicionarLuz(Iluminacao *luz);

};