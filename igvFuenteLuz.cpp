#include "igvFuenteLuz.h"

// M�todos constructores

/**
 * Construye una fuente de luz puntual encendida por defecto
 * @param _idLuz Identificador de la luz (GL_LIGHT0 a GL_LIGHT7)
 * @param _posicion Ubicaci�n de la luz en la escena
 * @param cAmb Color de la componente ambiente de la luz
 * @param cDif Color de la componente difusa de la luz
 * @param cEsp Color de la componente especular de la luz
 * @param a0 Coeficiente de atenuaci�n a0
 * @param a1 Coeficiente de atenuaci�n a1
 * @param a2 Coeficiente de atenuaci�n a2
 * @pre Se asume que los par�metros tienen valores v�lidos
 */
igvFuenteLuz::igvFuenteLuz ( const unsigned int _idLuz
                             , const igvPunto3D &_posicion, const igvColor &cAmb
                             , const igvColor &cDif, const igvColor &cEsp
                             , const double a0, const double a1, const double a2 ):
                           idLuz ( _idLuz ), posicion( _posicion )
                           , colorAmbiente( cAmb ), colorDifuso( cDif )
                           , colorEspecular( cEsp ), aten_a0( a0 ), aten_a1( a1 )
                           , aten_a2( a2 ), direccion_foco( { 0, 0, 0 } )
                           , angulo_foco( 180 ), exponente_foco( 0 )
                           , encendida( true )
{}

/**
 * Construye una fuente de tipo foco encendida por defecto
 * @param _idLuz Identificador de la luz (GL_LIGHT0 a GL_LIGHT7)
 * @param _posicion Ubicaci�n de la luz en la escena
 * @param cAmb Color de la componente ambiente de la luz
 * @param cDif Color de la componente difusa de la luz
 * @param cEsp Color de la componente especular de la luz
 * @param a0 Coeficiente de atenuaci�n a0
 * @param a1 Coeficiente de atenuaci�n a1
 * @param a2 Coeficiente de atenuaci�n a2
 * @param dir_foco Direcci�n hacia la que apunta el foco
 * @param ang_foco �ngulo de apertura del cono de luz
 * @param exp_foco Exponente de atenuaci�n del cono de luz
 * @pre Se asume que los par�metros tienen valores v�lidos
 */
igvFuenteLuz::igvFuenteLuz ( const unsigned int _idLuz
                             , const igvPunto3D &_posicion, const igvColor &cAmb
                             , const igvColor &cDif, const igvColor &cEsp
                             , const double a0, const double a1, const double a2
                             , const igvPunto3D &dir_foco, const double ang_foco
                             , const double exp_foco ): idLuz( _idLuz )
                           , posicion( _posicion ), colorAmbiente( cAmb )
                           , colorDifuso( cDif ), colorEspecular( cEsp )
                           , aten_a0( a0 ), aten_a1( a1 ), aten_a2( a2 )
                           , direccion_foco( dir_foco ), angulo_foco( ang_foco )
                           , exponente_foco( exp_foco ), encendida( true )
{}

//45 angulo foco 0 exp

// M�todos p�blicos ----------------------------------------

/**
 * Consulta la posici�n de la luz
 * @return Una referencia a la posici�n de la luz
 */
igvPunto3D &igvFuenteLuz::getPosicion ()
{  return posicion;
}

/**
 * Cambia la posici�n de la luz
 * @param pos Nueva posici�n de la luz
 * @post La posici�n de la luz cambia
 * @pre Se asume que el par�metro es v�lido
 */
void igvFuenteLuz::setPosicion ( igvPunto3D pos )
{  posicion = pos;
}

/**
 * Cambia el color de la luz
 * @param cAmb Nueva componente ambiente de la luz (valores en el rango [0,1])
 * @param cDif Nueva componente difusa de la luz (valores en el rango [0,1])
 * @param cEsp Nueva componente especular de la luz (valores en el rango [0,1])
 * @pre Se asume que los par�metros son v�lidos
 * @post El color de la luz cambia
 */
