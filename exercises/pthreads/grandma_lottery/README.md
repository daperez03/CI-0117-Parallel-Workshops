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

bin/grandma_lottery
AddressSanitizer:DEADLYSIGNAL
=================================================================
==31075==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000001 (pc 0x7f00f74b3d64 bp 0x7f00f3cfee00 sp 0x7f00f3cfe588 T1)
==31075==The signal is caused by a READ memory access.
==31075==Hint: address points to the zero page.
    #0 0x7f00f74b3d63 in rand_r (/lib/x86_64-linux-gnu/libc.so.6+0x47d63)
    #1 0x7f00f76bea01 in __interceptor_rand_r ../../../../src/libsanitizer/sanitizer_common/sanitizer_common_interceptors.inc:4946
    #2 0x55e4aa6ba71a in lottery_Case1 src/grandma_lottery.c:56
    #3 0x7f00f7666608 in start_thread /build/glibc-sMfBJT/glibc-2.31/nptl/pthread_create.c:477
    #4 0x7f00f758b162 in __clone (/lib/x86_64-linux-gnu/libc.so.6+0x11f162)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (/lib/x86_64-linux-gnu/libc.so.6+0x47d63) in rand_r
Thread T1 created by T0 here:
    #0 0x7f00f76bb815 in __interceptor_pthread_create ../../../../src/libsanitizer/asan/asan_interceptors.cc:208
    #1 0x55e4aa6ba430 in main src/grandma_lottery.c:34
    #2 0x7f00f74900b2 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x240b2)

==31075==ABORTING
AddressSanitizer:DEADLYSIGNAL
make: *** [../../../common/Makefile:115: run] Error 1
