#include "../include/cilindro.h"

Cilindro::Cilindro(){}

Cilindro::Cilindro(double altura, double raio, Vetor centroBase, Vetor direcao){
    this->altura = altura;
    this->raio = raio;
    this->centroBase = centroBase;
    this->direcao = al.vetorDivEscalar(direcao,al.norma(direcao));
}

bool Cilindro::verificarIntersecao(Vetor p0, Vetor dr){
    //w = dr - (dr * direcao) . direcao
    Vetor w = al.vetorSubVetor(
        dr, 
        al.vetorMultEscalar(
            this->direcao, 
            al.produtoEscalar(dr, this->direcao)
        )
    );

    //v = (p0 - centroBase) - (((p0 - centroBase) * u) * u)
    Vetor p0MenosCentro = al.vetorSubVetor(p0, this->centroBase);
    Vetor v = al.vetorSubVetor(
        p0MenosCentro, 
        al.vetorMultEscalar(
            this->direcao, 
            al.produtoEscalar(p0MenosCentro, this->direcao)
        )
    );

    //Interseção com o Corpo
    double a = al.produtoEscalar(w,w);
    double b = 2*al.produtoEscalar(v, w);
    double c = al.produtoEscalar(v,v) - (this->raio*this->raio);

    double tCorpo;
    Vetor piCorpo, piBase, piTopo;

    double delta = (b*b) - (4*a*c);

    if(delta < 0){
        tCorpo = numeric_limits <double>::infinity();

    }else{
        double t1 = (-b - sqrt(delta)) / (2*a);
        double t2 = (-b + sqrt(delta)) / (2*a);
        
        tCorpo = max(min(t1,t2),0.0);

        if(tCorpo < 0.0001){
            tCorpo = numeric_limits <double>::infinity();
        }
        
        piCorpo = al.vetorSomaVetor(al.vetorMultEscalar(dr, tCorpo), p0);

        Vetor piMenosCentroBase = al.vetorSubVetor(piCorpo, this->centroBase);
        double alturaIntersecao = al.produtoEscalar(piMenosCentroBase, this->direcao);
        
        if(alturaIntersecao < 0.0 || alturaIntersecao >= this->altura){
            tCorpo = numeric_limits <double>::infinity();
        }
        
    }

    //Interseção com a Base
    double tBase;
    Vetor wBase = al.vetorSubVetor(p0, this->centroBase);
    double drEscalarMenosDrBase = al.produtoEscalar(dr, al.vetorMultEscalar(this->direcao, -1));

    if(drEscalarMenosDrBase == 0){
        tBase = numeric_limits <double>::infinity();
    }

    double wEscalarNbase = al.produtoEscalar(wBase, al.vetorMultEscalar(this->direcao, -1));

    tBase = (-wEscalarNbase)/drEscalarMenosDrBase;

    piBase = al.soma(p0, al.vetorMultEscalar(dr, tBase));

    Vetor piMenosCentroBase = al.vetorSubVetor(piBase, this->centroBase);
    double raioIntersecaoBase = al.norma(piMenosCentroBase);

    if(tBase < 0.0001 || raioIntersecaoBase >= this->raio){
        tBase = numeric_limits <double>::infinity();
    }
    //Fim interseção com a Base

    //Interseção com o topo
    double tTopo;
    Vetor wTopo = al.vetorSubVetor(
        p0, 
        al.soma(
            al.vetorMultEscalar(direcao, altura), 
            centroBase
        )
    );

    double drEscalarMenosDrTopo = al.produtoEscalar(dr, this->direcao);

    if(drEscalarMenosDrTopo == 0){
        tTopo = numeric_limits <double>::infinity();
    }

    double wEscalarNtopo = al.produtoEscalar(wTopo, this->direcao);

    tTopo = (-wEscalarNtopo)/drEscalarMenosDrTopo;

    piTopo = al.soma(p0, al.vetorMultEscalar(dr, tTopo));
    
    Vetor piMenosCentroTopo = al.vetorSubVetor(piTopo, al.soma(
            al.vetorMultEscalar(direcao, altura), 
            centroBase
        ));
        
    double raioIntersecaoTopo = al.norma(piMenosCentroTopo);
    
    if(tTopo < 0.0001 || raioIntersecaoTopo >= this->raio){
        tTopo = numeric_limits <double>::infinity();
    }
    //Fim interseção com o Topo

    if(tCorpo < tBase && tCorpo < tTopo){
        
        this->setDistancia(tCorpo);
        this->setPontoIntersecao(piCorpo);
        this->flagIntersecao = 1;

    }else if(tBase < tCorpo && tBase < tTopo){

        this->setDistancia(tBase);
        this->setPontoIntersecao(piBase);
        this->flagIntersecao = 0;

    }else if(tTopo < tBase && tTopo < tCorpo){

        this->setDistancia(tTopo);
        this->setPontoIntersecao(piTopo);
        this->flagIntersecao = 2;

    }else{
        return false;
    }

    return true;
}

Vetor Cilindro::calcularNormal(Vetor posicao){

    //Corpo
    if(this->flagIntersecao == 1){
        
        Vetor posMenosCentroBase = al.vetorSubVetor(posicao, centroBase);

        Vetor normal = al.produtoVetorial(
            direcao,
            al.produtoVetorial(posMenosCentroBase, direcao)
        );

        return al.vetorDivEscalar(normal,al.norma(normal));

    //Base
    }else if(this->flagIntersecao == 0){
        return al.vetorMultEscalar(direcao, -1);

    //Topo
    }else{
        return direcao;
    }
    
}