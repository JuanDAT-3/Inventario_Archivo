
// Estructura para los productos
typedef struct producto {
    int id;
    char nombre[50];
    int cantidad;
    float precio;
} Producto;

// Prototipos de las funciones
void Mostrar();
void Agregar();
void Modificar();
void Eliminar();
void ReiniciarInventario();
int Contar(); 

// Función para contar la cantidad de productos en el inventario
int Contar() {
    FILE *archivo = fopen("inventario.txt", "r"); // Abre el archivo en modo lectura

    if (archivo == NULL) { // Si el archivo no existe o no puede abrirse
        printf("El inventario está vacío o no se pudo abrir el archivo.\n");
        return 0;
    }

    Producto t; // Variable temporal para leer los productos
    int contador = 0;

    // Lee el archivo y cuenta cuántos productos hay.
    while (fscanf(archivo, "%d,%49[^,],%d,%f\n", &t.id, t.nombre, &t.cantidad, &t.precio) == 4) {
        contador++; // Incrementa el contador por cada producto leído
    }

    fclose(archivo); // Cierra el archivo después de contar
    return contador; // Retorna la cantidad total de productos
}

void Mostrar(){
    // Apertura del archivo 
    FILE *archivo = fopen("inventario.txt", "r");
    
    // Verifica si el archivo no se pudo abrir y muestra un mensaje de error
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return; 
    }

    Producto t; // Temporal para mostrar.

    // Formato de archivo.
    printf("\n-------------------------\n");
    printf("  INVENTARIO\n");
    printf("-------------------------\n");

    // Lectura e impresión de productos.
    while(fscanf(archivo, "%d,%49[^,],%d,%f\n", &t.id, t.nombre, &t.cantidad, &t.precio) == 4){
        printf("ID: %d\n", t.id);
        printf("Nombre: %s\n", t.nombre);
        printf("Cantidad: %d\n", t.cantidad);
        printf("Precio: %.2f\n", t.precio);
        printf("-------------------------\n");
    }

    // Cierre de archivo.
    fclose(archivo); 
}

// Función para agregar un nuevo producto.
void Agregar() {
    Producto p; // Variable temporal para almacenar los datos del producto a agregar.
    FILE *archivo = fopen("inventario.txt", "a"); // Abre el archivo en modo append para agregar al final.

    if (archivo == NULL) { // Si el archivo no puede abrirse, muestra un mensaje de error.
        printf("No se pudo abrir el archivo.\n");
        return;
    }

     // Asignar el ID automáticamente basado en la cantidad de productos existentes
    int cantidadProductos = Contar();
    p.id = cantidadProductos + 1;

    printf("Ingrese el nombre del producto: "); 
    fgets(p.nombre, sizeof(p.nombre), stdin); // Lee el nombre ingresado, incluyendo espacios
    p.nombre[strcspn(p.nombre, "\n")] = '\0'; // Elimina el salto de línea que agrega `fgets`

    printf("Ingrese la cantidad del producto: "); 
    scanf("%d", &p.cantidad); // Lee la cantidad ingresada.

    printf("Ingrese el precio del producto: "); 
    scanf("%f", &p.precio); // Lee el precio ingresado

    // Escribe los datos del producto en el archivo
    fprintf(archivo, "%d,%s,%d,%.2f\n", p.id, p.nombre, p.cantidad, p.precio);
    fclose(archivo); // Cierra el archivo después de escribir
    printf("Producto agregado exitosamente.\n");
}

