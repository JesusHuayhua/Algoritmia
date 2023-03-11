#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "pregunta1.h"
#include "pregunta2.h"

#define FILE_NAME "Lab1_P2_data.txt"
#define MAX_CURSOS 20
#define MIN_CREDITOS 12

void pregunta2() {
    Curso *cursos;
    int L, cantCursos;
    leerDatos(&cursos, &L, &cantCursos);
    // Verificación de la lectura de los datos
    //    std::cout << "L: " << L << " C: " << cantCursos << "\n";
    //    for (int i = 0; i < cantCursos; i++) {
    //        std::cout << cursos[i].id
    //                << " " << cursos[i].creditos
    //                << " " << cursos[i].horario
    //                << " " << cursos[i].sesionTeoria
    //                << " " << cursos[i].horaInicioTeoria
    //                << " " << cursos[i].horaFinalTeoria
    //                << " " << cursos[i].sesionPractica
    //                << " " << cursos[i].horaInicioPractica
    //                << " " << cursos[i].horaFinalPractica
    //                << " " << cursos[i].evaluacion << "\n";
    //    }

    int lim = pow(2, cantCursos),
            creditos = 0,
            creditosMaximos = 0,
            cromosoma[cantCursos],
            cromosomaFinal[cantCursos];


    for (int i = 0; i < lim; i++) {
        CargarCromosoma(cromosoma, cantCursos, i);
        if (EsValido(cursos, cromosoma, cantCursos)) {
            CreditosTotales(cursos, cromosoma, cantCursos, &creditos);
            if (CreditosValidos(creditos, L) && creditos >= creditosMaximos) {
                creditosMaximos = creditos;
                CargarCromosomaFinal(cromosoma, cromosomaFinal, cantCursos);
            }
        }
    }
    for (int i = 0; i < cantCursos; i++) {
        if (cromosomaFinal[i]) {
            std::cout << std::setfill('0') << std::setw(6) << cursos[i].id
                    << "-" << std::setfill('0') << std::setw(4) << cursos[i].horario << "\n";
        }
    }
    std::cout << "Creditos finales: " << creditosMaximos << "\n";
    std::cout << "Creditos finales: " << creditos << "\n";
}

/**
 * Lectura de los datos
 * @param cursos: almacenamiento de la función
 * @param L: maximo cantidad de creditos
 * @param cant: cantidad de cursos del archivo
 */
void leerDatos(Curso **cursos, int *L, int *cant) {
    std::ifstream archivo(FILE_NAME, std::ios::in);
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo " << FILE_NAME << "para su lectura\n";
        exit(1);
    }
    *cursos = new Curso[MAX_CURSOS];
    int i = 0;
    archivo >> *L;
    while (!archivo.eof()) {
        archivo >> (*cursos)[i].id
                >> (*cursos)[i].creditos
                >> (*cursos)[i].horario
                >> (*cursos)[i].sesionTeoria
                >> (*cursos)[i].horaInicioTeoria
                >> (*cursos)[i].horaFinalTeoria
                >> (*cursos)[i].sesionPractica
                >> (*cursos)[i].horaInicioPractica
                >> (*cursos)[i].horaFinalPractica
                >> (*cursos)[i].evaluacion;
        i++;
    }
    *cant = i;
    archivo.close();
}

bool EsValido(Curso *cursos, int *cromosoma, int size) {
    int id[size] = {0}, index = 0;
    for (int i = 0; i < size; i++) {
        //Se repite curso en el cromosoma
        if (cromosoma[i]) {
            if (!NewId(cursos, id, index, cromosoma, i)) {
                return false;
            }
            id[index++] = i; // almacenamos la posición del curso valido
        }
    }
    // id => arreglo con todas las posiciones validas
    // Verficamos que el horario sea valido
    for (int i = 0; i < index; i++) {
        if (!HorarioValido(cursos, id, i)) return false;
    }
    return true;
}

bool NewId(Curso *cursos, int *id, int index, int *cromosoma, int i) {
    for (int j = 0; j < i; j++) {
        for (int k = 0; k < index; k++) {
            if (cromosoma[j] && cursos[j].id == cursos[id[k]].id) return false;
        }
    }
    return true;
}

bool HorarioValido(Curso *curso, int *id, int i) {
    for (int j = 0; j < i; j++) {
        if ((curso[id[j]].sesionTeoria == curso[id[i]].sesionTeoria && verificarTeoria(curso, id[j], id[i]))
                || (curso[id[j]].sesionPractica == curso[id[i]].sesionTeoria && verificarTeoPrac(curso, id[j], id[i]))
                || (curso[id[j]].sesionPractica == curso[id[i]].sesionPractica && verificarPractica(curso, id[j], id[i]))
                || (curso[id[j]].sesionTeoria == curso[id[i]].sesionPractica && verificarPracTeo(curso, id[j], id[i]))) {
            return false;
        }
    }
    return true;
}

bool verificarTeoria(Curso *curso, int j, int i) {
    return (curso[j].horaInicioTeoria < curso[i].horaInicioTeoria
            && curso[i].horaInicioTeoria < curso[j].horaFinalTeoria)
            ||
            (curso[j].horaInicioTeoria < curso[i].horaFinalTeoria
            && curso[i].horaFinalTeoria < curso[j].horaFinalTeoria);
}

bool verificarPractica(Curso *curso, int j, int i) {
    return (curso[j].horaInicioPractica < curso[i].horaInicioPractica
            && curso[i].horaInicioPractica < curso[j].horaFinalPractica)
            ||
            (curso[j].horaInicioPractica < curso[i].horaFinalPractica
            && curso[i].horaFinalPractica < curso[j].horaFinalPractica);
}

bool verificarTeoPrac(Curso *curso, int j, int i) {
    return (curso[j].horaInicioPractica < curso[i].horaInicioTeoria
            && curso[i].horaInicioTeoria < curso[j].horaFinalPractica)
            ||
            (curso[j].horaInicioPractica < curso[i].horaFinalTeoria
            && curso[i].horaFinalTeoria < curso[j].horaFinalPractica);
}

bool verificarPracTeo(Curso *curso, int j, int i) {
    return (curso[j].horaInicioTeoria < curso[i].horaInicioPractica
            && curso[i].horaInicioPractica < curso[j].horaFinalTeoria)
            ||
            (curso[j].horaInicioTeoria < curso[i].horaInicioPractica
            && curso[i].horaInicioPractica < curso[j].horaFinalTeoria);
}

void CreditosTotales(Curso *cursos, int *cromosoma, int size, int *creditos) {
    *creditos = 0;
    for (int i = 0; i < size; i++) {
        if (cromosoma[i]) {
            *creditos += cursos[i].creditos;
        }
    }
}

bool CreditosValidos(int creditos, int max) {
    return MIN_CREDITOS <= creditos && creditos <= max;
}