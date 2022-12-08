#include "../include/canvas.h"

Canvas::Canvas() {}

Canvas::Canvas(int wJanela, int hJanela, int nLinhas, int nColunas){
  this->wJanela = wJanela;
  this->hJanela = hJanela;
  this->nLinhas = nLinhas;
  this->nColunas = nColunas;
}

int Canvas::getWJanela(){
  return this->wJanela;
}
void Canvas::setWJanela(int wJanela){
  this->wJanela = wJanela; 
}

int Canvas::getHJanela(){
  return this->hJanela;
}
void Canvas::setHJanela(int hJanela){
  this->hJanela = hJanela; 
}

int Canvas::getNLinhas(){
  return this->nLinhas;
}
void Canvas::setNLinhas(int nLinhas){
  this->nLinhas = nLinhas; 
}

int Canvas::getNColunas(){
  return this->nColunas;
}
void Canvas::setNColunas(int nColunas){
  this->nColunas = nColunas; 
}