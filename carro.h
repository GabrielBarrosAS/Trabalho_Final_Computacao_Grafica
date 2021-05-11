#ifndef CARRO_H
#define CARRO_H

#include "ponto.h"
#include "pista.h"

class carro{
    private:
        Ponto vertices[8];

    public:
        int altura;
        int largura;
        int comprimento;
        int angulo;
        Ponto aux;
        int passosX;
        int passosZ;
        carro();
        void setPropriedades(int a, int l,int c);
        void setVertices();
        float* getVertices(int v);
        void desenhaCarro();
        void andar();
        void re();
        void girarEsq();
        void girarDir();
        int colisao(Pista p);
};

#endif // CARRO_H
