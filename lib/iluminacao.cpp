#include "../include/iluminacao.h"

Iluminacao::Iluminacao(){}

Iluminacao::Iluminacao(Vetor intensidade, Vetor posicao){
  this->intensidade = intensidade;
  this->posicao = posicao;
}