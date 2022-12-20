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
  this->executando = true;
  this->perspectiva = true;
  this->ambienteLigada = true;
}

Cenario::Cenario(Vetor fundo, Canvas &canvas, Janela &janela, Vetor luzAmbiente, Observador observador){
  this->fundo = fundo;
  this->canvas = &canvas;
  this->janela = &janela;
  this->luzAmbiente = luzAmbiente;
  this->observador = observador;
  this->executando = true;
  this->perspectiva = true;
  this->ambienteLigada = true;
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
  
  s.initializeSDLAndWindow(&window, &renderer, janela->nLinhas, janela->nColunas);

  while(executando){

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

        if(perspectiva){
          dr.set(x, y, -this->janela->distancia, 1);
        }else{
          dr.set(0, 0, -1, 0);
          p = Vetor(x, y, -this->janela->distancia, 1);
        }

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
    menu();
  }
  
 
}

Vetor Cenario::buscarCor(Vetor pi, Vetor dr, int index){
  AlgebraLinear al;
  
  Vetor n = this->objetos[index]->calcularNormal(pi);
  
  Vetor v = al.vetorDivEscalar(al.vetorMultEscalar(dr,-1), al.norma(dr));

  Vetor fAmbiente = Vetor(0,0,0,1);
  
  if(ambienteLigada){
    fAmbiente = al.arroba(this->objetos[index]->getKa(), luzAmbiente);
  }  

  Vetor fDifusa = Vetor(0,0,0,1);

  Vetor fEspecular = Vetor(0,0,0,1);

  Vetor l = Vetor(0,0,0,1);

  bool isIntersected = false;

  for(int i = 0; i < luzes.size(); i++){
    if(luzes[i]->ligada){
      isIntersected = false;

      double normaPfMenosPi = luzes[i]->calcularDistancia(pi, &l);

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
          max(al.produtoEscalar(l, n), 0.0)
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
              max(al.produtoEscalar(r, v), 0.0), 
              this->objetos[index]->getShininess()
            )
          )
        )
      );
    }
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
              
              if(perspectiva){
                dr = al.vetorSubVetor(Patualizado, p0);
              }
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

void Cenario::menu(){
  int opcao;
  cout << "--------MENU--------\n";
  cout << "1: Alterar tamanho da janela\n";
  cout << "2: Alterar distancia\n";
  cout << "3: Modificar fontes luminosas\n";
  cout << "4: Mudar tipo de projecao\n";
  cout << "5: Picking\n";
  cout << "6: Sair\n";
  cout << "Digite a opção desejada: ";
  cin >> opcao;
  
  switch(opcao){
    case 1:
      //mudar tamanho da janela
      double largura;
      double altura;

      cout << "Digite a largura da janela: ";
      cin >> largura;
      cout << "Digite a altura da janela: ";
      cin >> altura;

      this->janela->wJanela = largura;
      this->janela->hJanela = altura;
      // this->janela->nLinhas = largura*4;
      // this->janela->nColunas = altura*4;

      s.listenEventQuit(window, renderer);
      s.initializeSDLAndWindow(&window, &renderer, janela->nLinhas, janela->nColunas);

      break;
    case 2:
      double distancia;
      cout << "Digite a nova distancia da janela: ";
      cin >> distancia;

      this->janela->distancia = distancia;
      break;
    case 3:
      //modificar luzes
      menuLuzes();
      break;
    case 4:
      //mudar projecao
      perspectiva = !perspectiva;
      break;
    case 5:
      //picking
      this->picking();
      break;
    case 6:
      //sair
      executando = false;
      s.listenEventQuit(window, renderer);
      break;
  }
}

