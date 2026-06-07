#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "mesas.h"
#include "reclamos.h"
#include "tipos.h"

int ocupacion[MAX_MESAS][MAX_HORAS];

int main() {

    Mesa* mesas    = NULL;
    int   cantMesas = 0;

    cargarMesasDesdeArchivo(&mesas, &cantMesas);

    int opcion;

    do {
        printf("\n|------- Casino Spiderman — Menú Principal -------|\n");
        printf("1. Gestión de Clientes \n");
        printf("2. Gestión de Mesas \n");
        printf("3. Reclamos del día \n");
        printf("0. Salir \n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion) {

            case 1: { //menu de clientes
                printf("Módulo de clientes en desarrollo.\n");
                break;
            }

            case 2: { //menu de mesas
                int opMesa;
                do {
                    printf("\n|------- Gestión de Mesas -------|\n");
                    printf(" MENU PRINCIPAL \n");
                    printf("1. Alta mesa\n");
                    printf("2. Baja mesa\n");
                    printf("3. Modificar mesa\n");
                    printf("4. Consultar mesa\n");
                    printf("5. Consultar mesas por tipo\n");
                    printf("6. Listar alfabético\n");
                    printf("7. Listar por capacidad\n");
                    printf("8. Ocupación diaria\n");
                    printf("0. Volver al menú principal\n");
                    printf("Opción: ");
                    scanf("%d", &opMesa);

                    switch (opMesa) {
                        case 1: altaMesa(&mesas, &cantMesas);              break;
                        case 2: bajaMesa(&mesas, &cantMesas);              break;
                        case 3: modificarMesa(mesas, cantMesas);           break;
                        case 4: consultarMesa(mesas, cantMesas);           break;
                        case 5: consultarMesasPorTipo(mesas, cantMesas);   break;
                        case 6: listarMesasAlfabetico(mesas, cantMesas);   break;
                        case 7: listarMesasPorCapacidad(mesas, cantMesas); break;
                        case 8: mostrarOcupacionDiaria(mesas, cantMesas, ocupacion); break;
                        case 0: break;
                        default: printf("Opción inválida.\n");
                    }

                } while (opMesa != 0);
                break;
            }

            case 3: { //menu de reclamos
                printf("Módulo de reclamos en desarrollo.\n");
                break;
            }

            case 0: printf("Saliendo...\n"); break;
            default: printf("Opción inválida.\n");
        }

    } while (opcion != 0);

    free(mesas); //liberamos la memoria del arreglo de mesas antes de salir
    return 0;
}
