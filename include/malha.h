#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
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
    vector<Vertice*> vertices;

    //Envoltorio
    Vetor centro;
    double raio;

    Vetor normal;

    AlgebraLinear al;

    Malha();
    void adicionarAresta(Aresta aresta);
    void adicionarFace(Face face);
    void adicionarVertice(Vertice* vertice);

    bool verificarIntersecao(Vetor p0, Vetor dr) override;
    Vetor calcularNormal(Vetor posicao) override;

    bool verificarIntersecaoEnvoltorio(Vetor p0, Vetor dr);

    void rotacionarX(double angulo) override;
    void rotacionarY(double angulo) override;
    void rotacionarZ(double angulo) override;
    void translacao(double x, double y, double z) override;
    void escala(double sx, double sy, double sz) override;
    void espelhamentoXY() override;
    void espelhamentoXZ() override;
    void espelhamentoYZ() override;
    void cisalhamentoYX(double angulo) override;
    void cisalhamentoXY(double angulo) override;
    void cisalhamentoXZ(double angulo) override;
    void cisalhamentoZX(double angulo) override;
    void cisalhamentoYZ(double angulo) override;
    void cisalhamentoZY(double angulo) override;
};