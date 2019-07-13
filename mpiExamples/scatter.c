#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void vecAdd(int *result, int *lhs, int *rhs, int size) {
  for(int i = 0; i < size; i++){
    result[i] = lhs[i] + rhs[i];
  }
}

int main(int argc, char ** argv) {
  MPI_Init(&argc, &argv);

  int rank; MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size; MPI_Comm_size(MPI_COMM_WORLD, &size);
  int vecSize = (argc > 1) ? atoi(argv[1]) : 16;


  int *localA = (int*)malloc(sizeof(int) * vecSize / size);
  int *localB = (int*)malloc(sizeof(int) * vecSize / size);
  int *localResult = (int*)malloc(sizeof(int) * vecSize / size);
  int *a = NULL, *b = NULL, *result = NULL;


  if(rank == 0) {
    a = (int*)malloc(vecSize * sizeof(int));
    b = (int*)malloc(vecSize * sizeof(int));
    result = (int*)malloc(vecSize * sizeof(int));
    for(int i = 0; i < vecSize; i++){
      a[i] = i;
      b[i] = i * 2;
    }
  }

  MPI_Scatter(a, vecSize/size, MPI_INT, localA, vecSize/size, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(b, vecSize/size, MPI_INT, localB, vecSize/size, MPI_INT, 0, MPI_COMM_WORLD);

  vecAdd(localResult, localA, localB, vecSize/size);

  MPI_Gather(localResult, vecSize/size, MPI_INT, result, vecSize/size, MPI_INT, 0, MPI_COMM_WORLD);

  if(rank == 0){
    printf("A: %d %d %d %d\n", a[0], a[1], a[2], a[3]);
    printf("B: %d %d %d %d\n", b[0], b[1], b[2], b[3]);
    printf("C: %d %d %d %d\n", result[0], result[1], result[2], result[3]);
    free(a);
    free(b);
    free(result);
  } else {
    free(localA);
    free(localB);
    free(localResult);
  }

  MPI_Finalize();
  return 0;
}
