#include "../include/malha.h"

Malha::Malha(){}

void Malha::adicionarAresta(Aresta aresta){
    this->arestas.push_back(aresta);
}

void Malha::adicionarFace(Face face){
    this->faces.push_back(face);
}

void Malha::adicionarVertice(Vertice* vertice){
    this->vertices.push_back(vertice);
}

bool Malha::verificarIntersecao(Vetor p0, Vetor dr){

    // if(!this->verificarIntersecaoEnvoltorio(p0, dr)){
    //     return false;
    // }
    double distancia = numeric_limits<double>::infinity();
    this->setTemIntersecao(false);
    
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

        Vetor p1 = vertices[v1]->ponto;
        Vetor p2 = vertices[v2]->ponto;
        Vetor p3 = vertices[v3]->ponto;

        Vetor r1 = al.vetorSubVetor(p2, p1);
        Vetor r2 = al.vetorSubVetor(p3, p1);

        Vetor normalMalha = al.produtoVetorial(r1, r2);
        normalMalha = al.vetorDivEscalar(normalMalha, al.norma(normalMalha));

        Vetor w = al.vetorSubVetor(p0, p1);

        // Vetor dr = al.vetorDivEscalar(dr, al.norma(dr));
        double drEscalarN = al.produtoEscalar(dr, normalMalha);
        //cout << drEscalarN << "\n";
        double t;    
        Vetor pi, v;

        double c1, c2, c3;

        if(drEscalarN != 0 && ((t = -al.produtoEscalar(w, normalMalha) /drEscalarN) > 0)){
            
            pi = al.soma(p0, al.vetorMultEscalar(dr, t));

            Vetor piV1 = al.vetorSubVetor(p1, pi);
            Vetor piV2 = al.vetorSubVetor(p2, pi);
            Vetor piV3 = al.vetorSubVetor(p3, pi);

            c1 = al.produtoEscalar(al.produtoVetorial(piV3, piV1), normalMalha) / 
                    al.produtoEscalar(al.produtoVetorial(r1, r2), normalMalha);

            c2 = al.produtoEscalar(al.produtoVetorial(piV1, piV2), normalMalha) / 
                    al.produtoEscalar(al.produtoVetorial(r1, r2), normalMalha);

            c3 = al.produtoEscalar(al.produtoVetorial(piV2, piV3), normalMalha) / 
                    al.produtoEscalar(al.produtoVetorial(r1, r2), normalMalha);

            double s = c1 + c2 + c3;

            if(s <= 1.01 && c1 >= 0 && c2 >= 0 && c3 >= 0 && (!this->getTemIntersecao() || distancia > t)){
                this->setTemIntersecao(true);
                distancia = t;
                this->setDistancia(t);
                this->setPontoIntersecao(pi);
                this->normal = normalMalha;
            }
        }
    }
    return this->getTemIntersecao();
}


bool Malha::verificarIntersecaoEnvoltorio(Vetor p0, Vetor dr){
    Vetor w = al.vetorSubVetor(p0, centro);

    double a = al.produtoEscalar(dr,dr);
    double b = 2*al.produtoEscalar(w, dr);
    double c = al.produtoEscalar(w,w) - (this->raio*this->raio);

    double delta = (b*b) - (4*a*c);

    if(delta < 0){
        return false;
    }else{
        double t1 = (-b - sqrt(delta)) / (2*a);
        double t2 = (-b + sqrt(delta)) / (2*a);

        double t = max(min(t1,t2),0.0);

        if(t < 0.0001){
            return false;
        }
    }
    return true;
}


Vetor Malha::calcularNormal(Vetor posicao){
    return this->normal;
}

void Malha::rotacionarX(double angulo){
    for (Vertice *v : vertices) {
        v->ponto = al.rotacionarX(v->ponto, angulo);
    }
    this->centro = al.rotacionarX(this->centro, angulo);
}

void Malha::rotacionarY(double angulo){
	for (Vertice* v : vertices) {
        v->ponto = al.rotacionarY(v->ponto, angulo);
    }
    this->centro = al.rotacionarY(this->centro, angulo);
}

void Malha::rotacionarZ(double angulo){
	for (Vertice* v : vertices) {
        v->ponto = al.rotacionarZ(v->ponto, angulo);
    }
    this->centro = al.rotacionarZ(this->centro, angulo);
}

void Malha::translacao(double x, double y, double z){
	for (Vertice* v : vertices) {
        v->ponto = al.translacao(v->ponto, x, y, z);
    }
    this->centro = al.translacao(this->centro, x, y, z);
}

void Malha::escala(double sx, double sy, double sz){
    for (Vertice* v : vertices) {
        v->ponto = al.escala(v->ponto,sx, sy, sz);
    }
    this->centro = al.escala(this->centro, sx, sy, sz);
    this->raio = max(sx, max(sy, sz)) * this->raio;
}

void Malha::espelhamentoXY(){
	for (Vertice* v : vertices) {
        v->ponto = al.espelhamentoXY(v->ponto);
    }
    this->centro = al.espelhamentoXY(this->centro);
}

void Malha::espelhamentoXZ(){
  	for (Vertice* v : vertices) {
        v->ponto = al.espelhamentoXZ(v->ponto);
    }
    this->centro = al.espelhamentoXZ(this->centro);
}

void Malha::espelhamentoYZ(){
	for (Vertice* v : vertices) {
        v->ponto = al.espelhamentoYZ(v->ponto);
    }
    this->centro = al.espelhamentoYZ(this->centro);
}

void Malha::cisalhamentoYX(double angulo){
	for (Vertice* v : vertices) {
        v->ponto = al.cisalhamentoYX(v->ponto, angulo);
    }
    this->centro = al.cisalhamentoYX(this->centro, angulo);
}

void Malha::cisalhamentoXY(double angulo){
	for (Vertice* v : vertices) {
        v->ponto = al.cisalhamentoXY(v->ponto, angulo);
    }
    this->centro = al.cisalhamentoXY(this->centro, angulo);
}

void Malha::cisalhamentoXZ(double angulo){
	for (Vertice* v : vertices) {
        v->ponto = al.cisalhamentoXZ(v->ponto, angulo);
    }
    this->centro = al.cisalhamentoXZ(this->centro, angulo);
}

void Malha::cisalhamentoZX(double angulo){
	for (Vertice* v : vertices) {
        v->ponto = al.cisalhamentoZX(v->ponto, angulo);
    }
    this->centro = al.cisalhamentoZX(this->centro, angulo);
}

void Malha::cisalhamentoYZ(double angulo){
	for (Vertice* v : vertices) {
        v->ponto = al.cisalhamentoYZ(v->ponto, angulo);
    }
    this->centro = al.cisalhamentoYZ(this->centro, angulo);
}

void Malha::cisalhamentoZY(double angulo){
	for (Vertice* v : vertices) {
        v->ponto = al.cisalhamentoZY(v->ponto, angulo);
    }
    this->centro = al.cisalhamentoZY(this->centro, angulo);
}