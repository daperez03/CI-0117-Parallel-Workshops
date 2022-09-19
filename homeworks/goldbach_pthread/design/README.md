# Diseño general de estructura de datos
 
## Descripción
 
Para para el problema propuesto se implemento un diseño para la estructura de datos de tipo array, implementado en un objeto goldbach_sums, con funciones las cuales permiten manipular el contenido de sus datos. La estructura almacenara datos necesarios para la correcta funcion del array y almacenamiento de caracteristicas de los numeros ingresados, como lo seria un contador y la capacidad.

### Datos
#### goldbach_sums_t

* capacity: uint64_t
* count: uint64_t
* numbers: number_t*

#### number_t

* number: uint64_t
* capacity: uint64_t
* sum_count: uint64_t
* sums: uint64_t*

### Funciones

* **init:** Toma la responsabilidad de inicializar el contenido de goldbach_sums_t.
* **resize_numbers:** Reestructura el tamaño del array de numeros, del struct goldbach_sums_t
* **resize_sums:** Reestructura el tamaño del array de sums del struct number_t
* **result:** Envia a la salida estandar un resumen sobre los resultados obtenidos.
* **destroy:** Libera todo lo que contiene la estructura de datos.
 
## Diagrama UML

![Diseño general de estructura de datos](./SVG/EstructuraDeDatos.drawio.svg)

## Pseudocódigo

### Funcion principal

![goldbach_serial](./pseudocode/goldbach_serial.pseudo)

### Funciones encargadas de la extracción de datos

![buffer](./pseudocode/buffer.pseudo)

### Funciones encargadas de manipular la estructura de datos

![goldbach_sums](./pseudocode/goldbach_sums.pseudo)

### Funciones encargadas de los procesos matemáticos

![my_math](./pseudocode/my_math.pseudo)
