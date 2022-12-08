#pragma once

#include "../algebraLinear/vetor.h"

class Iluminacao {
public:
  Vetor intensidade;
  Vetor posicao;
  Vetor dr;

  Iluminacao();
  Iluminacao(Vetor intensidade, Vetor posicao);

};