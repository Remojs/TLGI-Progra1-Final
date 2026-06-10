#include <stdio.h>
#include <string.h>
#include "clientes.h"
#include "tipos.h"

Cliente cargarCliente()
{
    Cliente c;

    printf("Ingrese el ID del cliente\n");
    scanf("%i", &c.id);

    printf("Ingrese el Nombre del cliente\n");
    scanf("%s", c.nombre);

    printf("Ingrese el DNI del cliente\n");
    scanf("%i", &c.dni);

    printf("Ingrese el Nivel VIP del cliente\n");
    scanf("%i", &c.nivelVip);

    printf("Ingrese el Saldo del cliente\n");
    scanf("%f", &c.saldo);

    c.estado = 1; // El estado se pone en 1 para que el usuario al crearlo ya este de alta

    return c;
}

void cargarClientesDesdeArchivo(Cliente arreglo[], int *cantidad)
{

    FILE *archivo = fopen("Clientes", "rb"); // Para

    *cantidad = 0;

    if (archivo != NULL)
    {
        while (*cantidad < MAX_CLIENTES && fread(&arreglo[*cantidad], sizeof(Cliente), 1, archivo) == 1)
        {
            *cantidad++;
        }
    }
    else
    {
        printf("No se encontro el archivo de clientes, se crea uno nuevo\n");
    }
    fclose(archivo);

    printf("Se cargaron %i clientes desde el archivo\n", *cantidad);
}
void guardarClientesEnArchivo(Cliente arreglo[], int cantidad)
{

    FILE *archivo = fopen("Clientes", "wb");

    if (archivo != NULL)
    {
        fwrite(arreglo, sizeof(Cliente), cantidad, archivo);
    }
    else
    {
        printf("Error, no se pudo abrir el archivo\n");
    }
    fclose(archivo);
}

void mostrarClientes()
{
    FILE *archivo = fopen("clientes", "rb");
    if (archivo != NULL)
    {
        Cliente c;
        while (fread(&c, sizeof(Cliente), 1, archivo) == 1) // mientras haya clientes para leer
        {
            printf("ID del cliente: %i\n", c.id);
            printf("Nombre del cliente: %s\n", c.nombre);
            printf("DNI del cliente: %i\n", c.dni);
            printf("Nivel VIP del cliente: %i\n", c.nivelVip);
            printf("Saldo del cliente: %.2f\n", c.saldo);
            printf("Estado del cliente 1(activo)-0(de baja): %i\n\n", c.estado);
        }
        fclose(archivo);
    }
}
// Esta funcion la hice para buscar un ID en el arreglo, y fijarme si estaba cargado, si lo encuentra devuelve
// el indice del arreglo en el que esta, y sino devuelve -1
int buscarPorId(Cliente arreglo[], int cantidad, int id)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (arreglo[i].id == id)
        {
            return i;
        }
    }
    return -1;
}
void altaCliente(Cliente arreglo[], int *cantidad)
{
    if (*cantidad >= MAX_CLIENTES)
    {
        printf("ERROR, NO SE PUEDEN CREAR MAS CLIENTES, SE ALCANZO EL LIMITE (%i) \n", MAX_CLIENTES);
    }

    Cliente nuevo = cargarCliente();

    for (int i = 0; i < *cantidad; i++)
    {
        if (arreglo[i].dni == nuevo.dni && arreglo[i].estado == 1)
        {
            printf("Error, Ya se ha creado un cliente con ese DNI \n");
        }
    }
    arreglo[*cantidad] = nuevo;
    *cantidad++;

    guardarClientesEnArchivo(arreglo, *cantidad);
    printf("Se creo el cliente correctamente\n");
}
// Esta funcion busca el ID que le damos para dar de baja, si lo encuentra, le cambia el estado de 1 a 0,
// no lo borra, solo le cambia el estado, reutilice la funcion de buscarPorId ya que me permite llegar al resultado q busco, que es encontrar el ID

int bajaCliente(Cliente arreglo[], int cantidad)
{
    int id;
    printf("Ingrese el ID del cliente que desea dar de baja \n ");
    scanf("%i", &id);

    int pos = buscarPorId(arreglo, cantidad, id);

    if (pos == -1)
    {
        print("No se encontro el cliente con el ID %i \n", id);
        return 0;
    }
    if (arreglo[pos].estado == 0)
    {
        print("El cliente ya estaba dado de baja\n");
        return 0;
    }
    arreglo[pos].estado = 0;

    guardarClientesEnArchivo(arreglo, cantidad);
    printf("El cliente fue dado de baja de manera correcta\n");
    return 1;
}

