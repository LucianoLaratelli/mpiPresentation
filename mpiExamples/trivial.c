



#include <mpi.h>

int main(int argc, char ** argv){
  MPI_Init(&argc, &argv);
  //ALL OTHER MPI CALLS GO HERE
  MPI_Finalize();
}



