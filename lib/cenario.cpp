#include "../include/cenario.h"

Cenario::Cenario(){}

Cenario::Cenario(vector<Objeto*> objetos, vector<Iluminacao*> luzes, Vetor fundo, Canvas &canvas, Janela &janela, Vetor luzAmbiente, Observador observador){
  this->objetos = objetos;
  this->luzes = luzes;
  this->fundo = fundo;
  this->canvas = &canvas;
  this->janela = &janela;
  this->luzAmbiente = luzAmbiente;
  this->observador = observador;
}

Cenario::Cenario(Vetor fundo, Canvas &canvas, Janela &janela, Vetor luzAmbiente, Observador observador){
  this->fundo = fundo;
  this->canvas = &canvas;
  this->janela = &janela;
  this->luzAmbiente = luzAmbiente;
  this->observador = observador;
}

vector<Objeto*> getObjetos();
void setObjetos(vector<Objeto*> objetos);

vector<Iluminacao*> getLuzes();
void setLuzes(vector<Iluminacao*> luzes);

Vetor getLuzAmbiente();
void setLuzAmbiente(Vetor luzAmbiente);

Vetor getFundo();
void setFundo(Vetor fundo);

Canvas getCanvas();
void setCanvas(Canvas canvas);

Janela getJanela();
void setJanela(Janela janela);

Observador getObservador();
void setObservador(Observador observador);

void Cenario::adicionarObjeto(Objeto *obj){
  this->objetos.push_back(obj);
}

void Cenario::adicionarLuz(Iluminacao *luz){
  this->luzes.push_back(luz);
}

void Cenario::pintarCanvas(SDL_Renderer *renderer){
  Vetor p = this->observador.p0;

  //60
  double wJ = this->janela->wJanela;
  double hJ = this->janela->hJanela;
  
  //500
  double nL = this->janela->nLinhas;
  double nC = this->janela->nColunas;

  // 60/500
  double dx = wJ/nC;
  double dy = hJ/nL;

  double x,y;
  Vetor dr;

  int posObjFrontal;
  
  for (int l = 0; l < nL; l++){
    y = hJ/2.0 - dy/2.0 - dy*l;
    for(int c = 0; c < nC; c++){
      
      posObjFrontal = -1;
      
      x = -wJ/2.0 + dx/2.0 + c*dx;
      
      dr.set(x, y, -this->janela->distancia, 1);

      for(int i = 0; i < objetos.size(); i++){
        if(objetos[i]->verificarIntersecao(p, dr)){
          
          if((posObjFrontal < 0) || (objetos[i]->getDistancia() < objetos[posObjFrontal]->getDistancia())){
            posObjFrontal = i;
          }
          
        } 
      }

      if(posObjFrontal == -1){
        SDL_SetRenderDrawColor(renderer, fundo.r, fundo.g, fundo.b, 0);
      }else{
        Vetor pi = objetos[posObjFrontal]->getPontoIntersecao();
        // Vetor cor = this->objetos[posObjFrontal]->buscarCor(pi, luzes, objetos, p, dr, luzAmbiente, posObjFrontal);
        Vetor cor = this->buscarCor(pi, dr, posObjFrontal);
        SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, 0);
      }
      SDL_RenderDrawPoint(renderer, c, l);
      
    }
  }
}

Vetor Cenario::buscarCor(Vetor pi, Vetor dr, int index){
  AlgebraLinear al;
  
  Vetor n = this->objetos[index]->calcularNormal(pi);
  
  Vetor v = al.vetorDivEscalar(al.vetorMultEscalar(dr,-1), al.norma(dr));

  Vetor fAmbiente = al.arroba(this->objetos[index]->getKa(), luzAmbiente);

  Vetor fDifusa = Vetor(0,0,0,1);

  Vetor fEspecular = Vetor(0,0,0,1);

  bool isIntersected = false;

  for(int i = 0; i < luzes.size(); i++){

    isIntersected = false;

    Vetor pfMenosPi = al.vetorSubVetor(luzes[i]->posicao, pi);  
    double normaPfMenosPi = al.norma(pfMenosPi);
  
    Vetor l = al.vetorDivEscalar(pfMenosPi, normaPfMenosPi);

    for(int j = 0; j < objetos.size(); j++){
      if(objetos[j]->verificarIntersecao(pi, l)){
        if(objetos[j]->getDistancia() < normaPfMenosPi){
          isIntersected = true;
          break;
        }
      }
    }

    if(isIntersected){
      continue;
    }
  
    // n * (2*l*n) - l
    Vetor r = al.vetorSubVetor(al.vetorMultEscalar(n, 2*al.produtoEscalar(l, n)), l);  
  
    //difusa -> (fonte @ K) * (l.n)
    fDifusa = al.vetorSomaVetor(fDifusa, al.vetorMultEscalar(al.arroba(luzes[i]->intensidade, this->objetos[index]->getKd()), std::max(al.produtoEscalar(l, n), 0.0)));
  
    //especular -> (fonte @ K) * (v.r)
    fEspecular = al.vetorSomaVetor(fEspecular, al.vetorMultEscalar(al.arroba(luzes[i]->intensidade, this->objetos[index]->getKe()), (pow(std::max(al.produtoEscalar(r, v), 0.0), this->objetos[index]->getShininess()))));
  }

  Vetor lFinal = al.soma(al.soma(fDifusa, fEspecular), fAmbiente);

  double maxF = max(lFinal.r, max(lFinal.g, lFinal.b));

  if(maxF > 1){
    lFinal = Vetor(lFinal.r/maxF, lFinal.g/maxF, lFinal.b/maxF, 1);
  }

  return al.vetorMultEscalar(lFinal, 255.0);
}
