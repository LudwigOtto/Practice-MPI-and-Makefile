#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "sample.h"
#include "walker.h"
#include "mean_std.h"

using namespace std;

void random_walk() {
	int domain_size = 20;
	int num_walkers = 3;
	int max_step = 40;
	
	sample *mpi_wrapper = new sample();
	const int world_rank = mpi_wrapper->get_rank();
	const int world_size = mpi_wrapper->get_worldsize();

	if(domain_size < world_size) {
		printf("Domain size must be larger than the number of MPI processes\n");
		exit(EXIT_FAILURE);
	}
	walker *rw = new walker(world_rank, world_size, domain_size, num_walkers);
	vector<T_Walker> before, after;

	if(world_rank == 0)
		rw->init_walker(&before, num_walkers, max_step);

	for(int step=0; step < (max_step/(domain_size/world_size)); step++) {
		if(before.size() > 0)
			rw->move_walker(&before, &after, domain_size);

		if(world_rank % 2 == 0) {
			rw->send_walker(&after, mpi_wrapper);
			rw->recv_walker(&before, mpi_wrapper);
		}
		else {
			rw->recv_walker(&before, mpi_wrapper);
			rw->send_walker(&after, mpi_wrapper);
		}
		if(before.size() > 0)
			rw->dump_walker(&before, world_rank);
	}

	delete mpi_wrapper;
	delete rw;
}

void ring() {
	sample *func = new sample();
	func->ring_example();
	delete func;
}

void mean_std() {
	sample *mpi_wrapper = new sample();
	int num_per_proc = 10;
	rdm_num_set *rns = new rdm_num_set(num_per_proc);
	float mean = rns->compute_mean(mpi_wrapper);
	float std = rns->compute_std(mpi_wrapper, 0);
	rns->dump();
	mpi_wrapper->sync_wrapper();
	if(mpi_wrapper->get_rank() == 0) {
		printf("Mean of Random Dataset: %f\n", mean);
		printf("Standard Deviation: %f\n", std);
	}
	delete mpi_wrapper;
	delete rns;
}

void help() {
	sample *mpi_wrapper = new sample();
	if(mpi_wrapper->get_rank() == 0) {
		printf("r: demonstrate ring\n");
		printf("w: demonstrate random walk\n");
		printf("p: demonstrate parallel rank\n");
		printf("m: compute mean and standard deviation with MPI reduce\n");
		printf("h: show help\n");
	}
	delete mpi_wrapper;
}

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Please specify the test item\n");
		help();
		exit(EXIT_FAILURE);
	}
	switch(*(argv[1])) {
		case 'r':
			ring();
			break;
		case 'w':
			random_walk();
			break;
		case 'm':
			mean_std();
			break;
		default:
			help();
	}
	exit(EXIT_SUCCESS);
}
