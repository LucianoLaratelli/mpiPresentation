#include <mpi.h>
#include <stdio.h>

int main(int argc, char ** argv) {
  MPI_Init(&argc, &argv);

  int worldSize;
  int rank;

  MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  printf("Hello from rank %d out of %d processors\n", rank, worldSize);

  MPI_Finalize();
}
