#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "mesas.h"
#include "reclamos.h"
#include "tipos.h"

int ocupacion[MAX_MESAS][MAX_HORAS];

int main() {

    // ── inicialización ───────────────────────────────────────────────────
    Mesa*  mesas       = NULL;
    int    cantMesas   = 0;
    Cliente clientes[MAX_CLIENTES];
    int    cantClientes = 0;

    cargarMesasDesdeArchivo(&mesas, &cantMesas);
    cargarClientesDesdeArchivo(clientes, &cantClientes);
    iniciarReclamos();

    int opcion;

    do {
        printf("\n|------- Casino Spiderman — Menú Principal -------|\n");
        printf("1. Gestión de Clientes\n");
        printf("2. Gestión de Mesas\n");
        printf("3. Reclamos del día\n");
        printf("0. Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion) {

            case 1: { // ── menú clientes ──────────────────────────────────
                int opCliente;
                do {
                    printf("\n|------- Gestión de Clientes -------|\n");
                    printf("1. Alta cliente\n");
                    printf("2. Baja cliente\n");
                    printf("3. Modificar cliente\n");
                    printf("4. Consultar cliente\n");
                    printf("5. Listar alfabético\n");
                    printf("6. Listar por ID\n");
                    printf("0. Volver al menú principal\n");
                    printf("Opción: ");
                    scanf("%d", &opCliente);
                    printf("\n|---------------------------------|\n\n");

                    switch (opCliente) {
                        case 1: altaCliente(clientes, &cantClientes);        break;
                        case 2: bajaCliente(clientes, cantClientes);         break;
                        case 3: modificarCliente(clientes, cantClientes);    break;
                        case 4: consultarCliente(clientes, cantClientes);    break;
                        case 5: listarClientesAlfabetico(clientes, cantClientes); break;
                        case 6: listarClientesPorId(clientes, cantClientes); break;
                        case 0: break;
                        default: printf("Opción inválida.\n");
                    }

                } while (opCliente != 0);
                break;
            }

            case 2: { // ── menú mesas ─────────────────────────────────────
                int opMesa;
                do {
                    printf("\n|------- Gestión de Mesas -------|\n");
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
                    printf("\n|---------------------------------|\n\n");

                    switch (opMesa) {
                        case 1: altaMesa(&mesas, &cantMesas);                        break;
                        case 2: bajaMesa(&mesas, &cantMesas);                        break;
                        case 3: modificarMesa(mesas, cantMesas);                     break;
                        case 4: consultarMesa(mesas, cantMesas);                     break;
                        case 5: consultarMesasPorTipo(mesas, cantMesas);             break;
                        case 6: listarMesasAlfabetico(mesas, cantMesas);             break;
                        case 7: listarMesasPorCapacidad(mesas, cantMesas);           break;
                        case 8: mostrarOcupacionDiaria(mesas, cantMesas, ocupacion); break;
                        case 0: break;
                        default: printf("Opción inválida.\n");
                    }

                } while (opMesa != 0);
                break;
            }

            case 3: { // ── menú reclamos ──────────────────────────────────
                int opReclamo;
                do {
                    printf("\n|------- Reclamos del día -------|\n");
                    printf("1. Agregar reclamo\n");
                    printf("2. Atender reclamo\n");
                    printf("3. Ver reclamos pendientes\n");
                    printf("4. Vaciar pila de reclamos\n");
                    printf("0. Volver al menú principal\n");
                    printf("Opción: ");
                    scanf("%d", &opReclamo);
                    printf("\n|---------------------------------|\n\n");

                    switch (opReclamo) {
                        case 1: agregarReclamo(); break;
                        case 2: atenderReclamo(); break;
                        case 3: verReclamos();    break;
                        case 4: vaciarPila();     break;
                        case 0: break;
                        default: printf("Opción inválida.\n");
                    }

                } while (opReclamo != 0);
                break;
            }

            case 0: printf("Saliendo...\n"); break;
            default: printf("Opción inválida.\n");
        }

    } while (opcion != 0);

    free(mesas);
    return 0;
}