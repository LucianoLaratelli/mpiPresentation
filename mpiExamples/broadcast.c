#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int rank, buf;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0) {
    buf = 777;
  }

  printf("rank %d, buf is %d\n", rank, buf);
  // everyone calls bcast, data is taken from root and ends up in everyone's buf
  MPI_Bcast(&buf, 1, MPI_INT, 0, MPI_COMM_WORLD);

  printf("rank %d, buf is %d\n", rank, buf);

  MPI_Finalize();
  return 0;
}
