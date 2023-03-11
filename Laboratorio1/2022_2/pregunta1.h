/* 
 * File:   pregunta1.h
 * Author: Jesus Huayhua
 *
 */

#ifndef PREGUNTA1_H
#define PREGUNTA1_H

typedef struct {
    int tipo;
    int precio;
    int cantRenovar;
} Herramienta;

void pregunta1();
void leerArchivos(Herramienta **herramientas, int *P_ptr, int *M_ptr, int *cantHerramientas);
void CargarCromosoma(int *cromosoma, int size, int num);
bool EsValido(Herramienta *herramientas, int size, int *cromosoma, int P, int M);
void MaxHerramientasReparar(Herramienta *herramientas, int cantHerramientas, int *cromosoma, int *cantHerramientasReparar, int *montoTotal);
void CargarCromosomaFinal(int *cromosoma, int *cromosomaFinal, int size);
void PreguntaB(int *cromosoma,int size,
        int cantHerramientasReparar, int montoTotal, int caso);

#endif /* PREGUNTA1_H */

