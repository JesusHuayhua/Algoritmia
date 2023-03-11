/* 
 * File:   pregunta1.h
 * Author: Jesus Huayhua
 *
 * Created on 22 de febrero de 2023, 20:20
 */

#ifndef PREGUNTA1_H
#define PREGUNTA1_H

typedef struct {
    int x;
    int y;
    int sano;
}PersonaContagio;

typedef struct{
    int x;
    int y;
}PersonaMINSA;

void Pregunta1(void);
void LeerDatos(PersonaContagio **perContagio, PersonaMINSA **perMinsa,
        int *cantContagio, int *cantMinsa, double *radio);
double DistanciaPacMinsa(int perX, int perY, int minsaX, int minsaY);

#endif /* PREGUNTA1_H */

