/*
*Copyright 2022 Daniel Perez Morera <daniel.perezmorera@ucr.ac.cr> CC-BY 4.0
*Imprime un hello
*/
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
    struct privateStruct structTeam[2];
    //  privateStruct structTeam2
    //  publicStruct structGeneral
    struct publicStruct structGeneral;
    //  team1->structGeneral = &structGeneral
    structTeam[0].general = &structGeneral;
    structTeam[0].teamNumber = 1;
    //  team2->structGeneral = &structGeneral
    structTeam[1].general = &structGeneral;
    structTeam[1].teamNumber = 2;
    //  structGeneral.number_Atletas = argv[1]
    if(sscanf(argv[1], "%d", &(structGeneral.number_Atletas)) == 1) {
    //  if (structGeneral.number_Atletas is impar) {
      float number_Atletas = structGeneral.number_Atletas; 
      if((number_Atletas / 2 - (int)(number_Atletas) / 2) * 2 != 0) {
        structTeam[0].result = calloc(structGeneral.number_Atletas, sizeof(double));
        structTeam[1].result = calloc(structGeneral.number_Atletas, sizeof(double));
        //  createThread team1(teams(structTeam1))
        //  createThread team2(teams(structTeam2))
        pthread_t threadTeam[2];
        for (int i = 0; i < 2; ++i){
          error = pthread_create(&threadTeam[i], /*attr*/ NULL, teams, /*arg*/ (void*)&structTeam[i]);
          if (error != EXIT_SUCCESS) {
            fprintf(stderr, "Error: could not create secondary thread\n");
            error = EXIT_FAILURE;
            break;
          }
        }
        for (int i = 0; i < 2; ++i) {
          pthread_join(threadTeam[i], /*value_ptr*/ NULL);
        }
        int pointsTeam1 = 0;
        int pointsTeam2 = 0;
        for(int i = 0; i < number_Atletas; ++i) {
          if(structTeam[0].result[i] > structTeam[1].result[i]){
            ++pointsTeam1;
          }else{
            ++pointsTeam2;
          }
        }
        if(pointsTeam1 > pointsTeam2){
          printf("result %i:%i, team 1 wins\n", pointsTeam1, pointsTeam2);
        }else{
          printf("result %i:%i, team 2 wins\n", pointsTeam1, pointsTeam2);
        }
        free(structTeam[0].result);
        free(structTeam[1].result);
      }else{
        //  print "Error: the number is not odd"
        fprintf(stderr, "Error: invalid number\n");
        error = EXIT_FAILURE;
      }
    } else {
      fprintf(stderr, "Error: invalid thread number1\n");
      error = EXIT_FAILURE;
    }
  } else {
    fprintf(stderr, "Error: there are no arguments\n");
    error = EXIT_FAILURE;
  }
  return error;
}

void* athletes(void* data);

  //  procedure teams(structTeam) {
void* teams(void* data) {
  int error;
  struct privateStruct* structTeam = (struct privateStruct*)data;
  //  for (i = 0 to *(structTeam.structGeneral.number_Atletas))
  pthread_t athlete[structTeam->general->number_Atletas];
  for(int i = 0; i < structTeam->general->number_Atletas; ++i) {
    double param = (double)structTeam->teamNumber + (double)(i+1)/10;
    while(param >= 10){
      param = param / 10;
    }
    void** paramConvers = (void**)&param;
    error = pthread_create(&athlete[i], /*attr*/ NULL, athletes, /*arg*/ *paramConvers);
    if (error != EXIT_SUCCESS) {
    fprintf(stderr, "Error: could not create secondary thread\n");
    error = EXIT_FAILURE;
    break;
    }
  }
  for (int i = 0; i < structTeam->general->number_Atletas; ++i) { 
    void* cast = 0; 
    pthread_join(athlete[i], /*value_ptr*/&cast);
    //  structTeam.result[i] = createThread(athletes(i))
    structTeam->result[i] = *(double*)&cast;//(double)data;
  }
  return 0;
}


  //  procedure athletes(i) {
void* athletes(void* data) {
  double participante = *((double*)&data);
  //  large_number = 0
  double large_number = 0;
  //  ranadom_number = 0
  double random_number = -1;
  //  for (i = 0 to 3) {
  for (int i = 0; i < 3; ++i) {
    //  ranadom_number = rand(0.0 to 25.0)
    //unsigned int* seed = (unsigned int*) &raiz;
    unsigned int* seed = (unsigned int*) &participante; 
    random_number = rand_r(seed)%2500;
    random_number = random_number/100;
    //  if(ranadom_number > large_number) {
      if(random_number > large_number) {
        //  large_number = ranadom_number
        large_number = random_number;
      }
  }
  //  print "Athleta number " i ": " large_number "m"
  printf("%.1f: best shot put %.3fm\n", participante, large_number);
  //  return large_number
  return *((void**)&large_number);
}