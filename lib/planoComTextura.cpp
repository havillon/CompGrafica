#include "../include/planoComTextura.h"

void PlanoComTextura::setTextura(Imagem* textura) {
    this->textura = textura;
}

Imagem* PlanoComTextura::getTextura() {
    return this->textura;
}

PlanoComTextura::PlanoComTextura() {}

PlanoComTextura::PlanoComTextura(Imagem* textura, Vetor pi, Vetor normal, double shininess) {
    this->setTextura(textura);
    this->setPontoIntersecao(pi);
    this->normal = normal;
    this->setShininess(shininess);
}