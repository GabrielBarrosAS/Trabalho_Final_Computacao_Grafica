#include "ponto.h"

Ponto::Ponto(){

}

Ponto::Ponto(float x,float y,float z){
    this->coods[0] = x;
    this->coods[1] = y;
    this->coods[2] = z;
}

Ponto::Ponto(float x,float y){
    this->coods[0] = x;
    this->coods[1] = y;
    this->coods[2] = 1;
}

void Ponto::setCoods(float x,float y,float z){
    this->coods[0] = x;
    this->coods[1] = y;
    this->coods[2] = z;
}

float* Ponto::getCoods(){
    return this->coods;
}
