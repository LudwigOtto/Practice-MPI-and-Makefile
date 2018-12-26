#include <mpi.h>
#include <stdio.h>
#include "sample.h"

static int world_rank, world_size;

sample::sample()
{
	// Initialize the MPI environment
    MPI_Init(NULL, NULL);

	// Find out rank, size
	//int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	//int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
}

sample::~sample()
{
    // Finalize the MPI environment.
    MPI_Finalize();
}


void sample::simple_send_recv() {
	int number;
	if (world_rank == 0) {
		number = -1;
		MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	} else if (world_rank == 1) {
		MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
				MPI_STATUS_IGNORE);
		printf("Process 1 received number %d from process 0\n", number);
	}

}

void sample::ring_example() {
	int token;
	if(world_rank != 0) {
		MPI_Recv(&token, 1, MPI_INT, world_rank-1, 0, MPI_COMM_WORLD,
				MPI_STATUS_IGNORE);
		printf("Process %d received token %d from process %d\n",
           world_rank, token, world_rank - 1);
	}
	else
		token = -1;
	MPI_Send(&token, 1, MPI_INT, (world_rank+1)%world_size, 0, MPI_COMM_WORLD);
	
	if(world_rank == 0) {
		MPI_Recv(&token, 1, MPI_INT, world_size-1, 0, MPI_COMM_WORLD,
				MPI_STATUS_IGNORE);
		printf("Process %d received token %d from process %d\n",
				world_rank, token, world_size - 1);
	}
}

void sample::send_wrapper(int* packet, int count, int dst, int tag)
{
	MPI_Send(packet, count, MPI_INT, dst, tag, MPI_COMM_WORLD);
}

int sample::recv_wrapper(int* buffer, int src, int tag)
{
	MPI_Status status;
	int number_amount;
	MPI_Probe(src, tag, MPI_COMM_WORLD, &status);
	MPI_Get_count(&status, MPI_INT, &number_amount);
	MPI_Recv(buffer, number_amount, MPI_INT, src, tag, MPI_COMM_WORLD, &status);
	return number_amount;
}

void sample::test_wrapper()
{
	int *buffer = new int[100];
	if(world_rank != 0) {
		int count = recv_wrapper(buffer, world_rank-1, 0);
		for(int i=0; i<count; i++)
			printf("Process %d received token %d from process %d\n",
					world_rank, buffer[i], world_rank - 1);
		send_wrapper(buffer, count, (world_rank+1)%world_size, 0);
	}
	else {
		int token[3] = { 3+world_rank, 7+world_rank, 11+world_rank };
		send_wrapper(token, 3, (world_rank+1)%world_size, 0);
	}
	
	if(world_rank == 0) {
		int count = recv_wrapper(buffer, world_size-1, 0);
		for(int i=0; i<count; i++)
			printf("Process %d received token %d from process %d\n",
					world_rank, buffer[i], world_size - 1);
	}
	delete buffer;
}

