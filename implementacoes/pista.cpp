#include "pista.h"
#include "GL/glu.h"
#include "math.h"
#include "stdio.h"
Pista::Pista()
{

}

Pista::Pista(float l, float c){
    largura = l;
    comprimento = c;
}

void Pista::setCoord(float l, float c){
    largura = l;
    comprimento = c;
    setVertices();
}

void Pista::setVertices(){
    vertices[0].setCoods(-comprimento,-0.1,-largura);
    vertices[1].setCoods(comprimento,-0.1,-largura);
    vertices[2].setCoods(comprimento,-0.1,largura);
    vertices[3].setCoods(-comprimento,-0.1,largura);
}

void Pista::desenhaPista(){
    glColor3f(0,1,0.2);
    glBegin(GL_QUADS);//Gramado
        glVertex3fv(getVertice(0));
        glVertex3fv(getVertice(1));
        glVertex3fv(getVertice(2));
        glVertex3fv(getVertice(3));
    glEnd();

    glColor3f(1,1,1);
    glBegin(GL_QUADS);//Linhas do meio campo
        glVertex3f(-0.5,0,getVertice(0)[2]+5);
        glVertex3f(0.5,0,getVertice(0)[2]+5);
        glVertex3f(0.5,0,-getVertice(0)[2]-5);
        glVertex3f(-0.5,0,-getVertice(0)[2]-5);
    glEnd();
    glBegin(GL_LINE_STRIP);//Circulo central
        for (int ii = 0; ii <= 360; ii++)   {
            float raio = 0.3*largura;
            float theta = 2.0f * 3.1415926f * float(ii) / float(360);
            float x_externo = raio * cosf(theta);
            float y_externo = raio * sinf(theta);
            float x_interno = (raio-1) * cosf(theta);
            float y_interno = (raio-1) * sinf(theta);
            glVertex3f(x_externo, 0,y_externo);
            glVertex3f(x_interno, 0,y_interno);
        }
    glEnd();
    glBegin(GL_LINE_STRIP);//Circulo central "bola"
        for (int ii = 0; ii <= 360; ii++)   {
            float theta = 2.0f * 3.1415926f * float(ii) / float(360);
            float x_externo = 2 * cosf(theta);
            float y_externo = 2 * sinf(theta);
            float x_interno = 1 * cosf(theta);
            float y_interno = 1 * sinf(theta);
            glVertex3f(x_externo, 0,y_externo);
            glVertex3f(x_interno, 0,y_interno);
        }
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(getVertice(0)[0]+5,0,getVertice(0)[2]+5);
        glVertex3f(getVertice(1)[0]-5,0,getVertice(1)[2]+5);
        glVertex3f(getVertice(2)[0]-5,0,getVertice(2)[2]-5);
        glVertex3f(getVertice(3)[0]+5,0,getVertice(3)[2]-5);
    glEnd();

    glBegin(GL_QUADS);
        float disLateral = 0.65*largura;
        float disFundo = 0.35*comprimento;
        //Área esquerda
        glVertex3f(getVertice(0)[0]+5,0,getVertice(0)[2]+disLateral);
        glVertex3f(getVertice(0)[0]+5,0,getVertice(0)[2]+disLateral+1);
        glVertex3f(getVertice(0)[0]+disFundo,0,getVertice(0)[2]+disLateral+1);
        glVertex3f(getVertice(0)[0]+disFundo,0,getVertice(0)[2]+disLateral);

        glVertex3f(getVertice(0)[0]+disFundo,0,getVertice(0)[2]+disLateral+1);
        glVertex3f(getVertice(0)[0]+disFundo-1,0,getVertice(0)[2]+disLateral+1);
        glVertex3f(getVertice(3)[0]+disFundo-1,0,getVertice(3)[2]-disLateral);
        glVertex3f(getVertice(3)[0]+disFundo,0,getVertice(3)[2]-disLateral);

        glVertex3f(getVertice(3)[0]+disFundo,0,getVertice(3)[2]-disLateral);
        glVertex3f(getVertice(3)[0]+disFundo,0,getVertice(3)[2]-disLateral+1);
        glVertex3f(getVertice(3)[0]+5,0,getVertice(3)[2]-disLateral+1);
        glVertex3f(getVertice(3)[0]+5,0,getVertice(3)[2]-disLateral);
        //Área direita
        glVertex3f(getVertice(1)[0]-5,0,getVertice(1)[2]+disLateral);
        glVertex3f(getVertice(1)[0]-5,0,getVertice(1)[2]+disLateral+1);
        glVertex3f(getVertice(1)[0]-disFundo,0,getVertice(1)[2]+disLateral+1);
        glVertex3f(getVertice(1)[0]-disFundo,0,getVertice(1)[2]+disLateral);

        glVertex3f(getVertice(1)[0]-disFundo,0,getVertice(1)[2]+disLateral+1);
        glVertex3f(getVertice(1)[0]-disFundo+1,0,getVertice(1)[2]+disLateral+1);
        glVertex3f(getVertice(2)[0]-disFundo+1,0,getVertice(2)[2]-disLateral);
        glVertex3f(getVertice(2)[0]-disFundo,0,getVertice(2)[2]-disLateral);

        glVertex3f(getVertice(2)[0]-disFundo,0,getVertice(2)[2]-disLateral);
        glVertex3f(getVertice(2)[0]-disFundo,0,getVertice(2)[2]-disLateral+1);
        glVertex3f(getVertice(2)[0]-5,0,getVertice(2)[2]-disLateral+1);
        glVertex3f(getVertice(2)[0]-5,0,getVertice(2)[2]-disLateral);
    glEnd();
    glPushMatrix();
    glTranslatef(getVertice(1)[0]-disFundo,0,0);
    glBegin(GL_LINE_STRIP);//Meia lua direita
        for (int ii = 0; ii <= 360; ii++)   {
            if(ii >= 90 && ii <= 270){
                float raio = 0.2*largura;
                float theta = 2.0f * 3.1415926f * float(ii) / float(360);
                float x_externo = raio* cosf(theta);
                float y_externo = raio * sinf(theta);
                float x_interno = (raio-1) * cosf(theta);
                float y_interno = (raio-1) * sinf(theta);
                glVertex3f(x_externo, 0,y_externo);
                glVertex3f(x_interno, 0,y_interno);
            }
        }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(getVertice(0)[0]+disFundo,0,0);
    glBegin(GL_LINE_STRIP);//Meia lua esquerda
        for (int ii = 0; ii <= 360; ii++)   {
            if(ii <= 90 || ii >= 270){
                float raio = 0.2*largura;
                float theta = 2.0f * 3.1415926f * float(ii) / float(360);
                float x_externo = raio * cosf(theta);
                float y_externo = raio * sinf(theta);
                float x_interno = (raio-1) * cosf(theta);
                float y_interno = (raio-1) * sinf(theta);
                glVertex3f(x_externo, 0,y_externo);
                glVertex3f(x_interno, 0,y_interno);
            }
        }
    glEnd();
    glPopMatrix();
    glColor3f(1,1,1);
    glBegin(GL_QUAD_STRIP);
        glVertex3fv(getVertice(0));
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1],getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1],getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0],getVertice(0)[1],getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
        glVertex3fv(getVertice(0));
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
    glEnd();
    glPushMatrix();
    glTranslatef(0,0,largura*2+comprimento*0.5);
    glBegin(GL_QUAD_STRIP);
        glVertex3fv(getVertice(0));
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1],getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1],getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0],getVertice(0)[1],getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
        glVertex3fv(getVertice(0));
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(comprimento*2+comprimento*0.5,0,0);
    glBegin(GL_QUAD_STRIP);
        glVertex3fv(getVertice(0));
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1],getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1],getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0],getVertice(0)[1],getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
        glVertex3fv(getVertice(0));
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(comprimento*2+comprimento*0.5,0,largura*2+comprimento*0.5);
    glBegin(GL_QUAD_STRIP);
        glVertex3fv(getVertice(0));
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1],getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1],getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0],getVertice(0)[1],getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
        glVertex3fv(getVertice(0));
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]);
        glVertex3f(getVertice(0)[0]-comprimento*0.5,getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
        glVertex3f(getVertice(0)[0],getVertice(0)[1]+largura,getVertice(0)[2]-comprimento*0.5);
    glEnd();
    glPopMatrix();
    for(float i = largura/4,j = -largura;i <= largura;i = i + largura/4,j-=comprimento*0.125){
        glBegin(GL_QUADS);//Arquibancada Vermelha
            glColor3f(1,0,0);
            glVertex3f(getVertice(1)[0],getVertice(1)[1],j);
            glVertex3f(getVertice(0)[0],getVertice(0)[1],j);
            glVertex3f(getVertice(0)[0],i,j);
            glVertex3f(getVertice(1)[0],i,j);
            glColor3f(0.5,0.5,0.5);
            glVertex3f(getVertice(0)[0],i,j);
            glVertex3f(getVertice(1)[0],i,j);
            glVertex3f(getVertice(1)[0],i,j-comprimento*0.125);
            glVertex3f(getVertice(0)[0],i,j-comprimento*0.125);

        glEnd();
    }
    glPushMatrix();
    glTranslatef(0,0,largura);
    glRotatef(180,0,1,0);
    glTranslatef(0,0,largura);
    for(float i = largura/4,j = -largura;i <= largura;i = i + largura/4,j-=comprimento*0.125){
        glBegin(GL_QUADS);//Arquibancada amarela
            glColor3f(1,1,0);
            glVertex3f(getVertice(1)[0],getVertice(1)[1],j);
            glVertex3f(getVertice(0)[0],getVertice(0)[1],j);
            glVertex3f(getVertice(0)[0],i,j);
            glVertex3f(getVertice(1)[0],i,j);
            glColor3f(0.5,0.5,0.5);
            glVertex3f(getVertice(0)[0],i,j);
            glVertex3f(getVertice(1)[0],i,j);
            glVertex3f(getVertice(1)[0],i,j-comprimento*0.125);
            glVertex3f(getVertice(0)[0],i,j-comprimento*0.125);

        glEnd();
    }
    glPopMatrix();
    glPushMatrix();

    glTranslatef(-comprimento,0,0);
    glRotatef(90,0,1,0);
    glScalef(largura/comprimento,1,1);
    glTranslatef(0,0,largura);

    for(float i = largura/4,j = -largura;i <= largura;i = i + largura/4,j-=comprimento*0.125){
        glBegin(GL_QUADS);//Arquibancada azul
            glColor3f(0,0,1);
            glVertex3f(getVertice(1)[0],getVertice(1)[1],j);
            glVertex3f(getVertice(0)[0],getVertice(0)[1],j);
            glVertex3f(getVertice(0)[0],i,j);
            glVertex3f(getVertice(1)[0],i,j);
            glColor3f(0.5,0.5,0.5);
            glVertex3f(getVertice(0)[0],i,j);
            glVertex3f(getVertice(1)[0],i,j);
            glVertex3f(getVertice(1)[0],i,j-comprimento*0.125);
            glVertex3f(getVertice(0)[0],i,j-comprimento*0.125);

        glEnd();
    }
    glPopMatrix();
    glPushMatrix();

    glTranslatef(comprimento,0,0);
    glRotatef(-90,0,1,0);
    glScalef(largura/comprimento,1,1);
    glTranslatef(0,0,largura);

    for(float i = largura/4,j = -largura;i <= largura;i = i + largura/4,j-=comprimento*0.125){
        glBegin(GL_QUADS);//Arquibancada rosa
            glColor3f(1,0,1);
            glVertex3f(getVertice(1)[0],getVertice(1)[1],j);
            glVertex3f(getVertice(0)[0],getVertice(0)[1],j);
            glVertex3f(getVertice(0)[0],i,j);
            glVertex3f(getVertice(1)[0],i,j);
            glColor3f(0.5,0.5,0.5);
            glVertex3f(getVertice(0)[0],i,j);
            glVertex3f(getVertice(1)[0],i,j);
            glVertex3f(getVertice(1)[0],i,j-comprimento*0.125);
            glVertex3f(getVertice(0)[0],i,j-comprimento*0.125);

        glEnd();
    }
    glPopMatrix();
}

float* Pista::getVertice(int index){
    return vertices[index].getCoods();
}
