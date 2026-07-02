#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

struct Tarea {
    char titulo[50];
    char descripcion[100];
    char estado[20];       
    char dificultad[10];   
    char vencimiento[15];
    char fechaCreacion[11];
};

void obtenerFechaActual(char *buffer, size_t size) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, size, "%Y-%m-%d", timeinfo);
}

void parsearTareaDesdeLinea(const char *linea, struct Tarea *t) {
    char fecha[11] = "";
    int campos = sscanf(linea, "%49[^|]|%99[^|]|%19[^|]|%9[^|]|%14[^|]|%10[^\n]",
                        t->titulo, t->descripcion, t->estado, t->dificultad,
                        t->vencimiento, fecha);

    if (campos >= 5) {
        if (campos >= 6 && fecha[0] != '\0') {
            strcpy(t->fechaCreacion, fecha);
        } else {
            obtenerFechaActual(t->fechaCreacion, sizeof(t->fechaCreacion));
        }
    } else {
        strcpy(t->titulo, "");
        strcpy(t->descripcion, "");
        strcpy(t->estado, "");
        strcpy(t->dificultad, "");
        strcpy(t->vencimiento, "");
        obtenerFechaActual(t->fechaCreacion, sizeof(t->fechaCreacion));
    }
}

void editarYGuardarTarea(char tituloOriginal[]) {
    struct Tarea todasLasTareas[100];
    int total = 0;
    int indiceAEditar = -1;

    FILE *f = fopen("tareas.txt", "r");
    if (f != NULL) {
        char linea[512];
        while (fgets(linea, sizeof(linea), f) != NULL) {
            parsearTareaDesdeLinea(linea, &todasLasTareas[total]);
            
            if (strcmp(todasLasTareas[total].titulo, tituloOriginal) == 0) {
                indiceAEditar = total;
            }
            total++;
        }
        fclose(f);
    }

    if (indiceAEditar == -1) {
        printf("\n[!] Error: No se encontro la tarea en la base de datos.\n");
        return;
    }


    int opcion = 0;
    do {
        printf("\n--- EDITANDO UNA TAREA ---\n");
        printf("Editando tarea: %s\n", todasLasTareas[indiceAEditar].titulo);
        printf("[1] Editar titulo\n");
        printf("[2] Editar descripcion\n");
        printf("[3] Editar estado\n");
        printf("[4] Editar dificultad\n");
        printf("[5] Editar vencimiento\n");
        printf("[0] Finalizar edicion y Guardar\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        if (opcion == 1) {
            printf("\nTitulo actual: %s\n", todasLasTareas[indiceAEditar].titulo);
            printf("Ingrese el nuevo titulo: ");
            scanf(" %[^\n]", todasLasTareas[indiceAEditar].titulo);
        } 
        else if (opcion == 2) {
            printf("\nDescripcion actual: %s\n", todasLasTareas[indiceAEditar].descripcion);
            printf("Ingrese la nueva descripcion: ");
            scanf(" %[^\n]", todasLasTareas[indiceAEditar].descripcion);
        }
        else if (opcion == 3) {
            char nuevoEstado[20];
            printf("\nEstado actual: %s\n", todasLasTareas[indiceAEditar].estado);
            printf("Ingrese el nuevo estado [P]endiente [E]n progreso [T]erminada [C]ancelada: ");
            scanf(" %[^\n]", nuevoEstado);

            if (nuevoEstado[0] == 'P' || nuevoEstado[0] == 'p') strcpy(todasLasTareas[indiceAEditar].estado, "Pendiente");
            else if (nuevoEstado[0] == 'E' || nuevoEstado[0] == 'e') strcpy(todasLasTareas[indiceAEditar].estado, "En Curso");
            else if (nuevoEstado[0] == 'T' || nuevoEstado[0] == 't') strcpy(todasLasTareas[indiceAEditar].estado, "Terminada");
            else if (nuevoEstado[0] == 'C' || nuevoEstado[0] == 'c') strcpy(todasLasTareas[indiceAEditar].estado, "Cancelada");
            else strcpy(todasLasTareas[indiceAEditar].estado, nuevoEstado);
        }
        else if (opcion == 4) {
            printf("\nDificultad actual: %s\n", todasLasTareas[indiceAEditar].dificultad);
            printf("Ingrese la nueva dificultad [1] [2] [3]: ");
            scanf(" %[^\n]", todasLasTareas[indiceAEditar].dificultad);
        }
        else if (opcion == 5) {
            printf("\nVencimiento actual: %s\n", todasLasTareas[indiceAEditar].vencimiento);
            printf("Ingrese el nuevo vencimiento: ");
            scanf(" %[^\n]", todasLasTareas[indiceAEditar].vencimiento);
        }
    } while (opcion != 0);

    f = fopen("tareas.txt", "w");
    if (f != NULL) {
        for (int i = 0; i < total; i++) {
            fprintf(f, "%s|%s|%s|%s|%s|%s\n", 
                    todasLasTareas[i].titulo, todasLasTareas[i].descripcion, 
                    todasLasTareas[i].estado, todasLasTareas[i].dificultad, 
                    todasLasTareas[i].vencimiento, todasLasTareas[i].fechaCreacion);
        }
        fclose(f);
        printf("\n[+] ¡Tarea editada y guardada exitosamente!\n");
    } else {
        printf("\n[!] Error al reescribir tareas.txt\n");
    }
}


