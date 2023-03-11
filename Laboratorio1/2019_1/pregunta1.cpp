/* 
 * File:   pregunta1.cpp
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * Primera Practica del Curso de Algoritmia del ciclo 2019-1
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "pregunta1.h"
#include "funcionesComunes.h"

#define M_MAX 10
#define FILE_NAME "Lab1_P1_data.txt"

//pregunta1

void pregunta1(void) {
    Producto *productos;
    int M, W;
    leerDatos(&productos, &M, &W);
    // Verificaciones de la lectura de los datos
    //    std::cout << "M: " << M << " W: " << W << std::endl;
    //    for (int i = 0; i < M; i++) {
    //        std::cout << productos[i].articulo
    //                << "\t" << productos[i].peso
    //                << "\t" << productos[i].ganancia<<"\n";
    //    }
    int lim = pow(2, M),
            cromosoma[M],
            cromosomaFinal[M],
            ganancia = 0,
            gananciaFinal = 0;

    for (int i = 0; i < lim; i++) {
        CargarCromosoma(cromosoma, M, i);
        if (EsValido(productos, cromosoma, M, W)) {
            CalcularGanancia(productos, cromosoma, M, &ganancia);
            if (ganancia > gananciaFinal) {
                CargarCromosomaFinal(cromosoma,cromosomaFinal,M);
                gananciaFinal = ganancia;
            }
        }
    }
    TituloItem('B');
    std::cout << "Articulos: ";
    for (int i = 0; i < M; i++) {
        if (cromosomaFinal[i]) {
            std::cout << productos[i].articulo << " ";
        }
    }
    std::cout << "\nGanancia total: " << gananciaFinal;
    
}

void leerDatos(Producto **producto, int *M_ptr, int *W_ptr) {
    std::ifstream archivo(FILE_NAME, std::ios::in);
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo: " << FILE_NAME << std::endl;
        exit(1);
    }
    archivo >> *M_ptr >> *W_ptr;
    if (archivo.fail()) {
        std::cout << "No se pudo leer el peso o la cantidad de archivos\n";
        exit(2);
    }
    *producto = new Producto[*M_ptr];
    for (int i = 0; i < *M_ptr; i++) {
        archivo >> (*producto)[i].articulo
                >> (*producto)[i].peso
                >> (*producto)[i].ganancia;
    }
    archivo.close();
}

/**
 * Validación del cromosoma
 * @param productos
 * @param cromosoma
 * @param size
 * @param W
 * @return 
 */
bool EsValido(Producto *productos, int *cromosoma, int size, int W) {
    int peso = 0;
    for (int i = 0; i < size; i++) {
        if (cromosoma[i]) {
            peso += productos[i].peso;
            if (peso > W) return false;
        }
    }
    return true;
}

void CalcularGanancia(Producto *productos, int *cromosoma, int size, int *ganancia) {
    *ganancia = 0;
    for (int i = 0; i < size; i++) {
        if (cromosoma[i]) {
            *ganancia += productos[i].ganancia;
        }
    }
}
