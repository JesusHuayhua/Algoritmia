/* 
 * File:   pregunta1.h
 * Author: Jesus Huayhua
 * Pregunta #1 del curso de Algoritmia 2019-2
 */

#ifndef PREGUNTA1_H
#define PREGUNTA1_H

typedef struct {
    int id;
    int costo;
    int ganancia;
    int cantPredecesores;
    int *predecesores;
} Proyecto;

void pregunta1(void);
void leerDatos(Proyecto **proyectos, int *N, int *P);
bool EsValido(Proyecto *proyectos, int *cromosoma, int size, int presupuesto);
void CalcularTotalGanancia(Proyecto *proyectos, int *cromosoma, int size, int *ganancia);
void MostrarProyecto(Proyecto *proyectos,int *cromosoma,int size,int ganancia);
void OrdenarProyectos(Proyecto *proyectos, int *cromosoma, int size);
void SwapProyectos(Proyecto *proyectos,int i,int j);
#endif /* PREGUNTA1_H */

