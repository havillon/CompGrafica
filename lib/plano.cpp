#include "../include/plano.h"

Plano::Plano(){}

Plano::Plano(Vetor p_pi, Vetor n_pi, Vetor Ke, Vetor Kd, Vetor Ka, double shininess){
  this->p_pi = p_pi;
  this->n_pi = n_pi;
  this->setKe(Ke);
  this->setKd(Kd);
  this->setKa(Ka);
  this->setShininess(shininess);
}

bool Plano::verificarIntersecao(Vetor p0, Vetor dr){
  AlgebraLinear al;
  Vetor w = al.vetorSubVetor(p0, this->p_pi);
  double drEscalarN = al.produtoEscalar(dr, this->n_pi);

  if(drEscalarN == 0){
    return false;
  }

  double wEscalarN = al.produtoEscalar(w, this->n_pi);

  double t = (-wEscalarN)/drEscalarN;

  if(t < 0){
    return false;
  }

  Vetor pi = al.soma(p0, al.vetorMultEscalar(dr, t));

  //Vetor v =  al.vetorDivEscalar(al.vetorMultEscalar(dr,-1), al.norma(dr)); 

  double distancia = al.norma(al.vetorSubVetor(pi, p0));

  this->setDistancia(distancia);
  this->setPontoIntersecao(pi);

  return true;
  
}

Vetor Plano::calcularNormal(Vetor posicao){
  return this->n_pi;
}

// Vetor Plano::buscarCor(Vetor pi, vector<Iluminacao*> luzes, vector<Objeto*> objetos, Vetor p0, Vetor dr, Vetor luzAmbiente, int index){
//   AlgebraLinear al;
//   Vetor corFinal;

//   Vetor v = al.vetorDivEscalar(al.vetorMultEscalar(dr,-1), al.norma(dr));

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
//       Vetor r = al.vetorSubVetor(al.vetorMultEscalar(this->n_pi, 2*al.produtoEscalar(l, this->n_pi)), l);  

//       fDifusa = al.vetorSomaVetor(fDifusa, al.vetorMultEscalar(al.arroba(luzes[i]->intensidade, this->Kd), max(al.produtoEscalar(l, this->n_pi), 0.0)));
  
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