#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"

#include <iostream>

// Aplicaci�n del patr�n de dise�o Singleton
igvInterfaz *igvInterfaz::_instancia = nullptr;

// M�todos p�blicos ----------------------------------------

/**
 * M�todo para acceder al objeto �nico de la clase, en aplicaci�n del patr�n de
 * dise�o Singleton
 * @return Una referencia al objeto �nico de la clase
 */
igvInterfaz &igvInterfaz::getInstancia() {
    if (!_instancia) {
        _instancia = new igvInterfaz;
    }

    return *_instancia;
}

/**
 * Crea el mundo que se visualiza en la ventana
 */
void igvInterfaz::crear_mundo() {  // inicia la c�mara
    _instancia->camara.set(IGV_PARALELA, {3.0, 2.0, 4}, {0, 0, 0}, {0, 1.0, 0}, -1.5, 1.5, -1.5, 1.5,
                           1, 200);
    _instancia->camara2.set(IGV_PARALELA, {0.0, 5.0, 0.0}, {0, 0, 0}, {1.0, 0.0, 0}, -1.5, 1.5, -1.5, 1.5,
                           1, 200);
}

/**
 * Inicializa todos los par�metros para crear una ventana de visualizaci�n
 * @param argc N�mero de par�metros por l�nea de comandos al ejecutar la
 *             aplicaci�n
 * @param argv Par�metros por l�nea de comandos al ejecutar la aplicaci�n
 * @param _ancho_ventana Ancho inicial de la ventana de visualizaci�n
 * @param _alto_ventana Alto inicial de la ventana de visualizaci�n
 * @param _pos_X Coordenada X de la posici�n inicial de la ventana de
 *               visualizaci�n
 * @param _pos_Y Coordenada Y de la posici�n inicial de la ventana de
 *               visualizaci�n
 * @param _titulo T�tulo de la ventana de visualizaci�n
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Cambia el alto y ancho de ventana almacenado en el objeto
 */
void
igvInterfaz::configura_entorno(int argc, char **argv, int _ancho_ventana, int _alto_ventana, int _pos_X, int _pos_Y,
                               std::string _titulo) {
    // inicializaci�n de las variables de la interfaz
    ancho_ventana = _ancho_ventana;
    alto_ventana = _alto_ventana;

    // inicializaci�n de la ventana de visualizaci�n
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_ancho_ventana, _alto_ventana);
    glutInitWindowPosition(_pos_X, _pos_Y);
    glutCreateWindow(_titulo.c_str());

    create_menu ();

    glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
    glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana

    glEnable(GL_LIGHTING); // activa la iluminaci�n de la escena
    glEnable(GL_NORMALIZE); // normaliza los vectores normales para c�lculo iluminaci�n

    crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::create_menu ()
{  int menu_id = glutCreateMenu ( menuHandle );
    glutAddMenuEntry ( _instancia->escena.Nombre_noTexture
                       , _instancia->escena.noTexture );
    glutAddMenuEntry ( _instancia->escena.Nombre_Texture
                       , _instancia->escena.texture );
    glutAddMenuEntry ( _instancia->escena.Nombre_noLightnoTexture
                        ,_instancia->escena.basic);

    glutAttachMenu ( GLUT_RIGHT_BUTTON );
}

/**
 * M�todo para visualizar la escena y esperar a eventos sobre la interfaz
 */
void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop(); // inicia el bucle de visualizaci�n de GLUT
}

/**
 * M�todo para control de eventos del teclado
 * @param key C�digo de la tecla pulsada
 * @param x Coordenada X de la posici�n del cursor del rat�n en el momento del
 *          evento de teclado
 * @param y Coordenada Y de la posici�n del cursor del rat�n en el momento del
 *          evento de teclado
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 * @post Los atributos de la clase pueden cambiar, dependiendo de la tecla pulsada
 */
