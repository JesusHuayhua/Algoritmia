/* 
 * File:   pregunta2.cpp
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * Primera Practica del Curso de Algoritmia del ciclo 2019-2
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "pregunta2.h"
#include "funcionesComunes.h"

#define MAX_REPARTO 20
#define FILE_NAME "Lab1_P2_data.txt"

void pregunta2(void) {
    Reparto *repartos;
    int cantRepartos;
    LeerReparto(&repartos, &cantRepartos);
//    for (int i = 0; i < cantRepartos; i++) {
//        std::cout << repartos[i].codigo << "\t"
//                << repartos[i].prioridad << "\t"
//                << repartos[i].horaEntrega << "\t"
//                << repartos[i].tiempoReparto << "\n";
//    }
    int lim = pow(2, cantRepartos),
//            cromosoma[cantRepartos],
            cromosomaFinal[cantRepartos];
    for (int i = 0; i < lim; i++) {
//        CargarCromosoma(cromosoma, cantRepartos, i);
        int cromosoma[cantRepartos] = {0,0,0,1,1,1,1,1,0,1,0,0};
        if (RepartoValido(repartos, cromosoma, cantRepartos)) {
            CargarCromosomaFinal(cromosoma, cromosomaFinal, cantRepartos);
        }
    }
    TituloItem('D');
    for (int i = 0; i < cantRepartos; i++) {
        if (!cromosomaFinal[i]) continue;
        std::cout << repartos[i].codigo << "\t"
                << repartos[i].prioridad << "\t"
                << repartos[i].horaEntrega << "\t"
                << repartos[i].tiempoReparto << "\n";
    }
}

/**
 * Lectura del archio de Reparto
 * @param repartos: Repartos de empresa Linio
 * @param cantRepartos: cantidad de repartos a repartir
 */
void LeerReparto(Reparto **repartos, int *cantRepartos) {
    std::ifstream archivo(FILE_NAME, std::ios::in);
    if (!archivo) {
        std::cout << "No se pudo leer el archivo con la lista de Repartos: " << FILE_NAME;
        exit(1);
    }
    *repartos = new Reparto[MAX_REPARTO];
    *cantRepartos = 0;
    while (!archivo.eof()) {
        archivo >> (*repartos)[*cantRepartos].codigo
                >> (*repartos)[*cantRepartos].prioridad
                >> (*repartos)[*cantRepartos].horaEntrega
                >> (*repartos)[*cantRepartos].tiempoReparto;
        (*cantRepartos)++;
    }
    archivo.close();
}

/**
 * 
 * @param repartos
 * @param cromosoma
 * @param size
 * @return 
 */
bool RepartoValido(Reparto *repartos, int *cromosoma, int size) {
    int prioridad[4] = {0, 0, 0, 0};
    for (int i = 0; i < size; i++) {
        if (!cromosoma[i]) continue;
        prioridad[ repartos[i].prioridad - 1]++;
        // Analizamos la hora:
        for (int j = 0; j < i; j++) {
            if (!cromosoma[j]) continue;

            int entrega = repartos[j].horaEntrega,
                    entregaFinalisada = repartos[j].horaEntrega + repartos[j].tiempoReparto,
                    pedidoEntrega = repartos[i].horaEntrega,
                    pedidoEntregaFinal = repartos[i].horaEntrega + repartos[i].tiempoReparto;
            if ((entrega < pedidoEntrega && pedidoEntrega < entregaFinalisada)
                    || (entrega < pedidoEntregaFinal && pedidoEntregaFinal < entregaFinalisada)
                    || (pedidoEntrega < entrega && entrega < pedidoEntregaFinal)
                    || (pedidoEntrega < entregaFinalisada && entregaFinalisada < pedidoEntregaFinal)) {
                return false;
            }
        }
    }
    return prioridad[0] == 2 && prioridad[1] == 2 && prioridad[2] == 1 && prioridad[3] == 1;
}


















