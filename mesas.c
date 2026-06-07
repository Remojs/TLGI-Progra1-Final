#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "mesas.h"

//-------------------------------------------------------------------------------------------------

//Arreglo de juegos validos para cada mesa
static const char* juegosValidos[] = { "Ruleta", "Blackjack", "Poker" };

//Constantes para validaciones y aux
static const int CANT_JUEGOS = 3;
static const int MESA_CAPACIDADMAX = 30;


//Fucnion auxiliar para validar los juegos
static int esValido(const char* juego) {
    for (int i = 0; i < CANT_JUEGOS; i++) {
        if (strcmp(juego, juegosValidos[i]) == 0) {
            return 1; // 1: Juego valido
        }
    }
    return 0; // 0: Juego no valido 
}

static int buscarPorId(Mesa* mesas, int cantidad, int id) {
    for (int i = 0; i < cantidad; i++) {
        if (mesas[i].id == id) { 
            return i;
        }
    }
    return -1; // No se encontró la mesa
}

static int generarId(Mesa* mesas, int cantidad) {
    for (int id = 1; ; id++) {       // probamos desde el 1 en adelante
        int existe = 0;
        for (int i = 0; i < cantidad; i++) {
            if (mesas[i].id == id) {  // si ese id ya está usado
                existe = 1;
                break;
            }
        }
        if (!existe) return id; // si no está usado, ese es el libre
    }
}

//-------------------------------------------------------------------------------------------------

void altaMesa(Mesa** mesas, int* cantidad) {
    Mesa nuevaMesa; //creacion de la mesa
    nuevaMesa.id = generarId(*mesas, *cantidad); // Asignacion del ID

    printf("Ingrese el nombre del juego (Ruleta, Blackjack, Poker): "); //solicita y agrega nombre del juego de la mesa
    scanf("%s", nuevaMesa.nombreJuego);

    if (!esValido(nuevaMesa.nombreJuego)) { //comprueba que el juego sea valido, sino tira error
        printf("Juego no válido. Mesa no creada.\n");
        return;
    }

    printf("Capacidad máxima: "); //solicita la capacidad maxima de la mesa
    scanf("%i", &nuevaMesa.capacidadMax);

    if (nuevaMesa.capacidadMax <= 0 || nuevaMesa.capacidadMax > MESA_CAPACIDADMAX) { //comprueba que la capacidad sea valida, sino tira error
        printf("Capacidad no válida. Mesa no creada.\n");
        return;
    }

    nuevaMesa.disponible = 1; //asigna el resto de la informacion de la mesa
    nuevaMesa.activa     = 1;

    Mesa* temp = (Mesa*) realloc(*mesas, (*cantidad + 1) * sizeof(Mesa)); //redimensiona el arreglo de mesas para agregar la nueva mesa

    if (temp == NULL) { //comprueba que se haya podido redimensionar el arreglo, sino tira error
        printf("Error: no hay memoria disponible.\n");
        return; 
    }

    *mesas = temp; //asigna el nuevo arreglo al puntero original
    (*mesas)[*cantidad] = nuevaMesa; //agrega la nueva mesa al arreglo
    (*cantidad)++; //aumento la cantidad de mesas

    guardarMesasEnArchivo(*mesas, *cantidad);
    printf("Mesa agregada correctamente.\n");
    printf("-----------------------------------------\n");

}

// int → 1 si encontró y eliminó, 0 si no encontró el ID
int bajaMesa(Mesa** mesas, int* cantidad) {

    int idBuscado;
    printf("Ingrese el ID de la mesa a eliminar: "); //pedimos y guardamos el ID de la mesa a eliminar
    scanf("%i", &idBuscado);

    int id = buscarPorId(*mesas, *cantidad, idBuscado); //buscamos la mesa por ID y comprobamos que exista, sino tira error
    if (id == -1) {
            printf("No existe una mesa con ID %i \n", idBuscado);
            return 0;
        }
    
    printf("Mesa encontrada, seguro que desea eliminar? (1=si, 0=no) \n"); //confirmacion de eliminacion
    int confirmacion;
    scanf("%i", &confirmacion);

    if (confirmacion == 0) {
        printf("Eliminación cancelada.\n");
        return 0;
    }

    for(int i = id; i < *cantidad - 1; i++) { //desplazamos las mesas siguientes para eliminar la mesa deseada
        (*mesas)[i] = (*mesas)[i + 1];
    }

    (*cantidad)--; //disminuimos la cantidad de mesas

    if(*cantidad == 0){
        free(*mesas); //si no quedan mesas, liberamos la memoria y asignamos el puntero a NULL
        *mesas = NULL;
    } else {
        Mesa* temp = (Mesa*) realloc(*mesas, *cantidad * sizeof(Mesa)); //redimensionamos el arreglo de mesas
        if (temp != NULL) *mesas = temp; //asignamos el nuevo arreglo al puntero original
    }

    guardarMesasEnArchivo(*mesas, *cantidad);
    printf("Mesa eliminada correctamente.\n");
    printf("-----------------------------------------\n");
    return 1;

}

