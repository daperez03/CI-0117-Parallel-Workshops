# Reportes de Optimizacion

## Reporte 01 Optimizacion serial

#### Rendimiento del código antes de realizar las modificaciones.

Hasta este momento el codigo tiene un rendimiento bajo, esto se puede visualizar en
el resultados de la suma de Goldbach respecto a numeros impares principalmente y
obtener los numeros primos.

#### Regiones críticas a optimizar (profiling).

Para este profiling se desea obtimizar 3 regiones:

1. Resize de goldbach_sums_t
2. Resize de number_t
3. Calculo de numeros primos
4. Calculo de sumas de Goldbach

#### Modificaciones que se cree incrementarán el rendimiento en las regiones críticas.

1. El resize de los numeros y sumas de Goldbach.

1. Forma de otencion de un numeros primo, ya que anteriormente era mediante fuerza bruta y se
podria modificar por un modelo matematico el cual reduzca el recorrido para saber si un numero es primo o no.

2. Utilizar un vector de bits que contenga el resultado de primalidad hasta el mayor de los numeros y de esta forma
reducir los numeros de procesos y el orden de duracion de las combinaciones.

3. Las sumas de Goldbach se verifican con un algoritmo O(n^2) en numero pares y un O(n^3) en
numero impares. Por lo que si logramos convertir esos tiempos en una exponencial menor se podria
lograr un mejor tiempo. Una forma para esto es resta el numero que buscamos por sus iteradores y asi
ahorrar un ciclo.

#### Indiferentemente de si se incrementó o no el rendimiento, documentar las lecciones aprendidas, ya que servirán para otros desarrolladores que intenten optimizar la misma sección de código.

El resultado de esta optimizacion fue muy bueno, el tiempo de duracion se vio reducido en una
muy garnde diferencia y todas las implementaciones trabajaron de la forma esperada. Ademas la
nueva funcion para calcular numeros primos ha sido mas rapido que el anterior.

## Reporte 02 Optimizacion Pthreads con Mapeo dinamico

#### Rendimiento del código antes de realizar las modificaciones.

Hasta este momento el codigo tiene un rendimiento bastante mediano y
rapido en comparacion al anterior, sin embargo aun este podria verser
incrementado si utilizamos mas hilos de ejecucion.

#### Regiones críticas a optimizar (profiling).

Para este profiling se desea optimizar la region de las combinaciones de Goldbach
para evitar que un solo hilo sea responsable de esto.

#### Modificaciones que se cree incrementarán el rendimiento en las regiones críticas.

1. Implementar mas hilos de ejecucion para calcular las sumas de Goldbach y
que el consumo de estas sumas sea dinamico para evitar los hilos ocioso.

#### Indiferentemente de si se incrementó o no el rendimiento, documentar las lecciones aprendidas, ya que servirán para otros desarrolladores que intenten optimizar la misma sección de código.

El resultado de la implementacion fue exitoso, los hilos lograron reducir la cargas de trabajo en la
forma mas equitativa posible y por ende lograron su cometido.
