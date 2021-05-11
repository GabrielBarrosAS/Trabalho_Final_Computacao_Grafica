#ifndef CAMERA_H
#define CAMERA_H

#include "ponto.h"
#include "carro.h"
#include "pista.h"

class Camera{
public:
    Camera();
    Ponto posicao;
    Ponto at;
    Ponto up;
    int camCar;
    void setPropriedades(Ponto pos,Ponto olhandoPara,Ponto vetUp);
    float getPosicao(int index);
    float getAt(int index);
    float getUp(int index);
    void setPosicao(float x,float y,float z);
    void setAt(float x,float y,float z);
    void setUp(float x,float y,float z);
    void atualizar(carro car,Pista pista,int key);
};

#endif // CAMERA_H