// int → 1 si encontró y modificó, 0 si no encontró
int modificarMesa(Mesa* mesas, int cantidad) {

    int idBuscado;
    printf("Ingrese el ID de la mesa a modificar: "); //pedimos y guardamos el ID de la mesa a modificar
    scanf("%i", &idBuscado);

    int id = buscarPorId(mesas, cantidad, idBuscado); //buscamos la mesa por ID y comprobamos que exista, sino tira error
    if (id == -1) {
            printf("No existe una mesa con ID %i \n", idBuscado);
            return 0;
        }

    printf("---------------------------\n");
    printf("\nDatos actuales de la mesa %i: \n", idBuscado); //muestro los datos actuales de la mesa
    printf("Juego: %s\n", mesas[id].nombreJuego);
    printf("Capacidad: %i \n", mesas[id].capacidadMax);
    printf("Disponibilidad: %s\n", mesas[id].disponible ? "Disponible" : "Ocupada");
    printf("Activa: %s\n", mesas[id].activa ? "Activa" : "Dada de baja");
    printf("---------------------------\n");
    // - Modificar mesa ------------
    printf("\n -- Tabla de modificaciones: --\n");

    // - Modificar ""Tipo de juego"" ------------
    
    printf("\n Nuevo tipo de juego: (selecciona la opcion del menu)\n");
    printf("0. Mantener actual\n");
    printf("1. Ruleta\n");
    printf("2. Blackjack\n");
    printf("3. Poker\n");
    printf("---------------------------\n");

    int opcion;
    scanf("%i", &opcion);

    if (opcion >= 1 && opcion <= CANT_JUEGOS)
        strcpy(mesas[id].nombreJuego, juegosValidos[opcion - 1]);

    // - Modificar ""Capacidad"" ------------

    printf("Nueva capacidad: (0 para mantener actual) \n");
    printf("[Valor actual: %i] \n", mesas[id].capacidadMax);
    printf("---------------------------\n");


    int nuevaCap;
    scanf("%i", &nuevaCap);
    if (nuevaCap > 0) mesas[id].capacidadMax = nuevaCap;

    // - Modificar ""disponibilidad"" ------------
    printf("Disponible: (1=si, 0=ocupada) \n");
    printf("[Valor actual: %s] \n", mesas[id].disponible ? "Disponible" : "Ocupada");
    printf("---------------------------\n");


    int nuevaDisp;
    scanf("%i", &nuevaDisp);
    if (nuevaDisp == 0 || nuevaDisp == 1) mesas[id].disponible = nuevaDisp;

    // - Modificar ""activa"" ------------
    printf("Activa: (1=si, 0=dada de baja) \n");
    printf("[Valor actual: %s] \n", mesas[id].activa ? "Activa" : "Dada de baja");
    printf("---------------------------\n");


    int nuevaAc;
    scanf("%i", &nuevaAc);
    if (nuevaAc == 0 || nuevaAc == 1) mesas[id].activa = nuevaAc;

    //--------------------------

    guardarMesasEnArchivo(mesas, cantidad);
    printf("Mesa modificada correctamente.\n");
    printf("------------------------------------------------------\n");

    return 1;
}

// int → 1 si encontró y mostró, 0 si no existe
int consultarMesa(Mesa* mesas, int cantidad) {

    int idBuscado;
    printf("Ingrese el ID de la mesa a consultar: "); //pedimos y guardamos el ID de la mesa a consultar
    scanf("%i", &idBuscado);

    int id = buscarPorId(mesas, cantidad, idBuscado); //buscamos la mesa por ID y comprobamos que exista, sino tira error
    if (id == -1) {
            printf("No existe una mesa con ID %i \n", idBuscado);
            return 0;
        }

    printf("    |------------------------------| \n");
    printf("    | Mesa #%i                     | \n",   mesas[id].id);
    printf("    | Juego: %s                    | \n",   mesas[id].nombreJuego);
    printf("    | Capacidad: %i jugadores      | \n",   mesas[id].capacidadMax);
    printf("    | Disponible: %s               | \n",   mesas[id].disponible ? "Disponible" : "Ocupada");
    printf("    | Estado: %s                   | \n",   mesas[id].activa     ? "Activa" : "Dada de baja");
    printf("    |------------------------------| \n");
    return 1;
}


