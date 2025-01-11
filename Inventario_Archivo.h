/* Header Inventario_Archivos */

// Función de Modificar

void Modificar(int indice,){

    Producto t; //Producto temporal para traspasar datos.
    int contador = 0;
    int dato;
    int error = 0; //Comprobar errores


    //Apertura de archivo principal. 
    FILE *archivo = fopen("(Dirección de archivo)", "r");
    //Archivo copia.
    FILE *copia = fopen("(Nombre archivo copia)", "w"); //Al abrirse en modo write, el archivo es creado.

    if (archivo == NULL || copia == NULL){
        printf("Error al abrir archivo. \n");
        return;
    };

    //Lectura del archivo original.
    while (fscanf(file, "Formato de inventario",&t.id,t.nombre,&t.cantidad, &t.precio) == 4 ){

        //Condicional que identifica el producto a modificar.
        if (contador == indice){
            printf("Selecciona el dato a modificar: \n");
            printf("1.id\n"
                    "2.Nombre\n"
                    "3. Cantidad\n"
                    "4. Precio\n");
            scanf("%i", &dato);
            //Validación de opción
            if (dato < 1 || dato > 4){
                printf("Opción no valida. No se realizaron cambios en el producto");
                error == 1; //Error es igual a True. 

            }else{
                //Menú interno para elegir la caracteristica a modificar.
                switch (dato){
                
                case 1:
                    printf("Nuevo nombre: ");
                    scanf(" %49[^\n]", t.nombre); //Formato que lee todo incluyendo espacio.
                    break;
                case 2:
                    printf("Nuevo nombre: ");
                    scanf(" %49[^\n]", t.nombre);
                case 3:
                    printf("Nueva cantidad: ");
                    scanf("%d", &t.cantidad);               
                case 4: 
                    printf("Nuevo precio: ");
                    scanf("%f", &t.precio);
                    break;
                }
            }
        
        }
        //Escritura del producto del archivo original en la copia.
        fprintf(copia, "%d,%s,%d,%.2f\n", t.id, t.nombre, t.cantidad, t.precio);
        contador++;
    }
    //Cierre del archivo original y la copia (Con los datos modificados de ser el caso.)
    fclose(archivo);
    fclose(copia);

    //Reemplazar al archivo original con la copia con datos modificados.

    if (error == 1){
        remove("(Nombre Archivo copia)")
        printf("No se realizaron cambios en el archivo.")
        
    }else{
        remove("(Dirección de archivo)");
        rename("(Nombre del archivo copia)", "(Nombre del archivo original)");

        printf("Poducto modificado exitosamente.");
    }
     
}

void Mostrar(){
    //Apertira del Archivo 

    FILE *archivo = fopen("(Dirección del archivo.)", "r");
    
    if ( archivo == NULL)[
        printf("Error al abrir el archivo\n");
        return; 
    ];

    Producto t //Temporal para mostrar.

    //Fprmato de Archivo.
    printf("\n-------------------------\n");
    printf("  INVENTARIO\n");
    printf("-------------------------\n");

    //Lectura e impresion de productos.

    while(fscanf(archivo, "(Formato de Archivo)",&t.id, t.nombre, &t.cantidad, &t.precio)==4){
        printf("ID: %d\n", t.id);
        printf("Nombre: %s\n", t.nombre);
        printf("Cantidad: %d\n", t.cantidad);
        printf("Precio: %.2f\n", t.precio);
        printf("-------------------------\n");

    }

    //Cerrar de archivos.
    fclose(archivo); 
    
}

int Contar(){
    //Apertura del inventario.
    FILE *archivo = fopen("(Nombre del inventario)", "r");

    if (archivo == NULL){
        printf("Error al abrir el archivo");
        return 0;
    }

    Producto t;
    int contador = 0;

    //Proceso de contar cuantos archivos hay.

    while (fscanf(archivo, "(Formato)", &t.id, t.nombre, &t.cantidad, &t.precio) == 4){
        contador ++;
    }

    fclose(archivo);
    return contador; 

    //Así debería ir pana;En el principal
    
    //int contador = ContarProductos();

}

