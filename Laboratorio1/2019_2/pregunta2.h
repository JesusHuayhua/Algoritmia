/* 
 * File:   pregunta2.h
 * Author: Jesus Huayhua
 * Codigo: 20196201
 * Primera Practica del Curso de Algoritmia del ciclo 2019-2
 */

#ifndef PREGUNTA2_H
#define PREGUNTA2_H

typedef struct{
    int codigo;
    int prioridad;
    int horaEntrega;
    int tiempoReparto;
}Reparto;

void pregunta2(void);
void LeerReparto(Reparto **repartos, int *cantRepartos);
bool RepartoValido(Reparto *repartos,int *cromosoma,int cantRepartos);
#endif /* PREGUNTA2_H */

