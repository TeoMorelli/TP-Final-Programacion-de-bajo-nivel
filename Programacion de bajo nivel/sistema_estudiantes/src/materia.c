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
    Inscripcion *nuevo = realloc(m->inscriptos, sizeof(Inscripcion) * (m->cantidad + 1));
    if (!nuevo) return;
    m->inscriptos = nuevo;

    // Inicializar la nueva inscripción
    m->inscriptos[m->cantidad].alumno = a;
    m->inscriptos[m->cantidad].notas = NULL;
    m->inscriptos[m->cantidad].cantidad_notas = 0;
    m->inscriptos[m->cantidad].promedio = 0.0;

    m->cantidad++;
}

static void inscripcion_actualizar_promedio(Inscripcion *insc) {
    if (!insc || insc->cantidad_notas == 0) {
        if (insc) insc->promedio = 0.0;
        return;
    }
    float suma = 0;
    for (size_t i = 0; i < insc->cantidad_notas; i++) {
        suma += insc->notas[i];
    }
    insc->promedio = suma / insc->cantidad_notas;
}

void materia_asignar_nota(Materia *m, int id_alumno, float nota) {
    if (!m) return;
    
    for (size_t i = 0; i < m->cantidad; i++) {
        if (m->inscriptos[i].alumno->id == id_alumno) {
            Inscripcion *insc = &m->inscriptos[i];
            float *nuevas_notas = realloc(insc->notas, sizeof(float) * (insc->cantidad_notas + 1));
            if (!nuevas_notas) return;

            insc->notas = nuevas_notas;
            insc->notas[insc->cantidad_notas] = nota;
            insc->cantidad_notas++;
            
            inscripcion_actualizar_promedio(insc);
            return;
        }
    }
    printf("Alumno con ID %d no encontrado en la materia.\n", id_alumno);
}

void materia_mostrar(const Materia *m) {
    if (!m) return;
    printf("Materia: %s (ID %d)\n", m->nombre, m->id);
    printf("Inscriptos:\n");
    if (m->cantidad == 0) {
        printf("  (No hay alumnos inscriptos)\n");
    } else {
        for (size_t i = 0; i < m->cantidad; i++) {
            printf("  - ID: %d | Nombre: %s | Edad: %d | Promedio en materia: %.2f\n", 
                   m->inscriptos[i].alumno->id, m->inscriptos[i].alumno->nombre, m->inscriptos[i].alumno->edad, m->inscriptos[i].promedio);
            if (m->inscriptos[i].cantidad_notas > 0) {
                printf("    Notas: ");
                for (size_t j = 0; j < m->inscriptos[i].cantidad_notas; j++) {
                    printf("%.2f ", m->inscriptos[i].notas[j]);
                }
                printf("\n");
            }
        }
    }
}

void materia_destruir(Materia *m) {
    if (!m) return;
    free(m->nombre);
    for (size_t i = 0; i < m->cantidad; i++) {
        free(m->inscriptos[i].notas);
    }
    free(m->inscriptos);
    free(m);
}

void materia_remover_alumno(Materia *m, int id_alumno) {
    if (!m) return;
    
    for (size_t i = 0; i < m->cantidad; i++) {
        if (m->inscriptos[i].alumno->id == id_alumno) {
            // Liberar las notas de esta inscripción específica
            free(m->inscriptos[i].notas);
            // Mover los elementos restantes
            for (size_t j = i; j < m->cantidad - 1; j++) {
                m->inscriptos[j] = m->inscriptos[j + 1];
            }
            m->cantidad--;
            // Redimensionar el array
            Inscripcion *nuevo = realloc(m->inscriptos, sizeof(Inscripcion) * m->cantidad);
            if (nuevo || m->cantidad == 0) {
                m->inscriptos = nuevo;
            }
            return;
        }
    }
}