# Ejercicio 64 [mpi_reduce_send_recv]

Implemente la reducción de la Ejemplo 52 con operaciones de send y receive. Su solución no debe hacer un envío de todos los procesos al receptor directamente, dado que no es eficiente. Su solución debe realizar un árbol binario de envíos de la misma forma que MPI_Reduce() trabaja. Es decir, los procesos envían a otros intermediarios quienes realizan la operación de reducción, y éstos a su vez la envían a otros intermediarios, hasta que finalmente el valor resultante queda en el proceso receptor.

Nota: Este ejercicio tiene una complejidad alta y se recomienda idear un modelo solución antes de implementarlo.