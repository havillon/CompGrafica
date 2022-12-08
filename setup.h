#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "src/cenario/cenario.h"
#include "src/canvas.h"
#include "src/janela.h"
#include "src/observador.h"
#include "src/algebraLinear/vetor.h"
#include "src/algebraLinear/algebraLinear.h"


class Setup {

public:

	void paintPixel(SDL_Renderer *renderer, int x, int y);

	void update(SDL_Renderer *renderer);

	void setPaintColor(SDL_Renderer *renderer, int r, int g, int b, int a);

	void setWindowBackground(SDL_Renderer *renderer, int r, int g, int b, int a);

	void listenEventQuit(SDL_Window *window);

	void initializeSDLAndWindow(SDL_Window **window, SDL_Renderer **renderer, int width, int height);

	void pintarCanvas (SDL_Renderer *renderer, Canvas *canvas, Observador observador, Janela janela, Esfera* esfera, Vetor fundo, int d);

	void renderizar(SDL_Renderer *renderer, Canvas canvas);
};