# Ejercicio 16 [sem_vs_condsafe]

## Enunciado

Ejecute al menos tres veces los códigos de Ejemplo 7 (imprimir en orden con semáforos)
y Ejemplo 8 (imprimir en orden con seguridad condicional) con tantos hilos como su
sistema operativo permite. Reporte en su readme.md las tres duraciones de cada solución.
Tome la menor duración de las tres corridas de cada versión. 

| Ejemplo 7 | Ejemplo 8  |
|---------- | ---------- |
| 0.613794s | 0.999974s  |	
| 0.155981s | 0.981874s  |
| 0.168082s | 0.939212s  |

¿Cuál solución realiza su trabajo en menor tiempo?

La solucion del Ejemplo 7

Discuta en máximo un párrafo cuál podría ser la causa de este comportamiento.

Posiblemente esto ocurre ya que la solucion 7 evita la manipulacion de memoria,
contrario a lo que el ejemplo 8 si ocupa, principalmente en los vectors, eso sin 
entrar en detalle sobre los tiempos para almacenar y retirar esos datosa, otro
tema el cual se puede vincular a este suceso es que impresion del ejercicio 8
fue realizada unicamente por un hilo.
