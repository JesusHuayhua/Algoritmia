/* 
 * File:   pregunta1.cpp
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * Primera Practica del Curso de Algoritmia del ciclo 2019-2
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "pregunta1.h"
#include "funcionesComunes.h"

#define N_MAX_PROYECTOS 12
#define FILE_NAME "Lab1_P1_data.txt"

void pregunta1(void) {
    Proyecto *proyectos;    
    
    int N, P;
    leerDatos(&proyectos, &N, &P);
    // Verificación de la Lectura de datos
    //    std::cout << N << "\n" << P << "\n";
    //    for (int i = 0; i < N; i++) {
    //        std::cout << proyectos[i].id << "\t"
    //                << proyectos[i].costo << "\t"
    //                << proyectos[i].ganancia << "\t"
    //                << proyectos[i].cantPredecesores;
    //        int cant = proyectos[i].cantPredecesores;
    //        if (cant > 0) {
    //            for (int j = 0; j < cant; j++) {
    //                std::cout <<"\t"<<proyectos[i].predecesores[j]<< "\t";
    //            }
    //        }
    //        std::cout << "\n";
    //    }


    int lim = pow(2, N),
            //            cromosoma[N],
            cromosomaFinal[N],
            ganancia = 0,
            gananciaFinal = 0;
    for (int i = 0; i < lim; i++) {
        //        CargarCromosoma(cromosoma, N, i);
        int cromosoma[N] = {1, 1, 1, 0, 1, 0, 0, 0};
        CalcularTotalGanancia(proyectos, cromosoma, N, &ganancia);
        if (EsValido(proyectos, cromosoma, N, P) && ganancia > gananciaFinal) {
            CargarCromosomaFinal(cromosoma, cromosomaFinal, N);
            gananciaFinal = ganancia;
        }
    }
    TituloItem('B');
    MostrarProyecto(proyectos, cromosomaFinal, N, gananciaFinal);
    TituloItem('E');
    OrdenarProyectos(proyectos, cromosomaFinal, N);
    MostrarProyecto(proyectos, cromosomaFinal, N, gananciaFinal);
}

/**
 * 
 * @param proyectos: Posibles proyectos de la empresa
 * @param N_ptr: Cantidad de proyectos
 * @param P_ptr: Presupuesto máximo de la empresa
 */
void leerDatos(Proyecto **proyectos, int *N_ptr, int *P_ptr) {
    std::ifstream archivo(FILE_NAME, std::ios::in);
    if (!archivo) {
        std::cout << "No se pudo abrir el siguiente archivos para su lectura: "
                << FILE_NAME << "\n";
        exit(1);
    }
    archivo >> *N_ptr >> *P_ptr;
    if (archivo.fail()) {
        std::cout << "No se pudo leer la cantidad de proyectos o el presupuesto\n";
        exit(2);
    }
    *proyectos = new Proyecto[*N_ptr];
    for (int i = 0; i < *N_ptr; i++) {
        archivo >> (*proyectos)[i].id
                >> (*proyectos)[i].costo
                >> (*proyectos)[i].ganancia
                >> (*proyectos)[i].cantPredecesores;

        int cant = (*proyectos)[i].cantPredecesores;

        if (cant > 0) {
            (*proyectos)[i].predecesores = new int[cant];
            for (int j = 0; j < cant; j++) {
                archivo >> (*proyectos)[i].predecesores[j];
            }
        }
    }
    archivo.close();
}

/**
 * Validación del cromosoma
 * @param proyectos: Posibles proyectos
 * @param cromosoma: cromosoma a pasar validación
 * @param size: tamaño del cromosoma
 * @param presupuesto: Presupuesto máximo de la empresa
 * @return 
 */
bool EsValido(Proyecto *proyectos, int *cromosoma, int size, int presupuesto) {
    int costo = 0;
    for (int i = 0; i < size; i++) {
        // validación de Predecesores
        if (proyectos[i].cantPredecesores && cromosoma[i]) {
            for (int j = 0; j < proyectos[i].cantPredecesores; j++) {
                if (!cromosoma[ proyectos[i].predecesores[j] - 1 ]) {
                    return false;
                }
            }
        }
        // Calculo del costo, de tal forma que no pase el presupuesto
        costo += proyectos[i].costo * cromosoma[i];
        if (costo > presupuesto) {
            return false;
        }
    }
    return true;
}

/**
 * Calcular la ganancia del cromosoma
 * @param proyectos 
 * @param cromosoma
 * @param size: tamamaño del cromosoma
 * @param ganancia: Posible maxima ganancia del proyecto
 */
void CalcularTotalGanancia(Proyecto *proyectos, int *cromosoma, int size,
        int *ganancia) {

    *ganancia = 0;
    for (int i = 0; i < size; i++) {
        // Calculo la ganancia del cromosoma
        *ganancia += proyectos[i].ganancia * cromosoma[i];
    }
}

/**
 * Mostar los proyectos seleccionados según nuestro algoritmo
 * @param proyectos: proyectos seleccionados
 * @param cromosoma: Cromosoma con la mayor ganacia
 * @param size: tamaño del cromosoma
 * @param ganancia: ganancia maxima
 */
void MostrarProyecto(Proyecto *proyectos, int *cromosoma, int size, int ganancia) {
    for (int i = 0; i < size; i++) {
        // Caso no valido
        if (!cromosoma[i]) continue;
        std::cout << "Proyecto: " << proyectos[i].id
                << " Ganancia: " << proyectos[i].ganancia
                << " Costo: " << proyectos[i].costo << "\n";
    }
    std::cout << "La ganancia máxima es: " << ganancia << "\n";
}

/**
 * 
 * @param proyectos
 * @param cromosoma
 * @param size
 */
void OrdenarProyectos(Proyecto *proyectos, int *cromosoma, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (proyectos[i].ganancia > proyectos[j].ganancia) {
                SwapProyectos(proyectos,i,j);
                int aux = cromosoma[i];
                cromosoma[i] = cromosoma[j];
                cromosoma[j] = aux;
            }
        }
    }
}

/**
 * Cambiar de posición los valores del proyecto
 * @param proyectos
 * @param i: proyectos[i] => proyectos[j]
 * @param j: proyectos[j] => proyectos[i]
 */
void SwapProyectos(Proyecto *proyectos,int i,int j){
    Proyecto aux = proyectos[i];
    proyectos[i] = proyectos[j];
    proyectos[j] = aux;
}