#include "include/setup.h"

int main(int argc, char *argv[]){
  //Observador
  Vetor p0 (0,0,0,1);
  Observador obs (p0);
  //Fim Observador
  
  //Janela
  int dJanela = 30;
  Vetor cJanela (0,0, -30, 1);
  Janela janela (cJanela, 60, 60, 500, 500, dJanela);
  //Fim Janela
  
  //Esfera
  int raio = 40;
  Vetor centro (0,0, -100, 1);
  Esfera esfera (raio, centro, Vetor(0.7,0.2,0.2,1), Vetor(0.7,0.2,0.2,1), Vetor(0.7,0.2,0.2,1), 10);
  //Fim Esfera

  //Cor Fundo
  Vetor fundo (100,100,100,1);
  
  //Luzes
  Vetor luzAmbiente = Vetor(0.3, 0.3, 0.3, 1);
  Iluminacao luzPontual = Iluminacao(Vetor(0.7, 0.7, 0.7, 1), Vetor(0, 60, -30, 0));
  
  Canvas c;

  //Planos
  Plano planoChao (Vetor(0,-40,0,0), Vetor(0,1,0,0), Vetor(0.2, 0.7, 0.2, 0), Vetor(0.2, 0.7, 0.2, 0), Vetor(0,0,0,0), 1);
  Plano planoFundo (Vetor(0,0,-200,0), Vetor(0,0,1,0), Vetor(0.3, 0.3, 0.7, 0), Vetor(0.3, 0.3, 0.7, 0), Vetor(0,0,0,0), 1);
	
  Setup s;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  s.initializeSDLAndWindow(&window, &renderer, 500, 500);

  //Cenario
  Cenario *cenario = new Cenario(fundo, c, janela, luzAmbiente, obs);
  cenario->adicionarObjeto(&planoChao);
  cenario->adicionarObjeto(&planoFundo);
  cenario->adicionarObjeto(&esfera);
  cenario->adicionarLuz(&luzPontual);
  cenario->pintarCanvas(renderer);
  //Fim Cenario
  
  s.update(renderer);
  s.listenEventQuit(window);
  return 0;

}
