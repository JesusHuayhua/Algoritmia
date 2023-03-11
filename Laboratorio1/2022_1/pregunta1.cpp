#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

#include "pregunta1.h"

#define FILE_NAME "Lab1_P1_data.txt"
#define MAX_CARACTER_CANAL 30

void pregunta1() {
    Canal *canales;
    int P, N;
    // P = presuppuesto; N = cantidad de canales
    leerArchivos(&canales, &P, &N);
    // Confirmación de lectura de archivos
    //    std::cout << "P: " << P << " N: " << N << "\n";
    //    for (int i = 0; i < N; i++) {
    //        std::cout << std::left << std::setfill(' ') << std::setw(5) << canales[i].codigo
    //                << std::left << std::setfill(' ') << std::setw(20) << canales[i].canal
    //                << std::setw(15) << canales[i].USD
    //                << std::setw(15) << canales[i].ROAS
    //                << std::setw(15) << canales[i].nivelDeMarca
    //                << std::setw(15) << canales[i].ingresoPorVentas << "\n";
    //    }
    int lim = pow(2, N),
            cromosoma[N],
            cromosomaFinal[N],
            inversionTotal = 0,
            inversionTotalFinal = 0;
    int cromosomaFinalPublicidad[N],
            recordacionMarca = 0,
            recordacionMarcaFinal = 0,
            inversionTotalPublicidad = 0,
            inversionTotalPublicidadFinal = 0;
    double maxIngresoVentas = 0,
            maxIngresoVentasFinal = 0,
            ingresoPublicidad = 0,
            ingresoPublicidadFinal = 0;
    for (int i = 0; i < lim; i++) {
        CargarCromosoma(cromosoma, N, i);
        if (EsValido(canales, cromosoma, N, P)) {

            MaxVentas(canales, cromosoma, N, &inversionTotal, &maxIngresoVentas);
            MaxPublicidad(canales, cromosoma, N, &inversionTotalPublicidad, &recordacionMarca, &ingresoPublicidad);

            if (maxIngresoVentas > maxIngresoVentasFinal) {
                CargarCromosomaFinal(cromosoma, cromosomaFinal, N);
                maxIngresoVentasFinal = maxIngresoVentas;
                inversionTotalFinal = inversionTotal;
            }
            if (recordacionMarca > recordacionMarcaFinal) {
                CargarCromosomaFinal(cromosoma, cromosomaFinalPublicidad, N);
                inversionTotalPublicidadFinal = inversionTotalPublicidad;
                recordacionMarcaFinal = recordacionMarca;
                ingresoPublicidadFinal = ingresoPublicidad;
            }

        }
    }
    ItemB(maxIngresoVentasFinal);
    ItemC(canales, cromosomaFinal, N, maxIngresoVentasFinal, inversionTotalFinal);
    ItemD(canales, cromosomaFinalPublicidad, N, recordacionMarcaFinal, inversionTotalPublicidadFinal, ingresoPublicidadFinal);
}

void leerArchivos(Canal **canales, int *P_ptr, int *N_ptr) {
    std::ifstream archivo(FILE_NAME, std::ios::in);
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo: " << FILE_NAME << "\n";
        exit(1);
    }
    archivo >> *P_ptr >> *N_ptr;
    if (archivo.fail()) {
        std::cout << "No se pudo leer el presupuesto o la cantidad de empresas\n";
        exit(2);
    }
    *canales = (Canal *) malloc(sizeof (Canal) * (*N_ptr));
    for (int i = 0; i < *N_ptr; i++) {
        (*canales)[i].canal = (char *) malloc(sizeof (char) * MAX_CARACTER_CANAL);
        archivo >> (*canales)[i].codigo // Codigo
                >> (*canales)[i].canal // Nombre del canal
                >> (*canales)[i].USD // Inversion publicitaria
                >> (*canales)[i].ROAS // Retorno de inversion
                >> (*canales)[i].nivelDeMarca; // Recaudación de la marca
        // Ingreso por ventas => ROAS = ingresoPorVentas / USD
        (*canales)[i].ingresoPorVentas = (*canales)[i].ROAS * (*canales)[i].USD;
    }
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
 * Validación del cromosoma
 * @param canales
 * @param cromosoma
 * @param size
 * @param P
 * @return 
 */
