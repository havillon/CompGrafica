#pragma once

#include "plano.h"
#include "imagem.h"

class PlanoComTextura : public Plano {
    public:
        Imagem* textura = nullptr;
        AlgebraLinear al;
        void setTextura(Imagem* textura);
        Imagem* getTextura();
        Vetor normal;

        PlanoComTextura();
        PlanoComTextura(Imagem* textura, Vetor pi, Vetor normal, double shininess);
        void setIntensidades();
};