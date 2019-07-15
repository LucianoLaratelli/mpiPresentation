#include <mpi.h>

int main(int argc, char ** argv){
  MPI_Init(&argc, &argv);
  int size; MPI_Comm_size(MPI_COMM_WORLD, &size);
  int rank; MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Recv(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, 0);
  MPI_Finalize();
}
