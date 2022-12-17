#pragma once

#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "algebraLinear.h"

using std::string;

class Imagem {
public:
    Vetor pixel;
    SDL_Surface* imagem;

    void carregarImagem(string path);
    Vetor getPixel(int x, int y);

    int getLargura();
    int getAltura();
    
    Imagem(string path);
    Imagem();    
};