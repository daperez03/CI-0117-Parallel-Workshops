# Diseño general de estructura de datos

## Descripción

Para el problema propuesto se implementó un diseño para la estructura de datos de tipo array, implementado en un objeto goldbach_sums, con funciones las cuales permiten manipular el contenido de sus datos. La estructura almacenará datos necesarios para la correcta función del array y almacenamiento de características de los números ingresados, como lo sería un contador y la capacidad.

### Datos

#### goldbach_sums_t

* capacity: uint64_t
* count: uint64_t
* numbers: number_t*
* can_access_solution_count: pthread_mutex_t
* solution_count: uint64_t

#### number_t

* number: int64_t
* capacity: uint64_t
* sum_count: uint64_t
* sums: uint64_t*

### Funciones

* **init:** Toma la responsabilidad de inicializar el contenido de goldbach_sums_t.
* **resize_numbers:** Reestructura el tamaño del array de numeros, del struct goldbach_sums_t
* **resize_sums:** Reestructura el tamaño del array de sums del struct number_t
* **result:** Envía a la salida estándar un resumen sobre los resultados obtenidos.
* **destroy:** Libera todo lo que contiene la estructura de datos.

## Diagrama UML

![Diseño general de estructura de datos](./SVG/EstructuraDeDatos.drawio.svg)

## Pseudocódigo

### Función principal

![goldbach_serial](./pseudocode/goldbach_serial.pseudo)

### Funciones encargadas de implementar paralelismo

![parallelism](./pseudocode/parallelism.pseudo)

### Funciones encargadas de la extracción de datos

![buffer](./pseudocode/buffer.pseudo)

### Funciones encargadas de manipular la estructura de datos

![goldbach_sums](./pseudocode/goldbach_sums.pseudo)

### Funciones encargadas de los procesos matemáticos

![my_math](./pseudocode/my_math.pseudo)
