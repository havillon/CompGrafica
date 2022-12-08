#include "objeto.h"

//Ka
Vetor Objeto::getKa(){
  return this->Ka;
}
void Objeto::setKa(Vetor Ka){
  this->Ka = Ka;
}

//Kd
Vetor Objeto::getKd(){
  return this->Kd;
}
void Objeto::setKd(Vetor Kd){
  this->Kd = Kd;
}

//Ke
Vetor Objeto::getKe(){
  return this->Ke;
}
void Objeto::setKe(Vetor Ke){
  this->Ke = Ke;
}

//Shininess
double Objeto::getShininess(){
  return this->shininess;
}
void Objeto::setShininess(double shininess){
  this->shininess = shininess;
}

//Distancia
double Objeto::getDistancia(){
  return this->distancia;
}
void Objeto::setDistancia(double distancia){
  this->distancia = distancia;
}

//PontoIntersecao
Vetor Objeto::getPontoIntersecao(){
  return this->pontoIntersecao;
}
void Objeto::setPontoIntersecao(Vetor pontoIntersecao){
  this->pontoIntersecao = pontoIntersecao;
}

//DistanciaSombra
double Objeto::getDistanciaSombra(){
  return this->distanciaSombra;
}
void Objeto::setDistanciaSombra(double distanciaSombra){
  this->distanciaSombra = distanciaSombra;
}

//TemIntersecao
bool Objeto::getTemIntersecao(){
  return this->temIntersecao;
}
void Objeto::setTemIntersecao(bool temIntersecao){
  this->temIntersecao = temIntersecao;
}

