# Ejercicio 27 [network_simul_bounded]

## Enunciado
Modifique la simulación de red para recibir en un argumento de línea de comandos la capacidad máxima de
paquetes que cabe en cada cola de la simulación. Modifique la plantilla Queue para que represente un
buffer acotado. Sugerencia, agregue un semárofo canProduce que se inicialice en esta capacidad indicada
por el usuario en el constructor de la cola. Si este número no se provee, suponga el número más grande
que cabe en una variable unsigned.

Corra su simulación de red con dieferentes límites en las colas ¿Se afecta el tiempo de ejecución?

Si, solo que es mas notable cuuando la cantidad de paquetes es alta y el capacidad de la cola es poca
