#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include "objeto.h"
#include "algebraLinear.h"
#include "aresta.h"
#include "face.h"
#include "vertice.h"

using namespace std;

class Malha : public Objeto {
public:
    vector<Aresta> arestas;
    vector<Face> faces;
    vector<Vertice> vertices;

    Vetor normal;

    AlgebraLinear al;

    Malha();
    void adicionarAresta(Aresta aresta);
    void adicionarFace(Face face);
    void adicionarVertice(Vertice vertice);

    bool verificarIntersecao(Vetor p0, Vetor dr) override;
    Vetor calcularNormal(Vetor posicao) override;
};