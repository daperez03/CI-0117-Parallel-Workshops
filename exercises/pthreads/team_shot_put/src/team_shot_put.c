#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#if 0
struct privateStruct{
  publicStruct* general
  result[]
}

struct publicStruct{
  number_Atletas
}

procedure main(argc, argv[]) {
  privateStruct structTeam1
  privateStruct structTeam2
  publicStruct structGeneral
  team1->structGeneral = &structGeneral
  team2->structGeneral = &structGeneral
  structGeneral.number_Atletas = argv[1]
  error = false
  if (structGeneral.number_Atletas is impar) {
      createThread team1(teams(structTeam1))
      createThread team2(teams(structTeam1))
  } else {
      print "Error: the number is not odd"
  }
}

procedure teams(structTeam) {
  for (i = 0 to *(structTeam.structGeneral.number_Atletas)) {
      structTeam.result[i] = createThread(athletes(i))
  }
}

procedure athletes(i) {
  large_number = 0
  ranadom_number = 0
  for (i = 0 to 3) {
      ranadom_number = rand(0.0 to 25.0)
      if(ranadom_number > large_number) {
          large_number = ranadom_number
      }
  }
  print "Athleta number " i ": " large_number "m"
  return large_number
}
#endif

void* teams(void* data);

  //  struct publicStruct{
struct publicStruct
{
  //  number_Atletas
  int number_Atletas;
  //  }
};


  //  struct privateStruct{
struct privateStruct
{
  //  publicStruct* general
  struct publicStruct* general;
  //  result[]
  int teamNumber;
  double* result;
  //  }
};

  //  procedure main(argc, argv[]) {
int main(int argc, char* argv[]){
  //  error = false
  int error = EXIT_SUCCESS;
  if(argc > 1){

    //  privateStruct structTeam1
    struct privateStruct structTeam1;
    //  privateStruct structTeam2
    struct privateStruct structTeam2;
    //  publicStruct structGeneral
    struct publicStruct structGeneral;
    //  team1->structGeneral = &structGeneral
    structTeam1.general = (const)&structGeneral;
    structTeam1.teamNumber = 1;
    //  team2->structGeneral = &structGeneral
    structTeam2.general = (const)&structGeneral;
    structTeam2.teamNumber = 2;
    //  structGeneral.number_Atletas = argv[1]
    if(sscanf(argv[1], "%d", &(structGeneral.number_Atletas)) == 1) {
    //  if (structGeneral.number_Atletas is impar) {
      if((double)(structGeneral.number_Atletas % 2) - (int)(structGeneral.number_Atletas % 2) != 0) {
        //  createThread team1(teams(structTeam1))
        //  createThread team2(teams(structTeam2))
        pthread_t threadTeam[2];
        for (int i = 0; i < 2; ++i){
          error = pthread_create(&threadTeam[i], /*attr*/ NULL, teams, /*arg*/ (void*)&structTeam1);
          if (error != EXIT_SUCCESS) {
            fprintf(stderr, "Error: could not create secondary thread\n");
            error = EXIT_FAILURE;
            break;
          }
        }
        for (int i = 0; i < 2; ++i) {
          pthread_join(threadTeam[i], /*value_ptr*/ NULL);
        }
      }else{
        //  print "Error: the number is not odd"
        fprintf(stderr, "Error: invalid number\n");
        error = EXIT_FAILURE;
      }
    } else {
      fprintf(stderr, "Error: invalid thread number\n");
      error = EXIT_FAILURE;
    }
  } else {
    error = EXIT_FAILURE;
  }
  return error;
}

  //  procedure teams(structTeam) {
void* teams(void* data) {
  struct privateStruct* structTeam = data;
  //  for (i = 0 to *(structTeam.structGeneral.number_Atletas))
  pthread_t athlete[number_Atletas2];
for (int i = 0; i < 2; ++i) {
  pthread_join(threadTeam[i], /*value_ptr*/ NULL);
}
  for(int i = 0; i < structTeam->number_Atletas, ++i) {
    error = pthread_create(&athlete[i], /*attr*/ NULL, teams, /*arg*/ (void*) );
    if (error != EXIT_SUCCESS) {
    fprintf(stderr, "Error: could not create secondary thread\n");
    error = EXIT_FAILURE;
    break;
}
  //  structTeam.result[i] = createThread(athletes(i))
  //  }
  }
}

  //  procedure athletes(i) {
void* athletes(void* data) {
  //  large_number = 0
  //  ranadom_number = 0
  //  for (i = 0 to 3) {
  //  ranadom_number = rand(0.0 to 25.0)
  //  if(ranadom_number > large_number) {
  //  large_number = ranadom_number
  //  }
  //  }
  //  print "Athleta number " i ": " large_number "m"
  //  return large_number
  //  }
}