void Cenario::menuPicking(int indice){

  int a;

  cout << "\n1: Translação"
          "\n2: RotacionarX"
          "\n3: RotacionarY"
          "\n4: RotacionarZ"
          "\n5: EspelhamentoXY"
          "\n6: EspelhamentoXZ"
          "\n7: EspelhamentoYZ"
          "\n8: CisalhamentoYX"
          "\n9: CisalhamentoXY"
          "\n10: CisalhamentoXZ"
          "\n11: CisalhamentoZX"
          "\n12: CisalhamentoYZ"
          "\n13: CisalhamentoZY"
          "\n14: Escala"
          "\n15: Mudar propriedades do material\n";
  cin >> a;
  getchar();
  
  double tx, ty, tz, alfa, ex, ey, ez;
  if (a == 1){
    cout << "x: ";
    cin >> tx;
    cout << "y: ";
    cin >> ty;
    cout << "z: ";
    cin >> tz;
    objetos[indice]->translacao(tx, ty, tz);
  }

  else if (a == 2 || a == 3 || a == 4 || ((a > 7) && (a < 14))){
    cout << "Angulo (em graus): ";
    cin >> alfa;
    alfa = (alfa * M_PI) / 180;

    if (a == 2){
      objetos[indice]->rotacionarX(alfa);
    }

    else if (a == 3){
      objetos[indice]->rotacionarY(alfa);
    }

    else if (a == 4){
      objetos[indice]->rotacionarZ(alfa);
    }

    else if (a == 8){
      objetos[indice]->cisalhamentoYX(alfa);
    }

    else if (a == 9){
      objetos[indice]->cisalhamentoXY(alfa);
    }

    else if (a == 10){
      objetos[indice]->cisalhamentoXZ(alfa);
    }

    else if (a == 11){
      objetos[indice]->cisalhamentoZX(alfa);
    }

    else if (a == 12){
      objetos[indice]->cisalhamentoYZ(alfa);
    }

    else{
      objetos[indice]->cisalhamentoZY(alfa);
    }
  }

  else if (a == 5){
    objetos[indice]->espelhamentoXY();
  }

  else if (a == 6){
    objetos[indice]->espelhamentoXZ();
  } 

  else if (a == 7){
    objetos[indice]->espelhamentoYZ();
  }

  else if (a == 14){
    cout << "x: ";
    cin >> ex;
    cout << "y: ";
    cin >> ey;
    cout << "z: ";
    cin >> ez;
    objetos[indice]->escala(ex, ey, ez);
  }

  else if (a == 15){
    objetos[indice]->alterarPropriedades();
  }

  else{
    cout << "\nInválido! Tente novamente\n";
    this->menuPicking(indice);
  }

}

void Cenario::menuLuzes(){
  int opcao;
  cout << "\nLuzes do cenário:\n";
  for (int i = 0; i < luzes.size(); i++){
    cout << i+1;
    
    switch (luzes[i]->tipo){
    case 0:
      cout << ": Pontual\n";
      break;
    case 1:
      cout << ": Direcional\n";
      break;
    case 2:
      cout << ": Spot\n";
      break;
    default:
      break;
    }
  }
  cout << luzes.size()+1 << ": Ambiente\n";
  cout << "Digite a luz que deseja alterar: ";
  cin >> opcao;

  if(opcao >= 0 && opcao <= luzes.size() + 1){
    alterarLuzes(opcao);
  }else{
    cout << "Opção inválida!\n";
  }


}

void Cenario::alterarLuzes(int indice){
  int opcao;

  cout << "\n1: Alterar intensidade\n";
  cout << "2: Ligar/desligar\n";
  cout << "Digite a opção desejada: ";
  cin >> opcao;

  if(opcao == 1){
    Vetor K;

    printf("K (red): ");
    cin >> K.r;
    printf("K (green): ");
    cin >> K.g;
    printf("K (blue): ");
    cin >> K.b;
    
    printf("\n");

    if(indice <= luzes.size()){
      luzes[indice-1]->intensidade = K;
    }else{
      this->luzAmbiente = K;
    }

  }else if (opcao == 2){
    if(indice <= luzes.size()){
      luzes[indice-1]->ligada = !luzes[indice-1]->ligada;
    }else{
      ambienteLigada = false;
    }
  }else{
    cout << "Opção inválida!\n";
  }
}