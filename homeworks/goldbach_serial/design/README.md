# Diseño general de estructura de datos
 
## Descripción
 
Para para el problema propuesto se implemento un diseño para la estructura de datos de tipo array, implementado en un objeto goldbach_sums, con subrutinas las cuales permiten de manipular el contenido de sus datos. La estructura almacenara datos necesarios para la correcta funcion del array y almacenamiento de caracteristicas de los numeros ingresados

### Datos
#### goldbach_sums_t

* capacity: uint64_t
* count: uint64_t
* numbers: number_t*

#### number_t

* number: uint64_t
* result_t: uint64_t
* capacity: uint64_t
* sum_count: uint64_t
* sums: uint64_t*

### Subrutinas

* **init:** Toma la responsabilidad de inicializar el contenido de goldbach_sums_t.
* **resize:** Reestructura el tamaño de numbers si es necesario
* **resume:** Imprime un resumen sobre los resultados obtenidos.
* **destroy:** Libera todo lo que contiene la estructura de datos.
 
## Diagrama UML

![Diseño general de estructura de datos](./SVG/EstructuraDeDatos.drawio.svg)

## Pseudocódigo

### Clase principal

![goldbach_serial](./pseudocode/goldbach_serial.pseudo)

### Clase encargada de la extracción de datos

![Buffer](./pseudocode/Buffer.pseudo)

### Clase encargada de manipular la estructura de datos

![Global_Data_Structure](./pseudocode/Global_Data_Structure.pseudo)

### Clase encargada de los procesos matemáticos

![Math](./pseudocode/Math.pseudo)
