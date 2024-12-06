#include "igvCilindro.h"
#include <cmath>

/**
 * Constructor por defecto
 */
igvCilindro::igvCilindro() :igvMallaTriangulos()
{
}

float euclideanDistance(float a,float b, float c){
    return std::sqrt(a * a + b * b + c * c);
}



void igvCilindro::normalizar(float r) {
    for (int i = 0; i < num_vertices * 3; i += 3) {
        float a = vertices[i];
        float b = vertices[i + 1];
        float c = vertices[i + 2];
        normales[i] = a / r;
        normales[i + 1] = b / r;
        normales[i + 2] = c / r;
    }
}




/**
 * Constructor parametrizado
 * @param r Radio de la base del cilindro
 * @param a Altura del cilindro
 * @param divU N�mero de divisiones laterales
 * @param divV N�mero de divisiones en altura
 * @pre Se asume que los par�metros tienen valores v�lidos
 * @post Se crea una nueva malla de tri�ngulos que representa la cara lateral de
 *       un cilindro con altura a y radio r
 */
igvCilindro::igvCilindro(float r, float a, int divU, int divV)
{	// TODO: Apartado B: Construir la malla de tri�ngulos para representar el cilindro

    num_vertices = divU * (divV + 1);
    num_triangulos = divU * divV * 2;

    vertices = new float[num_vertices * 3];
    normales = new float[num_vertices * 3];
    triangulos = new unsigned int[num_triangulos * 3];

    int vertexIndex = 0;
    double angleIncrement = (2 * M_PI) / divU;
    double heightIncrement = a / divV;

    for (int i = 0; i < divU; i++) {
        double currentAngle = i * angleIncrement;

        for (int j = 0; j <= divV; j++) {
            double currentHeight = j * heightIncrement;

            vertices[vertexIndex++] = r * std::cos(currentAngle);  // x
            vertices[vertexIndex++] = currentHeight;               // y
            vertices[vertexIndex++] = r * std::sin(currentAngle);  // z
        }
    }

    int triangleIndex = 0;
    for (int i = 0; i < divU; i++) {
        for (int j = 0; j < divV; j++) {
            int v1 = i * (divV + 1) + j;
            int v2 = (i + 1) % divU * (divV + 1) + j;
            int v3 = v1 + 1;
            int v4 = v2 + 1;

            // Triangle 1
            triangulos[triangleIndex++] = v1;
            triangulos[triangleIndex++] = v2;
            triangulos[triangleIndex++] = v3;

            // Triangle 2
            triangulos[triangleIndex++] = v3;
            triangulos[triangleIndex++] = v2;
            triangulos[triangleIndex++] = v4;
        }
    }

	// TODO: Apartado C: A�adir el vector de normales
    normalizar(r);

}

/**
 * Destructor
 */
igvCilindro::~igvCilindro()
{
}


