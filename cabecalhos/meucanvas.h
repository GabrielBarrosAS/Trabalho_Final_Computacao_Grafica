#ifndef MEUCANVAS_H
#define MEUCANVAS_H

#include "carro.h"
#include "ponto.h"
#include "pista.h"
#include "camera.h"

#include <QGLWidget>

class MeuCanvas : public QGLWidget{
public:
    Pista pista;
    carro car[10];
    Camera camera;
    int quantidadeCarros;
    int index;
    MeuCanvas(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void keyPressEvent(QKeyEvent *e);
public slots:
    void idleGL();
};

#endif // MEUCANVAS_H
