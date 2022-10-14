# Reportes de Optimizacion

## Reporte 01

#### Rendimiento del código antes de realizar las modificaciones.

Hasta este momento el codigo tiene un rendimiento bajo, esto se puede visualizar en
el resultados de la suma de Goldbach respecto a numeros impares y obtener los
numeros primos.

#### Regiones críticas a optimizar (profiling).

Para este profiling se desea obtimizar 3 regiones:

1. Calculo de numeros primos
2. Calculo de sumas de Goldbach
3. Salida de datos

#### Modificaciones que se cree incrementarán el rendimiento en las regiones críticas.

1. Si se modifica la obtencion de un numero primo mediante fuerza bruta
por un modelo matematico se podria reducir en gran cantidad el tiempo en la obtencion
de este.

2. Si en vez de averiguar n cantidad de veces si un numero es primo, se podria utilizar un vector
con los resultados de primalidad, obtenidos con varios hilos de ejecucion hasta el numero maximo,
de cada numero y una formula de acceso para obtener esos resultados.

3. Las sumas de Goldbach se verifican con un algoritmo O(n^2) en numero pares y un O(n^3) en
n7umero impares. Por lo que si logramos convertir esos tiempos en una exponencial menor se podria
lograr un mejor tiempo

4. La salida de datos para datos muy grandes usualmente consumen una cantidad de tiempo considerebale
y en este caso en especifico la salida de datos espera a que todos los hilos que se encuentre en
ejecucion finalicen esa ejeucion, por lo que podriamos ganar tiempo si la impresion inicia desde que
el primero finaliza hasta el ultimo aplicando concurrencia de tareas.

#### Asegurarse de que las modificaciones sean correctas (correr el programa de pruebas).



#### Medir el rendimiento del código después de realizar las modificaciones y comparar para determinar si hubo una ganancia.



#### Indiferentemente de si se incrementó o no el rendimiento, documentar las lecciones aprendidas, ya que servirán para otros desarrolladores que intenten optimizar la misma sección de código.



#### Si es realmente requerido incrementar aún más el rendimiento, repetir desde el paso 2.


