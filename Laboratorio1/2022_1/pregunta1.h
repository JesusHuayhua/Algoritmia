/* 
 * File:   pregunta1.h
 * Author: Jesus Huayhua
 *
 */

#ifndef PREGUNTA1_H
#define PREGUNTA1_H

typedef struct {
    int codigo;
    char *canal;
    int USD;
    double ROAS;
    double ingresoPorVentas;
    int nivelDeMarca;
} Canal;

void pregunta1();
void leerArchivos(Canal **canales, int *P, int *N);
void CargarCromosoma(int *cromosoma, int size, int num);
bool EsValido(Canal *canales, int *cromosoma, int size, int P);
void CargarCromosomaFinal(int *cromosoma, int *cromosomaFinal, int size);
void MaxVentas(Canal *canales, int *cromosoma, int size, int *inversion, double *ingresoVentas);
void MaxPublicidad(Canal *canales, int *cromosoma, int size, int *inversion,
        int *recordacionMarca, double *ingresoPublicidad);
double ItemB(double maxIngresoVentasFinal);
void ItemC(Canal *canales,int *cromosoma, int size, double ingresoVentas, int inversionTotal);
void ItemD(Canal *canales, int *cromosoma, int size, int marca, int inversion,double ingreso);
void TituloItem(char item);
#endif /* PREGUNTA1_H */

