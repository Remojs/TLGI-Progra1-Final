# Casino — TP Final

Proyecto grupal, no se rompan la cabeza, cualquier duda consultar a Thiago (porfavor no rompan nada)

![dealer](https://media.tenor.com/aR8BhQyiSrYAAAAM/casino-gambling.gif)

---

## Cómo está organizado el proyecto

El proyecto está dividido en archivos, y cada uno tiene su responsabilidad. La idea es que cada uno trabaje en su propio archivo.

```
casino/
│
├── main.c          → Menú principal (acá traemos todo)
├── tipos.h         → Las structs, constantes y la matriz de ocupación
│
├── clientes.h      → Declaración de cada función para Clientes
├── clientes.c      → Desarrollo de cada función para Clientes
│
├── mesas.h         → Declaración de cada función para Mesas
├── mesas.c         → Desarrollo de cada función para Mesas
│
├── reclamos.h      → Declaración de cada función para la Pila de Reclamos
├── reclamos.c      → Desarrollo de cada función para la Pila de Reclamos
```

---

## Para qué sirven el .h y el .c

Cada módulo tiene dos archivos: un `.h` y un `.c`.

No se asusten loco!

- El `.h` es como el **índice de un libro**: lista qué funciones existen y qué parámetros reciben (la declaración que hacen en el main siempre).

- El `.c` es el **contenido del libro**: ahí está el código real de cada función.

Sería algo así un ejemplo de declaración en el `.h`:
```c
void altaCliente(Cliente arreglo[], int* cantidad);
```
Y en `clientes.c` van a ver esa misma función pero con todo el código adentro.

Está bueno porque si se necesita usar una función de Clientes, solo ponen `#include "clientes.h"` al principio del archivo y listo.

---

## Qué tiene que hacer cada archivo

### `tipos.h`
Acá están definidas las dos structs principales, las constantes del sistema, **y la matriz de ocupación**. Si hay que cambiar algo acá pregunten primero, si rompen algo se pudre todo.

**Structs:**
```c
#define MAX_CLIENTES 200
#define MAX_MESAS    10   // máximo de mesas simultáneas
#define MAX_HORAS    24   // horas del día

typedef struct {
    int     id;
    char    nombre[50];
    char    dni[15];
    int     nivelVip;      // 1=Bronce, 2=Plata, 3=Oro
    float   saldo;
    int     activo;        // 1=activo, 0=dado de baja
} Cliente;

typedef struct {
    int     id;
    char    nombreJuego[50];  // "Ruleta", "Blackjack", "Póker", etc.
    int     capacidadMax;
    int     disponible;       // 1=disponible, 0=ocupada
    int     activa;           // 1=activa, 0=dada de baja
} Mesa;

typedef struct {
    int     idReclamo;
    int     idCliente;
    char    descripcion[200];
    int     prioridad;
} Reclamo;
```

**Matriz de ocupación:** representa cuántos jugadores tiene cada mesa en cada hora del día:
```c
int ocupacion[MAX_MESAS][MAX_HORAS];
```

---

### `clientes.c` — Arreglo **ESTÁTICO**
Todo lo relacionado con los clientes del casino. Usa un arreglo estático de tamaño fijo (`MAX_CLIENTES`).

Funciones que tiene que tener:
- `altaCliente` → pedir datos, verificar que el DNI no esté repetido, guardar en archivo
- `bajaCliente` → buscar por ID, marcarlo como inactivo (`activo = 0`), guardar
- `modificarCliente` → buscar por ID, cambiar datos (nombre, nivel VIP, saldo), guardar
- `consultarCliente` → buscar por ID y mostrar todos los datos en pantalla
- `listarClientesAlfabetico` → ordenar por nombre usando **método Selección**
- `listarClientesPorId` → ordenar por ID usando **método Inserción**
- `cargarClientesDesdeArchivo` → leer el archivo binario al iniciar el sistema
- `guardarClientesEnArchivo` → escribir el archivo binario cada vez que haya cambios

---

### `mesas.c` — Arreglo **DINÁMICO**
Todo lo relacionado con las mesas del casino. Usa un **arreglo dinámico** (`malloc`/`realloc`) porque el casino puede habilitar nuevas mesas.

Funciones que tiene que tener:
- `altaMesa` → pedir datos, validar que el tipo de juego sea válido, usar `realloc` para agrandar el arreglo, guardar
- `bajaMesa` → buscar por ID, eliminarlo del arreglo (compactar), guardar
- `modificarMesa` → buscar por ID, cambiar datos, guardar
- `consultarMesa` → buscar por ID y mostrar
- `consultarMesasPorTipo` → mostrar todas las mesas de un tipo de juego (ej: todas las ruletas)
- `listarMesasAlfabetico` → ordenar por nombre del juego usando **método Selección**
- `listarMesasPorCapacidad` → ordenar por capacidad máxima usando **método Inserción**
- `mostrarOcupacionDiaria` → recorre la matriz `ocupacion[MAX_MESAS][MAX_HORAS]` y muestra un reporte de actividad por mesa y hora
- `cargarMesasDesdeArchivo` → leer el archivo al iniciar
- `guardarMesasEnArchivo` → escribir el archivo cuando haya cambios

---

### `reclamos.c` — **PILA**
La pila de reclamos urgentes del día (quejas de clientes, problemas técnicos, situaciones VIP). Los reclamos **no se guardan en archivo**, son solo del día.

Funciones que tiene que tener:
- `agregarReclamo` → agrega un reclamo urgente en el tope de la pila (push)
- `atenderReclamo` → saca y muestra el reclamo del tope (pop), el más reciente se atiende primero
- `verReclamos` → recorre y muestra todos los reclamos sin sacarlos
- `vaciarPila` → descarta todos los reclamos pendientes al cerrar el turno

---

### `main.c` — El menú (quien integra todo)
- Acá arranca el programa. Llama a las funciones de los otros archivos según lo que elija el usuario.
- **Que no tenga lógica propia**, solo organiza los menús.
- Define e inicializa la matriz de ocupación (`int ocupacion[MAX_MESAS][MAX_HORAS]`) con ceros al arrancar.

Menú sugerido:
```
=== SISTEMA DE GESTIÓN CASINO ===
1. Gestión de Clientes
2. Gestión de Mesas
3. Reclamos del día
4. Reporte de ocupación diaria
0. Salir
```

---

## Reglas para no pisarse en GitHub

### ✅ Está bien hacer
- Trabajar solo en tus archivos (el `.c` y el `.h` que te tocan)
- Hacer commit seguido con mensajes que expliquen qué hiciste
- Avisar al grupo cuando terminaste algo para que puedan probar

### ❌ No hacer sin hablar con el grupo
- **No tocar `tipos.h` solo** — si cambiás una struct sin avisar, el código de todos deja de compilar y cobras
- **Avisar si modificás funciones en el `.h` (la declaración)** — si cambiás los parámetros de una función, el `main.c` deja de funcionar
