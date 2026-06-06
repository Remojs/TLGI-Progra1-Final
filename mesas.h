#ifndef MESAS_H
#define MESAS_H
#include "tipos.h"

void altaMesa    (Mesa** mesas, int* cantidad);
int  bajaMesa    (Mesa** mesas, int* cantidad);
int  modificarMesa (Mesa*  mesas, int  cantidad);
int  consultarMesa (Mesa*  mesas, int  cantidad);
void consultarMesasPorTipo  (Mesa* mesas, int cantidad);
void listarMesasAlfabetico  (Mesa* mesas, int cantidad);
void listarMesasPorCapacidad (Mesa* mesas, int cantidad);
void mostrarOcupacionDiaria (Mesa* mesas, int cantidad, int ocupacion[][MAX_HORAS]);
void cargarMesasDesdeArchivo (Mesa** mesas, int* cantidad);
void guardarMesasEnArchivo  (Mesa*  mesas, int  cantidad);

#endif 