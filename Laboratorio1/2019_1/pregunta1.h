/* 
 * File:   pregunta1.h
 * Author: Jesus Huayhua
 * Codigo: 20196201
 * Primera Practica del Curso de Algoritmia del ciclo 2019-1
 */

#ifndef PREGUNTA1_H
#define PREGUNTA1_H

typedef struct {
    int articulo;
    int peso;
    int ganancia;
} Producto;

void pregunta1(void);
void leerDatos(Producto **productos, int *M_ptr, int *W_ptr);
bool EsValido(Producto *productos, int *cromosoma, int size, int W);
void CalcularGanancia(Producto *productos, int *cromosoma, int size, int *ganancia);
#endif /* PREGUNTA1_H */

