# Reportes de Optimización

## Reporte 01 Optimización serial

#### Rendimiento del código antes de realizar las modificaciones.

Hasta este momento el código tiene un rendimiento bajo, esto se puede visualizar en
el resultados de la suma de Goldbach respecto a números impares principalmente y
obtener los números primos.

#### Regiones críticas a optimizar (profiling).

Para este profiling se desea optimizar 3 regiones:

1. Resize de goldbach_sums_t
2. Resize de number_t
3. Calculo de numeros primos
4. Cálculo de sumas de Goldbach

#### Modificaciones que se cree incrementarán el rendimiento en las regiones críticas.

1. El resize de los números y sumas de Goldbach.

1. Forma de obtención de un números primo, ya que anteriormente era mediante fuerza bruta y se
podrá modificar por un modelo matemático el cual reduzca el recorrido para saber si un número es primo o no.

2. Utilizar un vector de bits que contenga el resultado de primalidad hasta el mayor de los números y de esta forma
reducir los números de procesos y el orden de duración de las combinaciones.

3. Las sumas de Goldbach se verifican con un algoritmo O(n^2) en número pares y un O(n^3) en
número impares. Por lo que si logramos convertir esos tiempos en una exponencial menor se podría
lograr un mejor tiempo. Una forma para esto es resta el número que buscamos por sus iteradores y así
ahorrar un ciclo.

#### Indiferentemente de si se incrementó o no el rendimiento, documentar las lecciones aprendidas, ya que servirán para otros desarrolladores que intenten optimizar la misma sección de código.

El resultado de esta optimización fue muy bueno, el tiempo de duración se vio reducido en una
gran diferencia y todas las implementaciones trabajaron de la forma esperada. Además la
nueva función para calcular números primos ha sido más rápida que el anterior.

## Reporte 02 Optimización Pthreads con Mapeo dinámico

#### Rendimiento del código antes de realizar las modificaciones.

Hasta este momento el código tiene un rendimiento bastante mediano y
rapido en comparacion al anterior, sin embargo aun este podría verse
incrementado si utilizamos más hilos de ejecución.

#### Regiones críticas a optimizar (profiling).

Para este profiling se desea optimizar la región de las combinaciones de Goldbach
para evitar que un solo hilo sea responsable de esto.

#### Modificaciones que se cree incrementarán el rendimiento en las regiones críticas.

1. Implementar más hilos de ejecución para calcular las sumas de Goldbach y
que el consumo de estas sumas sea dinámico para evitar los hilos ociosos.

#### Indiferentemente de si se incrementó o no el rendimiento, documentar las lecciones aprendidas, ya que servirán para otros desarrolladores que intenten optimizar la misma sección de código.

El resultado de la implementación fue exitoso, los hilos lograron reducir la cargas de trabajo en la
forma más equitativa posible y por ende lograron su cometido.

