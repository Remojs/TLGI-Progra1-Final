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
    scanf("%s", &c.nombre);
    printf("Ingrese el DNI del cliente\n");
    scanf("%i", &c.dni);
    printf("Ingrese el Nivel VIP del cliente\n");
    scanf("%i", &c.nivelVip);
    printf("Ingrese el Saldo del cliente\n");
    scanf("%fi", &c.saldo);
    printf("Ingrese el Estado del cliente, 1(activo) \n");
    scanf("%i", &c.estado);
    return c;
}

int cargarArrClientes(Cliente cliente[], int dim)
{

    char control = 's';
    int i = 0;

    while (control == 's' && i < dim)
    {

        cliente[i] = cargarCliente();
        i++;
        printf("Desea cargar otro cliente?\n");
        scanf(" %c", &control);
    }
    return i;
}

void cargarClientesDesdeArchivo(Cliente cliente[], int dim)
{
    int val = cargarArrClientes(cliente, dim);
    FILE *archivo = fopen("clientes", "ab");
    Cliente c;
    if (archivo != NULL)
    {
        fwrite(&c, sizeof(Cliente), val, archivo);
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