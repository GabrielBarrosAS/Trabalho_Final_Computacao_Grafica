#include "meucanvas.h"
#include "ponto.h"
#include "GL/glu.h"
#include "carro.h"
#include "QKeyEvent"
#include "stdio.h"
#include "stdlib.h"
#include <time.h>
MeuCanvas::MeuCanvas(QWidget *parent) : QGLWidget(parent){

}

void MeuCanvas::initializeGL(){
    glEnable(GL_DEPTH_TEST);
    glClearColor(0,0,0,1);
    quantidadeCarros = 1;
    index = 0;
    car[index].setPropriedades(2,3,5);
    pista.setCoord(60,120);
    camera.setPropriedades({20,20,20},{0,20,-20},{0,1,0});
}

void MeuCanvas::paintGL(){
    glViewport(0,0,width(),height());
    float largura, altura;
    altura = 2;
    largura = 2.0*width()/height();

    car[index].setVertices();
    int i = car[index].colisao(pista);
    for(int j = 0;j < quantidadeCarros ;j++) {
    for(int i = 0;i < quantidadeCarros ;i++) {
        if(i != j){
            switch(car[j].angulo) {
                case 0:
                    if(car[j].aux.getCoods()[0] + car[j].comprimento == car[i].aux.getCoods()[0]-car[i].comprimento
                    &&((car[j].aux.getCoods()[2] < car[i].aux.getCoods()[2]+2*car[i].largura && car[j].aux.getCoods()[2] > car[i].aux.getCoods()[2]-2*car[i].largura)
                    ||(car[j].aux.getCoods()[2] < car[i].aux.getCoods()[2]+car[i].comprimento+car[i].largura && car[j].aux.getCoods()[2] > car[i].aux.getCoods()[2]-car[i].comprimento-car[i].largura))){

                        car[j].angulo = (car[j].angulo + 180 > 350) ? car[j].angulo+180-360 : car[j].angulo+180;
                    }
                break;
                case 180:
                    if(car[j].aux.getCoods()[0] - car[j].comprimento == car[i].aux.getCoods()[0]+car[i].comprimento
                    &&((car[j].aux.getCoods()[2] < car[i].aux.getCoods()[2]+2*car[i].largura && car[j].aux.getCoods()[2] > car[i].aux.getCoods()[2]-2*car[i].largura)
                    ||(car[j].aux.getCoods()[2] < car[i].aux.getCoods()[2]+car[i].comprimento+car[i].largura && car[j].aux.getCoods()[2] > car[i].aux.getCoods()[2]-car[i].comprimento-car[i].largura))){

                        car[j].angulo = (car[j].angulo + 180 > 350) ? car[j].angulo+180-360 : car[j].angulo+180;
                    }
                break;
                case 90:
                    if(car[j].aux.getCoods()[2] - car[j].comprimento == car[i].aux.getCoods()[2]+car[i].comprimento
                    &&((car[j].aux.getCoods()[0] < car[i].aux.getCoods()[0]+2*car[i].largura && car[j].aux.getCoods()[0] > car[i].aux.getCoods()[0]-2*car[i].largura)
                    ||(car[j].aux.getCoods()[0] < car[i].aux.getCoods()[0]+car[i].comprimento+car[i].largura && car[j].aux.getCoods()[0] > car[i].aux.getCoods()[0]-car[i].comprimento-car[i].largura))){

                        car[j].angulo = (car[j].angulo + 180 > 350) ? car[j].angulo+180-360 : car[j].angulo+180;
                    }
                break;
                case 270:
                    if(car[j].aux.getCoods()[2] + car[j].comprimento == car[i].aux.getCoods()[2]-car[i].comprimento
                    &&((car[j].aux.getCoods()[0] < car[i].aux.getCoods()[0]+2*car[i].largura && car[j].aux.getCoods()[0] > car[i].aux.getCoods()[0]-2*car[i].largura)
                    ||(car[j].aux.getCoods()[0] < car[i].aux.getCoods()[0]+car[i].comprimento+car[i].largura && car[j].aux.getCoods()[0] > car[i].aux.getCoods()[0]-car[i].comprimento-car[i].largura))){

                        car[j].angulo = (car[j].angulo + 180 > 350) ? car[j].angulo+180-360 : car[j].angulo+180;
                    }
                break;
            }
        }
    }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-largura/2,largura/2,-altura/2,altura/2,1,1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.atualizar(car[index],pista,i);
    gluLookAt(camera.getPosicao(0),camera.getPosicao(1),camera.getPosicao(2),
              camera.getAt(0),camera.getAt(1),camera.getAt(2),
              camera.getUp(0),camera.getUp(1),camera.getUp(2));
    glBegin(GL_LINES);
        glColor3f(1,0,1);
        glVertex3fv(car[index].aux.getCoods());
        glVertex3f(car[index].aux.getCoods()[0],50,car[index].aux.getCoods()[2]);
    glEnd();
    pista.desenhaPista();
    for(int i = 0;i < quantidadeCarros;i++){
        car[i].desenhaCarro();
    }
}

void MeuCanvas::keyPressEvent(QKeyEvent *e){
    char tecla = e->text().data()->unicode();
    switch (tecla) {
        //Movimentando o carro
        case 'w': car[index].andar();break;
        case 's': car[index].re();break;
        case 'q': car[index].girarEsq();break;
        case 'e': car[index].girarDir();break;

        //Alterando coordenadas de camera uma por uma
        case 'X': camera.setPosicao(camera.getPosicao(0)+1,camera.getPosicao(1),camera.getPosicao(2));break;
        case 'x': camera.setPosicao(camera.getPosicao(0)-1,camera.getPosicao(1),camera.getPosicao(2));break;
        case 'Y': camera.setPosicao(camera.getPosicao(0),camera.getPosicao(1)+1,camera.getPosicao(2));break;
        case 'y': camera.setPosicao(camera.getPosicao(0),camera.getPosicao(1)-1,camera.getPosicao(2));break;
        case 'Z': camera.setPosicao(camera.getPosicao(0),camera.getPosicao(1),camera.getPosicao(2)+1);break;
        case 'z': camera.setPosicao(camera.getPosicao(0),camera.getPosicao(1),camera.getPosicao(2)-1);break;

        //Cameras pre definidas
        case '0': camera.setPosicao(20,20,20);camera.setAt(0,0,0);camera.camCar = 0;break;
        case '1': camera.setPosicao(1,100,0);camera.setAt(0,0,0);camera.camCar = 0;break;
        case '2': camera.setPosicao(0,80,-pista.largura*2);camera.setAt(0,0,0);camera.camCar = 0;break;

        //Cameras relacionadas ao carro
        case '8': camera.camCar = 8;break;
        case '9': camera.camCar = 9;break;

        //Gerando novos carros
        case 'n':
            if(quantidadeCarros < 9){
                quantidadeCarros++;
                index = quantidadeCarros-1;
                car[index].setPropriedades(2,3,5);
            }
        break;
        case 't':
            if(index == quantidadeCarros-1){
                index = 0;
            }else{
                index++;
            }
        break;
        case 'r':
            if(quantidadeCarros < 9){
                quantidadeCarros++;
                index = quantidadeCarros-1;
                car[index].setPropriedades(2,3,5);
            }
            srand(time(NULL));
            index = rand() % (quantidadeCarros);
            srand(time(NULL));
            int mov = rand() % 20;
            (mov <= 16) ? car[index].andar() : (mov <= 18) ? car[index].girarDir():car[index].girarEsq();
        break;
    }
    updateGL();
}

void MeuCanvas::idleGL(){
    for(int k = 0;k < quantidadeCarros;k++){
        car[k].andar();
        car[k].colisao(pista);
        for(int j = 0;j < quantidadeCarros ;j++) {
            for(int i = 0;i < quantidadeCarros ;i++) {
                if(i != j){
                    switch(car[j].angulo) {
                        case 0:
                            if(car[j].aux.getCoods()[0] + car[j].comprimento == car[i].aux.getCoods()[0]-car[i].comprimento
                            &&((car[j].aux.getCoods()[2] < car[i].aux.getCoods()[2]+2*car[i].largura && car[j].aux.getCoods()[2] > car[i].aux.getCoods()[2]-2*car[i].largura)
                            ||(car[j].aux.getCoods()[2] < car[i].aux.getCoods()[2]+car[i].comprimento+car[i].largura && car[j].aux.getCoods()[2] > car[i].aux.getCoods()[2]-car[i].comprimento-car[i].largura))){

                                car[j].angulo = (car[j].angulo + 180 > 350) ? car[j].angulo+180-360 : car[j].angulo+180;
                            }
                            break;
                        case 180:
                            if(car[j].aux.getCoods()[0] - car[j].comprimento == car[i].aux.getCoods()[0]+car[i].comprimento
                            &&((car[j].aux.getCoods()[2] < car[i].aux.getCoods()[2]+2*car[i].largura && car[j].aux.getCoods()[2] > car[i].aux.getCoods()[2]-2*car[i].largura)
                            ||(car[j].aux.getCoods()[2] < car[i].aux.getCoods()[2]+car[i].comprimento+car[i].largura && car[j].aux.getCoods()[2] > car[i].aux.getCoods()[2]-car[i].comprimento-car[i].largura))){

                                car[j].angulo = (car[j].angulo + 180 > 350) ? car[j].angulo+180-360 : car[j].angulo+180;
                            }
                            break;
                        case 90:
                            if(car[j].aux.getCoods()[2] - car[j].comprimento == car[i].aux.getCoods()[2]+car[i].comprimento
                            &&((car[j].aux.getCoods()[0] < car[i].aux.getCoods()[0]+2*car[i].largura && car[j].aux.getCoods()[0] > car[i].aux.getCoods()[0]-2*car[i].largura)
                            ||(car[j].aux.getCoods()[0] < car[i].aux.getCoods()[0]+car[i].comprimento+car[i].largura && car[j].aux.getCoods()[0] > car[i].aux.getCoods()[0]-car[i].comprimento-car[i].largura))){

                                car[j].angulo = (car[j].angulo + 180 > 350) ? car[j].angulo+180-360 : car[j].angulo+180;
                            }
                            break;
                        case 270:
                            if(car[j].aux.getCoods()[2] + car[j].comprimento == car[i].aux.getCoods()[2]-car[i].comprimento
                            &&((car[j].aux.getCoods()[0] < car[i].aux.getCoods()[0]+2*car[i].largura && car[j].aux.getCoods()[0] > car[i].aux.getCoods()[0]-2*car[i].largura)
                            ||(car[j].aux.getCoods()[0] < car[i].aux.getCoods()[0]+car[i].comprimento+car[i].largura && car[j].aux.getCoods()[0] > car[i].aux.getCoods()[0]-car[i].comprimento-car[i].largura))){

                                car[j].angulo = (car[j].angulo + 180 > 350) ? car[j].angulo+180-360 : car[j].angulo+180;
                            }
                            break;
                    }
                }
            }
        }
    }
    updateGL();
}