void consultarMesasPorTipo(Mesa* mesas, int cantidad) {

    char tipo[50];
    printf("Tipo de juego a buscar: "); //pedimos el tipo a buscar y lo guardamos
    scanf("%s", tipo);

    int encontradas = 0; //contador de mesas encontradas del tipo buscado
    printf("\n Mesas de tipo '%s':\n", tipo);

    for (int i = 0; i < cantidad; i++) {
        if (strcmp(mesas[i].nombreJuego, tipo) == 0) { //iteramos y mapeamos todas las mesas del tipo buscado, mostrando su informacion
            printf("    |------------------------------| \n");
            printf("    | Mesa #%i                     | \n",   mesas[i].id);
            printf("    | Juego: %s                    | \n",   mesas[i].nombreJuego);
            printf("    | Capacidad: %i jugadores      | \n",   mesas[i].capacidadMax);
            printf("    | Disponible: %s               | \n",   mesas[i].disponible ? "Disponible" : "Ocupada");
            printf("    | Estado: %s                   | \n",   mesas[i].activa     ? "Activa" : "Dada de baja");
            printf("    |------------------------------| \n");  
            encontradas++;
        }
    }

    if (encontradas == 0)
        printf("No hay mesas de tipo '%s' registradas. \n", tipo); //si no hay mesas del tipo buscado, mostramos un mensaje indicando esto
    else
        printf("\n Total: %i mesa(s).\n", encontradas); //si hay mesas del tipo buscado, mostramos el total encontrado
}


void listarMesasAlfabetico(Mesa* mesas, int cantidad) {

    if (cantidad == 0) { 
        printf("No hay mesas registradas.\n"); 
        return;} //si no hay mesas registradas, mostramos un mensaje 
    
    Mesa* copia = (Mesa*) malloc(cantidad * sizeof(Mesa)); //creamos una copia del arreglo

    if(copia == NULL) {
        printf("Error: no hay memoria disponible.\n");
        return;} //si no se hizo la copia, mostramos un mensaje 

    for(int i = 0; i < cantidad; i++) {
         copia[i] = mesas[i];
    }//copiamos el arreglo original a la copia

    //orden alfabetico con metodo de seleccion
    for (int i = 0; i < cantidad - 1; i++) {
        int minIdx = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (strcmp(copia[j].nombreJuego, copia[minIdx].nombreJuego) < 0)
            minIdx = j;
        }

        if (minIdx != i) {
            Mesa temp   = copia[i];
            copia[i]    = copia[minIdx];
            copia[minIdx] = temp;
        }
    }

    for (int i = 0; i < cantidad; i++) { //mapeamos la copia ordenada
            printf("    |------------------------------| \n");
            printf("    | Mesa #%i                     | \n",   copia[i].id);
            printf("    | Juego: %s                    | \n",   copia[i].nombreJuego);
            printf("    | Capacidad: %i jugadores      | \n",   copia[i].capacidadMax);
            printf("    | Disponible: %s               | \n",   copia[i].disponible ? "Disponible" : "Ocupada");
            printf("    | Estado: %s                   | \n",   copia[i].activa     ? "Activa" : "Dada de baja");
            printf("    |------------------------------| \n");  
    }

    free(copia); //limpiamos la memoria
}


