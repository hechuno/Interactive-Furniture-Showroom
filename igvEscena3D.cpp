#include <cstdlib>
#include <stdio.h>
#include <cmath>

#include "igvEscena3D.h"

#include <igvFuenteLuz.h>
#include <igvTextura.h>
#include <iostream>
#include <ostream>

#include "igvMallaTriangulos.h"


// M�todos constructores

/**
 * Constructor por defecto
 */
igvEscena3D::igvEscena3D ()
{  // TODO: Apartado B: Inserta el c�digo para crear un cilindro

   malla= new igvCilindro(0.1,0.4,10,2);

    luzPuntual = new igvFuenteLuz(
        GL_LIGHT0,
        {luzX, luzY, luzZ},
        {0.0, 0.0, 0.0, 1.0},
        {1.0, 1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0, 1.0},
        1.0,
        0.0,
        0.0
        );

    luzCono = new igvFuenteLuz(
    GL_LIGHT1,
    {0.0, 2.0, 2.0},
    {0.0, 0.0, 0.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    1.0,
    1.0,
    1.0,
    {0, -1, -1},
    30,
    1
    );

}

/**
 * Destructor
 */
igvEscena3D::~igvEscena3D ()
{  if ( malla != nullptr )
   {  delete malla;
      malla = nullptr;
      delete cilindro;
      cilindro=nullptr;
   }

    if (luzCono) {
        delete luzCono;
        luzCono = nullptr;
    }
}

void igvEscena3D::pintar_quad(int div_x, int div_z) {
    float lado = 5.0f;
    float paso_x = lado / div_x;
    float paso_z = lado / div_z;

    float inicio_x = -lado / 2.0f;
    float inicio_z = -lado / 2.0f;

    for (int i = 0; i < div_x; ++i) {
        for (int j = 0; j < div_z; ++j) {
            float x0 = inicio_x + i * paso_x;
            float z0 = inicio_z + j * paso_z;
            float x1 = x0 + paso_x;
            float z1 = z0 + paso_z;

            float s0 = (float)i / div_x;
            float t0 = (float)j / div_z;
            float s1 = (float)(i + 1) / div_x;
            float t1 = (float)(j + 1) / div_z;

            glBegin(GL_QUADS);

            glNormal3f(0.0f, 1.0f, 0.0f);

            glTexCoord2f(s0, t0);
            glVertex3f(x0, 0.0f, z0);

            glTexCoord2f(s1, t0);
            glVertex3f(x1, 0.0f, z0);

            glTexCoord2f(s1, t1);
            glVertex3f(x1, 0.0f, z1);

            glTexCoord2f(s0, t1);
            glVertex3f(x0, 0.0f, z1);

            glEnd();
        }
    }
}


// M�todos p�blicos

/**
 * M�todo para pintar los ejes coordenados llamando a funciones de OpenGL
 */
void igvEscena3D::pintar_ejes()
{	GLfloat rojo[] = { 1,0,0,1.0 };
   GLfloat verde[] = { 0,1,0,1.0 };
   GLfloat azul[] = { 0,0,1,1.0 };

   glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
   glBegin(GL_LINES);
   glVertex3f(1000, 0, 0);
   glVertex3f(-1000, 0, 0);
   glEnd();

   glMaterialfv(GL_FRONT, GL_EMISSION, verde);
   glBegin(GL_LINES);
   glVertex3f(0, 1000, 0);
   glVertex3f(0, -1000, 0);
   glEnd();

   glMaterialfv(GL_FRONT, GL_EMISSION, azul);
   glBegin(GL_LINES);
   glVertex3f(0, 0, 1000);
   glVertex3f(0, 0, -1000);
   glEnd();
}

/**
 * M�todo con las llamadas OpenGL para visualizar la escena
 */
void igvEscena3D::visualizar ( void )
{
   // crear luces
   // luz puntual para visualizar el cubo
    if(!modoSeleccion)
    {
        luzPuntual->encenderLuz();
        luzCono->encenderLuz();

        luzPuntual->setPosicion({luzX, luzY, luzZ});
    } else
    {
        luzPuntual->apagarLuz();
        luzCono->apagarLuz();
    }

    visualizarVB();
}

void igvEscena3D::visualizarVB( void )
{
    // se pintan los ejes
    if ( ejes )
    {  pintar_ejes ();
    }


    glMaterialfv ( GL_FRONT, GL_EMISSION, color_malla );

    //everything
    glPushMatrix ();
        glRotatef(anguloScene, 0, 1, 0);
        glPushMatrix ();
    //Mesa
            glPushMatrix();
                glMaterialfv ( GL_FRONT, GL_EMISSION, leg_color);
                glTranslatef(transX-0.5, 0, transZ-0.5);
                glRotatef(anguloY, 0, 1, 0);
                glPushMatrix();
                    glPushMatrix();
                        malla->visualizar();
                        glTranslatef(1,0,0);
                        malla->visualizar();
                        glTranslatef(0, 0, 1);
                        malla->visualizar();
                        glTranslatef(-1, 0, 0);
                        malla->visualizar();
                    glPopMatrix();
    //Counter
                    glPushMatrix();
                        glMaterialfv(GL_FRONT, GL_EMISSION, counter_color);
                        glTranslatef(0.5, 0.4, 0.5);
                        glScalef(1.0, 0.1, 1.0);
                        glutSolidCube(1.2);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();

    //Suelo
            glPushMatrix();

                if(textura)
                {
                    glMaterialfv(GL_FRONT, GL_EMISSION, white);
                } else
                {
                    glMaterialfv(GL_FRONT, GL_EMISSION, color_malla);
                }

                    if(textura)
                    {
                        static igvTextura textura("../ujaen_default_icon.png");
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D, textura.getIdTextura());
                        pintar_quad(50, 50);
                        glBindTexture(GL_TEXTURE_2D, 0);
                        glDisable(GL_TEXTURE_2D);
                    } else
                    {
                        pintar_quad(50, 50);
                    }
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

/**
 * M�todo para consultar si hay que dibujar los ejes o no
 * @retval true Si hay que dibujar los ejes
 * @retval false Si no hay que dibujar los ejes
 */
bool igvEscena3D::get_ejes ()
{  return ejes;
}

/**
 * M�todo para activar o desactivar el dibujado de los _ejes
 * @param _ejes Indica si hay que dibujar los ejes (true) o no (false)
 * @post El estado del objeto cambia en lo que respecta al dibujado de ejes,
 *       de acuerdo al valor pasado como par�metro
 */
void igvEscena3D::set_ejes ( bool _ejes )
{  ejes = _ejes;
}

igvMallaTriangulos *igvEscena3D::getMalla() const {
    return malla;
}

igvCilindro *igvEscena3D::getCilindro() const {
    return cilindro;
}

float igvEscena3D::getTransX()
{
    return transX;
}

void igvEscena3D::setTransX(float _transX)
{
    transX = _transX;
}

float igvEscena3D::getTransZ()
{
    return transZ;
}

void igvEscena3D::setTransZ(float _transZ)
{
    transZ = _transZ;
}

float igvEscena3D::getAnguloY()
{
    return anguloY;
}

void igvEscena3D::setAnguloY(float _anguloY)
{
    anguloY = _anguloY;
}

float igvEscena3D::getAnguloScene()
{
    return anguloScene;
}

void igvEscena3D::setAnguloScene(float _anguloScene)
{
    anguloScene = _anguloScene;
}

void igvEscena3D::setCounterColor(float r, float g, float b) {
    counter_color[0] = r;
    counter_color[1] = g;
    counter_color[2] = b;
}

void igvEscena3D::getCounterColor(GLfloat &r, GLfloat &g, GLfloat &b) {
    r = counter_color[0];
    g = counter_color[1];
    b = counter_color[2];
}

void igvEscena3D::setTexture(bool _texture)
{
    textura = _texture;
}