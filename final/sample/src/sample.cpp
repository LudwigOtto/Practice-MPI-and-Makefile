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

void sample::send_wrapper(void* packet, int count, int dst, int tag)
{
	MPI_Send(packet, count, MPI_BYTE, dst, tag, MPI_COMM_WORLD);
}

int sample::recv_wrapper(void* buffer, int src, int tag)
{
	MPI_Status status;
	int number_amount;
	MPI_Probe(src, tag, MPI_COMM_WORLD, &status);
	MPI_Get_count(&status, MPI_BYTE, &number_amount);
	MPI_Recv(buffer, number_amount, MPI_BYTE, src, tag, MPI_COMM_WORLD, &status);
	return number_amount;
}

void sample::sync_wrapper()
{
	MPI_Barrier(MPI_COMM_WORLD);
}

void sample::bcst_wrapper(void* data, int count, int root)
{
	MPI_Bcast(data, count, MPI_BYTE, root, MPI_COMM_WORLD);
}

void sample::sctr_wrapper(void* src, int s_cnt, void* dst, int r_cnt, int root)
{
	MPI_Scatter(src, s_cnt, MPI_BYTE, dst, r_cnt, MPI_INT, root, MPI_COMM_WORLD);
}

void sample::gatr_wrapper(void* src, int s_cnt, void* dst, int r_cnt, int root)
{
	MPI_Gather(src, s_cnt, MPI_BYTE, dst, r_cnt, MPI_INT, root, MPI_COMM_WORLD);
}
void sample::rduc_wrapper(void* src, int cnt, void* dst, int root)
{
	MPI_Reduce(src, dst, 1, MPI_FLOAT, MPI_SUM, root, MPI_COMM_WORLD);
}

void sample::all_rduc_wrapper(void* src, int cnt, void* dst)
{
	MPI_Allreduce(src, dst, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
}

int sample::get_typesize()
{
	int size;
	MPI_Type_size(MPI_INT, &size);
	return size;
}

const int sample::get_rank()
{
	return world_rank;
}

const int sample::get_worldsize()
{
	return world_size;
}

void sample::stop()
{
	MPI_Abort(MPI_COMM_WORLD, 1);
}


