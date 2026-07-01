#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Tarea {
    char titulo[50];
    char descripcion[100];
    char estado[20];       
    char dificultad[10];   
    char vencimiento[15];
};

int main(){
    int opcion = 0;
    char bufferOpcion[10];

    struct Tarea nuevaTarea;
    do{
        printf("\nHola Eduardo ¿Que deseas hacer?\n");
        printf("[1] Ver mis tareas.\n");
        printf("[2] Buscar una tarea\n");
        printf("[4] Agregar una tarea\n");
        printf("[0] Salir\n");
        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);

        if (opcion == 1)
        {
            printf("Tareas:");
        } 
        else if (opcion == 2)
        {
            printf("Buscar una tarea");
        }
        else if (opcion == 4)
        {
            // esta linea sirve para borrar la basura que queda por teclado, asi no repite printf's. //
            int c; while ((c = getchar()) != '\n' && c != EOF);

            printf("\n--- AGREGAR NUEVA TAREA ---\n");
            printf("¿Que Tarea le gustaria agregar hoy?\n");

            printf("1. Ingrese el Titulo: ");
            fgets(nuevaTarea.titulo, 50, stdin); // fgets obtiene lo ingresa por teclado osea "stdin" y se lo asigna a lista nuevaTarea y a "titulo", con un maximo de 50 caracteres.
            nuevaTarea.titulo[strcspn(nuevaTarea.titulo, "\n")] = 0; /** strcspn, busca en lo ingresado a "titulo" un salto de linea, el enter ya que el enter tambien lo copia 
            y hace saltos de linea asi que lo busca "\n" y le dice que sea igual a 0 que es lo que explica walter sobre los strings. */

            printf("2. Descripcion de la tarea: ");
            fgets(nuevaTarea.descripcion, 100, stdin);
            nuevaTarea.descripcion[strcspn(nuevaTarea.descripcion, "\n")] = 0;

            printf("3. Estado [P]endiente [E]n Curso [T]erminada [C]ancelada: ");
            fgets(nuevaTarea.estado, 20, stdin);
            nuevaTarea.estado[strcspn(nuevaTarea.estado, "\n")] = 0;

            printf("4. Dificultad [1] [2] [3]: ");
            fgets(nuevaTarea.dificultad, 10, stdin);
            nuevaTarea.dificultad[strcspn(nuevaTarea.dificultad, "\n")] = 0;

            printf("5. Fecha de Vencimiento: ");
            fgets(nuevaTarea.vencimiento, 15, stdin);
            nuevaTarea.vencimiento[strcspn(nuevaTarea.vencimiento, "\n")] = 0;
            // esta parte es para crear un archivo de texto con el nombre de la tarea y guardar los datos ingresados en el archivo. Pero no si ya existe una con el mismo nombre //
            char nombreArchivo[120];
            snprintf(nombreArchivo, sizeof(nombreArchivo), "%s.txt", nuevaTarea.titulo);

            FILE *archivoTareas = fopen(nombreArchivo, "r");
            if (archivoTareas != NULL) {
                fclose(archivoTareas);
                printf("\nYa existe una tarea con ese nombre.\n");
            } else {
                archivoTareas = fopen(nombreArchivo, "w");

                if (archivoTareas == NULL) {
                    printf("Error al abrir el archivo %s.\n", nombreArchivo);
                } else {
                    fprintf(archivoTareas, "-Nota-\n");
                    fprintf(archivoTareas, "Titulo: %s\n", nuevaTarea.titulo);
                    fprintf(archivoTareas, "Descripcion: %s\n", nuevaTarea.descripcion);
                    fprintf(archivoTareas, "Estado: %s\n", nuevaTarea.estado);
                    fprintf(archivoTareas, "Dificultad: %s\n", nuevaTarea.dificultad);
                    fprintf(archivoTareas, "Vencimiento: %s\n", nuevaTarea.vencimiento);
                    fprintf(archivoTareas, "-Fin Nota-\n");
                    fclose(archivoTareas);

                    printf("\n¡Tarea guardada con exito en %s!\n", nombreArchivo);
                }
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