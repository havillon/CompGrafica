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

void Cenario::pintarCanvas(){
  Setup s;
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  s.initializeSDLAndWindow(&window, &renderer, 500, 500);

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

  while(true){
    for (int l = 0; l < nL; l++){
      y = hJ/2.0 - dy/2.0 - dy*l;
      for(int c = 0; c < nC; c++){
        
        posObjFrontal = -1;
        
        x = -wJ/2.0 + dx/2.0 + c*dx;

        // p = Vetor(x, y, -20, 0);
        
        dr.set(x, y, -this->janela->distancia, 1);
        // dr.set(0, 0, -1, 0);

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
          objetos[posObjFrontal]->verificarIntersecaoTextura(pi);

          Vetor cor = this->buscarCor(pi, dr, posObjFrontal);
          SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, 0);
        }
        SDL_RenderDrawPoint(renderer, c, l);
      }
    }
    s.update(renderer);
    picking();
    // s.listenEventQuit(window);
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
    fDifusa = al.vetorSomaVetor(
      fDifusa, 
      al.vetorMultEscalar(
        al.arroba(luzes[i]->intensidade, this->objetos[index]->getKd()), 
        std::max(al.produtoEscalar(l, n), 0.0)
      )
    );
  
    //especular -> (fonte @ K) * (v.r)
    fEspecular = al.vetorSomaVetor(
      fEspecular, 
      al.vetorMultEscalar(
        al.arroba(
          luzes[i]->intensidade, 
          this->objetos[index]->getKe()
        ), 
        (
          pow(
            std::max(al.produtoEscalar(r, v), 0.0), 
            this->objetos[index]->getShininess()
          )
        )
      )
    );
  }

  Vetor lFinal = al.soma(al.soma(fDifusa, fEspecular), fAmbiente);

  double maxF = max(lFinal.r, max(lFinal.g, lFinal.b));

  if(maxF > 1){
    lFinal = Vetor(lFinal.r/maxF, lFinal.g/maxF, lFinal.b/maxF, 1);
  }

  return al.vetorMultEscalar(lFinal, 255.0);
}

void Cenario::picking(){
  bool quit = false;
  SDL_Event e;
  int cMouse, lMouse;

  Objeto* objClicado;
  Vetor p0 = observador.p0;
  Vetor Pdesatualizado, Patualizado;
  double dx = (double)janela->wJanela / janela->nLinhas;
  double dy = (double)janela->hJanela / janela->nColunas;
  double x, y;
  Vetor dr;
  int posObjFrontal;
  double distancia;
  double janelaX = 0;
  double janelaY = 0;
  double janelaZ = janela->distancia;
  double ti;
  double *pont_ti = &ti;

  cout << "\nClique em algum objeto\n";
  while(quit == false)
  {
      while(SDL_PollEvent(&e) != 0)
      {
          if(e.type == SDL_MOUSEBUTTONDOWN)
          {
              posObjFrontal = -1;
              SDL_GetMouseState(&cMouse,&lMouse);

              y = (janela->hJanela / 2) - (dy * (lMouse + 0.5)) + janelaY;
              x = -(janela->wJanela / 2) + (dx * (cMouse + 0.5)) + janelaX;

              Pdesatualizado = Vetor(x, y, -janelaZ, 0);

              Patualizado = Pdesatualizado;
              
              dr = al.vetorSubVetor(Patualizado, p0);
              // if (camera->tipo_visao == 1)
              // {
              //   dr = subP(Patualizado, P0);
              // }

              // else if (camera->tipo_visao == 2)
              // {
              //   P0 = Patualizado;
              //   dr = camera->dr_camera;
              // }

              quit = true;
              for(int i = 0; i < objetos.size(); i++){
                if(objetos[i]->verificarIntersecao(p0, dr)){
                  
                  if((posObjFrontal < 0) || (objetos[i]->getDistancia() < objetos[posObjFrontal]->getDistancia())){
                    posObjFrontal = i;
                  }
                  
                } 
              }

              if (posObjFrontal >= 0){
                this->menuPicking(posObjFrontal);
              }else{
                cout << "\nNenhum objeto clicado!\n";
              }
          }
      }
  }
}


void Cenario::menuPicking(int indice)
{
  int a;

  cout << "\n1 -> Translação"
          "\n2 -> rx    3 -> ry    4 -> rz"
          "\n5 -> espxy    6 -> espxz    7 -> espyz"
          "\n8 -> cisYX    9 -> cisXY    10 -> cisXZ"
          "\n11 -> cisZX    12 -> cisYZ    13 -> cisZY"
          "\n14 -> escala"
          "\n15 -> Mudar propriedades do material\n";
  cin >> a;
  getchar();
  
  double tx, ty, tz, alfa, ex, ey, ez;
  if (a == 1)
  {
    cout << "x: ";
    cin >> tx;
    cout << "y: ";
    cin >> ty;
    cout << "z: ";
    cin >> tz;
    objetos[indice]->translacao(tx, ty, tz);
  }

  else if (a == 2 || a == 3 || a == 4 || ((a > 7) && (a < 14)))
  {
    cout << "angulo (em graus): ";
    cin >> alfa;
    alfa = (alfa * M_PI) / 180;

    if (a == 2)
    {
      objetos[indice]->rotacionarX(alfa);
    }

    else if (a == 3)
    {
      objetos[indice]->rotacionarY(alfa);
    }

    else if (a == 4)
    {
      objetos[indice]->rotacionarZ(alfa);
    }

    else if (a == 8)
    {
      objetos[indice]->cisalhamentoYX(alfa);
    }

    else if (a == 9)
    {
      objetos[indice]->cisalhamentoXY(alfa);
    }

    else if (a == 10)
    {
      objetos[indice]->cisalhamentoXZ(alfa);
    }

    else if (a == 11)
    {
      objetos[indice]->cisalhamentoZX(alfa);
    }

    else if (a == 12)
    {
      objetos[indice]->cisalhamentoYZ(alfa);
    }

    else
    {
      objetos[indice]->cisalhamentoZY(alfa);
    }
  }

  else if (a == 5)
  {
    objetos[indice]->espelhamentoXY();
  }

  else if (a == 6)
  {
    objetos[indice]->espelhamentoXZ();
  } 

  else if (a == 7)
  {
    objetos[indice]->espelhamentoYZ();
  }

  else if (a == 14)
  {
    cout << "ex: ";
    cin >> ex;
    cout << "ey: ";
    cin >> ey;
    cout << "ez: ";
    cin >> ez;
    objetos[indice]->escala(ex, ey, ez);
  }

  // else if (a == 15)
  // {
  //   objetos[indice]->mudarPropriedadesMaterial();
  // }

  else
  {
    cout << "\nPor favor, digite uma opção válida!\n";
    this->menuPicking(indice);
  }

}