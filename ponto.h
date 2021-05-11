#ifndef PONTO_H
#define PONTO_H


class Ponto{
    private:
        float coods[3];
    public:
        Ponto();
        Ponto(float x,float y,float z);
        Ponto(float x,float y);
        void setCoods(float x,float y,float z);
        float* getCoods();
};

#endif // PONTO_H
