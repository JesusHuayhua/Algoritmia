/* 
 * File:   pregunta2.cpp
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * Primera Practica del Curso de Algoritmia del ciclo 2020-1
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "pregunta2.h"
#include "funcionesComunes.h"

#define CANT_ROLES 3

void Pregunta2(void) {
    Rol *roles;
    Postulante *postulantes;
    int t, MPxH;
    LeerPostulantes(&roles, &postulantes, &t, &MPxH);

    // Revisión de la lectura de postulantes
    //    for (int i = 0; i < CANT_ROLES; i++) {
    //        std::cout << roles[i].rol << "\t"
    //                << roles[i].salarioMensual << "\t"
    //                << roles[i].salarioHora << "\n";
    //    }
    //    std::cout << "Segunda parte\n";
    //    for (int i = 0; i < t; i++) {
    //        std::cout << postulantes[i].postulante << "\t"
    //                << postulantes[i].rol << "\t"
    //                << postulantes[i].mph << "\t"
    //                << postulantes[i].bpm << "\n";
    //    }

    
    
}

/**
 * Lectura de los Postulantes
 * 
 * @param roles: roles de postulantes
 * @param postulantes: postulantes 
 * @param t: cantidad de trabajadores
 * @param MPxH: meta a alcanzar por horas
 */
void LeerPostulantes(Rol **roles, Postulante **postulantes, int *t, int *MPxH) {
    LeerRoles(roles);
    std::cin >> *t >> *MPxH;

    *postulantes = new Postulante[*t];

    for (int i = 0; i < *t; i++) {
        std::cin >> (*postulantes)[i].postulante
                >> (*postulantes)[i].rol
                >> (*postulantes)[i].mph
                >> (*postulantes)[i].bpm;
    }
}

/**
 * Roles insertados manualmente
 * Lo lamento tenía flojera de pasarlo a un archivo.txt
 * @param roles
 */
void LeerRoles(Rol **roles) {
    *roles = new Rol[CANT_ROLES];
    (*roles)[0].rol = 1;
    (*roles)[1].rol = 2;
    (*roles)[2].rol = 3;

    (*roles)[0].salarioMensual = 2560;
    (*roles)[1].salarioMensual = 3040;
    (*roles)[2].salarioMensual = 3520;

    (*roles)[0].salarioHora = 16;
    (*roles)[1].salarioHora = 19;
    (*roles)[2].salarioHora = 22;
}