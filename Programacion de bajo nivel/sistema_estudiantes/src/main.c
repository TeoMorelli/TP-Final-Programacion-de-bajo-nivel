#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alumno.h"
#include "materia.h"

#define MAX_ALUMNOS 100
#define MAX_MATERIAS 50

Alumno* alumnos[MAX_ALUMNOS];
Materia* materias[MAX_MATERIAS];
int cantidad_alumnos = 0;
int cantidad_materias = 0;

void menu_alumnos();
void menu_materias();
void precargar_datos();

void menu_principal() {
    int opcion;
    do {
        printf("\n============================\n");
        printf("  SISTEMA DE ESTUDIANTES  \n");
        printf("============================\n");
        printf("1) Gestionar Alumnos\n");
        printf("2) Gestionar Materias\n");
        printf("0) Salir\n");
        printf("Elija una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                menu_alumnos();
                break;
            case 2:
                menu_materias();
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 0);
}

void menu_alumnos() {
    int opcion;
    do {
        printf("\n--- GESTION DE ALUMNOS ---\n");
        printf("1) Alta alumno\n");
        printf("2) Listar alumnos\n");
        printf("3) Modificar alumno\n");
        printf("4) Eliminar alumno\n");
        printf("5) Buscar por nombre\n");
        printf("6) Buscar por rango de edad\n");
        printf("0) Volver\n");
        printf("Seleccione: ");
        scanf("%d", &opcion);
        getchar();

    if (opcion == 1) {
        char nombre[50];
        int edad;
        printf("Nombre: ");
        fgets(nombre, sizeof(nombre), stdin);
        nombre[strcspn(nombre, "\n")] = '\0';
        printf("Edad: ");
        scanf("%d", &edad); getchar();
        int nuevo_id = cantidad_alumnos + 1;
            alumnos[cantidad_alumnos] = alumno_crear(nuevo_id, nombre, edad);
            cantidad_alumnos++;
            printf("Alumno agregado correctamente (ID: %d, Nombre: %s, Edad: %d).\n", nuevo_id, nombre, edad);
        } else if (opcion == 2) {
            printf("\n--- LISTA DE ALUMNOS ---\n");
            for (int i = 0; i < cantidad_alumnos; i++) {
                printf("- ");
                alumno_mostrar(alumnos[i]);
            }
        } else if (opcion == 3) {
            int id;
            printf("ID del alumno a modificar: ");
            scanf("%d", &id); getchar();
            if (id <= 0 || id > cantidad_alumnos) {
                printf("ID invalido.\n");
                continue;
            }
            char nuevo_nombre[50];
            int nueva_edad;
            printf("Nuevo nombre: ");
            fgets(nuevo_nombre, sizeof(nuevo_nombre), stdin);
            nuevo_nombre[strcspn(nuevo_nombre, "\n")] = '\0';
            printf("Nueva edad: ");
            scanf("%d", &nueva_edad); getchar();
            alumno_modificar(alumnos[id-1], nuevo_nombre, nueva_edad);
            printf("Alumno modificado.\n");
        } else if (opcion == 4) {
            int id;
            printf("ID del alumno a eliminar: ");
            scanf("%d", &id); getchar();
            if (id <= 0 || id > cantidad_alumnos) {
                printf("ID invalido.\n");
                continue;
            }
            alumno_destruir(alumnos[id-1]);
            for (int i = id - 1; i < cantidad_alumnos - 1; i++) {
                alumnos[i] = alumnos[i + 1];
            }
            cantidad_alumnos--;
            printf("Alumno eliminado.\n");
        } else if (opcion == 5) {
            buscar_alumno_por_nombre();
        } else if (opcion == 6) {
            buscar_alumno_por_edad();
        }
    } while (opcion != 0);
}

void menu_materias() {
        int opcion;
    do {
        printf("\n--- GESTION DE MATERIAS ---\n");
        printf("1) Alta materia\n");
        printf("2) Listar materias\n");
        printf("3) Modificar materia\n");
        printf("4) Eliminar materia\n");
        printf("5) Agregar alumno a materia\n");
        printf("6) Asignar nota a alumno\n");
        printf("0) Volver\n");
        printf("Seleccione: ");
        scanf("%d", &opcion);
        getchar();

        if (opcion == 1) {
            char nombre[50];
            printf("Nombre materia: ");
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = '\0';
            int nuevo_id = cantidad_materias + 1;
            materias[cantidad_materias] = materia_crear(nuevo_id, nombre);
            cantidad_materias++;
            printf("Materia agregada correctamente (ID: %d, Nombre: %s).\n", nuevo_id, nombre);
        } else if (opcion == 2) {
            printf("\n--- LISTA DE MATERIAS ---\n");
            for (int i = 0; i < cantidad_materias; i++) {
                materia_mostrar(materias[i]);
            }
        } else if (opcion == 3) {
            if (cantidad_materias == 0) {
                printf("No hay materias registradas.\n");
                continue;
            }
            
            int id;
            printf("ID de la materia a modificar: ");
            scanf("%d", &id); getchar();
            
            if (id <= 0 || id > cantidad_materias) {
                printf("ID invalido.\n");
                continue;
            }
            
            char nuevo_nombre[50];
            printf("Nuevo nombre de la materia: ");
            fgets(nuevo_nombre, sizeof(nuevo_nombre), stdin);
            nuevo_nombre[strcspn(nuevo_nombre, "\n")] = '\0';
            
            materia_modificar(materias[id-1], nuevo_nombre);
            printf("Materia modificada correctamente.\n");
            
        } else if (opcion == 4) {
            if (cantidad_materias == 0) {
                printf("No hay materias registradas.\n");
                continue;
            }
            
            int id;
            printf("ID de la materia a eliminar: ");
            scanf("%d", &id); getchar();
            
            if (id <= 0 || id > cantidad_materias) {
                printf("ID invalido.\n");
                continue;
            }
            
            materia_destruir(materias[id-1]);
            for (int i = id - 1; i < cantidad_materias - 1; i++) {
                materias[i] = materias[i + 1];
            }
            cantidad_materias--;
            printf("Materia eliminada correctamente.\n"); 
        
        }   else if (opcion == 5) {
            int id_materia, id_alumno;
            printf("ID de la materia: ");
            scanf("%d", &id_materia); getchar();
            printf("ID del alumno: ");
            scanf("%d", &id_alumno); getchar();
            
            if (id_materia <= 0 || id_materia > cantidad_materias || 
                id_alumno <= 0 || id_alumno > cantidad_alumnos) {
                printf("ID invalido.\n");
                continue;
            }
            materia_agregar_alumno(materias[id_materia-1], alumnos[id_alumno-1]);
            printf("Alumno agregado a la materia.\n");
        } else if (opcion == 6) {
            int id_materia, id_alumno;
            float nota;
            printf("ID de la materia: ");
            scanf("%d", &id_materia); getchar();
            printf("ID del alumno: ");
            scanf("%d", &id_alumno); getchar();
            printf("Nota: ");
            scanf("%f", &nota); getchar();
            
            if (id_materia <= 0 || id_materia > cantidad_materias) {
                printf("ID de materia invalido.\n");
                continue;
            }
            materia_asignar_nota(materias[id_materia-1], id_alumno, nota);
        }
    } while (opcion != 0);
}

void precargar_datos() {
    // Crear alumnos
    alumnos[cantidad_alumnos++] = alumno_crear(1, "Juan Perez", 20);
    alumnos[cantidad_alumnos++] = alumno_crear(2, "Maria Garcia", 22);
    alumnos[cantidad_alumnos++] = alumno_crear(3, "Pedro Rodriguez", 21);
    alumnos[cantidad_alumnos++] = alumno_crear(4, "Ana Lopez", 19);
    alumnos[cantidad_alumnos++] = alumno_crear(5, "Carlos Sanchez", 23);

    // Crear materias
    materias[cantidad_materias++] = materia_crear(1, "Programacion I");
    materias[cantidad_materias++] = materia_crear(2, "Matematica Discreta");
    materias[cantidad_materias++] = materia_crear(3, "Algebra I");
    materias[cantidad_materias++] = materia_crear(4, "Introduccion a Ingenieria en Computacion");
    materias[cantidad_materias++] = materia_crear(5, "Algoritmos y Programacion II");

    // Inscribir alumnos
    // Juan (ID 1) a Programacion I (ID 1)
    materia_agregar_alumno(materias[0], alumnos[0]); 
    // Maria (ID 2) a Programacion I (ID 1)
    materia_agregar_alumno(materias[0], alumnos[1]); 
    // Juan (ID 1) a Algoritmos y Programacion II (ID 5)
    materia_agregar_alumno(materias[4], alumnos[0]);

    // Juan (ID 1) a Matematica Discreta (ID 2)
    materia_agregar_alumno(materias[1], alumnos[0]); 
    // Pedro (ID 3) a Matematica Discreta (ID 2)
    materia_agregar_alumno(materias[1], alumnos[2]);

    // Maria (ID 2), Ana (ID 4) y Carlos (ID 5) a Algebra I (ID 3)
    materia_agregar_alumno(materias[2], alumnos[1]);
    materia_agregar_alumno(materias[2], alumnos[3]);
    materia_agregar_alumno(materias[2], alumnos[4]);

    // Pedro (ID 3) y Ana (ID 4) a Introduccion a Ingenieria en Computacion (ID 4)
    materia_agregar_alumno(materias[3], alumnos[2]);
    materia_agregar_alumno(materias[3], alumnos[3]);
}

int main() {
    precargar_datos();
    menu_principal();

    for (int i = 0; i < cantidad_alumnos; i++) alumno_destruir(alumnos[i]);
    for (int i = 0; i < cantidad_materias; i++) materia_destruir(materias[i]);

    return 0;
}