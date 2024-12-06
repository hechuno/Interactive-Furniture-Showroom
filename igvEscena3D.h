#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif // defined(__APPLE__) && defined(__MACH__)

#include <igvFuenteLuz.h>

#include "igvMallaTriangulos.h"
#include "igvCilindro.h"

/**
 * Los objetos de esta clase representan escenas 3D para su visualizaci�n
 */
class igvEscena3D
{
    private:
      // Atributos
      bool ejes = true;///< Indica si hay que dibujar los _ejes coordenados o no

      bool textura = false;
  igvFuenteLuz* luzPuntual;
  igvFuenteLuz* luzCono;

    float luzX = 0.0f;
    float luzY = 1.0f;
    float luzZ = -1.0f;

      float
      anguloY = 0.0,
      transX = 0.0,
      transZ = 0.0,
      anguloScene= 0.0;

      igvMallaTriangulos *malla = nullptr; ///< Malla de tri�ngulos asociada a la escena
      igvCilindro *cilindro=nullptr;

        void pintar_ejes ();

   public:

      // Constructores por defecto y destructor
      igvEscena3D ();
      ~igvEscena3D ();

    bool counterSelected = false;
    bool modoSeleccion = false;

    GLfloat color_malla[3] = { 0.0f, 0.0f, 1.0f };
    GLfloat leg_color[3] = { 0.0f, 1.0f, 0.0f };
    GLfloat counter_color[3] = { 1.0f, 0.0f, 0.0f };
    GLfloat white[3] = { 1.0f, 1.0f, 1.0f };

    const int noTexture = 1;
    const int texture = 2;
    const int basic = 3;

    const char *Nombre_noTexture = "Sin Textura";
    const char *Nombre_Texture = "Con Textura";
    const char *Nombre_noLightnoTexture = "Sin Luz y Textura";

      // M�todos
      // m�todo con las llamadas OpenGL para visualizar la escena
      void visualizar ();
      void visualizarVB();

      bool get_ejes ();

      void set_ejes ( bool _ejes );

      float getAnguloY();
      void setAnguloY ( float _anguloY );
      float getAnguloScene();
      void setAnguloScene(float _anguloScence);
      float getTransX();
      void setTransX ( float _transX );
      float getTransZ();
      void setTransZ ( float _transZ );
      void getCounterColor(GLfloat& r, GLfloat& g, GLfloat& b);
      void setTexture(bool _texture);
      void setCounterColor(GLfloat r, float g, float b);

    void setluzX(float val) { luzX = val; }
    void setluzY(float val) {luzY = val;}
    void setluzZ(float val) {luzZ = val;}

    float getluzX() const { return luzX; }
    float getluzY() const { return luzY; }
    float getluzZ() const { return luzZ; }

    void setCounterSelection(bool val){counterSelected = val;}
    bool getCounterSelection() const { return counterSelected; }

    void setTextura(bool val){textura = val;}
    bool getTextura() const {return textura;}

    void setModoSeleccion(bool val){modoSeleccion = val;}
    bool getModoSeleccion() const {return modoSeleccion;}

    void pintar_quad (int divX, int divZ);
    igvMallaTriangulos *getMalla() const;

    igvCilindro *getCilindro() const;





};

#endif   // __IGVESCENA3D
