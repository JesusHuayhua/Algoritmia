#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "pregunta1.h"

const char *FILE_NAME = "Lab1_P1_data.txt";
const int MAX_RENOVACION = 10;

void pregunta1() {
    Herramienta *herramientas;
    int P, M, cantHerramientas;
    leerArchivos(&herramientas, &P, &M, &cantHerramientas);

    //Testeo de la lectura de los archivos
    //    std::cout << "P: " << P << " M: " << M << " CANT: " << cantHerramientas << "\n";
    //    for (int i = 0; i < cantHerramientas; i++) {
    //        std::cout << herramientas[i].tipo
    //                << "\t" << herramientas[i].precio
    //                << "\t" << herramientas[i].cantRenovar << "\n";
    //    }

    int lim = pow(2, cantHerramientas);
    int cromosoma[cantHerramientas];
    int cromosomaFinal[cantHerramientas];
    int cantHerramientasReparar = 0;
    int cantHerramientasRepararFinal = 0;
    int montoTotal = 0;
    int montoTotalFinal = 0;
    int caso = 1;

    std::cout << std::setfill('*') << std::setw(30) << "*" << "\n"
            << "Pregunta B\n"
            << std::setfill('*') << std::setw(30) << "*" << "\n";
    for (int i = 0; i < lim; i++) {
        CargarCromosoma(cromosoma, cantHerramientas, i);
        // Verificamos que es valido el cromosoma
        if (EsValido(herramientas, cantHerramientas, cromosoma, P, M)) {
            // Encontrarmos las cantidad de herramietnas a reparar y el monto que costaría
            MaxHerramientasReparar(herramientas, cantHerramientas, cromosoma,
                    &cantHerramientasReparar, &montoTotal);
            // Al ser caso valido, se imprime por condición de la pregunta B
            PreguntaB(cromosoma, cantHerramientas, cantHerramientasReparar, montoTotal, caso);
            caso++;
            // Guardamos la solución más optima
            if (cantHerramientasReparar > cantHerramientasRepararFinal) {
                CargarCromosomaFinal(cromosoma, cromosomaFinal, cantHerramientas);
                cantHerramientasRepararFinal = cantHerramientasReparar;
                montoTotalFinal = montoTotal;
            }
        }
    }
    // Solución del Item A
    std::cout << std::setfill('*') << std::setw(30) << "*" << "\n"
            << "Pregunta A\n"
            << std::setfill('*') << std::setw(30) << "*" << "\n";
    for (int i = 0; i < cantHerramientas; i++) {
        if (cromosomaFinal[i]) std::cout << (i + 1) << " ";
    }
    std::cout << "\nMonto Total: " << montoTotalFinal
            << "\nCantidad de Herramientas: " << cantHerramientasRepararFinal << "\n";
}

/**
 * 
 * @param herramientas = &herramientas
 * @param P_ptr = Presupuesto
 * @param M_ptr = Tipos de Herramientas
 * @param cantHerramientas = cantidad de herramientas
 */
void leerArchivos(Herramienta **herramientas, int *P_ptr, int *M_ptr, int *cantHerramientas) {
    std::ifstream archivo(FILE_NAME, std::ios::in);
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo: " << FILE_NAME << "\n";
        exit(1);
    }
    archivo >> *M_ptr >> *P_ptr;
    *herramientas = (Herramienta *) malloc(sizeof (Herramienta) * MAX_RENOVACION);
    if (*herramientas == nullptr) {
        std::cout << "No se pudo asignar memoría\n";
        exit(2);
    }
    int i = 0;
    while (1) {
        if (archivo.eof()) break;
        archivo >> (*herramientas)[i].tipo
                >> (*herramientas)[i].precio
                >> (*herramientas)[i].cantRenovar;
        i++;
    }
    *cantHerramientas = i - 1;
    archivo.close();
}

/**
 * Convierte el num a binario
 * @param cromosoma: arreglo
 * @param size: tamaño del arreglo
 * @param num: numero a convertir a binario
 */
void CargarCromosoma(int *cromosoma, int size, int num) {
    int i = size - 1;
    while (num != 0) {
        cromosoma[i] = num % 2;
        num /= 2;
        i--;
    }
    for (int j = 0; j <= i; j++) {
        cromosoma[j] = 0;
    }
}

/**
 * Validar si el cromosoma es valido
 * @param herramientas
 * @param size
 * @param cromosoma
 * @param P: presupuesto
 * @param M: Casos totales
 * @return bool
 */
bool EsValido(Herramienta *herramientas, int size, int *cromosoma, int P, int M) {
    int total_presupuesto = 0,
            casos_totales = 1;
    for (int i = 0; i < size; i++) {
        if (cromosoma[i]) {
            total_presupuesto += herramientas[i].precio * herramientas[i].cantRenovar;
            if (total_presupuesto > P) return false; // No puede superar el presupuesto
            if (casos_totales > M) return false; // No puede superar la cantidad de herramientas
            casos_totales++;
        }
    }
    return true;
}

/**
 * Cantidad de herramientas a Reparar
 * @param herramientas
 * @param size
 * @param cromosoma
 * @param cantHerramientasReparar
 * @param montoTotal
 */
void MaxHerramientasReparar(Herramienta *herramientas, int size,
        int *cromosoma, int *cantHerramientasReparar, int *montoTotal) {
    *cantHerramientasReparar = 0;
    *montoTotal = 0;
    for (int i = 0; i < size; i++) {
        if (cromosoma[i]) {
            *cantHerramientasReparar += herramientas[i].cantRenovar;
            *montoTotal += herramientas[i].precio * herramientas[i].cantRenovar;
        }
    }
}

/**
 * Cromosoma => cromosmaFinal
 * @param cromosoma
 * @param cromosomaFinal
 * @param size: tamaño del cromosoma
 */
void CargarCromosomaFinal(int *cromosoma, int *cromosomaFinal, int size) {
    for (int i = 0; i < size; i++) {
        cromosomaFinal[i] = cromosoma[i];
    }
}

/**
 * Todos los casos validos
 * @param cromosoma
 * @param size
 * @param cantHerramientasReparar
 * @param montoTotal
 * @param caso
 */
void PreguntaB(int *cromosoma, int size,
        int cantHerramientasReparar, int montoTotal, int caso) {
    std::cout << "Caso: " << caso << "\n";
    for (int i = 0; i < size; i++) {
        if (cromosoma[i]) std::cout << (i + 1) << " ";
    }
    std::cout << "\nMontoTotal: " << montoTotal
            << "\ncantidad de Herramientas: " << cantHerramientasReparar
            << "\n" << std::setfill('-') << std::setw(30) << '-' << "\n";
}
