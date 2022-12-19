#include "include/setup.h"
#include "include/cenario.h"

AlgebraLinear al;

int main(int argc, char *argv[]){
  //Observador
  Vetor p0 (0,0,0,1);
  Observador obs (p0);
  //Fim Observador
  
  //Janela
  int dJanela = 50;
  Vetor cJanela (0,0, -dJanela, 1);
  Janela janela (cJanela, 125, 125, 500, 500, dJanela);
  //Fim Janela
  
  //Esfera
  //double raio, Vetor centro, Vetor Ke, Vetor Kd, Vetor Ka, double shininess
  Esfera esfera(
    5, 
    Vetor(130, 10, -360, 0), 
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
    Vetor(130.0, -160.0, -360.0, 0),
    Vetor(0.0, 1.0, 0.0, 0.0)
  );

  cilindro.setKa(Vetor(0.824, 0.706, 0.549, 0));
  cilindro.setKd(Vetor(0.824, 0.706, 0.549, 0));
  cilindro.setKe(Vetor(0.824, 0.706, 0.549, 0));
  cilindro.setShininess(10);
  
  //Cone 
  //altura, raio, centrobase, direcao
  Cone cone (
    80.0,
    30.0,
    Vetor(130, -70, -360, 0),
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
  LuzPontual luzPontual (Vetor(0.5, 0.5, 0.5, 1), Vetor(0, 130, -200, 0));
  LuzSpot luzSpot (Vetor(0.3, 0.3, 0.3, 0), Vetor(0, -1, 0, 0), Vetor(0, 120, -70, 0), M_PI/8);
  Canvas c;

  //Planos
  //Vetor p_pi, Vetor n_pi, Vetor Ke, Vetor Kd, Vetor Ka, double shininess
  // Plano planoChao (Vetor(0, -150, 0, 0), Vetor(0, 1, 0, 0), Vetor(0.2, 0.7, 0.2, 0), Vetor(0.2, 0.7, 0.2, 0), Vetor(0.2, 0.7, 0.2, 0), 10); 
  Plano paredeDireita (Vetor(200, -150, 0, 0), Vetor(-1, 0, 0, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), 10);
  Plano paredeFrontal (Vetor(200, -150, -400, 0), Vetor(0, 0, 1, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), 10);
  Plano paredeEsquerda (Vetor(-200, -150, 0, 0), Vetor(1, 0, 0, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), 10);
  Plano teto (Vetor(0, 150, 0, 0), Vetor(0, -1, 0, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), Vetor(0.686, 0.933, 0.933, 0), 10);
 
  PlanoComTextura planoChao (new Imagem("texturas/Madeira.jpg"), Vetor(0, -150, 0, 0), Vetor(0, 1, 0, 0), 10.0); 
  
  //Cubo
  //Vetor centroBase, double comprimentoAresta, Vetor Ka, Vetor Kd, Vetor Ke, double shininess
  Cubo cubo;

  //Cama

  double larguraPerna = 8.0;
  double alturaPerna = 30.0;
  double larguraColchao = 200 + 2*larguraPerna;
  double alturaColchao = 20;
  double comprimentoColchao = 80;

  Malha perna1 = cubo.criarCubo(
    Vetor(0.5, 0, 0.5, 0),
    40.0,
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    10
  );

  perna1.escala(larguraPerna, alturaPerna, larguraPerna);
  perna1.translacao(-200, -150, -400); //canto

  Malha perna2 = cubo.criarCubo(
    Vetor(0.5, 0, 0.5, 0),
    40.0,
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    10
  );

  perna2.escala(larguraPerna, alturaPerna, larguraPerna);
  perna2.translacao(-200, -150, -400 + comprimentoColchao);

  Malha perna3 = cubo.criarCubo(
    Vetor(0.5, 0, 0.5, 0),
    40.0,
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    10
  );

  perna3.escala(8, 30, 8);
  perna3.translacao(-200 + larguraColchao, -150, -400);

  Malha perna4 = cubo.criarCubo(
    Vetor(0.5, 0, 0.5, 0),
    40.0,
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    10
  );

  perna4.escala(8, 30, 8);
  perna4.translacao(-200 + larguraColchao, -150, -400 + comprimentoColchao);


  Malha colchao = cubo.criarCubo(
    Vetor(0.5, 0, 0.5, 0),
    40.0,
    Vetor(0.8, 0.8, 0.9, 0),
    Vetor(0.8, 0.8, 0.9, 0),
    Vetor(0.8, 0.8, 0.9, 0),
    10
  );

  colchao.escala(larguraColchao + larguraPerna, alturaColchao, comprimentoColchao);
  colchao.translacao(-200, -150 + 2*alturaColchao-10, -400 + larguraPerna);



  //Estante

  double larguraEstante = 60.0;
  double alturaEstante = 8.0;
  double comprimentoEstante = 30.0;

  Malha estante = cubo.criarCubo(
    Vetor(0.5, 0, 0.5, 0),
    40.0,
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    Vetor((double)99/255, (double)28/255, (double)4/255, 0),
    10
  );

  estante.escala(larguraEstante, alturaEstante, comprimentoEstante);
  estante.translacao(0-larguraEstante, -150 + 200, -400); //partindo do canto inferior esquerdo


  //Livros
  Malha livro1 = cubo.criarCubo(
    Vetor(0.5, 0, 0.5, 0),
    40.0,
    Vetor(0.9, 0.1, 0.1, 0),
    Vetor(0.9, 0.1, 0.1, 0),
    Vetor(0.9, 0.1, 0.1, 0),
    10
  );

  livro1.escala(8.0, 30.0, 20.0);
  livro1.translacao(-20, 50+15-8, -400);

  Malha livro2 = cubo.criarCubo(
    Vetor(0.5, 0, 0.5, 0),
    40.0,
    Vetor(0.4, 0.2, 0.6, 0),
    Vetor(0.4, 0.2, 0.6, 0),
    Vetor(0.4, 0.2, 0.6, 0),
    10
  );

  livro2.escala(8.0, 30.0, 20.0);
  livro2.translacao(-20 -8, 50+15-8, -400);

  Malha livro3 = cubo.criarCubo(
    Vetor(0.5, 0, 0.5, 0),
    40.0,
    Vetor(0.3, 0.7, 0.5, 0),
    Vetor(0.3, 0.7, 0.5, 0),
    Vetor(0.3, 0.7, 0.5, 0),
    10
  );

  livro3.escala(8.0, 30.0, 20.0);
  livro3.translacao(-20 -8*2, 50+15-8, -400);

  Malha livro4 = cubo.criarCubo(
    Vetor(0.5, 0, 0.5, 0),
    40.0,
    Vetor(153.0/255.0, 67.0/255.0, 9.0/255.0, 0),
    Vetor(153.0/255.0, 67.0/255.0, 9.0/255.0, 0),
    Vetor(153.0/255.0, 67.0/255.0, 9.0/255.0, 0),
    10
  );

  livro4.escala(8.0, 30.0, 20.0);
  livro4.translacao(-20 -8*3, 50+15-8, -400);

  Malha livro5 = cubo.criarCubo(
    Vetor(0.5, 0, 0.5, 0),
    40.0,
    Vetor(25.0/255.0, 74.0/255.0, 120.0/255.0, 0),
    Vetor(25.0/255.0, 74.0/255.0, 120.0/255.0, 0),
    Vetor(25.0/255.0, 74.0/255.0, 120.0/255.0, 0),
    10
  );

  livro5.escala(8.0, 30.0, 20.0);
  livro5.translacao(-20 -8*4, 50+15-8, -400);


  //Arvore tarefa 5
  Malha malha = cubo.criarCubo(
    Vetor(0.5, 0, 0.5, 0),
    40.0,
    Vetor(1, 0.078, 0.576, 0),
    Vetor(1, 0.078, 0.576, 0),
    Vetor(1, 0.078, 0.576, 0),
    10
  );

  malha.escala(40.0, 10.0, 20.0);
  malha.translacao(130.0-20.0, -160.0, -370.0);


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
  cenario->adicionarObjeto(&perna1);
  cenario->adicionarObjeto(&perna2);
  cenario->adicionarObjeto(&perna3);
  cenario->adicionarObjeto(&perna4);
  cenario->adicionarObjeto(&colchao);
  cenario->adicionarObjeto(&estante);
  cenario->adicionarObjeto(&livro1);
  cenario->adicionarObjeto(&livro2);
  cenario->adicionarObjeto(&livro3);
  cenario->adicionarObjeto(&livro4);
  cenario->adicionarObjeto(&livro5);
  cenario->adicionarObjeto(&malha);
  cenario->adicionarLuz(&luzPontual);
  // cenario->adicionarLuz(&luzSpot);
  cenario->pintarCanvas();
  //Fim Cenario
  
  return 0;

}