void igvInterfaz::keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        static bool isPerspectiva = false;
        static bool automatic = false;
        case 'y': // TODO: Apartado A: rotar Y positivo
            _instancia->escena.setAnguloY(_instancia->escena.getAnguloY()+10);
            _instancia->escena.visualizar();
            break;
        case 'Y': // TODO: Apartado A: rotar Y negativo
            _instancia->escena.setAnguloY(_instancia->escena.getAnguloY()-10);
            _instancia->escena.visualizar();
            break;
        case 'x': // mover X positivo
            _instancia->escena.setTransX(_instancia->escena.getTransX()+0.1);
            _instancia->escena.visualizar();
            break;
        case 'X': // mover X negativo
            _instancia->escena.setTransX(_instancia->escena.getTransX()-0.1);
            _instancia->escena.visualizar();
            break;
        case 'z': // TODO: Apartado A: mover z positivo
            _instancia->escena.setTransZ(_instancia->escena.getTransZ()+0.1);
            _instancia->escena.visualizar();
            break;
        case 'Z': // TODO: Apartado A: mover Z negativo
            _instancia->escena.setTransZ(_instancia->escena.getTransZ()-0.1);
            _instancia->escena.visualizar();
            break;
        case 'p':
        case 'P':
            if (!isPerspectiva)
            {
                _instancia->camara.set(IGV_PERSPECTIVA, {3.0, 2.0, 4}, {0, 0, 0}, {0, 1.0, 0}, _instancia->camara.getAngulo(), 1.0, 0.1, 200.0);
            }
            else{
                _instancia->camara.set(IGV_PARALELA, {3.0, 2.0, 4}, {0, 0, 0}, {0, 1.0, 0}, _instancia->camara.getXmin(), _instancia->camara.getXmax(), _instancia->camara.getYwmin(), _instancia->camara.getYwmax(), -3.0, 200.0);
            }
            isPerspectiva = !isPerspectiva;
            break;
        case 'a':
        case 'A':
            _instancia->set_automatic(!_instancia->get_automatic());
            break;
        case '+': // TODO: zoom in
            _instancia->camara.zoom(0.95);
            break;
        case '-': // TODO: zoom out
            _instancia->camara.zoom(1.05);
            break;
        case 'n':
        case 'N':
            if (!_instancia->escena.getMalla()->normal) {
                _instancia->escena.getMalla()->normal = true;
            } else {
                _instancia->escena.getMalla()->normal = false;
            }
            break;
        case 'i':
            _instancia->escena.setluzX(_instancia->escena.getluzX()-0.1);
            break;
        case 'I':
            _instancia->escena.setluzX(_instancia->escena.getluzX()+0.1);
            break;
        case 'j':
            _instancia->escena.setluzY(_instancia->escena.getluzY()-0.1);
            break;
        case 'J':
            _instancia->escena.setluzY(_instancia->escena.getluzY()+0.1);
            break;
        case 'k':
            _instancia->escena.setluzZ(_instancia->escena.getluzZ()-0.1);
            break;
        case 'K':
            _instancia->escena.setluzZ(_instancia->escena.getluzZ()+0.1);
            break;
        case 'e': // activa/desactiva la visualizacion de los ejes
            _instancia->escena.set_ejes(!_instancia->escena.get_ejes());
            break;
        case 27: // tecla de escape para SALIR
            exit(1);
        }
    glutPostRedisplay(); // renueva el contenido de la ventana de visi�n
}

/**
 * M�todo que define la c�mara de visi�n y el viewport. Se llama autom�ticamente
 * cuando se cambia el tama�o de la ventana.
 * @param w Nuevo ancho de la ventana
 * @param h Nuevo alto de la ventana
 * @pre Se asume que todos los par�metros tienen valores v�lidos
 */
void igvInterfaz::reshapeFunc(int w, int h) {  // dimensiona el viewport al nuevo ancho y alto de la ventana
    // guardamos valores nuevos de la ventana de visualizaci�n
    _instancia->set_ancho_ventana(w);
    _instancia->set_alto_ventana(h);

    // establece los par�metros de la c�mara y de la proyecci�n
    _instancia->camara.aplicar();
}

/**
 * M�todo para visualizar la escena
 */
void igvInterfaz::displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

    // se establece el viewport
    glViewport(0, 0, _instancia->get_ancho_ventana(), _instancia->get_alto_ventana());
    if (_instancia->modo == IGV_SELECCIONAR)
    {
        // establece los par�metros de la c�mara y de la proyecci�n
        _instancia->camara.aplicar();
        _instancia->escena.visualizar();

        glViewport(2*_instancia->get_ancho_ventana() / 3, 2*_instancia->get_alto_ventana() / 3, _instancia->get_ancho_ventana() / 3, _instancia->get_alto_ventana() / 3);
        _instancia->camara2.aplicar();
        _instancia->escena.visualizar();

        _instancia->modo = IGV_VISUALIZAR;
        glutSwapBuffers();
    } else
    {
        _instancia->camara.aplicar ();
        _instancia->escena.visualizar ();
        glViewport(2*_instancia->get_ancho_ventana() / 3, 2*_instancia->get_alto_ventana() / 3, _instancia->get_ancho_ventana() / 3, _instancia->get_alto_ventana() / 3);
        _instancia->camara2.aplicar();
        _instancia->escena.visualizar();
        glutSwapBuffers ();
    }

}

/**
 * M�todo para inicializar los callbacks GLUT
 */