// Función para modificar un producto
void Modificar() {
    Producto p; // Variable temporal para almacenar los datos de cada producto
    FILE *archivo = fopen("inventario.txt", "r"); // Abre el archivo en modo lectura
    FILE *temp = fopen("temp.txt", "w"); // Crea un archivo temporal en modo escritura
    int idModificar, encontrado = 0; // Variables para el ID del producto a modificar y una bandera
    int opc;

    if (archivo == NULL) { // Si el archivo no puede abrirse, muestra un mensaje de error
        printf("No se pudo abrir el archivo original.\n");
        return;
    }

    if (temp == NULL) { // Si el archivo temporal no puede crearse, muestra un mensaje de error
        printf("No se pudo crear el archivo temporal.\n");
        fclose(archivo);
        return;
    }

    printf("Ingrese el ID del producto a modificar: "); // Solicita el ID del producto a modificar
    scanf("%d", &idModificar); // Lee el ID ingresado
    getchar(); // Limpia el búfer de entrada

    // Recorre el archivo y busca el producto con el ID especificado.
    while (fscanf(archivo, "%d,%49[^,],%d,%f\n", &p.id, p.nombre, &p.cantidad, &p.precio) == 4) {
        if (p.id == idModificar) { // Si el ID coincide con el producto buscado
            encontrado = 1; // Marca que el producto fue encontrado

            printf("Producto actual: ID=%d, Nombre=%s, Cantidad=%d, Precio=%.2f\n",
                   p.id, p.nombre, p.cantidad, p.precio);
            do
            {
                printf("Selecciona el dato a modificar: \n");
                printf("1.Nombre\n"
                        "2. Cantidad\n"
                        "3. Precio\n");
                scanf("%i", &opc);
                getchar();

                //Menú interno para modificación.

                switch(opc){
                    case 1:
                        printf("Ingrese el nuevo nombre del producto: ");
                        fgets(p.nombre, sizeof(p.nombre), stdin);
                        p.nombre[strcspn(p.nombre, "\n")] = '\0';
                        break;

                    case 2:
                        printf("Ingrese la nueva cantidad: ");
                        scanf("%d", &p.cantidad);
                        break;
                    
                    case 3:
                         printf("Ingrese el nuevo precio: ");
                        scanf("%f", &p.precio);
                        break;
                    
                    default:
                        printf("Opción no disponible; ingrese nuevamente");
                        break;
                }

            } while (opc < 1 || opc > 3);
            
        }

        // Escribe los datos (modificados o no) en el archivo temporal
        fprintf(temp, "%d,%s,%d,%.2f\n", p.id, p.nombre, p.cantidad, p.precio);
    }

    fclose(archivo); // Cierra el archivo original
    fclose(temp); // Cierra el archivo temporal

    if (encontrado) { // Si se encontró el producto
        remove("inventario.txt"); // Elimina el archivo original
        rename("temp.txt", "inventario.txt"); // Renombra el archivo temporal al original
        printf("Producto modificado exitosamente.\n");
    } else { // Si no se encontró el producto
        remove("temp.txt"); // Elimina el archivo temporal
        printf("Producto con ID %d no encontrado.\n", idModificar);
    }
}

// Función para eliminar un producto
void Eliminar() {
    Producto p;
    FILE *archivo = fopen("inventario.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int idEliminar, eliminado = 0, nuevoID = 1;

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo original.\n");
        return;
    }

    if (temp == NULL) {
        printf("No se pudo crear el archivo temporal.\n");
        fclose(archivo);
        return;
    }

    printf("Ingrese el ID del producto a eliminar: "); // Solicita el ID del producto a eliminar
    scanf("%d", &idEliminar); // Lee el ID ingresado
    getchar(); // Limpia el búfer de entrada

    // Recorre el archivo original y copia al temporal los productos que no se van a eliminar
    while (fscanf(archivo, "%d,%49[^,],%d,%f\n", &p.id, p.nombre, &p.cantidad, &p.precio) == 4) {
        if (p.id == idEliminar) { // Si el ID coincide con el producto a eliminar
            eliminado = 1; // Marca que el producto fue eliminado
            printf("Producto eliminado: ID=%d, Nombre=%s, Cantidad=%d, Precio=%.2f\n",
                   p.id, p.nombre, p.cantidad, p.precio);
        } else { // Si el producto no coincide, lo escribe en el archivo temporal
            fprintf(temp, "%d,%s,%d,%.2f\n", nuevoID++, p.nombre, p.cantidad, p.precio);
        }
    }

    fclose(archivo); // Cierra el archivo original
    fclose(temp); // Cierra el archivo temporal

    if (eliminado) { // Si se eliminó un producto:
        remove("inventario.txt"); // Elimina el archivo original
        rename("temp.txt", "inventario.txt"); // Renombra el archivo temporal al original
        printf("Producto eliminado y IDs reenumerados exitosamente.\n");
    } else { // Si no se encontró el producto:
        remove("temp.txt"); // Elimina el archivo temporal
        printf("Producto con ID %d no encontrado.\n", idEliminar);
    }
}

// Función para reiniciar el inventario.
void ReiniciarInventario() {
    FILE *archivo = fopen("inventario.txt", "w"); // Abre el archivo en modo escritura para sobrescribirlo
    if (archivo == NULL) { // Si no se puede abrir el archivo:
        printf("No se pudo reiniciar el inventario.\n");
        return;
    }
    fclose(archivo); // Cierra el archivo vacío
    printf("Inventario reiniciado exitosamente.\n"); // Confirma que el inventario fue reiniciado
}
  