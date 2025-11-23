#ifndef MATERIA_H
#define MATERIA_H

#include "alumno.h"
#include <stddef.h>

typedef struct {
    Alumno *alumno;
    float *notas;
    size_t cantidad_notas;
    float promedio;
} Inscripcion;


typedef struct Materia {
    int id;
    char *nombre;
    Inscripcion *inscriptos;
    size_t cantidad;
} Materia;

Materia *materia_crear(int id, const char *nombre);
void materia_modificar(Materia *m, const char *nuevo_nombre);
void materia_agregar_alumno(Materia *m, Alumno *a);
void materia_asignar_nota(Materia *m, int id_alumno, float nota);
void materia_mostrar(const Materia *m);
void materia_destruir(Materia *m);
void materia_remover_alumno(Materia *m, int id_alumno);

#endif