bool EsValido(Canal *canales, int *cromosoma, int size, int P) {
    int inversionTotal = 0;
    for (int i = 0; i < size; i++) {
        if (cromosoma[i]) {
            inversionTotal += canales[i].USD;
            if (inversionTotal > P) return false;
        }
    }
    return true;
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
 * Calcular la Inversion y Ingreso de por publicidad sin conciderar la marca
 * @param canales
 * @param cromosoma
 * @param size
 * @param inversion
 * @param ingresoVentas
 */
void MaxVentas(Canal *canales, int *cromosoma, int size, int *inversion, double *ingreso) {
    *ingreso = 0;
    *inversion = 0;
    for (int i = 0; i < size; i++) {
        if (cromosoma[i]) {
            *ingreso += canales[i].ingresoPorVentas;
            *inversion += canales[i].USD;
        }
    }
}

/**
 * Calcular la maxima inversion, marca e ingreso; considerando la marca
 * @param canales
 * @param cromosoma
 * @param size
 * @param inversion
 * @param recordacionMarca
 * @param ingresoPublicidad
 */
void MaxPublicidad(Canal *canales, int *cromosoma, int size, int *inversion,
        int *marca, double *ingreso) {
    *inversion = 0;
    *marca = 0;
    *ingreso = 0;
    for (int i = 0; i < size; i++) {
        if (cromosoma[i]) {
            *marca += canales[i].nivelDeMarca;
            *inversion += canales[i].USD;
            *ingreso += canales[i].ingresoPorVentas;
        }
    }
}

/**
 * Mostrar en pantalla lo pedido en el Item B
 * @param ingresoVentas
 * @return 
 */
double ItemB(double ingresoVentas) {
    TituloItem('B');
    std::cout << "El máximo ingreso por ventas es de: "
            << std::fixed << std::setprecision(2) << ingresoVentas
            << " dolares\n";
}

/**
 * Mostrar en pantalla lo pedido en el Item C
 * @param canales
 * @param cromosoma
 * @param size
 * @param ingresoVentas
 * @param inversionTotal
 */
void ItemC(Canal *canales, int *cromosoma, int size, double ingresoVentas,
        int inversionTotal) {
    TituloItem('C');
    std::cout << "El máximo ingreso por ventas es de: "
            << std::fixed << std::setprecision(2) << ingresoVentas
            << " dolares con una inversion total en publicidad de: "
            << std::fixed << std::setprecision(2) << inversionTotal
            << " dolares.\n";
    std::cout << "Los canales de publicidad que se deben de elegir para obtener el máximo "
            << "ingreso total son: \n";

    for (int i = 0; i < size; i++) {
        if (cromosoma[i]) {
            std::cout << std::setfill(' ') << std::setw(4) << " "
                    << "- Canal " << (i + 1) << " - " << canales[i].canal
                    << ",ingreso = " << canales[i].ingresoPorVentas
                    << " dolares con una inversion publicitaria de "
                    << std::fixed << std::setprecision(2) << canales[i].USD
                    << " dolares\n";
        }
    }
}

/**
 * Mostrar el pantalla lo pedido en el Item D
 * @param canales
 * @param cromosoma
 * @param size
 * @param marca
 * @param inversion
 * @param ingreso
 */
void ItemD(Canal *canales, int *cromosoma, int size, int marca, int inversion,
        double ingreso) {
    TituloItem('D');
    std::cout << "El nivel máximo de recordación de marca es de " << marca
            << " con una inversion total en publicidad de "
            << std::fixed << std::setprecision(2) << inversion
            << " dolares y un ingreso de "
            << std::fixed << std::setprecision(2) << ingreso << " dolares\n";
    std::cout << "Los canales de publicidad que se deben de elegir para obtener el máximo "
            << "ingreso total son: \n";

    for (int i = 0; i < size; i++) {
        if (cromosoma[i]) {
            std::cout << std::setfill(' ') << std::setw(4) << " "
                    << "- Canal " << (i + 1) << " - " << canales[i].canal
                    << ", recordacion de marca = " << canales[i].nivelDeMarca
                    << ",ingreso = " << canales[i].ingresoPorVentas
                    << " dolares con una inversion publicitaria de "
                    << std::fixed << std::setprecision(2) << canales[i].USD
                    << " dolares\n";
        }
    }
}

/**
 * Mostrar cabecera del título que se está resolviendo
 * @param item
 */
void TituloItem(char item) {
    std::cout << std::setfill('*') << std::setw(30) << "*" << "\n"
            << "Item " << item << "\n"
            << std::setfill('*') << std::setw(30) << "*" << "\n";
}






