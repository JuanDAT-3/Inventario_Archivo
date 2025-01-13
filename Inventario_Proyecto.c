#include <stdio.h>
#include <string.h>
#include "inventario_Fun.H"

int main() {
    int opcion;
    int totalProductos = Contar(); // Llama a la función Contar al inicio y almacena el total de productos.

    printf("El inventario contiene actualmente %d producto(s).\n", totalProductos);

    while (1) {

        printf("\n    MENU INVENTARIO   \n");
        printf("1. Mostrar Inventario\n");
        printf("2. Agregar item\n");
        printf("3. Eliminar item\n");
        printf("4. Modificar item\n");
        printf("5. Reiniciar Inventario\n");
        printf("6. Salir\n");

        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpia el búfer.

        switch (opcion) {
            case 1:
                if(totalProductos == 0){
                    printf("Inventario Vacío.");
                    break;
                }else{
                    Mostrar();
                    break;    
                };
            case 2:
                Agregar();
                totalProductos = Contar();
                break;
            case 3:
                Eliminar();
                totalProductos = Contar();
                break;
            case 4:
                Modificar();
                break;
            case 5:
                ReiniciarInventario();
                totalProductos = Contar();
                break;
            case 6:
                printf("Programa Terminado.\n");
                return 0;
            default:
                printf("Opción Inválida\n");
        }
    }
    return 0;
}

