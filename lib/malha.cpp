#include "../include/malha.h"

Malha::Malha(){}

void Malha::adicionarAresta(Aresta aresta){
    this->arestas.push_back(aresta);
}

void Malha::adicionarFace(Face face){
    this->faces.push_back(face);
}

void Malha::adicionarVertice(Vertice vertice){
    this->vertices.push_back(vertice);
}

bool Malha::verificarIntersecao(Vetor p0, Vetor dr){
    this->setTemIntersecao(false);
    this->setDistancia(numeric_limits<double>::infinity());
    
    for(int i = 0; i < faces.size(); i++){
        int idAresta1 = faces[i].idAresta1;
        int idAresta2 = faces[i].idAresta2;

        int idVertice11 = arestas[idAresta1].idVertice1;
        int idVertice12 = arestas[idAresta1].idVertice2;

        int idVertice21 = arestas[idAresta2].idVertice1;
        int idVertice22 = arestas[idAresta2].idVertice2;

        double v1, v2, v3;

        double n = (((double)idVertice11) * ((double)idVertice12))/((double)idVertice21);

        if(n == ((double)idVertice11) || n == ((double)idVertice12)){
            v1 = (double)idVertice21;
            v2 = (double)idVertice22;
            v3 = n;
        }else{
            v1 = idVertice22;
            v2 = idVertice21;
            v3 = (((idVertice11) * (idVertice12))/(v1));
        }

        Vetor p1 = vertices[v1].ponto;
        Vetor p2 = vertices[v2].ponto;
        Vetor p3 = vertices[v3].ponto;

        Vetor r1 = al.vetorSubVetor(p2, p1);
        Vetor r2 = al.vetorSubVetor(p3, p1);

        Vetor normalMalha = al.produtoVetorial(r1, r2);
        normalMalha = al.vetorDivEscalar(normalMalha, al.norma(normalMalha));

        Vetor w = al.vetorSubVetor(p0, p1);

        double drEscalarN = al.produtoEscalar(dr, normalMalha);

        double t = -al.produtoEscalar(w, normalMalha) /drEscalarN;
    
        Vetor pi, v;

        double c1, c2, c3;

        if(drEscalarN != 0 && (t > 0)){
            
            pi = al.soma(p0, al.vetorMultEscalar(dr, t));

            Vetor piMenosP0 = al.vetorSubVetor(pi, p0);
            double distancia = al.norma(piMenosP0);

            v = al.vetorSubVetor(pi, p1);

            c1 = al.produtoEscalar(al.produtoVetorial(v, r2), normalMalha) / 
                    al.produtoEscalar(al.produtoVetorial(r1, r2), normalMalha);

            c2 = al.produtoEscalar(al.produtoVetorial(r1, v), normalMalha) / 
                    al.produtoEscalar(al.produtoVetorial(r1, r2), normalMalha);

            c3 = 1 - c1 - c2;


            if(c1 >= 0 && c2 >= 0 && c3 >= 0 && (!this->getTemIntersecao() || this->getDistancia() > distancia)){
                this->setTemIntersecao(true);
                this->setDistancia(distancia);
                this->setPontoIntersecao(pi);
                this->normal = normalMalha;
            }
        }
    }
    return this->getTemIntersecao();
}

Vetor Malha::calcularNormal(Vetor posicao){
    return this->normal;
}