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
    scanf("%f", &c.saldo);                    \
    printf("Ingrese el Estado del cliente, 1(activo) 0(de baja)\n");
    scanf("%i", &c.estado);
    return c;
}

int cargarArrClientes(Cliente cliente[], int dim)
{
    char control = 's';
    int i = 0;
    while ((control == 's' || control == 'S') && i < dim)
    {
        cliente[i] = cargarCliente();
        i++;
        printf("Desea cargar otro cliente? s/n\n");
        scanf(" %c", &control);
    }
    return i;
}

void cargarClientesDesdeArchivo(Cliente cliente[], int dim)
{
    int val = cargarArrClientes(cliente, dim);
    FILE *archivo = fopen("clientes", "ab");
    if (archivo != NULL)
    {
        fwrite(cliente, sizeof(Cliente), val, archivo); 
        fclose(archivo);                                
    }
}

void mostrarClientes()
{
    FILE *archivo = fopen("clientes", "rb");
    if (archivo != NULL)
    {
        Cliente c;
        while (fread(&c, sizeof(Cliente), 1, archivo) == 1)  // mientras haya clientes para leer
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


/* void guardarClientesEnArchivo(Cliente arreglo[], int cantidad){


}

void altaCliente(Cliente arreglo[], int* cantidad){

}

// int → 1 si encontró y dio de baja, 0 si no encontró el ID
int bajaCliente(Cliente arreglo[], int cantidad){

}

// int → 1 si encontró y dio de baja, 0 si no encontró el ID
int modificarCliente(Cliente arreglo[], int cantidad){

}

// int → 1 si encontró y mostró, 0 si no existe
int consultarCliente(Cliente arreglo[], int cantidad){

}

void listarClientesAlfabetico(Cliente arreglo[], int cantidad){
    Cliente copia[MAX_CLIENTES];

}

void listarClientesPorId(Cliente arreglo[], int cantidad){
    Cliente copia[MAX_CLIENTES];

}
 */