#include "../include/planoComTextura.h"

void PlanoComTextura::setTextura(Imagem* textura) {
    this->textura = textura;
}

Imagem* PlanoComTextura::getTextura() {
    return this->textura;
}

PlanoComTextura::PlanoComTextura() {}

PlanoComTextura::PlanoComTextura(Imagem* textura, Vetor p_pi, Vetor n_pi, double shininess){
  this->p_pi = p_pi;
  this->n_pi = n_pi;
  this->setTextura(textura);
  this->setShininess(shininess);
}

void PlanoComTextura::verificarIntersecaoTextura(Vetor pi){
    int Px = abs((int)pi.x);
    int Pz = abs((int)pi.z);
    int x, y;

    x = Px % (this->textura->getLargura());
    y = Pz % (this->textura->getLargura());

    Vetor p = this->textura->getPixel(x, y);

    Vetor CorPixel ((double)p.r / 255.0, (double)p.g / 255.0, (double)p.b / 255.0, 0);
    
    this->setKe(CorPixel);
    this->setKd(CorPixel);
    this->setKa(CorPixel);
}

bool PlanoComTextura::verificarIntersecao(Vetor p0, Vetor dr){
  AlgebraLinear al;
  Vetor w = al.vetorSubVetor(p0, this->p_pi);
  double drEscalarN = al.produtoEscalar(dr, this->n_pi);

  if(drEscalarN == 0){
    return false;
  }

  double wEscalarN = al.produtoEscalar(w, this->n_pi);

  double t = (-wEscalarN)/drEscalarN;

  if(t < 0.0001){
    return false;
  }

  Vetor pi = al.soma(p0, al.vetorMultEscalar(dr, t));

  double distancia = al.norma(al.vetorSubVetor(pi, p0));

  this->setDistancia(distancia);
  this->setPontoIntersecao(pi);

  return true;
  
}

Vetor PlanoComTextura::calcularNormal(Vetor posicao){
  return this->n_pi;
}

void PlanoComTextura::rotacionarX(double angulo){
  p_pi = al.rotacionarX(p_pi, angulo);
  n_pi = al.rotacionarX(n_pi, angulo);
}

void PlanoComTextura::rotacionarY(double angulo){
  p_pi = al.rotacionarY(p_pi, angulo);
  n_pi = al.rotacionarY(n_pi, angulo);
}

void PlanoComTextura::rotacionarZ(double angulo){
  p_pi = al.rotacionarZ(p_pi, angulo);
  n_pi = al.rotacionarZ(n_pi, angulo);
}

void PlanoComTextura::translacao(double x, double y, double z){
  p_pi = al.translacao(p_pi, x, y, z);
}

void PlanoComTextura::escala(double sx, double sy, double sz){
  p_pi = al.escala(p_pi, sx, sy, sz);
}

void PlanoComTextura::espelhamentoXY(){
  p_pi = al.espelhamentoXY(p_pi);
  n_pi = al.espelhamentoXY(n_pi);
}

void PlanoComTextura::espelhamentoXZ(){
  p_pi = al.espelhamentoXZ(p_pi);
  n_pi = al.espelhamentoXZ(n_pi);
}

void PlanoComTextura::espelhamentoYZ(){
  p_pi = al.espelhamentoYZ(p_pi);
  n_pi = al.espelhamentoYZ(n_pi);
}

//nada acontece aqui
void PlanoComTextura::cisalhamentoYX(double angulo){}
void PlanoComTextura::cisalhamentoXY(double angulo){}
void PlanoComTextura::cisalhamentoXZ(double angulo){}
void PlanoComTextura::cisalhamentoZX(double angulo){}
void PlanoComTextura::cisalhamentoYZ(double angulo){}
void PlanoComTextura::cisalhamentoZY(double angulo){}