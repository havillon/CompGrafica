#pragma once

#include <iostream>
#include <vector>
#include "iluminacao.h"
#include "../algebraLinear/vetor.h"
#include "../algebraLinear/algebraLinear.h"
#include "../objeto/objeto.h"
#include "../canvas.h"
#include "../observador.h"
#include "../janela.h"
#include "../objeto/esfera.h"
#include "../objeto/plano.h"
#include "../../setup.h"

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
  

  Cenario();
  Cenario(vector<Objeto*> objetos, vector<Iluminacao*> luzes, Vetor fundo, Canvas &canvas, Janela &janela, Vetor luzAmbiente, Observador observador);
  Cenario(Vetor fundo, Canvas &canvas, Janela &janela, Vetor luzAmbiente, Observador observador);
  
  void pintarCanvas(SDL_Renderer *renderer);

  Vetor buscarCor(Vetor pi, Vetor dr, int index); //Calcula a cor de um ponto

  void adicionarObjeto(Objeto *obj);
  void adicionarLuz(Iluminacao *luz);

  void setFundo(Vetor fundo);

};