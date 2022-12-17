#include "../include/cubo.h"

Malha Cubo::criarCubo(Vetor centroBase, double comprimentoAresta, Vetor Ka, Vetor Kd, Vetor Ke, double shininess){
    Malha* malha = new Malha();

    malha->setShininess(shininess);
    malha->setKa(Ka);
    malha->setKd(Kd);
    malha->setKe(Ke);

    malha->adicionarVertice(
        new Vertice(
            Vetor(
                centroBase.x - (comprimentoAresta/2),
                centroBase.y,
                centroBase.z - (comprimentoAresta/2),
                0
            ),
            Vetor(0,0,0,0)
        )
    );

    malha->adicionarVertice(
       new Vertice(
            Vetor(
                centroBase.x - (comprimentoAresta/2),
                centroBase.y,
                centroBase.z + (comprimentoAresta/2),
                1
            ),
            Vetor(0,0,0,0)
        )
    );

    malha->adicionarVertice(
       new Vertice(
            Vetor(
                centroBase.x + (comprimentoAresta/2),
                centroBase.y,
                centroBase.z + (comprimentoAresta/2),
                1
            ),
            Vetor(0,0,0,0)
        )
    );

    malha->adicionarVertice(
       new Vertice(
            Vetor(
                centroBase.x + (comprimentoAresta/2),
                centroBase.y,
                centroBase.z - (comprimentoAresta/2),
                1
            ),
            Vetor(0,0,0,0)
        )
    );

    malha->adicionarVertice(
       new Vertice(
            Vetor(
                centroBase.x - comprimentoAresta/2,
                centroBase.y + comprimentoAresta,
                centroBase.z - comprimentoAresta/2,
                1
            ),
            Vetor(0,0,0,0)
        )
    );

    malha->adicionarVertice(
       new Vertice(
            Vetor(
                centroBase.x - comprimentoAresta/2,
                centroBase.y + comprimentoAresta,
                centroBase.z + comprimentoAresta/2,
                1
            ),
            Vetor(0,0,0,0)
        )
    );

    malha->adicionarVertice(
       new Vertice(
            Vetor(
                centroBase.x + comprimentoAresta/2,
                centroBase.y + comprimentoAresta,
                centroBase.z + comprimentoAresta/2,
                1
            ),
            Vetor(0,0,0,0)
        )
    );

    malha->adicionarVertice(
       new Vertice(
            Vetor(
                centroBase.x + comprimentoAresta/2,
                centroBase.y + comprimentoAresta,
                centroBase.z - comprimentoAresta/2,
                1
            ),
            Vetor(0,0,0,0)
        )
    );

    malha->adicionarAresta(Aresta(0, 1));
    malha->adicionarAresta(Aresta(1, 2));
    malha->adicionarAresta(Aresta(2, 3));
    malha->adicionarAresta(Aresta(3, 0));
    malha->adicionarAresta(Aresta(4, 5));
    malha->adicionarAresta(Aresta(5, 6));
    malha->adicionarAresta(Aresta(6, 7));
    malha->adicionarAresta(Aresta(7, 4));
    malha->adicionarAresta(Aresta(0, 4));
    malha->adicionarAresta(Aresta(1, 5));
    malha->adicionarAresta(Aresta(2, 6));
    malha->adicionarAresta(Aresta(3, 7));
    malha->adicionarAresta(Aresta(2, 7));
    malha->adicionarAresta(Aresta(5, 7));
    malha->adicionarAresta(Aresta(5, 2));
    malha->adicionarAresta(Aresta(1, 4));
    malha->adicionarAresta(Aresta(1, 3));
    malha->adicionarAresta(Aresta(3, 4));

    
    malha->adicionarFace(Face(6, 10, 12));
    malha->adicionarFace(Face(12, 2, 11));
    malha->adicionarFace(Face(7, 4, 13));
    malha->adicionarFace(Face(13, 5, 6));
    malha->adicionarFace(Face(5, 14, 10));
    malha->adicionarFace(Face(9, 1, 14));
    malha->adicionarFace(Face(4, 15, 9));
    malha->adicionarFace(Face(8, 0, 15));
    malha->adicionarFace(Face(1, 16, 2));
    malha->adicionarFace(Face(3, 16, 10));
    malha->adicionarFace(Face(11, 17, 7));
    malha->adicionarFace(Face(3, 8, 17));

    return *malha;
}