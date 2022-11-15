/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*/

#include <unistd.h>
#include "buffer.h"
#include "goldbach_sums.h"
#include "Mpi.h"
#include "my_math.h"

#define is_error(x) x != EXIT_SUCCESS
#define absoluteValue(x) x < 0? x * -1 : x

uint64_t assembly(goldbach_sums_t* my_goldbach_sums, mpi_data_t* my_process_data);
uint64_t calculator(mpi_data_t* my_process_data);

/**
 * @brief Main funtion
 * @param argc Argument counter
 * @param argv Arguments
 * @return An error code
 */
int main(int argc, char* argv[]) {  //  function main(argv[])
  uint64_t error = EXIT_SUCCESS;
  mpi_data_t my_process_data;
  error = init_mpi(&my_process_data, &argc, &argv);
  if (!is_error(error)) {
    size_t threads_number = sysconf(_SC_NPROCESSORS_ONLN);
    if (argc == 2) {
      //  define threads_number := argv[1]
      if (sscanf(argv[1], "%" SCNu64, &threads_number) != 1) {
        fprintf(stderr , "Error: invalid thread count\n");
        error = 11;
      }
    }
    if (!is_error(error)) {
      if (my_process_data.process_number == 0) {
        //  create goldbach_sums_t my_goldbach_sums
        goldbach_sums_t my_goldbach_sums;
        error = init_goldbach_sums(&my_goldbach_sums);
        if (!is_error(error)) {
          read_data(&my_goldbach_sums);
          my_process_data.pending_process =
            (my_process_data.process_count - 1) * threads_number;
          --my_process_data.pending_process;
          assembly(&my_goldbach_sums, &my_process_data);
          result(&my_goldbach_sums);
          destroy_goldbach_sums(&my_goldbach_sums);
        }
      } else {
        calculator(&my_process_data);
      }
    }
  }
  return error;
}

uint64_t assembly(goldbach_sums_t* my_goldbach_sums
  , mpi_data_t* my_process_data) {

  assert(my_process_data);
  assert(my_goldbach_sums);

  uint64_t error = EXIT_SUCCESS;
  int32_t id_pending_process = 0;
  size_t pending_solution = 0;
  ssize_t pending_process = (ssize_t)my_process_data->process_count - 1;
  bool stopping_condition = false;
  bool salir = false;


  while (!salir) {

    // Se obtiene proceso con peticion de trabajo
    printf("assembly: Espero un proceso\n");
    error = receive_int32_t(&id_pending_process, 1
      , MPI_ANY_SOURCE, TAG_ID_PROCESS);
    printf("assembly: Recivo proceso %d\n", id_pending_process);

    // Se asigna una posicion de trabajo
    pending_solution = my_goldbach_sums->solution_count++;

    // Si esa posicion es mayor al trabajo total, entoces se indica que no hay mas trabajo
    if (!(pending_solution < my_goldbach_sums->count)) {

      stopping_condition = true;
      error = send_bool(&stopping_condition, id_pending_process, TAG_STOPPING_CONDITION);
      printf("assembly: Envio BOOL = TRUE\n");

      // Si el numero de prosesos pendientes es menor o igual a 0 se sale del ciclo
      if (--pending_process <= 0 ) {
        printf("assembly: Finalizo mi proceso\n");
        salir = true;
      }

    } else {
      // Si existe trabajo entonces se le indica al proceso
      error = send_bool(&stopping_condition, id_pending_process, TAG_STOPPING_CONDITION);
      printf("assembly: Envio BOOL = False\n");
      // Se envia datos para trabajar
      int64_t data_report[2] = {pending_solution
        , my_goldbach_sums->numbers[pending_solution].number};
      error = send_int64_t(data_report, 2, id_pending_process, TAG_DATA_REPORT);
      printf("assembly: Envio index = %ld, numero = %ld\n", data_report[0], data_report[1]);
    }
  }
  MPI_Status status;
  for (size_t index = 0; index < my_goldbach_sums->count; ++index) {
    int64_t data_report[2] = {0};

    // Se recive la capacidad de un dato
    error = receive_int64_t(data_report, 2, MPI_ANY_SOURCE
      , TAG_DATA_REPORT, &status);
    printf("assembly: proceso %d, posicion = %ld, count = %ld\n", status.MPI_SOURCE, data_report[0], data_report[1]);

    // se amolda el contenedor respecto a ese dato
    number_t* current_number = &my_goldbach_sums->numbers[data_report[index_data]];
    current_number->capacity = data_report[count_data];
    current_number->sum_count = data_report[count_data];
    current_number->sums = (uint64_t*) malloc(data_report[count_data] * sizeof(uint64_t));

    // Se obtienen los datos
    error = receive_uint64_t(current_number->sums
      , data_report[count_data], status.MPI_SOURCE, TAG_DATA);
    printf("assembly:Recivo los datos\n");
  }
  return error;
}

uint64_t calculator(mpi_data_t* my_process_data) {
  assert(my_process_data);
  bool stopping_condition = false;

  while (true) {

    // Se realiza una peticion de datos a este proceso
    send_int32_t(&my_process_data->process_number
      , 1, 0, TAG_ID_PROCESS);
    printf("calculator %d: Pido un dato\n", my_process_data->process_number);

    // Se obtiene la respuesta de la peticion
    receive_bool(&stopping_condition, 0, TAG_STOPPING_CONDITION);
    printf("calculator %d: BOOL = %d\n", my_process_data->process_number,stopping_condition);

    if (stopping_condition) {
      // Si no hay mas datos nos salimos del loop
      break;
    } else {
      // Si hay datos entonces los obtenemos
      int64_t data_report[2] = {0};

      // Se obtienen los datos
      receive_int64_t(data_report, 2, 0, TAG_DATA_REPORT, MPI_STATUS_IGNORE);
      printf("calculator %d: count = %ld, number = %ld\n"
        , my_process_data->process_number, data_report[0], data_report[1]);

      // Se trabajan los datos
      number_t my_number;
      init_number_t(&my_number);
      my_number.number = data_report[number_data];
      printf("calculator %d: Ingreso a solve\n", my_process_data->process_number);
      solve(&my_number);
      printf("calculator %d: Resuelvo suma\n", my_process_data->process_number);
      if (data_report[number_data] > 0) {
        data_report[count_data] = 1;
      } else {
        data_report[count_data] = my_number.sum_count;
      }
      // se envian los datos resueltos
      // Primero se envia info sobre los datos
      send_int64_t(data_report, 2, 0, TAG_DATA_REPORT);
      printf("calculator %d: Envia reporte de los datos\n", my_process_data->process_number);
      // Se envia solucion
      send_uint64_t(my_number.sums, data_report[count_data], 0, TAG_DATA);
      printf("calculator %d: Envia los datos\n", my_process_data->process_number);
      // Destruye el trabajo ya no ocupado
      destroy_numbert_t(&my_number);
    }
  }
  return EXIT_SUCCESS;
}