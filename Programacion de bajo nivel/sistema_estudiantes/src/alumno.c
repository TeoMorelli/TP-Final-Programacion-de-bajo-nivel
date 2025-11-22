#include "alumno.h"
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

Alumno *alumno_crear(int id, const char *nombre, int edad) {
    Alumno *a = malloc(sizeof(Alumno));
    if (!a) return NULL;
    a->id = id;
    a->edad = edad;
    a->nombre = duplicar_cadena(nombre);
    a->notas = NULL;
    a->cantidad_notas = 0;
    a->promedio = 0.0;
    return a;
}

void alumno_agregar_nota(Alumno *a, float nota) {
    if (!a) return;
    

    float *nuevas_notas = realloc(a->notas, sizeof(float) * (a->cantidad_notas + 1));
    if (!nuevas_notas) return;
    
    a->notas = nuevas_notas;
    a->notas[a->cantidad_notas] = nota;
    a->cantidad_notas++;
    

    alumno_actualizar_promedio(a);
}

void alumno_actualizar_promedio(Alumno *a) {
    if (!a) {
        a->promedio = 0.0;
        return;
    }
    if (a->cantidad_notas == 0){
        a->promedio = 0.0;
        return;
    }
    
    float suma = 0;
    for (size_t i = 0; i < a->cantidad_notas; i++) {
        suma += a->notas[i];
    }
    a->promedio = suma / a->cantidad_notas;
}

void alumno_mostrar(const Alumno *a) {
    if (!a) return;
    printf("ID: %d | Nombre: %s | Edad: %d | Promedio: %.2f\n", 
           a->id, a->nombre, a->edad, a->promedio);
    if (a->cantidad_notas > 0) {
        printf("Notas: ");
        for (size_t i = 0; i < a->cantidad_notas; i++) {
            printf("%.2f ", a->notas[i]);
        }
        printf("\n");
    }
}

void alumno_modificar(Alumno *a, const char *nuevo_nombre, int nueva_edad) {
    if (!a) return;
    free(a->nombre);
    a->nombre = duplicar_cadena(nuevo_nombre);
    a->edad = nueva_edad;
}

void alumno_destruir(Alumno *a) {
    if (!a) return;
    free(a->nombre);
    free(a->notas); 
    free(a);
}

void buscar_alumno_por_nombre() {
    if (cantidad_alumnos == 0) {
        printf("No hay alumnos registrados.\n");
        return;
    }
    
    char nombre_buscar[50];
    printf("Nombre a buscar: ");
    fgets(nombre_buscar, sizeof(nombre_buscar), stdin);
    nombre_buscar[strcspn(nombre_buscar, "\n")] = '\0';
    
    printf("Resultados de la busqueda:\n");
    int encontrados = 0;
    for (int i = 0; i < cantidad_alumnos; i++) {
        if (strstr(alumnos[i]->nombre, nombre_buscar) != NULL) {
            alumno_mostrar(alumnos[i]);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No se encontraron alumnos con ese nombre.\n");
    }
}

void buscar_alumno_por_edad() {
    if (cantidad_alumnos == 0) {
        printf("No hay alumnos registrados.\n");
        return;
    }
    
    int edad_min, edad_max;
    printf("Edad minima: ");
    scanf("%d", &edad_min);
    printf("Edad maxima: ");
    scanf("%d", &edad_max);
    getchar();
    
    printf("Resultados (edad entre %d y %d):\n", edad_min, edad_max);
    int encontrados = 0;
    for (int i = 0; i < cantidad_alumnos; i++) {
        if (alumnos[i]->edad >= edad_min && alumnos[i]->edad <= edad_max) {
            alumno_mostrar(alumnos[i]);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No se encontraron alumnos en ese rango de edad.\n");
    }
}