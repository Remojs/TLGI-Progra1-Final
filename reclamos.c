#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reclamos.h"
#include "pila.h"

static Reclamo reclamos[50];
static Pila    pila;
static int     cantidad = 0;


static int buscarSlotLibre() { //(idReclamo == 0 => libre)
    for (int i = 0; i < 50; i++) {//busca el primer slot libre en el arreglo
        if (reclamos[i].idReclamo == 0) return i;
    }
    return -1; // arreglo lleno
}

static int atender() {
    int idTope = desapilar(&pila); // (caso recursivo) sacamos el tope

    if (pilavacia(&pila)) { //(caso base) cuando llegamos al último elemento, lo printeamos
        printf("\n|------- Atendiendo Reclamo (más antiguo) -------|\n");
        printf("  Reclamo       #%i\n",  reclamos[idTope].idReclamo);
        printf("  Cliente ID:   %i\n",   reclamos[idTope].idCliente);
        printf("  Descripción:  %s\n",   reclamos[idTope].descripcion);
        printf("  Prioridad:    %i\n",   reclamos[idTope].prioridad);
        printf("|------------------------------------------------|\n");
        reclamos[idTope].idReclamo = 0; // marcamos el reclamo como atendido (slot libre)
        return idTope; //no se reapila porque es el ultimo elemento
    }

    int idUltimo = atender(); // seguimos bajando recursivamente
    apilar(&pila, idTope); //vamos reapilando los elementos luego de cada recursion
    return idUltimo; //devolvemos el id del reclamo atendido
}

// -------------------------------------

void iniciarReclamos() {
    inicpila(&pila);
    cantidad = 0;
}

void agregarReclamo() {

    if (pila.postope >= 50) { // comprobamos que la pila no esté llena
        printf("No se pueden agregar más reclamos, pila llena.\n");
        return;
    }

    Reclamo nuevo;
    nuevo.idReclamo = cantidad + 1; // generamos el ID del reclamo

    printf("ID del cliente: "); //pedimos el ID del cliente
    scanf("%d", &nuevo.idCliente);

    printf("Descripción: "); // pedimos la descripción del reclamo
    scanf(" %[^\n]", nuevo.descripcion); 

    printf("Prioridad (1=baja, 2=media, 3=alta):"); // pedimos la prioridad del reclamo
    scanf("%d", &nuevo.prioridad);

    int slot = buscarSlotLibre(); // buscamos un slot libre en el arreglo de reclamos
    if (slot == -1) { 
        printf("No hay espacio.\n"); 
        return; 
    } // validamos que haya espacio en el arreglo

    reclamos[slot] = nuevo; // guardamos el nuevo reclamo en el arreglo
    apilar(&pila, slot); // apilamos el índice del nuevo reclamo en la pila
    cantidad++; // incrementamos el contador de reclamos

    printf("Reclamo Nº #%i agregado correctamente.\n", nuevo.idReclamo);
    printf("-----------------------------------------\n");
}

void atenderReclamo() {

    if (pilavacia(&pila)) { //validacion si la pila esta vacia
        printf("No hay reclamos pendientes.\n");
        return;
    }

    printf("Quieres atender el reclamo? (1=si, 0=no): "); 
    int confirmacion; // confirmacion del usuario para atender el reclamo
    scanf("%d", &confirmacion);

    if (confirmacion != 1) { //validacion de la confirmacion del usuario
        printf("Reclamo no atendido.\n");
        return;
    }

    printf("Atendiendo reclamo...\n"); 

    atender(); // la recursion muestra el mas antiguo y muestra su slot como libre
    printf("Reclamo atendido correctamente.\n");
    printf("-----------------------------------------\n");
}

void verReclamos() {

    if (pilavacia(&pila)) { //validacion si la pila esta vacia
        printf("No hay reclamos pendientes.\n");
        return;
    }

    printf("\n|-- Índices internos de la pila --|\n");
    mostrar(&pila); // mostramos los ídReclamo de la pila (solo el id del reclamo)

    printf("|------- Reclamos pendientes -------|\n"); // mostramos los reclamos pendientes desde el más antiguo al más reciente
    for (int i = pila.postope - 1; i >= 0; i--) { 
        int idx = pila.valores[i]; 
        printf("\n  Reclamo       #%i   \n",    reclamos[idx].idReclamo);
        printf("    Cliente ID:   %i    \n",    reclamos[idx].idCliente);
        printf("    Descripción:  %s    \n",    reclamos[idx].descripcion);
        printf("    Prioridad:    %i    \n",    reclamos[idx].prioridad);
        printf("  ---------------------------------- \n");
    }


    printf("- Reclamo mas antiguo -\n");
    printf("\n Total pendientes: %i \n", pila.postope); // mostramos la cantidad total de reclamos pendientes
    printf("-----------------------------------------\n");

}

void vaciarPila() {

    if (pilavacia(&pila)) { //validacion si la pila esta vacia
        printf("La pila ya está vacía.\n");
        return;
    }

    printf("¿Seguro que desea descartar todos los reclamos? (1=si, 0=no): ");
    int confirmacionInicial;
    scanf("%i", &confirmacionInicial);
    if (confirmacionInicial != 1) {
        printf("Operación cancelada. Datos a salvo :) \n");
        return;
    }

    printf("Muy seguro? ESTA OPCION NO SE PUEDE DESHACER (1=si, 0=no): ");
    int confirmacion;
    scanf("%i", &confirmacion);
    if (confirmacion != 1) {
        printf("Operación cancelada. Datos a salvo :) \n");
        return;
    }

    for (int i = 0; i < 50; i++) reclamos[i].idReclamo = 0; // liberamos todos los slots

    inicpila(&pila);   // reseteamos la pila
    cantidad = 0;  // reseteamos el contador de IDs

    printf("Todos los reclamos del turno fueron descartados.\n");
    printf("-----------------------------------------\n");
}