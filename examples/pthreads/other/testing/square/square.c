#include <stdio.h>
/*
* @brief eleva a la dos
* @return long long numero elevado a la dos 
*/
long long square(long long number) {
 return number * number;
}

int main(void) {
  File* input = stdin;//asigna como archivo a la entrada estandar
  File* output = stdout;//contendra el archivo de salida
  long long value = 0ll;//Variable que almacenara contenido de input
  while (fscanf(input, "%lld", &value) == 1) {//lee archivo  long long y lo almacena en value
    fprintf(output, "%lld\n", square(value));//envia a output contenido del metodo square
  }
return 0;
}
