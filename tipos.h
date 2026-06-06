#ifndef TIPOS_H
#define TIPOS_H

// x Constantes 
#define MAX_CLIENTES 200
#define MAX_MESAS    10
#define MAX_HORAS    24

// x Structs 
typedef struct {
    int   id;
    char  nombre[50];
    char  dni[15];
    int   nivelVip;   // 1=Bronce, 2=Plata, 3=Oro
    float saldo;
    int   activo;     // 1=activo, 0=dado de baja
} Cliente;

typedef struct {
    int  id;
    char nombreJuego[50];
    int  capacidadMax;
    int  disponible;  // 1=disponible, 0=ocupada
    int  activa;      // 1=activa, 0=dada de baja
} Mesa;

typedef struct {
    int  idReclamo;
    int  idCliente;
    char descripcion[200];
    int  prioridad;
} Reclamo;

// x Matriz de ocupación 
extern int ocupacion[MAX_MESAS][MAX_HORAS];

#endif