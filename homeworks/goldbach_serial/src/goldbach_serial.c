#include "buffer.h"
#include "goldbach_sums.h"
#include "my_math.h"

int main(){
    uint64_t error = EXIT_SUCCESS;
    goldbach_sums_t my_goldbach_sums;
    error = init(&my_goldbach_sums);
    if (error == EXIT_SUCCESS){
        error = readData(&my_goldbach_sums);
        if (error == EXIT_SUCCESS) {
            error = solve(&my_goldbach_sums);
            if (error == EXIT_SUCCESS){
                resume(&my_goldbach_sums);
                destroy(&my_goldbach_sums);
            }
        }
    }
    return error;
}