void igvFuenteLuz::set ( const igvColor &cAmb, const igvColor &cDif
                         , const igvColor &cEsp )
{  colorAmbiente = cAmb;
   colorDifuso = cDif;
   colorEspecular = cEsp;
}

/**
 * Cambia el color de la componente ambiente de la luz
 * @param cAmb Nuevo color ambiente de la luz (valores en el rango [0,1])
 * @pre Se asume que el par�metro es v�lido
 * @post El color de la componente ambiente de la luz cambia
 */
void igvFuenteLuz::setAmbiental ( const igvColor &cAmb )
{  colorAmbiente = cAmb;
}

/**
 * Cambia el color de la componente difusa de la luz
 * @param cDif Nuevo color difuso de la luz (valores en el rango [0,1])
 * @pre Se asume que el par�metro es v�lido
 * @post El color de la componente difusa de la luz cambia
 */
void igvFuenteLuz::setDifuso ( const igvColor &cDif )
{  colorDifuso = cDif;
}

/**
 * Cambia el color de la componente especular de la luz
 * @param cEsp Nuevo color especular de la luz (valores en el rango [0,1])
 * @pre Se asume que el par�metro es v�lido
 * @post El color de la componente especular de la luz cambia
 */
void igvFuenteLuz::setEspecular ( const igvColor &cEsp )
{  colorEspecular = cEsp;
}

/**
 * Consulta el color de la componente ambiente de la luz
 * @return Una referencia a la componente ambiente de la luz
 */
igvColor &igvFuenteLuz::getAmbiental ()
{  return colorAmbiente;
}

/**
 * Consulta el color de la componente difusa de la luz
 * @return Una referencia a la componente difusa de la luz
 */
 igvColor &igvFuenteLuz::getDifuso ()
{  return colorDifuso;
}

/**
 * Consulta el color de la componente especular de la luz
 * @return Una referencia a la componente especular de la luz
 */
igvColor &igvFuenteLuz::getEspecular ()
{  return colorEspecular;
}

/**
 * Cambia los coeficientes de la f�rmula de atenuaci�n de la luz
 * @param a0 Nuevo valor para el coeficiente de atenuaci�n a0
 * @param a1 Nuevo valor para el coeficiente de atenuaci�n a1
 * @param a2 Nuevo valor para el coeficiente de atenuaci�n a2
 * @pre Se asume que los par�metros tienen valores v�lidos
 * @post Los coeficientes de atenuaci�n de la luz cambian
 */
void igvFuenteLuz::setAtenuacion ( double a0, double a1, double a2 )
{  aten_a0 = a0;
   aten_a1 = a1;
   aten_a2 = a2;
}

/**
 * Consulta los coeficientes de atenuaci�n de la luz
 * @param a0 Almacenar� el coeficiente de atenuaci�n a0
 * @param a1 Almacenar� el coeficiente de atenuaci�n a1
 * @param a2 Almacenar� el coeficiente de atenuaci�n a2
 */
void igvFuenteLuz::getAtenuacion ( double &a0, double &a1, double &a2 )
{  a0 = aten_a0;
   a1 = aten_a1;
   a2 = aten_a2;
}

/**
 * Cambia el estado de la luz a encendida
 * @post La luz pasa a estar encendida
 */
void igvFuenteLuz::encender ()
{  encendida = true;
}

/**
 * Cambia el estado de la luz a apagada
 * @post La luz pasa a estar apagada
 */
void igvFuenteLuz::apagar ()
{  encendida = false;
}

/**
 * Consulta el estado de la luz
 * @retval true Si la luz est� encendida
 * @retval false Si la luz no est� encendida
 */
bool igvFuenteLuz::esta_encendida ()
{  return encendida;
}

/**
 * Llama a las funciones OpenGL para aplicar la luz a la escena
 */
