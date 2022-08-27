# recursive_hello
## Enunciado

Copie su ejemplos/pthreads/hello a ejercicios/pthreads/recursive_hello. Puede renombrar ejercicios/pthreads/recursive_hello/src/hello.c a recursive_hello.c o si lo prefiere, main.c.

Modifique a greet() para recibir un número de tipo size_t. Si este número es 0, greet() imprime una despedida y el número recibido. Luego termina su ejecución.

Si el número que greet() recibe es mayor que cero, imprime un saludo y el número recibido. Luego crea un hilo para que invoque a greet() pero con un número menor que el recibido por parámetro.

Modifique el procedimiento main() para crear una variable local de tipo size_t inicializada en 2. Envíe este número como parámetro de la subrutina greet() que correrá en el hilo secundario.

Recuerde copiar este enunciado en una sección de su documeneto de análisis ejercicios/pthreads/recursive_hello/readme.md y darle el formato apropiado. En otra sección haga una predicción de la salida de su programa antes de corerlo. Compílelo y córralo con el Makefile. Copie la salida de su programa y péguela en un bloque de código debajo de su predicción. ¿Acertó la predicción?

## Prediccion

### Salida esperada:

Hello from main thread

Hello from secundary thread

Number: 2

Hello from secundary thread

Number: 1

Bye

Number: 0

### Salida generada:

Hello from main thread

Hello from secundary thread

Number: 2

Hello from secundary thread

Number: 1

Bye

Number: 0

## Memoria

### Rastreo de Memoria:

![Imagen de rastreo de memoria](exercises/pthreads/recursive_hello/trace/trace.svg) 

Imagen
