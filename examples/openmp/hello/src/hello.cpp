#include <iostream>

int main() {
  // base de OpenMP: #pragma omp
  //Las instrucciones deben estar encerradas por bloque {}
  // si solo se coloca el pragma va a parelisar la instruccion de abajo
  #pragma omp parallel
  {
    // Genera una region critica en omp(mutex), se puede nombrar mutex para
    // excluir varias regiones criticas
    #pragma omp critical(mutex1)
    {
      std::cout << "Hello form thread" << std::endl;
    }
  }
  #pragma omp parallel
  std::cout << "jijji\n";
}
