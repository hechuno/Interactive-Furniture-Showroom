#ifndef __IGVMALLATRIANGULOS
#define __IGVMALLATRIANGULOS

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include <string>

/**
     * Los objetos de esta clase representan mallas de tri�ngulos
 */
class igvMallaTriangulos
{  protected:
      // Atributos
      long int num_vertices = 0;
      float *vertices = nullptr;
      float *normales = nullptr;
      long int num_triangulos = 0;
      unsigned int *triangulos = nullptr;




   public:
      // Constructor y destructor
      /// Constructor por defecto
      bool normal=false;
      bool suavizar=false;

      igvMallaTriangulos () = default;

      igvMallaTriangulos ( long int _num_vertices, float *_vertices
                           , long int _num_triangulos, unsigned int *_triangulos );

      ~igvMallaTriangulos ();

      // M�todo con las llamadas OpenGL para visualizar la malla de tri�ngulos
      void visualizar ();

};

#endif   // __IGVMALLATRIANGULOS
