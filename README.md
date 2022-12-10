# concurrente22b-daniel_perez

Repositorio individual para ejercicios, tareas y ejemplos de Programación paralela y concurrente l l - 2022

## Glosario

### Programación serial

Paradigma de programación el cual ejecuta tareas una tras otra
    
### Programación concurrente

Lo opuesto a serial, puede ejecutar múltiples tareas y es un macroparadigma

### Programación paralela

Paradigma de programación que ejecuta varias tareas al mismo tiempo, es una forma de concurrencia

### Concurrencia de tareas

Utiliza el paradigma de concurrencia para resolver varias tareas de manera paralela o intercalada

### Paralelismo de datos

Son estructuras de datos que se crean para que cada hilo de ejecución contenga un espacio
no compartido de memoria y no genere ningún conflicto con los demás datos y hilos

### Hilo de ejecución

Es un arreglo de valores que él OS carga en los registros de una CPU y permiten
ejecutar código en ella

### Indeterminismo

Es cuando no se puede predecir el orden en que se va a ejercer de un hilo de
ejecución respecto a otro

### Memoria privada y compartida

La memoria privada es cuando se crea un espacio en la memoria a la cual únicamente dejaremos que acceda
la subrutina o hilo, lo cual sería opuesto a la memoria compartida la cual está establecida para que
todos tengan acceso

### Espera activa

Sucede cuando se ejecuta hilo, el cual está dormido o enciclado, por lo que este inicia una espera
dentro de la cpu en lugar a pasar a un modo de espera

### Condición de carrera

Es la inestabilidad de un resultado, dado por la modificación y lectura de distintos hilos a una
variable compartida

### Control de concurrencia

Mecanismos los cuales controlan a los hilos para que estos trabajen de una forma sincronizada

### Seguridad condicional

Es la creación de programas concurrentes sin necesidad a recurrir al control de recurrencia

### Exclusión mutua

Es la separación de varias regiones de ejecución concurrente para la ejecución de un único hilo el cual
implica al resto

### Semáforo

Es un indicador de paso para los hilos el cual cuenta con tres estados y cada hilo puede generar un
decremento o incremento al mismo

### Barrera

Control de concurrencia, el cual asegura la instancia de todos los hilos sobre una parte del
código.

### Variable de condición

Mecanismo el cual permite detener los hilos, generando así concurrencia de tareas. Estos se pueden comunicar
mediantes un signal(detiene a un solo hilo) o broadcast(detiene a todos los hilos).

### Candado de lectura y escritura

Es análogo a un mutex, con la excepción que a los hilos de lectura pueden ingresar todos al mismo tiempo
a la región crítica, siempre y cuando no haya ningún hilo de escritura en la región crítica.

### Descomposición

Forma en la cual se puede repartir trabajo entre distintos trabajadores. Esto es útil para poder asignarle
a los hilos y procesos, segmentos de trabajo.

### Mapeo

Forma en la cual se reparte trabajo entre trabajadores(hilos), alguno de estos son: dinámicos,
cíclicos y por bloque.

### Incremento de velocidad

Es el aumento de velocidad de un código respecto a otro.

### Comunicación punto a punto entre procesos

Comunicación de un proceso a otro, usualmente usado para repartir trabajo
o respectivamente su solución.

### Comunicación colectiva entre procesos

Comunicación entre todos los procesos que pertenecen a un mundo en específico. Usualmente
utilizado para datos comunes entre todos los procesos.

### Reducción

Reduce algunas operaciones a nivel global de los procesos. Para esto utiliza un sistema de árbol
para lograr un objetivo en común. Por ejemplo, el número mayor o menor de todos los procesos.
