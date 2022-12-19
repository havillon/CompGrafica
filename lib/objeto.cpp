#include "../include/objeto.h"

void Objeto::alterarPropriedades(){
  Vetor Ka, Ke, Kd;

  printf("Ka (red): ");
  cin >> Ka.r;
  printf("Ka (green): ");
  cin >> Ka.g;
  printf("Ka (blue): ");
  cin >> Ka.b;

  printf("Ke (red): ");
  cin >> Ke.r;
  printf("Ke (green): ");
  cin >> Ke.g;
  printf("Ke (blue): ");
  cin >> Ke.b;

  printf("Kd (red): ");
  cin >> Kd.r;
  printf("Kd (green): ");
  cin >> Kd.g;
  printf("Kd (blue): ");
  cin >> Kd.b;
  
  printf("\n");

  this->Ka = Ka;
  this->Ke = Ke;
  this->Kd = Kd;
}

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

//TemIntersecao
bool Objeto::getTemIntersecao(){
  return this->temIntersecao;
}
void Objeto::setTemIntersecao(bool temIntersecao){
  this->temIntersecao = temIntersecao;
}

void Objeto::verificarIntersecaoTextura(Vetor pi){

}