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
    struct Tarea Tarea;

    //cambiar la ruta del archivo a la ruta del archivo de texto en la cual se encuentra para que funcione
    FILE * archivo = fopen("C:\\Users\\Estudiante\\Desktop\\c\\tarea.txt", "r"); 
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }
    
    //el archivo es de 5 lineas, cada linea es un campo de la tarea
    fgets(Tarea.titulo, sizeof(Tarea.titulo), archivo);
    fgets(Tarea.descripcion, sizeof(Tarea.descripcion), archivo);
    fgets(Tarea.estado, sizeof(Tarea.estado), archivo);
    fgets(Tarea.dificultad, sizeof(Tarea.dificultad), archivo);
    fgets(Tarea.vencimiento, sizeof(Tarea.vencimiento), archivo);

    fclose(archivo);

    do{
        printf("\nEditar tarea\n");
        printf("Que desea hacer con la tarea?\n");
        printf("[1] Editar titulo\n");
        printf("[2] Editar descripcion\n");
        printf("[3] Editar estado\n");
        printf("[4] Editar dificultad\n");
        printf("[5] Editar vencimiento\n");
        printf("[0] Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        if (opcion == 1)
        {
            printf("\nEditar titulo\n");
            printf("Titulo actual: %s\n", Tarea.titulo);
            printf("Ingrese el nuevo titulo: ");
            scanf(" %[^\n]", Tarea.titulo);
        } 
        else if (opcion == 2)
        {
            printf("\nEditar descripcion\n");
            printf("Descripcion actual: %s\n", Tarea.descripcion);
            printf("Ingrese la nueva descripcion: ");
            scanf(" %[^\n]", Tarea.descripcion);
        }
        else if (opcion == 3)
        {
            printf("\nEditar estado [P]endiente [E]n progreso [T]erminada [C]ancelada\n");
            printf("Estado actual: %s\n", Tarea.estado);
            printf("Ingrese el nuevo estado: ");
            scanf(" %[^\n]", Tarea.estado);
            if (strcmp(Tarea.estado, "P") != 0 && strcmp(Tarea.estado, "E") != 0 && strcmp(Tarea.estado, "T") != 0 && strcmp(Tarea.estado, "C") != 0)
            {
                printf("Estado invalido. Ingrese un estado valido.\n");
                printf("Ingrese el nuevo estado: ");
                scanf(" %[^\n]", Tarea.estado);
            }
            if (strcmp(Tarea.estado, "P") == 0)
            {
                strcpy(Tarea.estado, "Pendiente");
            }
            else if (strcmp(Tarea.estado, "E") == 0)
            {
                strcpy(Tarea.estado, "En progreso");
            }
            else if (strcmp(Tarea.estado, "T") == 0)
            {
                strcpy(Tarea.estado, "Terminada");
            }
            else if (strcmp(Tarea.estado, "C") == 0)
            {
                strcpy(Tarea.estado, "Cancelada");
            }
        }
        else if (opcion == 4)
        {
            printf("\nEditar dificultad [1] [2] [3]\n");
            printf("Dificultad actual: %s\n", Tarea.dificultad);
            printf("Ingrese la nueva dificultad: ");
            scanf(" %[^\n]", Tarea.dificultad);
            if (strcmp(Tarea.dificultad, "1") != 0 && strcmp(Tarea.dificultad, "2") != 0 && strcmp(Tarea.dificultad, "3") != 0)
            {
                printf("Dificultad invalida. Ingrese una dificultad valida.\n");
                printf("Ingrese la nueva dificultad: ");
                scanf(" %[^\n]", Tarea.dificultad);
            }
        }
        else if (opcion == 5)
        {
            printf("\nEditar vencimiento\n");
            printf("Vencimiento actual: %s\n", Tarea.vencimiento);
            printf("Ingrese el nuevo vencimiento: ");
            scanf(" %[^\n]", Tarea.vencimiento);
        }
        //editar el titulo de la tarea, se guarda en el mismo archivo
        FILE * archivo = fopen("C:\\Users\\Estudiante\\Desktop\\Unvime\\epya\\c\\tarea.txt", "w");
        if (archivo == NULL) {
            printf("No se pudo abrir el archivo.\n");
            return 1;
        }
        fprintf(archivo, "%s\n", Tarea.titulo);
        fprintf(archivo, "%s\n", Tarea.descripcion);
        fprintf(archivo, "%s\n", Tarea.estado);
        fprintf(archivo, "%s\n", Tarea.dificultad);
        fprintf(archivo, "%s\n", Tarea.vencimiento);
        fclose(archivo);
    } while (opcion != 0);
    printf("Volviendo al menu principal...");
}