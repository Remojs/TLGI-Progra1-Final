# Veterinaria — TP Final 

Proyecto grupal, no se rompan la cabeza, cualquier duda consultar a Thiago (porfavor no rompan nada)

![gato](https://media.tenor.com/exRZ3es-yb8AAAAM/maxwell-maxwell-cat.gif)

---

## Cómo está organizado el proyecto

El proyecto está dividido en archivos, y cada uno tiene su responsabilidad. La idea es que cada uno trabaje en su propio archivo

```
veterinaria/
│
├── main.c          → Menú principal (aca traemos todo)
├── tipos.h         → Las structs y constantes.
│
├── duenios.h       → Declaracion de cada funcion para Dueños
├── duenios.c       → Desarrollo de cada funcion para Dueños
│
├── mascotas.h      → Declaracion de cada funcion para Mascotas
├── mascotas.c      → Desarrollo de cada funcion para Mascotas
│
├── turnos.h        → Declaracion de cada funcion para Turnos
├── turnos.c        → Desarrollo de cada funcion para Turnos
```

---

## Para qué sirven el .h y el .c

Cada módulo tiene dos archivos: un `.h` y un `.c`.

No se asusten loco!

- El `.h` es como el **índice de un libro**: lista qué funciones existen y qué parámetros reciben (la declaracion que hacen en el main siempre).

- El `.c` es el **contenido del libro**: ahí está el código real de cada función.


Seria algo asi un ejemplo de declaracion en el .h:
```c
void altaDuenio(Duenio arreglo[], int* cantidad);
```
Y en `duenios.c` vas a ver esa misma función pero con todo el código adentro.

Esta bueno porque si se necesita usar una función de Dueños, solo ponen `#include "duenios.h"` al principio del archivo y listo.

---

## Qué tiene que hacer cada archivo

### `tipos.h` 
Acá están definidas las dos structs principales y las constantes del sistema. Si hay que cambiar algo acá pregunten primero, si rompen algo se pudre todo


---

### `duenios.c` 
Todo lo relacionado con los dueños. 

Funciones que tiene que tener:
- `altaDuenio` → pedir datos, verificar que no esté repetido, guardar en archivo
- `bajaDuenio` → buscar por ID, marcarlo como inactivo, guardar
- `modificarDuenio` → buscar por ID, cambiar datos, guardar
- `consultarDuenio` → buscar por ID y mostrar los datos en pantalla
- `listarDueniosAlfabetico` → ordenar por nombre usando **método Selección**
- `listarDueniosPorId` → ordenar por ID usando **método Inserción**
- `cargarDueniosDesdeArchivo` → leer el archivo binario al iniciar el sistema
- `guardarDueniosEnArchivo` → escribir el archivo binario cada vez que haya cambios

---

### `mascotas.c`
Todo lo relacionado con las mascotas. Usa un **arreglo dinámico** (`malloc`/`realloc`) porque la cantidad de mascotas puede crecer.

Funciones que tiene que tener:
- `altaMascota` → pedir datos, validar que la especie sea válida, usar `realloc` para agrandar el arreglo, guardar
- `bajaMascota` → buscar por ID, eliminarlo del arreglo, guardar
- `modificarMascota` → buscar por ID, cambiar datos, guardar
- `consultarMascota` → buscar por ID y mostrar
- `consultarMascotasPorDuenio` → mostrar todas las mascotas de un dueño
- `listarMascotasAlfabetico` → ordenar por nombre usando **método Selección**
- `listarMascotasPorEdad` → ordenar por edad usando **método Inserción**
- `cargarMascotasDesdeArchivo` → leer el archivo al iniciar
- `guardarMascotasEnArchivo` → escribir el archivo cuando haya cambios

---

### `turnos.c` 
La **pila** de turnos urgentes del día. Los turnos no se guardan en archivo, son solo del día.

Funciones que tiene que tener:
- agregar un turno urgente arriba de la pila
- sacar y atender el turno del tope
- ver todos los turnos
- vaciarPila


---

### `main.c` — El menú (quien integra todo)
- Acá arranca el programa. Llama a las funciones de los otros archivos según lo que elija el usuario. 

- Que no tenga lógica propia, solo organiza los menús.

---

## Reglas para no pisarse en GitHub

### ✅ Está bien hacer
- Trabajar solo en tus archivos (el `.c` y el `.h` que te tocan)
- Hacer commit seguido con mensajes que expliquen qué hiciste
- Avisar al grupo cuando terminaste algo para que puedan probar

### ❌ No hacer sin hablar con el grupo
- **No tocar `tipos.h` solo** — si cambiás una struct sin avisar, el código de todos deja de compilar y cobras
- **Avisar si modificas funciones en el `.h` (la declaracion de la funcion)** — si cambiás los parámetros de una función, el `main.c` deja de funcionar