void igvFuenteLuz::aplicar ()
{

// TODO: APARTADO A
// si la luz est� encendida
//	activar la luz
//	establecer la posici�n de la luz
//	establecer los colores ambiental, difuso y especular
//	establecer la atenuaci�n radial
//	establecer la atenuaci�n angular y la direcci�n del foco

// si la luz est� apagada
//	desactivar la luz

 if (encendida) {
  glEnable(idLuz);

  GLfloat lightPosition[4] = { (GLfloat)posicion[0], (GLfloat)posicion[1], (GLfloat)posicion[2], 1.0f };
  glLightfv(idLuz, GL_POSITION, lightPosition);

  GLfloat ambientColor[4] = { (GLfloat)colorAmbiente[0], (GLfloat)colorAmbiente[1], (GLfloat)colorAmbiente[2], (GLfloat)colorAmbiente[3] };
  GLfloat diffuseColor[4] = { (GLfloat)colorDifuso[0], (GLfloat)colorDifuso[1], (GLfloat)colorDifuso[2], (GLfloat)colorDifuso[3] };
  GLfloat specularColor[4] = { (GLfloat)colorEspecular[0], (GLfloat)colorEspecular[1], (GLfloat)colorEspecular[2], (GLfloat)colorEspecular[3] };

  glLightfv(idLuz, GL_AMBIENT, ambientColor);
  glLightfv(idLuz, GL_DIFFUSE, diffuseColor);
  glLightfv(idLuz, GL_SPECULAR, specularColor);

  glLightf(idLuz, GL_CONSTANT_ATTENUATION, (GLfloat)aten_a0);
  glLightf(idLuz, GL_LINEAR_ATTENUATION, (GLfloat)aten_a1);
  glLightf(idLuz, GL_QUADRATIC_ATTENUATION, (GLfloat)aten_a2);

  if (angulo_foco < 180) {
   GLfloat spotDirection[3] = { (GLfloat)direccion_foco[0], (GLfloat)direccion_foco[1], (GLfloat)direccion_foco[1] };
   glLightfv(idLuz, GL_SPOT_DIRECTION, spotDirection);
   glLightf(idLuz, GL_SPOT_CUTOFF, (GLfloat)angulo_foco);
   glLightf(idLuz, GL_SPOT_EXPONENT, (GLfloat)exponente_foco);
  }
 } else {
  glDisable(idLuz);
 }

}

void igvFuenteLuz::encenderLuz()
{
 glEnable(idLuz);

 GLfloat lightPosition[4] = { (GLfloat)posicion[0], (GLfloat)posicion[1], (GLfloat)posicion[2], 1.0f };
 glLightfv(idLuz, GL_POSITION, lightPosition);

 GLfloat ambientColor[4] = { (GLfloat)colorAmbiente[0], (GLfloat)colorAmbiente[1], (GLfloat)colorAmbiente[2], (GLfloat)colorAmbiente[3] };
 GLfloat diffuseColor[4] = { (GLfloat)colorDifuso[0], (GLfloat)colorDifuso[1], (GLfloat)colorDifuso[2], (GLfloat)colorDifuso[3] };
 GLfloat specularColor[4] = { (GLfloat)colorEspecular[0], (GLfloat)colorEspecular[1], (GLfloat)colorEspecular[2], (GLfloat)colorEspecular[3] };

 glLightfv(idLuz, GL_AMBIENT, ambientColor);
 glLightfv(idLuz, GL_DIFFUSE, diffuseColor);
 glLightfv(idLuz, GL_SPECULAR, specularColor);

 glLightf(idLuz, GL_CONSTANT_ATTENUATION, (GLfloat)aten_a0);
 glLightf(idLuz, GL_LINEAR_ATTENUATION, (GLfloat)aten_a1);
 glLightf(idLuz, GL_QUADRATIC_ATTENUATION, (GLfloat)aten_a2);

 if (angulo_foco < 180) {
  GLfloat spotDirection[3] = { (GLfloat)direccion_foco[0], (GLfloat)direccion_foco[1], (GLfloat)direccion_foco[1] };
  glLightfv(idLuz, GL_SPOT_DIRECTION, spotDirection);
  glLightf(idLuz, GL_SPOT_CUTOFF, (GLfloat)angulo_foco);
  glLightf(idLuz, GL_SPOT_EXPONENT, (GLfloat)exponente_foco);
 }
}

void igvFuenteLuz::apagarLuz()
{
 glDisable(idLuz);
}