int main(){
    int opcion = 0;
    struct Tarea nuevaTarea;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("Hola Usuario ¿Que deseas hacer?\n");
        printf("[1] Ver mis tareas\n");
        printf("[2] Buscar una tarea\n");
        printf("[3] Agregar una tarea\n");
        printf("[0] Salir\n");
        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);
        // esta linea sirve para borrar la basura que queda por teclado, asi no repite printf's. //
        int c; while ((c = getchar()) != '\n' && c != EOF); 

        // VER MIS TAREAS, Angel Ferri
        if (opcion == 1) {
            int opcion_tareas = 0;
            do {
                printf("\n--- VER MIS TAREAS ---\n");
                printf("[1] Todas\n");
                printf("[2] Pendientes\n");
                printf("[3] En curso\n");
                printf("[4] Terminadas\n");
                printf("[0] Volver al Menu Principal\n");
                
                printf("Seleccione una opcion: ");
                scanf("%d", &opcion_tareas);
                while ((c = getchar()) != '\n' && c != EOF);

                if (opcion_tareas >= 1 && opcion_tareas <= 4) {
                    struct Tarea listaTareas[100]; 
                    int totalTareas = 0;

                    FILE *f = fopen("tareas.txt", "r");
                    if (f == NULL) {
                        printf("\n[!] No hay tareas guardadas.\n");
                    } else {
                        char linea[512];
                        while(fgets(linea, sizeof(linea), f) != NULL) {
                            struct Tarea t;
                            parsearTareaDesdeLinea(linea, &t);
                            
                            int coincide = 0;
                            if (opcion_tareas == 1) coincide = 1;
                            else if (opcion_tareas == 2 && (strstr(t.estado, "P") || strstr(t.estado, "p"))) coincide = 1;
                            else if (opcion_tareas == 3 && (strstr(t.estado, "E") || strstr(t.estado, "e") || strstr(t.estado, "C") || strstr(t.estado, "c"))) coincide = 1;
                            else if (opcion_tareas == 4 && (strstr(t.estado, "T") || strstr(t.estado, "t"))) coincide = 1;

                            if (coincide && totalTareas < 100) {
                                listaTareas[totalTareas] = t;
                                totalTareas++;
                            }
                        }
                        fclose(f);

                        if (totalTareas > 0) {
                            printf("\n--- LISTA DE TAREAS ---\n");
                            for (int i = 0; i < totalTareas; i++) {
                                printf("[%d] %s (Estado: %s)\n", i + 1, listaTareas[i].titulo, listaTareas[i].estado);
                            }

                            int seleccion;
                            printf("\nSeleccione el numero de la tarea para ver detalles (0 para volver): ");
                            scanf("%d", &seleccion);
                            while ((c = getchar()) != '\n' && c != EOF);

                            if (seleccion > 0 && seleccion <= totalTareas) {
                                int idx = seleccion - 1;
                                printf("\n--- DETALLES DE LA TAREA ---\n");
                                printf("Título: %s\n", listaTareas[idx].titulo);
                                printf("Descripción: %s\n", listaTareas[idx].descripcion);
                                printf("Estado: %s\n", listaTareas[idx].estado);
                                printf("Dificultad: %s\n", listaTareas[idx].dificultad);
                                printf("Vencimiento: %s\n", listaTareas[idx].vencimiento);
                                printf("Fecha de creación: %s\n", listaTareas[idx].fechaCreacion);
                                printf("----------------------------\n");

                                printf("\n¿Deseas editar esta tarea? (Presiona 'E' para editar o 'N' para volver): ");
                                char opcionEditar;
                                scanf(" %c", &opcionEditar);
                                while ((c = getchar()) != '\n' && c != EOF);

                                if (tolower(opcionEditar) == 'e') {

                                    editarYGuardarTarea(listaTareas[idx].titulo);
                                }
                            }
                        } else {
                            printf("\n[!] No se encontraron tareas para esta categoria.\n");
                        }
                    }
                    printf("\nPresiona Enter para continuar . . .");
                    getchar();
                }
            } while (opcion_tareas != 0);
        } 
        
        // BUSCAR TAREA, Walter Rodriguez

        else if (opcion == 2) {
            char busqueda[101];
            int tareasEncontradas = 0;

            printf("\n--- BUSCAR TAREA ---\n");
            printf("Ingrese el nombre o palabra de la tarea a buscar: ");
            fgets(busqueda, 101, stdin);
            busqueda[strcspn(busqueda, "\n")] = '\0';

            char busqueda_lower[101];
            for (int i = 0; busqueda[i] != '\0'; ++i) {
                busqueda_lower[i] = tolower((unsigned char)busqueda[i]);
            }
            busqueda_lower[strlen(busqueda)] = '\0';

            FILE *f = fopen("tareas.txt", "r");
            if (f == NULL) {
                printf("Error: No hay tareas guardadas o no se pudo abrir 'tareas.txt'.\n");
            } else {
                char linea[512];
                struct Tarea tareaLeida;

                while (fgets(linea, sizeof(linea), f) != NULL) {
                    parsearTareaDesdeLinea(linea, &tareaLeida);

                    char titulo_lower[50];
                    for(int i = 0; tareaLeida.titulo[i] != '\0'; i++) {
                        titulo_lower[i] = tolower((unsigned char)tareaLeida.titulo[i]);
                    }
                    titulo_lower[strlen(tareaLeida.titulo)] = '\0';

                    if (strstr(titulo_lower, busqueda_lower) != NULL) {
                        printf("\n--- TAREA ENCONTRADA ---\n");
                        printf("Título: %s\n", tareaLeida.titulo);
                        printf("Descripción: %s\n", tareaLeida.descripcion);
                        printf("Estado: %s\n", tareaLeida.estado);
                        printf("Dificultad: %s\n", tareaLeida.dificultad);
                        printf("Vencimiento: %s\n", tareaLeida.vencimiento);
                        printf("Fecha de creación: %s\n", tareaLeida.fechaCreacion);
                        printf("------------------------\n");
                        tareasEncontradas++;

                        printf("\n¿Deseas editar esta tarea? (Presiona 'E' para editar o 'N' para buscar otra): ");
                        char opcionEditar;
                        scanf(" %c", &opcionEditar); 
                        while ((c = getchar()) != '\n' && c != EOF); 

                        if (tolower(opcionEditar) == 'e') {

                            editarYGuardarTarea(tareaLeida.titulo);
                        }
                    }
                }
                fclose(f);

                if (tareasEncontradas == 0) {
                    printf("\nAviso: No se encontraron tareas que coincidan con '%s'.\n", busqueda);
                }
            }
            printf("\nPresiona Enter para continuar . . .\n");
            getchar();
        }

        // AGREGAR TAREA, Thiago Sturzenegger Varela

        else if (opcion == 3) {
            printf("\n--- AGREGAR NUEVA TAREA ---\n");
            printf("¿Que tarea le gustaria agregar hoy?\n");

            printf("1. Ingrese el Titulo: ");
            fgets(nuevaTarea.titulo, 50, stdin); // fgets obtiene lo ingresa por teclado osea "stdin" y se lo asigna a lista nuevaTarea y a "titulo", con un maximo de 50 caracteres.
            nuevaTarea.titulo[strcspn(nuevaTarea.titulo, "\n")] = '\0'; /** strcspn, busca en lo ingresado a "titulo" un salto de linea, el enter ya que el enter tambien lo copia
            y hace saltos de linea asi que lo busca "\n" y le dice que sea igual a 0 que es lo que explica walter sobre los strings. */
            printf("2. Descripcion de la tarea: ");
            fgets(nuevaTarea.descripcion, 100, stdin);
            nuevaTarea.descripcion[strcspn(nuevaTarea.descripcion, "\n")] = '\0';

            printf("3. Estado [P]endiente [E]n Curso [T]erminada [C]ancelada: ");
            fgets(nuevaTarea.estado, 20, stdin);
            nuevaTarea.estado[strcspn(nuevaTarea.estado, "\n")] = '\0';

            printf("4. Dificultad [1] Fácil [2] Medio [3] Difícil: ");
            fgets(nuevaTarea.dificultad, 10, stdin);
            nuevaTarea.dificultad[strcspn(nuevaTarea.dificultad, "\n")] = '\0';

            printf("5. Fecha de Vencimiento: ");
            fgets(nuevaTarea.vencimiento, 15, stdin);
            nuevaTarea.vencimiento[strcspn(nuevaTarea.vencimiento, "\n")] = '\0';

            obtenerFechaActual(nuevaTarea.fechaCreacion, sizeof(nuevaTarea.fechaCreacion));

            FILE *archivoTareas = fopen("tareas.txt", "a");
            if (archivoTareas == NULL) {
                printf("\nError al abrir el archivo tareas.txt.\n");
            } else {
                fprintf(archivoTareas, "%s|%s|%s|%s|%s|%s\n",
                        nuevaTarea.titulo, nuevaTarea.descripcion,
                        nuevaTarea.estado, nuevaTarea.dificultad,
                        nuevaTarea.vencimiento, nuevaTarea.fechaCreacion);
                fclose(archivoTareas);
                printf("\n¡Tarea guardada con exito en tareas.txt!\n");
            }
            printf("\nPresiona Enter para continuar . . .\n");
            getchar();
        }
        
        else if (opcion != 0) {
            printf("\n[!] Opcion no disponible. Intente de nuevo.\n");
        }

    } while (opcion != 0);

    printf("\nGracias por usar la agenda. ¡Vuelva Prontos!\n");
    return 0;
}