void igvInterfaz::inicializa_callbacks() {
    glutKeyboardFunc(keyboardFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
    glutIdleFunc ( idleFunc );

    glutMouseFunc ( mouseFunc );
    glutMotionFunc ( motionFunc );
}

/**
 * M�todo para consultar el ancho de la ventana de visualizaci�n
 * @return El valor almacenado como ancho de la ventana de visualizaci�n
 */
int igvInterfaz::get_ancho_ventana() {
    return ancho_ventana;
}

/**
 * M�todo para consultar el alto de la ventana de visualizaci�n
 * @return El valor almacenado como alto de la ventana de visualizaci�n
 */
int igvInterfaz::get_alto_ventana() {
    return alto_ventana;
}

/**
 * M�todo para cambiar el ancho de la ventana de visualizaci�n
 * @param _ancho_ventana Nuevo valor para el ancho de la ventana de visualizaci�n
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post El ancho de ventana almacenado en la aplicaci�n cambia al nuevo valor
 */
void igvInterfaz::set_ancho_ventana(int _ancho_ventana) {
    ancho_ventana = _ancho_ventana;
}

/**
 * M�todo para cambiar el alto de la ventana de visualizaci�n
 * @param _alto_ventana Nuevo valor para el alto de la ventana de visualizaci�n
 * @pre Se asume que el par�metro tiene un valor v�lido
 * @post El alto de ventana almacenado en la aplicaci�n cambia al nuevo valor
 */
void igvInterfaz::set_alto_ventana(int _alto_ventana) {
    alto_ventana = _alto_ventana;
}

void igvInterfaz::idleFunc ()
{  // TODO: Apartado D: incluir el c�digo para animar el modelo de la manera m�s realista posible
    if(_instancia->get_automatic())
    {
        _instancia->escena.setAnguloScene(_instancia->escena.getAnguloScene()+0.1);
    }
    glutPostRedisplay();
}

void igvInterfaz::mouseFunc ( GLint boton, GLint estado, GLint x, GLint y )
{
    if (boton == GLUT_LEFT_BUTTON) {
        if (estado == GLUT_DOWN) {
            _instancia->boton_retenido=true;
            _instancia->modo = IGV_SELECCIONAR;
            _instancia->cursorX = x;
            _instancia->cursorY = y;

            GLfloat r, g, b;
            _instancia->escena.getCounterColor(r, g, b);

            r = _instancia->clamp(r, 0.0f, 1.0f);
            g = _instancia->clamp(g, 0.0f, 1.0f);
            b = _instancia->clamp(b, 0.0f, 1.0f);

            r = r * 255.0f;
            g = g * 255.0f;
            b = b * 255.0f;

            GLubyte pixel[3];
            glReadPixels(x, _instancia->alto_ventana - y - 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
            const int tolerance = 15;

            if (abs(pixel[0] - r) < tolerance && abs(pixel[1] - g) < tolerance && abs(pixel[2] - b) < tolerance) {
                std::cout << "Table selected!" << std::endl;
                _instancia->escena.setCounterSelection(true);  // Set the selected object
            } else {
                _instancia->escena.setCounterSelection(false);  // No object selected
            }

            glutPostRedisplay();
        } else if (estado == GLUT_UP) {
            _instancia->boton_retenido = false;
        }
    }
}

void igvInterfaz::motionFunc ( GLint x, GLint y )
{
    if (_instancia->boton_retenido && _instancia->escena.getCounterSelection())
    {
        GLfloat r, g, b;
        _instancia->escena.getCounterColor(r, g, b);
        GLfloat deltaX = (x - _instancia->cursorX)/10000.0;

        _instancia->escena.setCounterColor(r+deltaX, g+deltaX, b+deltaX);
        glutPostRedisplay();
    }
}

bool igvInterfaz::get_automatic()
{
    return automatic;
}

void igvInterfaz::set_automatic(bool _automatic)
{
    automatic = _automatic;
}

void igvInterfaz::menuHandle ( int value )
{
    if(value == 1)
    {
        _instancia->escena.setModoSeleccion(false);
        _instancia->escena.setTextura(false);
    } else if (value == 2)
    {
        _instancia->escena.setModoSeleccion(false);
        _instancia->escena.setTextura(true);
    } else if (value == 3)
    {
        _instancia->escena.setModoSeleccion(true);
        _instancia->escena.setTextura(false);
    }
    glutPostRedisplay ();
}

GLfloat igvInterfaz::clamp(GLfloat value, GLfloat min_value, GLfloat max_value) {
    if (value < min_value) return min_value;
    if (value > max_value) return max_value;
    return value;
}
