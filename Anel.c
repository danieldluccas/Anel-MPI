#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	//inicializa o MPI
	MPI_Init(NULL, NULL);

	//define numero de processos
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	//define o rank dos processos
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	//Print processo
	//printf("Rank %d"" de %d processos\n", world_rank+1, world_size);
	time_t t;
	
	int valor = 0;
	if (world_rank == 0){
		// define valor
		srand((unsigned) time(&t));
		valor = valor +  rand()%1000;
		printf ("valor = %d\n",valor);
	}
	
	
	
	//mensagem recebida se processo rank != 0
	else if (world_rank != 0) {
		MPI_Recv(&valor, 1, MPI_INT, world_rank - 1, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Processo %d recebeu valor %d do processo %d\n",world_rank, valor, world_rank - 1);
	}
	valor = valor + world_rank; 
	MPI_Send(&valor, 1, MPI_INT, (world_rank + 1) % world_size,	0, MPI_COMM_WORLD);
	//recebendo a mensagem do ultimo processo
	if (world_rank == 0) {
		MPI_Recv(&valor, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Processo %d recebeu valor %d do processo %d\n",world_rank, valor, world_size - 1);
	}

	//Finaliza
	MPI_Finalize();
}
