#include "../include/cone.h"

Cone::Cone(){}

Cone::Cone(double altura, double raio, Vetor centroBase, Vetor direcao){
    this->altura = altura;
    this->raio = raio;
    this->centroBase = centroBase;
    this->direcao = al.vetorDivEscalar(direcao,al.norma(direcao));
}

bool Cone::verificarIntersecao(Vetor p0, Vetor dr){

    //v = V - p0 (vertice do cone)
    Vetor v = al.vetorSubVetor(
        al.soma(
            al.vetorMultEscalar(direcao, altura), 
            centroBase
        ),
        p0
    );

    //h²/(h² + r²)
    double cosQuadradoTheta = pow(altura, 2.0) / (pow(altura, 2.0) + pow(raio, 2.0));

    //Interseção com o Corpo

    //a = (d * n)² - (d * d) * cos²theta
    double a = pow(
        al.produtoEscalar(dr, direcao),
        2.0
    ) - al.produtoEscalar(dr, dr) * cosQuadradoTheta;

    //b = 2 * ((v * d) * cos²theta - (v * n) * (d * n))
    double b = al.produtoEscalar(v, dr) * cosQuadradoTheta - 
        al.produtoEscalar(v, direcao) * 
        al.produtoEscalar(dr, direcao);

    b = b * 2;

    //c = (v * n)² - (v * v) * cos²theta
    double c = pow(al.produtoEscalar(v,direcao), 2.0) - 
        al.produtoEscalar(v, v) * cosQuadradoTheta;

    double tCorpo;
    Vetor piCorpo, piBase;

    double delta = (b*b) - (4*a*c);

    if(delta < 0){
        tCorpo = numeric_limits <double>::infinity();

    }else{

        if(a == 0 || b == 0){

            tCorpo = numeric_limits <double>::infinity();
            

        }else{

            double t1 = (-b - sqrt(delta)) / (2*a);
            double t2 = (-b + sqrt(delta)) / (2*a);
            
            tCorpo = max(min(t1,t2),0.0);

            if(tCorpo < 0.0001){
                tCorpo = numeric_limits <double>::infinity();
            }

            piCorpo = al.soma(p0, al.vetorMultEscalar(dr, tCorpo));

            Vetor piMenosCentroBase = al.vetorSubVetor(piCorpo, this->centroBase);
            double alturaIntersecao = al.produtoEscalar(piMenosCentroBase, this->direcao);
            
            if(alturaIntersecao < 0.0 || alturaIntersecao >= this->altura){
                tCorpo = numeric_limits <double>::infinity();
            }
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

    if(tCorpo < tBase){

        this->setDistancia(tCorpo);
        this->setPontoIntersecao(piCorpo);
        this->flagIntersecao = 1;

    }else if(tBase < tCorpo){

        this->setDistancia(tBase);
        this->setPontoIntersecao(piBase);
        this->flagIntersecao = 0;

    }else{
        return false;
    }

    return true;
}

Vetor Cone::calcularNormal(Vetor posicao){
    //Corpo
    if(this->flagIntersecao == 1){
        //V - pi
        Vetor VMenosPi = al.vetorSubVetor(
            al.soma(
                al.vetorMultEscalar(direcao, altura), 
                centroBase
            ),
            posicao
        );

        Vetor normal = al.produtoVetorial(VMenosPi, direcao);

        return al.vetorDivEscalar(
            al.produtoVetorial(normal, VMenosPi),
            al.norma(al.produtoVetorial(normal, VMenosPi))
        );
    }
    //Base
    else{
        return al.vetorMultEscalar(direcao, -1);
    }
}