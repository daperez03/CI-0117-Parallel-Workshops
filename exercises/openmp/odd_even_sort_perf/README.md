# Ejercicio 51 [odd_even_sort_perf]

## Enunciado

Con la herramienta perf mida el tiempo de ejecución de su implementación serial, parallel-for, y two-for del algoritmo de ordenamiento
par-impar con un millón de elementos. Anote las duraciones obtenidas en una hoja de cálculo, con 1 hilo (1), tantos hilos como la
mitad de CPUs disponibles (h) en el sistema, igual a la cantidad de CPUs (C), y dos veces la cantidad de CPUs disponibles (2C) en la
máquina donde se realizaron las pruebas, la cual debe tener al menos 8 núcleos.

### Tiempos de ejecución

#### Serial

Numero de elementos: 1000000

Tiempo de ejecucion: 3299.721905340

#### Parallel-for

Numero de elementos: 1000000

|Threads|Time|
|----|-------|
|1   |4009.977594401|
|4   |467.789563530|
|8   |274.837571369|
|16  |476.154687830|

#### two-for

Numero de elementos: 1000000

|Threads|Time|
|----|-------|
|1   |4044.932838703|
|4   |460.233195860|
|8   |269.461170812|
|16  |314.971441018|
