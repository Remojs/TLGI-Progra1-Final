#ifndef CLIENTES_H
#define CLIENTES_H

#include "tipos.h"

// Lee el archivo binario al iniciar el sistema y llena el arreglo
void cargarClientesDesdeArchivo(Cliente arreglo[], int *cantidad);

// Escribe todo el arreglo en el archivo (se llama tras cada cambio)
void guardarClientesEnArchivo(Cliente arreglo[], int cantidad);

// Pide datos, verifica DNI duplicado y agrega al arreglo
void altaCliente(Cliente arreglo[], int *cantidad);

// Busca por ID y marca estado = 0 (baja lógica). Devuelve 1/0
int bajaCliente(Cliente arreglo[], int cantidad);

// Busca por ID y permite cambiar nombre, nivelVip y saldo. Devuelve 1/0
int modificarCliente(Cliente arreglo[], int cantidad);

// Busca por ID y muestra sus datos. Devuelve 1/0
int consultarCliente(Cliente arreglo[], int cantidad);

// Muestra los clientes ordenados alfabéticamente (Selección)
void listarClientesAlfabetico(Cliente arreglo[], int cantidad);

// Muestra los clientes ordenados por ID (Inserción)
void listarClientesPorId(Cliente arreglo[], int cantidad);

#endif 
