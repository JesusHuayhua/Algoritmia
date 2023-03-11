/* 
 * File:   pregunta2.h
 * Author: Jesus Huayhua
 *
 * Created on 22 de febrero de 2023, 20:20
 */

#ifndef PREGUNTA2_H
#define PREGUNTA2_H

typedef struct {
    int rol;
    /*
     * 1 => Despachador
     * 2 => Cajero
     * 3 => Supervisor
     */
    int salarioMensual; //Salario mensuales en soles
    int salarioHora; // Salario por hora en soles
}Rol;

typedef struct {
    int postulante; // Id postulante
    int rol; // Rol al que postula
    int mph; // Velocidad de reposición
    int bpm; // Bonificación en soles por marca en una hora 
}Postulante;

void Pregunta2(void);
void LeerPostulantes(Rol **roles, Postulante **postulantes, int *t, int *MPxH);
void LeerRoles(Rol **roles);


#endif /* PREGUNTA2_H */

