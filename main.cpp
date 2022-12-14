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
  //double raio, Vetor centro, Vetor Ke, Vetor Kd, Vetor Ka, double shininess
  Esfera esfera(
    5, 
    Vetor(0, 95, -200, 0), 
    Vetor(0.854, 0.647, 0.125, 0),
    Vetor(0.854, 0.647, 0.125, 0),
    Vetor(0.854, 0.647, 0.125, 0),
    10
  );
  //Fim Esfera

  //Cilindro 
  //altura, raio, centrobase, direcao
  Cilindro cilindro (
    90.0,
    5.0,
    Vetor(0.0, -150.0, -200.0, 0),
    Vetor(0.0, 1.0, 0.0, 0.0)
  );

  cilindro.setKa(Vetor(0.824, 0.706, 0.549, 0));
  cilindro.setKd(Vetor(0.824, 0.706, 0.549, 0));
  cilindro.setKe(Vetor(0.824, 0.706, 0.549, 0));
  cilindro.setShininess(10);
  
  //Cone 
  //altura, raio, centrobase, direcao
  Cone cone (
    150.0,
    90.0,
    Vetor(0, -60, -200, 0),
    Vetor (0,1,0,0)
  );
  cone.setKa(Vetor(0, 1, 0.498, 1));
  cone.setKd(Vetor(0, 1, 0.498, 1));
  cone.setKe(Vetor(0, 1, 0.498, 1));
  cone.setShininess(10.0);
  

  //Cor Fundo
  Vetor fundo (100,100,100,1);
  
  //Luzes
  Vetor luzAmbiente = Vetor(0.3, 0.3, 0.3, 1);
  Iluminacao luzPontual = Iluminacao(Vetor(0.7, 0.7, 0.7, 1), Vetor(-100, 140, -20, 0));
  
  Canvas c;

  //Planos
  //Vetor p_pi, Vetor n_pi, Vetor Ke, Vetor Kd, Vetor Ka, double shininess
  Plano planoChao (Vetor(0, -150, 0, 0), Vetor(0, 1, 0, 0), Vetor(0.2, 0.7, 0.2, 0), Vetor(0.2, 0.7, 0.2, 0), Vetor(0.2, 0.7, 0.2, 0), 10); 
  Plano paredeDireita (Vetor(200, -150, 0, 0), Vetor(-1, 0, 0, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), 10);
  Plano paredeFrontal (Vetor(200, -150, -400, 0), Vetor(0, 0, 1, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), 10);
  Plano paredeEsquerda (Vetor(-200, -150, 0, 0), Vetor(1, 0, 0, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), 10);
  Plano teto (Vetor(0, 150, 0, 0), Vetor(0, -1, 0, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), 10);
 
  //Cubo
  //Vetor centroBase, double comprimentoAresta, Vetor Ka, Vetor Kd, Vetor Ke, double shininess
  Cubo cubo;
  Malha malha = cubo.criarCubo(
    Vetor(0, -150, -165, 0),
    40,
    Vetor(0, 0.078, 0.576, 0),
    Vetor(0, 0.078, 0.576, 0),
    Vetor(0, 0.078, 0.576, 0),
    10
  );

  Setup s;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  s.initializeSDLAndWindow(&window, &renderer, 500, 500);

  //Cenario
  Cenario *cenario = new Cenario(fundo, c, janela, luzAmbiente, obs);
  cenario->adicionarObjeto(&planoChao);
  cenario->adicionarObjeto(&paredeDireita);
  cenario->adicionarObjeto(&paredeFrontal);
  cenario->adicionarObjeto(&paredeEsquerda);
  cenario->adicionarObjeto(&teto);
  cenario->adicionarObjeto(&cilindro);
  cenario->adicionarObjeto(&cone);
  cenario->adicionarObjeto(&esfera);
  cenario->adicionarObjeto(&malha);
  cenario->adicionarLuz(&luzPontual);
  cenario->pintarCanvas(renderer);
  //Fim Cenario
  
  s.update(renderer);
  s.listenEventQuit(window);
  return 0;

}
