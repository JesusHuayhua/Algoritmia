#include <iostream>
#include <iomanip>

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
 * Mostrar cabecera del título que se está resolviendo
 * @param item
 */
void TituloItem(char item) {
    std::cout << std::setfill('*') << std::setw(30) << "*" << "\n"
            << "Item " << item << "\n"
            << std::setfill('*') << std::setw(30) << "*" << "\n";
}

void TituloPregunta(char item){
    std::cout << std::setfill('*') << std::setw(30) << "*" << "\n"
            << "Pregunta: " << item << "\n"
            << std::setfill('*') << std::setw(30) << "*" << "\n";
}