// int → 1 si encontró y dio de baja, 0 si no encontró el ID
int modificarCliente(Cliente arreglo[], int cantidad){
    int id;
    printf("Ingrese el ID del cliente que quiere modificar:\n");
    scanf("%i", &id);

    int pos = buscarPorId(arreglo, cantidad, id);

    if(pos == -1 || arreglo[pos].estado == 0){
        print("No se encontro un cliente activo con el ID %i \n", id);
        return 0;
    }

    printf("Datos del cliente: \n");
    mostrarUnCliente(arreglo[pos]);

    printf("\n Nuevo nombre (presiona enter para dejarlo igual '%s'):", arreglo[pos].nombre);
    char temp[50];
    scanf("%s", temp);
     if(strlen(temp)>0){
        strcpy(arreglo[pos].nombre, temp);
     }

       printf("Nuevo nivel VIP (1/2/3, Enter=0 para mantener %d): ", arreglo[pos].nivelVip);
    int nuevoNivel;
    scanf("%d", &nuevoNivel);
    if (nuevoNivel >= 1 && nuevoNivel <= 3) {
        arreglo[pos].nivelVip = nuevoNivel;
    }
 
    printf("Nuevo saldo (Enter=0 para mantener %.2f): ", arreglo[pos].saldo);
    float nuevoSaldo;
    scanf("%f", &nuevoSaldo);
    if (nuevoSaldo > 0) {
        arreglo[pos].saldo = nuevoSaldo;
    }
 
    guardarClientesEnArchivo(arreglo, cantidad);
    printf("  Cliente modificado correctamente.\n");
    return 1;
}
 
// ─────────────────────────────────────────────
//  consultarCliente
//  Busca por ID y muestra todos sus datos.
//  Devuelve 1 si lo encontró, 0 si no.
// ─────────────────────────────────────────────
int consultarCliente(Cliente arreglo[], int cantidad) {
    int id;
    printf("Ingrese el ID del cliente a consultar: ");
    scanf("%d", &id);
 
    int pos = buscarPorId(arreglo, cantidad, id);
 
    if (pos == -1) {
        printf("  No se encontró un cliente con ID %d.\n", id);
        return 0;
    }
 
    mostrarUnCliente(arreglo[pos]);
    return 1;
}
 
// ─────────────────────────────────────────────
//  listarClientesAlfabetico
//  Ordena una COPIA del arreglo por nombre con Selección
//  y la muestra. No modifica el arreglo original.
// ─────────────────────────────────────────────
void listarClientesAlfabetico(Cliente arreglo[], int cantidad) {
    if (cantidad == 0) {
        printf("  No hay clientes cargados.\n");
        return;
    }
 
    // Hacemos una copia para no tocar el arreglo real
    Cliente copia[MAX_CLIENTES];
    for (int i = 0; i < cantidad; i++) {
        copia[i] = arreglo[i];
    }
 
    // ── Selección ──
    // Buscamos el "menor" (el que va primero alfabéticamente)
    // desde la posición i hasta el final, y lo ponemos en i.
    for (int i = 0; i < cantidad - 1; i++) {
        int menorPos = i;
        for (int j = i + 1; j < cantidad; j++) {
            // strcmp devuelve negativo si el primero va antes
            if (strcmp(copia[j].nombre, copia[menorPos].nombre) < 0) {
                menorPos = j;
            }
        }
        // Intercambiamos si encontramos uno más chico
        if (menorPos != i) {
            Cliente aux   = copia[i];
            copia[i]      = copia[menorPos];
            copia[menorPos] = aux;
        }
    }
 
    printf("\n  === Clientes ordenados alfabéticamente ===\n");
    for (int i = 0; i < cantidad; i++) {
        if (copia[i].estado == 1) {  // solo mostramos activos
            mostrarUnCliente(copia[i]);
            printf("  ---\n");
        }
    }
}
 
// ─────────────────────────────────────────────
//  listarClientesPorId
//  Ordena una COPIA del arreglo por ID con Inserción
//  y la muestra. No modifica el arreglo original.
// ─────────────────────────────────────────────
void listarClientesPorId(Cliente arreglo[], int cantidad) {
    if (cantidad == 0) {
        printf("  No hay clientes cargados.\n");
        return;
    }
 
    Cliente copia[MAX_CLIENTES];
    for (int i = 0; i < cantidad; i++) {
        copia[i] = arreglo[i];
    }
 
    // ── Inserción ──
    // Tomamos el elemento en posición i y lo "insertamos"
    // en el lugar correcto dentro de la parte ya ordenada (0..i-1)
    for (int i = 1; i < cantidad; i++) {
        Cliente actual = copia[i];  // el que vamos a insertar
        int j = i - 1;
 
        // Corremos hacia la derecha todos los que son mayores que actual
        while (j >= 0 && copia[j].id > actual.id) {
            copia[j + 1] = copia[j];
            j--;
        }
 
        // Insertamos actual en el hueco que quedó
        copia[j + 1] = actual;
    }
 
    printf("\n  === Clientes ordenados por ID ===\n");
    for (int i = 0; i < cantidad; i++) {
        if (copia[i].estado == 1) {
            mostrarUnCliente(copia[i]);
            printf("  ---\n");
        }
    }
}
 