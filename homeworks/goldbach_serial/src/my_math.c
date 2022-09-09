#include "my_math.h"
//#include "Global_Data_Structure.h"

struct tools{
  uint64_t* array_prime_number;
  uint64_t size;
  uint64_t iterator;
};

void numPrimos(struct tools* basic_tools, struct data_struct* data);
void combinaciones(struct tools* basic_tools, struct data_struct* local_data);

uint64_t solve(struct global_data_struct* global_data){
  uint64_t error = EXIT_SUCCESS;
	for (uint64_t i = 0; i < global_data->iterator && error == EXIT_SUCCESS; ++i) {
		struct data_struct local_data = global_data->data_structure_array[i];
		struct tools basic_tools;
		basic_tools.iterator = 0;
		basic_tools.size = local_data.number/2;
		basic_tools.array_prime_number = (uint64_t*)calloc(basic_tools.size, sizeof(uint64_t));
		if (basic_tools.array_prime_number) {
			numPrimos(&basic_tools, &local_data);
      combinaciones(&basic_tools, &local_data);
			free(basic_tools.array_prime_number);
		}else{
			fprintf(stderr, "Error: No work space\n");
      error = 31;
		}
	}
  return error;
}

void numPrimos(struct tools* basic_tools, struct data_struct* local_data){
	bool is_prime = true;
	for (uint64_t prime_number = 0; prime_number < local_data->number; ++prime_number) {
		for (uint64_t i = 0; i < pow(prime_number, 1/2) + 1 && is_prime; ++i) {
			if (local_data->number - ((uint64_t)(local_data->number / 2)) * 2 == 0) {
				is_prime = false;
			}
		}
		if (is_prime) {
			basic_tools->array_prime_number[basic_tools->iterator++] = prime_number;
		}
	}
}

void combinaciones(struct tools* basic_tools, struct data_struct* local_data){
	if (local_data->number - ((uint64_t)(local_data->number / 2)) * 2 == 0) {
		for (uint64_t i = 0; i < basic_tools->iterator; ++i) {
			// for(j = i to tools->iterator)
			for (uint64_t j = i; j < basic_tools->iterator; ++j) {
				if (local_data->number == basic_tools->array_prime_number[i] + basic_tools->array_prime_number[j]) {
					++local_data->result[0];
					local_data->result[local_data->iterator_of_result++] = basic_tools->array_prime_number[i];
					local_data->result[local_data->iterator_of_result++] = basic_tools->array_prime_number[j];
				}
			}
		}
	} else {
		for (uint64_t i = 0; i < basic_tools->iterator; ++i) {
			for (uint64_t j = i; j < basic_tools->iterator; ++j) {
				for (uint64_t h = j; h < basic_tools->iterator; ++h) {
					if (local_data->number == basic_tools->array_prime_number[i]
						+ basic_tools->array_prime_number[j] + basic_tools->array_prime_number[h]) {
					++local_data->result[0];
					local_data->result[local_data->iterator_of_result++] = basic_tools->array_prime_number[i];
					local_data->result[local_data->iterator_of_result++] = basic_tools->array_prime_number[j];
					local_data->result[local_data->iterator_of_result++] = basic_tools->array_prime_number[h];
					}
				}
			}
		}
	}
}