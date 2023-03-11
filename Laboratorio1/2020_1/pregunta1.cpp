/* 
 * File:   pregunta1.cpp
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * Primera Practica del Curso de Algoritmia del ciclo 2020-1
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "pregunta1.h"
#include "funcionesComunes.h"

void Pregunta1(void) {
    PersonaContagio *perContagio;
    PersonaMINSA *perMinsa;
    int cantContagio, cantMinsa;
    double radio;
    LeerDatos(&perContagio, &perMinsa, &cantContagio, &cantMinsa, &radio);
    // Prueba de Lectura
    //    std::cout << cantContagio << radio << "\n";
    //    for (int i = 0; i < cantContagio; i++) {
    //        std::cout << perContagio[i].sano << "\t"
    //                << perContagio[i].x << "\t"
    //                << perContagio[i].y << "\n";
    //    }
    //    for (int i = 0; i < cantMinsa; i++) {
    //        std::cout << perMinsa[i].x << "\t"
    //                << perMinsa[i].y << "\n";
    //    }
    for (int i = 0; i < cantMinsa; i++) {
        for (int j = 0; j < cantContagio; j++) {
            if (DistanciaPacMinsa(perContagio[j].x, perContagio[j].y, perMinsa[i].x, perMinsa[i].y) <= radio
                    && perContagio[j].sano) {
                std::cout << "Persona podría haberse contagiado en su movimiento " << (i + 1)
                        << " por la persona " << (j + 1)
                        << " con nivel de cercania " << radio << "\n";
            }
        }
    }
}

void LeerDatos(PersonaContagio **perContagio, PersonaMINSA **perMinsa,
        int *cantContagio, int *cantMinsa, double *radio) {

    std::cin >> *cantContagio >> *radio;
    *perContagio = new PersonaContagio[*cantContagio];
    for (int i = 0; i < *cantContagio; i++) {
        std::cin >> (*perContagio)[i].sano
                >> (*perContagio)[i].x
                >> (*perContagio)[i].y;
    }
    std::cin >> *cantMinsa;
    *perMinsa = new PersonaMINSA[*cantMinsa];
    for (int i = 0; i < *cantMinsa; i++) {
        std::cin >> (*perMinsa)[i].x
                >> (*perMinsa)[i].y;
    }
}

double DistanciaPacMinsa(int perX, int perY, int minsaX, int minsaY) {
    return sqrt(pow(perX - minsaX, 2) + pow(perY - minsaY, 2));
}