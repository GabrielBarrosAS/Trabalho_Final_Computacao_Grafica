#include "carro.h"
#include "ponto.h"
#include "GL/glu.h"
#include "stdio.h"
#include "pista.h"
#include "stdio.h"
#include "math.h"
#include "camera.h"
carro::carro(){

}

void carro::setPropriedades(int a,int l,int c){
    altura = a;
    largura = l;
    comprimento = c;
    setVertices();
    aux.setCoods(0,0,0);
    angulo = 0;
    passosX = 0;
    passosZ = 0;
}

void carro::setVertices(){
    vertices[0].setCoods(comprimento,0,largura);
    vertices[1].setCoods(comprimento,2*altura,largura);
    vertices[2].setCoods(comprimento,2*altura,-largura);
    vertices[3].setCoods(comprimento,0,-largura);
    vertices[4].setCoods(-comprimento,0,-largura);
    vertices[5].setCoods(-comprimento,2*altura,-largura);
    vertices[6].setCoods(-comprimento,2*altura,largura);
    vertices[7].setCoods(-comprimento,0,largura);
}

float *carro::getVertices(int v){
    return vertices[v].getCoods();
}

void carro::desenhaCarro(){
    glPushMatrix();
    glTranslatef(aux.getCoods()[0],aux.getCoods()[1],aux.getCoods()[2]);
    glRotatef(angulo,0,1,0);
    glBegin(GL_QUADS);
        glColor3f(1,0,0);//FRENTE VERMELHA
        glVertex3fv(getVertices(0));
        glVertex3fv(getVertices(1));
        glVertex3fv(getVertices(2));
        glVertex3fv(getVertices(3));
        glColor3f(0,0,0);//DIREITA PRETA
        glVertex3fv(getVertices(1));
        glVertex3fv(getVertices(0));
        glVertex3fv(getVertices(7));
        glVertex3fv(getVertices(6));
        glColor3f(0,0,1);//ESQUERDA AZUL
        glVertex3fv(getVertices(3));
        glVertex3fv(getVertices(2));
        glVertex3fv(getVertices(5));
        glVertex3fv(getVertices(4));
        glColor3f(1,0,1);//TRASEIRA ROSA
        glVertex3fv(getVertices(4));
        glVertex3fv(getVertices(5));
        glVertex3fv(getVertices(6));
        glVertex3fv(getVertices(7));
        glColor3f(1,1,0);//CIMA AMARELO
        glVertex3fv(getVertices(2));
        glVertex3fv(getVertices(1));
        glVertex3fv(getVertices(6));
        glVertex3fv(getVertices(5));
        glColor3f(1,1,1);//BAIXO BRANCO
        glVertex3fv(getVertices(3));
        glVertex3fv(getVertices(0));
        glVertex3fv(getVertices(7));
        glVertex3fv(getVertices(4));
        glEnd();
        glPopMatrix();
}

void carro::andar(){
    switch (angulo) {
        case 0:
            aux.setCoods(aux.getCoods()[0] + 1,aux.getCoods()[1],aux.getCoods()[2]);
        break;
        case 90:
            aux.setCoods(aux.getCoods()[0],aux.getCoods()[1],aux.getCoods()[2] - 1);
        break;
        case 180:
            aux.setCoods(aux.getCoods()[0] - 1,aux.getCoods()[1],aux.getCoods()[2]);
        break;
        case 270:
            aux.setCoods(aux.getCoods()[0],aux.getCoods()[1],aux.getCoods()[2] + 1);
        break;
    }
}

void carro::re(){
    switch (angulo) {
        case 0:
            aux.setCoods(aux.getCoods()[0] - 1,aux.getCoods()[1],aux.getCoods()[2]);
        break;
        case 90:
            aux.setCoods(aux.getCoods()[0],aux.getCoods()[1],aux.getCoods()[2] + 1);
        break;
        case 180:
            aux.setCoods(aux.getCoods()[0] + 1,aux.getCoods()[1],aux.getCoods()[2]);
        break;
        case 270:
            aux.setCoods(aux.getCoods()[0],aux.getCoods()[1],aux.getCoods()[2] - 1);
        break;
    }
}

void carro::girarEsq(){
    angulo = (angulo < 270) ? angulo + 90 : 0;
}

void carro::girarDir(){
    angulo = (angulo >= 90) ? angulo - 90 : 270;
}

int carro::colisao(Pista p){
    switch (angulo) {
        case 0:
            if(aux.getCoods()[0] > p.comprimento - comprimento){
                angulo = (angulo + 180 > 350) ? angulo+180-360 : angulo+180;
                aux.setCoods(p.comprimento - 3*comprimento,aux.getCoods()[1],aux.getCoods()[2]);
                return 1;
            }else{
                if(aux.getCoods()[0] < -p.comprimento + comprimento){
                    aux.setCoods(aux.getCoods()[0]+5,aux.getCoods()[1],aux.getCoods()[2]);
                }
            }
        break;
        case 90:
            if(aux.getCoods()[2] < -p.largura + comprimento){
                angulo = (angulo + 180 > 350) ? angulo+180-360 : angulo+180;
                aux.setCoods(aux.getCoods()[0],aux.getCoods()[1],-p.largura + 3*comprimento);
                return 2;
            }else{
                if(aux.getCoods()[2] > p.largura - comprimento){
                    aux.setCoods(aux.getCoods()[0],aux.getCoods()[1],aux.getCoods()[2]-5);
                }
            }
        break;
        case 180:
            if(aux.getCoods()[0] < -p.comprimento + comprimento){
                angulo = (angulo + 180 > 350) ? angulo+180-360 : angulo+180;
                aux.setCoods(-p.comprimento + 3*comprimento,aux.getCoods()[1],aux.getCoods()[2]);
                return 3;
            }else{
                if(aux.getCoods()[0] > p.comprimento - comprimento){
                    aux.setCoods(aux.getCoods()[0]-5,aux.getCoods()[1],aux.getCoods()[2]);
                }
            }
        break;
        case 270:
            if(aux.getCoods()[2] > p.largura - comprimento){
                angulo = (angulo + 180 > 350) ? angulo+180-360 : angulo+180;
                aux.setCoods(aux.getCoods()[0],aux.getCoods()[1],p.largura - 3*comprimento);
                return 4;
            }else{
                if(aux.getCoods()[2] < -p.largura + comprimento){
                    aux.setCoods(aux.getCoods()[0],aux.getCoods()[1],aux.getCoods()[2]+5);
                }
            }
        break;
    }
    return 0;
}

