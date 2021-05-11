#ifndef PISTA_H
#define PISTA_H

#include "ponto.h"

class Pista{
public:
    Pista();
    Pista(float l,float c);
    void setCoord(float l,float c);
    void setVertices();
    void desenhaPista();
    float* getVertice(int index);
    float largura;
    float comprimento;
    Ponto vertices[4];
};

#endif // PISTA_H
