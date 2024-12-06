#ifndef __IGVFUENTELUZ
#define __IGVFUENTELUZ

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include "igvPunto3D.h"
#include "igvColor.h"

/**
 * Los objetos de esta clase representan fuentes de luz
 */
class igvFuenteLuz
{  private:
      // Atributos
      unsigned int idLuz = 0;

      igvPunto3D posicion = { 0, 0, 0 };

      igvColor colorAmbiente = { 0, 0, 0 };
      igvColor colorDifuso = { 0, 0, 0 };
      igvColor colorEspecular = { 0, 0, 0 };

      double aten_a0 = 1;
      double aten_a1 = 0;
      double aten_a2 = 0;

      // par�metros para definir un foco
      igvPunto3D direccion_foco = { 0, 0, 0 };
      double angulo_foco = 0;
      double exponente_foco = 0;

      bool encendida = false;

      // M�todos

   public:
      // Constructores por defecto y destructor
      igvFuenteLuz () = default;
      ~igvFuenteLuz() = default;

      // Otros constructores
      // Construye una luz puntual
      igvFuenteLuz ( const unsigned int _idLuz, const igvPunto3D &_posicion
                     , const igvColor &cAmb, const igvColor &cDif
                     , const igvColor &cEsp, const double a0, const double a1
                     , const double a2 );

      // Construye un foco
      igvFuenteLuz ( const unsigned int _idLuz, const igvPunto3D &_posicion
                     , const igvColor &cAmb, const igvColor &cDif
                     , const igvColor &cEsp, const double a0, const double a1
                     , const double a2, const igvPunto3D &dir_foco
                     , const double ang_foco, const double exp_foco );

      // M�todos
      igvPunto3D &getPosicion (); // devuelve la posici�n de la luz
      void setPosicion ( igvPunto3D pos ); // establece la posici�n de la luz

      void set ( const igvColor &cAmb, const igvColor &cDif, const igvColor &cEsp );
      void setAmbiental ( const igvColor &cAmb );
      void setDifuso ( const igvColor &cDif );
      void setEspecular ( const igvColor &cEsp );
      igvColor &getAmbiental ();
      igvColor &getDifuso ();
      igvColor &getEspecular ();

      void setAtenuacion ( double a0, double a1, double a2 );
      void getAtenuacion ( double &a0, double &a1, double &a2 );

      void encender ();
      void apagar ();
      bool esta_encendida ();

      void aplicar ();
      void encenderLuz();
      void apagarLuz();
};

#endif   // __IGVFUENTELUZ

