
/* 
 * File:   pregunta2.h
 * Author: Jesus Huayhua
 *
 */

#ifndef PREGUNTA2_H
#define PREGUNTA2_H

typedef struct {
    int id;
    int creditos;
    int horario;
    int sesionTeoria;
    int horaInicioTeoria;
    int horaFinalTeoria;
    int sesionPractica;
    int horaInicioPractica;
    int horaFinalPractica;
    int evaluacion;
} Curso;

void pregunta2();
void leerDatos(Curso **cursos, int *L, int *cant);
bool EsValido(Curso *cursos, int *cromosoma, int size);
bool NewId(Curso *cursos, int *id, int index, int *cromosoma, int i);
bool HorarioValido(Curso *curso, int *id, int i);
bool verificarTeoria(Curso *curso, int j, int i);
bool verificarPractica(Curso *curso, int j, int i);
bool verificarTeoPrac(Curso *curso, int j, int i);
bool verificarPracTeo(Curso *curso, int j, int i);
void CreditosTotales(Curso *cursos, int *cromosoma, int size, int *creditos);
bool CreditosValidos(int max, int creditos);
#endif /* PREGUNTA2_H */

