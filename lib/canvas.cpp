#include "../include/canvas.h"

Canvas::Canvas() {}

Canvas::Canvas(int wJanela, int hJanela, int nLinhas, int nColunas){
  this->wJanela = wJanela;
  this->hJanela = hJanela;
  this->nLinhas = nLinhas;
  this->nColunas = nColunas;
}