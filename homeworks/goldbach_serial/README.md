# Tarea01: primefact_serial

## Descripción Del Problema

Se desarrolló un programa procedimental, en el lenguaje de programación C, el cual es capaz de captar una lista con números enteros de la entrada estándar y calcular las sumas de Goldbach equivalente de cada número, de manera serial y producir como resultado en la salida estándar un resumen, respecto a cuántos números fueron ingresados y cuántas sumas en total fueron halladas. Finalmente el programa imprimirá en la terminal los números en el mismo orden que fueron ingresados seguidos por la cantidad de sumas de Goldbach que contiene.

**Características e implicaciones:**

1. Si se le ordena al programa las sumas de Goldbach, estas sumas deben estar ordenadas por sus valores, del menor a mayor.
2. Si el número ingresado es negativo, se considerará como que el usuario quiere que el programa además liste todas las sumas del correspondiente número positivo
3. El programa solamente soporta dígitos numéricos dentro del intervalo de 0 a 2^63-1. De lo contrario el programa devolverá un “NA” en la salida estándar.
4. El programa no puede recibir un texto distinto la representación de un número. De lo contrario el programa devolverá el error “invalid input” en el error estándar y finalizará su ejecución.

## Manual De Uso

Este apartado contiene información breve para una adecuada manipulación y ejecución del programa respectivo. Para esto debemos seguir una serie de pasos mostradas a continuación:

1. Abrir la terminal respectiva de su dispositivo. **Ctrl+alt+t**
2. Desplazarse por los archivos hasta llegar a la carpeta nombrada primefact_serial. **cd _______**
3. Una vez ubicado en la carpeta se debe compilar y correr el programa respectivo de la siguiente forma:
  * **Compilación:**
      - make
  * **Ejecución:**
      - make run

**IMPORTANTE:**

En caso de algún error se le recomienda la ejecución del comando **"make clean"** y volver a ejecutar los procesos superiores nuevamente.

## Resultados

### Fase de análisis

## Más información
 
![Estructura De Datos Implementada](./design/README.md)
 
## Créditos

### Autor

Daniel Pérez Morera

### Información de Contacto

**Correo electrónico:** daniel.perezmorera@ucr.ac.cr
