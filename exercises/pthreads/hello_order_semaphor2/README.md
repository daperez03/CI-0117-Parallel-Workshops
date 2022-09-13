# Enunciado

Modifique su solución de Ejemplo 7 para inicializar todos los semáforos en 0. Luego haga que el hilo principal incremente el semáforo del hilo 0.

¿Produce el mismo resultado que su solución anterior?

No, se imprime primero en el hilo principal

¿Qué pasa si el hilo principal incrementa el semáforo del hilo 0 después de hacer su saludo Hello from main thread?

Se activa el semaforo de este y se genera una cadena con los demas hilos y sus impresiones, por ende las impresiones se vuelven seriales