void listarMesasPorCapacidad(Mesa* mesas, int cantidad) {
    if (cantidad == 0) { 
        printf("No hay mesas registradas.\n"); 
        return;} //si no hay mesas registradas, mostramos un mensaje 
    
    Mesa* copia = (Mesa*) malloc(cantidad * sizeof(Mesa)); //creamos una copia del arreglo

    if(copia == NULL) {
        printf("Error: no hay memoria disponible.\n");
        return;} //si no se hizo la copia, mostramos un mensaje 

    for(int i = 0; i < cantidad; i++) {
         copia[i] = mesas[i];
    }//copiamos el arreglo original a la copia

    //orden con metodo de insercion
    for (int i = 1; i < cantidad; i++) {
        Mesa actual = copia[i];
        int j = i - 1;

        while (j >= 0 && copia[j].capacidadMax > actual.capacidadMax) { //movemos los elementos mayores al actual
            copia[j + 1] = copia[j];
            j--;
        }

        copia[j + 1] = actual; // insertamos el elemento
    }

    for (int i = 0; i < cantidad; i++) { //mapeamos la copia ordenada
            printf("    |------------------------------| \n");
            printf("    | Mesa #%i                     | \n",   copia[i].id);
            printf("    | Juego: %s                    | \n",   copia[i].nombreJuego);
            printf("    | Capacidad: %i jugadores      | \n",   copia[i].capacidadMax);
            printf("    | Disponible: %s               | \n",   copia[i].disponible ? "Disponible" : "Ocupada");
            printf("    | Estado: %s                   | \n",   copia[i].activa     ? "Activa" : "Dada de baja");
            printf("    |------------------------------| \n");  
    }

    free(copia); //limpiamos la memoria
    
}


void mostrarOcupacionDiaria(Mesa* mesas, int cantidad, int ocupacion[][MAX_HORAS]) {
    if (cantidad == 0) { 
        printf("No hay mesas registradas.\n"); //si no hay mesas registradas, mostramos un mensaje
        return; 
    }

    printf("|------- Ocupación diaria de mesas -------| \n");
    for (int i = 0; i < cantidad; i++) { //recorro cada mesa

        printf("Mesa #%i — %s\n", mesas[i].id, mesas[i].nombreJuego); //mostrar encabezado

        printf("Hora: "); for (int j = 0; j < MAX_HORAS; j++) printf("%3i", j); //fila de horas (visual)

        printf(" \n Jug.: "); //recorre cada hora de la mesa
        for (int j = 0; j < MAX_HORAS; j++){
            printf(ocupacion[i][j] == 0 ? "  -" : "%3i", ocupacion[i][j]); //si no hubo jugadores muestra -, sino muestra la cantidad de jugadores que hubo en esa hora
        } //(jugadores de la mesa i en la hora j)

        printf("\n\n"); //separador visual
    }
}


void cargarMesasDesdeArchivo(Mesa** mesas, int* cantidad) {

    FILE* f = fopen("mesas.dat", "rb");

    if (f == NULL) { //si el archivo no existe, inicializamos el arreglo de mesas a NULL y la cantidad a 0
        *cantidad = 0;
        *mesas    = NULL;
        return;
    }

    fread(cantidad, sizeof(int), 1, f); //leemos la cantidad de mesas guardada al principio del archivo

    if (*cantidad <= 0) { //si la cantidad leida es 0 o negativa, inicializamos el arreglo de mesas a NULL y cerramos el archivo
        *mesas = NULL;
        fclose(f);
        return;
    }

    *mesas = (Mesa*) malloc(*cantidad * sizeof(Mesa)); //reservamos memoria para el arreglo de mesas segun la cantidad

    if (*mesas == NULL) { //si no se pudo asignar memoria para el arreglo de mesas, mostramos un mensaje de error y cerramos el archivo
        printf("Error: no hay memoria para cargar las mesas.\n");
        fclose(f);
        return;
    }

    int leidos = fread(*mesas, sizeof(Mesa), *cantidad, f); //leemos las mesas del archivo y comprobamos que se hayan leido la cantidad esperada, sino mostramos una advertencia indicando que el archivo puede estar incompleto
    if (leidos != *cantidad) {
        printf("Advertencia: el archivo puede estar incompleto.\n");
        *cantidad = leidos;
    }

    fclose(f);
    printf("%i mesa(s) cargada(s) desde el archivo.\n", *cantidad);

}


void guardarMesasEnArchivo(Mesa* mesas, int cantidad) {
    FILE* f = fopen("mesas.dat", "wb"); //abro el archivo 

    if (f == NULL) { //validacion si el archivo no se pudo abrir
        printf("Error: no se pudo abrir el archivo para guardar.\n");
        return;
    }

    fwrite(&cantidad, sizeof(int), 1, f); //guardamos la cantidad de mesas al principio del archivo para la gestion de memoria

    if (cantidad > 0) fwrite(mesas, sizeof(Mesa), cantidad, f); //si hay mesas, guardamos el arreglo de mesas en el archivo

    fclose(f); //cerramos el archivo
}