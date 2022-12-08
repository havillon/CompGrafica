#include "esfera.h"

Esfera::Esfera(){};

Esfera::Esfera(double raio, Vetor centro, Vetor Ke, Vetor Kd, Vetor Ka, double shininess){
  this->raio = raio;
  this->centro = centro;
  this->setKe(Ke);
  this->setKd(Kd);
  this->setKa(Ka);
  this->setShininess(shininess);
};

Vetor Esfera::calcularNormal(Vetor posicao){
  AlgebraLinear al;
  return al.vetorDivEscalar(al.vetorSubVetor(posicao,this->centro), (this->raio));
}

bool Esfera::verificarIntersecao(Vetor p0, Vetor dr){
  
  AlgebraLinear al;

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
    
    Vetor pi = al.vetorSomaVetor(al.vetorMultEscalar(dr, t), p0);
    
    this->setDistancia(t);
    this->setPontoIntersecao(pi);

    return true;
    
  }
}

// bool Esfera::verificarIntersecaoSombra(Vetor p0, Vetor dr){
//   AlgebraLinear al;

//   Vetor w = al.vetorSubVetor(p0, centro);

//   double a = al.produtoEscalar(dr,dr);
//   double b = 2*al.produtoEscalar(w, dr);
//   double c = al.produtoEscalar(w,w) - (this->raio*this->raio);
  
//   double delta = (b*b) - (4*a*c);
//   if(delta < 0){
//     return false;
//   }else{
//     double t1 = (-b - sqrt(delta)) / (2*a);
//     double t2 = (-b + sqrt(delta)) / (2*a);
    
//     double t = max(min(t1,t2),0.0);

//     if(t < 0.0001){
//       return false;
//     }
    
//     Vetor pi = al.vetorSomaVetor(al.vetorMultEscalar(dr, t), p0);
    
//     this->distancia_sombra = t;
//     this->pi_sombra = pi;

//     return true;
    
//   }
// }

// Vetor Esfera::buscarCor(Vetor pi, vector<Iluminacao*> luzes, vector<Objeto*> objetos, Vetor p0, Vetor dr, Vetor luzAmbiente, int index){
//   AlgebraLinear al;
//   Vetor corFinal;

//   Vetor v = al.vetorDivEscalar(al.vetorMultEscalar(dr,-1), al.norma(dr));
//   Vetor n = al.vetorDivEscalar(al.vetorSubVetor(p0, centro),this->raio);

//   Vetor fDifusa = Vetor(0,0,0,1);

//   Vetor fEspecular = Vetor(0,0,0,1);

//   Vetor fAmbiente = al.arroba(objetos[index]->Ka, luzAmbiente);

//   for(int i = 0; i < luzes.size(); i++){
//     Vetor pfMenosPi = al.vetorSubVetor(luzes[i]->posicao, pi);  
  
//     double normaPfMenosPi = al.norma(pfMenosPi);
  
//     Vetor l = al.vetorDivEscalar(pfMenosPi, normaPfMenosPi);

//     bool intersecOutrosObj = false;

//     for(int j = 0; (j < objetos.size() && !intersecOutrosObj); j++){
//       if(j != index){
//         // Vetor pontoAntigo = objetos[i]->pi;
//         // Vetor distanciaAntiga = objetos[i]->distancia;
//         bool teste = objetos[i]->verificarIntersecao(pi, dr);
//         intersecOutrosObj = teste && (objetos[j]->distancia < objetos[index]->distancia);
//       }
//     }

//     if(!intersecOutrosObj){
//       // n * (2*l*n) - l
//       Vetor r = al.vetorSubVetor(al.vetorMultEscalar(n, 2*al.produtoEscalar(l, n)), l);  

//       fDifusa = al.vetorSomaVetor(fDifusa, al.vetorMultEscalar(al.arroba( luzes[i]->intensidade, this->Kd), max(al.produtoEscalar(l, n), 0.0) ));
  
//       //especular -> (fonte @ K) * (v.r)
//       fEspecular = al.vetorSomaVetor(fEspecular, al.vetorMultEscalar(al.arroba(luzes[i]->intensidade, this->Ke), (pow(max(al.produtoEscalar(r, v), 0.0), this->shininess))));

//       Vetor lFinal = al.soma(al.soma(fDifusa, fEspecular), fAmbiente);

//       double maxF = max(lFinal.r, max(lFinal.g, lFinal.b));

//       if(maxF > 1){
//         lFinal = Vetor(lFinal.r/maxF, lFinal.g/maxF, lFinal.b/maxF, 1);
//       }

//       return al.vetorMultEscalar(lFinal, 255.0);
//     }
    
//   }
// }

