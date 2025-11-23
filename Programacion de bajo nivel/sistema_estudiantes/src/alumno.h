#ifndef ALUMNO_H
#define ALUMNO_H

#include <stddef.h> 

typedef struct Alumno {
    int id;
    char *nombre;
    int edad;
} Alumno;

extern Alumno* alumnos[];
extern int cantidad_alumnos;

Alumno *alumno_crear(int id, const char *nombre, int edad);
void alumno_mostrar(const Alumno *a);
void alumno_modificar(Alumno *a, const char *nuevo_nombre, int nueva_edad);
void alumno_destruir(Alumno *a);
void buscar_alumno_por_nombre();
void buscar_alumno_por_edad();
#endif
