#ifndef CLIENTES_H
#define CLIENTES_H
#include "tipos.h"

void cargarClientesDesdeArchivo(Cliente arreglo[], int dim);
void guardarClientesEnArchivo(Cliente arreglo[], int cantidad);
void altaCliente(Cliente arreglo[], int* cantidad);
int bajaCliente(Cliente arreglo[], int cantidad);
int modificarCliente(Cliente arreglo[], int cantidad);
int consultarCliente(Cliente arreglo[], int cantidad);
void listarClientesAlfabetico(Cliente arreglo[], int cantidad);
void listarClientesPorId(Cliente arreglo[], int cantidad);

#endif