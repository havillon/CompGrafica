#pragma once

#include "plano.h"
#include "imagem.h"

class PlanoComTextura : public Plano {
    private:
        Imagem* textura = nullptr;

    public:
        void setTextura(Imagem* textura);
        Imagem* getTextura();
        Vetor normal;

        PlanoComTextura();
        PlanoComTextura(Imagem* textura, Vetor pi, Vetor normal, double shininess);
};