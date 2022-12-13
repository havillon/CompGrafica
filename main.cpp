#include "include/setup.h"

AlgebraLinear al;

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
  double raio = 40;
  Vetor centro (0,0, -100, 1);
  Esfera esfera (raio, centro, Vetor(0.7,0.2,0.2,1), Vetor(0.7,0.2,0.2,1), Vetor(0.7,0.2,0.2,1), 10.0);
  //Fim Esfera

  //Cilindro (altura, raio, centrobase, direcao)
  Cilindro cilindro(3.0*raio, raio/3.0, centro, Vetor(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3), 0));
  cilindro.setKa(Vetor(0.2, 0.3, 0.8, 1));
  cilindro.setKd(Vetor(0.2, 0.3, 0.8, 1));
  cilindro.setKe(Vetor(0.2, 0.3, 0.8, 1));
  cilindro.setShininess(10.0);

  //Cone (altura, raio, centrobase, direcao)
  Vetor centroCone = al.soma(
            al.vetorMultEscalar(cilindro.direcao, cilindro.altura), 
            cilindro.centroBase
        );

  Cone cone(100, 1.5*raio, centroCone, Vetor(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3), 0));
  cone.setKa(Vetor(0.8, 0.3, 0.2, 1));
  cone.setKd(Vetor(0.8, 0.3, 0.2, 1));
  cone.setKe(Vetor(0.8, 0.3, 0.2, 1));
  cone.setShininess(10.0);
  

  //Cor Fundo
  Vetor fundo (100,100,100,1);
  
  //Luzes
  Vetor luzAmbiente = Vetor(0.3, 0.3, 0.3, 1);
  Iluminacao luzPontual = Iluminacao(Vetor(0.7, 0.7, 0.7, 1), Vetor(0, 60, -30, 0));
  
  Canvas c;

  //Planos
  Plano planoChao (Vetor(0,-40,0,0), Vetor(0,1,0,0), Vetor(0.2, 0.7, 0.2, 0), Vetor(0.2, 0.7, 0.2, 0), Vetor(0.2, 0.7, 0.2, 0), 1);
  Plano planoFundo (Vetor(0,0,-200,0), Vetor(0,0,1,0), Vetor(0.3, 0.3, 0.7, 0), Vetor(0.3, 0.3, 0.7, 0), Vetor(0.3, 0.3, 0.7, 0), 1);
	
  Setup s;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  s.initializeSDLAndWindow(&window, &renderer, 500, 500);

  //Cenario
  Cenario *cenario = new Cenario(fundo, c, janela, luzAmbiente, obs);
  cenario->adicionarObjeto(&planoChao);
  cenario->adicionarObjeto(&planoFundo);
  cenario->adicionarObjeto(&esfera);
  cenario->adicionarObjeto(&cilindro);
  cenario->adicionarObjeto(&cone);
  cenario->adicionarLuz(&luzPontual);
  cenario->pintarCanvas(renderer);
  //Fim Cenario
  
  s.update(renderer);
  s.listenEventQuit(window);
  return 0;

}
