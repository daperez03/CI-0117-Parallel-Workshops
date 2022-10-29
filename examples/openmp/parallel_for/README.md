Este ejercicio nos muestra como poder reutilizar hilos sin la necesidad de
crearlos y volverlos a destruir
Algunos pasos para esto son
1. Paralelizar un bloque de codigo con los for que se desean paralelizar

2. Crear un `pragma omp for` sobre cada for

3. Finalizar bloque de codigo paralelizado
