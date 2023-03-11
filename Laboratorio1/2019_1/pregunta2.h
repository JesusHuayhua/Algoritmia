/* 
 * File:   pregunta2.h
 * Author: Jesus Huayhua
 * Codigo: 20196201
 * Primera Practica del Curso de Algoritmia del ciclo 2019-1
 */
#ifndef PREGUNTA2_H
#define PREGUNTA2_H


void pregunta2(void);
void PopulateGameBoard(int t, char **tablero);
void ShowGameBoard(int t, char **tablero);
void SearchWord(char *word, int t, char **tablero, char *res);
bool SearchRight(char *word, int t, char **tablero, char *res);
bool SearchLeft(char *word, int t, char **tablero, char *res);
bool SearchDown(char *word, int t, char **tablero, char *res);
bool SearchUp(char *word, int t, char **tablero, char *res);

#endif /* PREGUNTA2_H */

