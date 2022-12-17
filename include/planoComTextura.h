#pragma once

#include "plano.h"
#include "imagem.h"

class PlanoComTextura : public Objeto {
public:
    Imagem* textura = nullptr;
    AlgebraLinear al;
    void setTextura(Imagem* textura);
    Imagem* getTextura();

    void verificarIntersecaoTextura(Vetor pi);

    Vetor p_pi;
    Vetor n_pi;
    PlanoComTextura();
    PlanoComTextura(Imagem* textura, Vetor p_pi, Vetor n_pi, double shininess);

    Vetor calcularNormal(Vetor posicao) override;
    bool verificarIntersecao(Vetor p0, Vetor dr) override;
    // Vetor buscarCor(Vetor pi, vector<Iluminacao*> luzes, vector<Objeto*> objetos, Vetor p0, Vetor dr, Vetor luzAmbiente, int index) override;
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