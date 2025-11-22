#include "materia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicar_cadena(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char *copy = malloc(len + 1);
    if (!copy) return NULL;
    memcpy(copy, s, len + 1);
    return copy;
}

Materia *materia_crear(int id, const char *nombre) {
    Materia *m = malloc(sizeof(Materia));
    if (!m) return NULL;
    m->id = id;
    m->nombre = duplicar_cadena(nombre);
    m->inscriptos = NULL;
    m->cantidad = 0;
    return m;
}

void materia_modificar(Materia *m, const char *nuevo_nombre) {
    if (!m) return;
    free(m->nombre);
    m->nombre = duplicar_cadena(nuevo_nombre);
}

void materia_agregar_alumno(Materia *m, Alumno *a) {
    if (!m || !a) return;
    Alumno **nuevo = realloc(m->inscriptos, sizeof(Alumno*) * (m->cantidad + 1));
    if (!nuevo) return;
    m->inscriptos = nuevo;
    m->inscriptos[m->cantidad] = a;
    m->cantidad++;
}

void materia_asignar_nota(Materia *m, int id_alumno, float nota) {
    if (!m) return;
    
    for (size_t i = 0; i < m->cantidad; i++) {
        if (m->inscriptos[i]->id == id_alumno) {
            alumno_agregar_nota(m->inscriptos[i], nota);
            return;
        }
    }
    printf("Alumno con ID %d no encontrado en la materia.\n", id_alumno);
}

void materia_mostrar(const Materia *m) {
    if (!m) return;
    printf("Materia: %s (ID %d)\n", m->nombre, m->id);
    printf("Inscriptos:\n");
    for (size_t i = 0; i < m->cantidad; i++) {
        printf("  - ");
        alumno_mostrar(m->inscriptos[i]);
    }
}

void materia_destruir(Materia *m) {
    if (!m) return;
    free(m->nombre);
    free(m->inscriptos); // no destruye alumnos, solo la lista
    free(m);
}

void materia_remover_alumno(Materia *m, int id_alumno) {
    if (!m) return;
    
    for (size_t i = 0; i < m->cantidad; i++) {
        if (m->inscriptos[i]->id == id_alumno) {
            // Mover los elementos restantes
            for (size_t j = i; j < m->cantidad - 1; j++) {
                m->inscriptos[j] = m->inscriptos[j + 1];
            }
            m->cantidad--;
            // Redimensionar el array
            Alumno **nuevo = realloc(m->inscriptos, sizeof(Alumno*) * m->cantidad);
            if (nuevo || m->cantidad == 0) {
                m->inscriptos = nuevo;
            }
            return;
        }
    }
}