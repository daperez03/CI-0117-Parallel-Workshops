# Enunciado:

Una adorable abuelita juega todos los domingos lotería. Como es peligroso que ella salga de casa, envía a sus dos nietos a comprar un par de pedacitos a vendedores diferentes para incrementar la suerte. Ella siempre juega a "gallo tapado", es decir, sin saber el número que le venden. Sin embargo, cuando sus nietos llegan a la casa, por su cansado estado de la vista ella les tiene que preguntar el número que los vendedores le dieron a cada uno.

Modele la situación anterior, con la abuela como el hilo principal, y los dos nietos como dos hilos secundarios. Los nietos generan un número pseudoaleatorio para representar la compra de la fracción de lotería. La espera de la abuela del regreso a casa de los dos nietos es representado por su join. Los nietos comunican a la abuela los números obtenidos a través del valor de retorno de la rutina secundaria. Indague en la documentación de Pthreads cómo este valor es recuperado por pthread_join(). Implemente dos variantes en que los nietos comunican este valor a la abuela:

1. Retornan la dirección de memoria de la variable que tiene el número comprado.

2. Retornan el número comprado como una falsa dirección de memoria.

Utilice las herramientas de análisis dinámico de código para determinar cuál de las dos variantes anteriores produce el resultado correcto.

# Resultado

## Salida esperada:

Boleto 1: 14
Boleto 2: 68

## Salida correcta:

Boleto 1: 14
Boleto 2: 68

## Salida incorrecta:

c15906@ECCI104L408200:~/Documents/concurrente22b-daniel_perez/exercises/pthreads/grandma_lottery$ make
mkdir -p build/
gcc -c -Wall -Wextra -pthread -g -std=gnu11 -Isrc -MMD src/grandma_lottery.c -o build/grandma_lottery.o
src/grandma_lottery.c: In function ‘loterry_Case1’:
src/grandma_lottery.c:53:10: warning: function returns address of local variable [-Wreturn-local-addr]
   53 |   return (void*)(&number);  //  Devuelve el numero generado
      |          ^~~~~~~~~~~~~~~~
mkdir -p bin/
gcc -Wall -Wextra -pthread -g -Isrc build/grandma_lottery.o -o bin/grandma_lottery 
c15906@ECCI104L408200:~/Documents/concurrente22b-daniel_perez/exercises/pthreads/grandma_lottery$ make run
bin/grandma_lottery
make: *** [../../../common/Makefile:115: run] Segmentation fault (core dumped)