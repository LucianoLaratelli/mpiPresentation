



#include <mpi.h>
#include <stdio.h>

int main(int argc, char ** argv) {
  MPI_Init(&argc, &argv);
  int rank;
  int size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int number = rank * 72;
  MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  if(rank == 0){
    for(int i = 0; i < size; i++){
      MPI_Recv(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("received %d from process with rank %d\n", number, i);
    }
  }
  MPI_Finalize();
  return 0;
}
