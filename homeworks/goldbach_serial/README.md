# Tarea01: goldbach_serial

## Descripción Del Problema

Se desarrolló un programa procedimental, en el lenguaje de programación C, el cual es capaz de captar una lista con números enteros de la entrada estándar y calcular las sumas de Goldbach equivalente de cada número, de manera serial y producir como resultado en la salida estándar un resumen, respecto a cuántos números fueron ingresados y cuántas sumas en total fueron halladas. Finalmente el programa imprimirá en la terminal los números en el mismo orden que fueron ingresados seguidos por la cantidad de sumas de Goldbach que contiene.

**Características e implicaciones:**

1. Si se le ordena al programa las sumas de Goldbach, estas sumas deben estar ordenadas por sus valores, del menor a mayor.
2. Si el número ingresado es negativo, se considerará como que el usuario quiere que el programa además liste todas las sumas del correspondiente número positivo
3. El programa solamente soporta dígitos numéricos dentro del intervalo de 0 a 2^63-1. De lo contrario el programa devolverá un “NA” en la salida estándar.
4. El programa no puede recibir un texto distinto la representación de un número. De lo contrario el programa devolverá el error “invalid input” en el error estándar y finalizará su ejecución.

## Manual De Uso

Este apartado contiene información breve para una adecuada manipulación y ejecución del programa respectivo. Para esto es necesario seguir una serie de pasos mostradas a continuación:

1. Tener el compilador GCC adecuado para C y preferiblemente un documento Makefile
configurado para la ejecución.
2. Abrir la terminal respectiva de su dispositivo(**Ctrl+alt+t**).
3. Desplazarse por los archivos hasta llegar a la carpeta nombrada goldbach_sums(**cd ___**).
4. Una vez ubicado en la carpeta se debe compilar y correr el programa.

### Compilación

Makefile: Si se cuenta con un documento Makefile configurado, solamente
debe ejecutar el comando 'make'.

Compilador normal: debe ingresar los comandos:

``
gcc -c -Wall -Wextra -pthread -g -std=gnu11 -Isrc -MMD src/buffer.c -o build/buffer.o
gcc -c -Wall -Wextra -pthread -g -std=gnu11 -Isrc -MMD src/goldbach_serial.c -o build/goldbach_serial.o
gcc -c -Wall -Wextra -pthread -g -std=gnu11 -Isrc -MMD src/goldbach_sums.c -o build/goldbach_sums.o
gcc -c -Wall -Wextra -pthread -g -std=gnu11 -Isrc -MMD src/my_math.c -o build/my_math.o mkdir -p bin/
gcc -Wall -Wextra -pthread -g -Isrc build/buffer.o build/goldbach_serial.o build/goldbach_sums.o build/my_math.o -o bin/goldbach_serial
``

### Ejecución

Para la ejecución se encuentra disponible dos formatos:

1. Entrada estándar: El primer método consiste en simplemente utilizar 'make run' e ingresar los
números deseados en la terminal, una vez ya haya ingresado todos los números se debe presionar
'ctrl d'

2. Redireccionamiento de entrada estándar: El segundo método debe redireccionar la entrada estándar,
para ello se debe crear un archivo de texto con un número deseado por línea, para ejecutar debe 
escribir el comando 'bin/goldbach_serial < **txt**' donde **txt** es la dirección de su archivo con 
los números

3. Redireccionamiento de salida standar: Para redireccionar la salida estándar debemos seguir con la
misma lógica que la de la entrada estándar, nada más debemos colocar 'bin/goldbach_serial > **txt**'
donde **txt** es el nombre del archivo donde queremos que vayan los resultados digitados, los
números se deben ingresar desde la termina con un cambio de línea entre cada uno y una vez todos hayan
sido ingresados se debe presionar 'ctrl d'

4. Redireccionamiento de entrada y salida standar: Para este cuarto y último punto debemos tener en
cuenta que el programa trabaja mediante archivos de texto, leyendo e imprimiendo así los archivos
indicados, para esto se debe ejecutar el comando 'bin/goldbach_serial < **input** > **output**',
dónde input sera la direccion del archivo de texto que desea ingresar y output el nombre de cómo
desea que el archivo de salida sea llamado

**IMPORTANTE:**

En caso de algún error se le recomienda la ejecución del comando **"make clean"**, o lo que es 
correspondiente a **rm -rf bin build doc**, y volver a ejecutar los procesos anteriores nuevamente. 
Además verificar que este error no se haya producido por un dígito válido o falta de memoria.

## Ejemplos de ejecución

```
bin/goldbach_serial
1
6
4
10
9
Total 5 numbers 6 sums

1: NA
6: 1 sums
4: 1 sums
10: 2 sums
9: 2 sums
```

```
bin/goldbach_serial < tests/input004.txt > output004.txt
```

## Más información
 
![Estructura De Datos Implementada](./design/README.md)
 
## Créditos

### Referencias

Jorge. (2022, May 3). Cómo verificar si un número es primo en python. cryptoshitcompra.com. Retrieved September 5, 2022, from https://cryptoshitcompra.com/como-verificar-si-un-numero-es-primo-en-python 

### Autor

Daniel Pérez Morera

### Información de Contacto

**Correo electrónico:** daniel.perezmorera@ucr.ac.cr
