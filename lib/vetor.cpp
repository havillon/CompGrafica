#include "../include/vetor.h"

Vetor::Vetor(){};

Vetor::Vetor(double x, double y, double z, double a){
    this->v[0] = x;
    this->v[1] = y;
    this->v[2] = z;
    this->v[3] = a;
};

void Vetor::set(double x, double y, double z, double a){
    this->v[0] = x;
    this->v[1] = y;
    this->v[2] = z;
    this->v[3] = a;
};



