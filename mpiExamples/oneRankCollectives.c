#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* localBuf = malloc(sizeof(int) * 4);
    int *buf = NULL, *res = NULL;
    if (rank == 0) {
        buf = malloc(sizeof(int) * 16);
        res = malloc(sizeof(int) * 16);
        for (int i = 0; i < 16; i++) {
            buf[i] = i + 1;
        }
    }
    MPI_Scatter(buf, 4, MPI_INT, localBuf, 4, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < 4; i++) {
        localBuf[i] *= 2;
    }
    if (rank == 0) {
        MPI_Gather(localBuf, 4, MPI_INT, res, 4, MPI_INT, 0, MPI_COMM_WORLD);
        for (int i = 0; i < 16; i++) {
            printf("%d ", res[i]);
        }
    }
    MPI_Finalize();
}
