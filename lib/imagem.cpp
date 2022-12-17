#include "../include/imagem.h"

void Imagem::carregarImagem(const string path) {

    SDL_Surface* imagem = IMG_Load(path.c_str());

    if (imagem == nullptr) {
        std::cout << "não foi possível carregar a imagem" << std::endl;
        return;
    }

    int superficie = SDL_LockSurface (imagem);

    if (superficie != 0) {
        std::cout << "erro ao travar os bytes da textura" << std::endl;
        SDL_FreeSurface (imagem);
        return;
    }

    if (this->imagem != nullptr) SDL_FreeSurface (this->imagem);

    this->imagem = imagem;

}

Vetor Imagem::getPixel (int x, int y) {

    int selectedPixel;

    int bytesPerPixel = this->imagem->format->BytesPerPixel;
    Uint8* pixel = (Uint8*) this->imagem->pixels + y * this->imagem->pitch + x * bytesPerPixel;

    switch (bytesPerPixel) {
        case 1:
            selectedPixel = *pixel;
            break;
        case 2:
            selectedPixel = *((Uint16*) pixel);
            break;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                selectedPixel = pixel[0] << 16 | pixel[1] << 8 | pixel[2];
            } else {
                selectedPixel = pixel[0] | pixel[1] << 8 | pixel[2] << 16;
            }
            break;
        case 4:
            selectedPixel = *((Uint32*)pixel);
            break;
        default:
            selectedPixel = 0;
    }

    SDL_Color rgb;
    SDL_GetRGB(selectedPixel, this->imagem->format, &rgb.r, &rgb.g, &rgb.b);

    return Vetor (rgb.r, rgb.g, rgb.b, 0);

}

int Imagem::getLargura() {
    return this->imagem->w;
}

int Imagem::getAltura () {
    return this->imagem->h;
}

Imagem::Imagem () {}

Imagem::Imagem (string path) {
    this->carregarImagem(path);
}