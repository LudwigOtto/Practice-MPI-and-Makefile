#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "sample.h"
#include "random_walker.h"

using namespace std;

int main(int argc, char** argv) {
	int domain_size = 20;
	int num_walkers = 3;
	int max_step = 40;
	//TODO user interface
	
	sample *mpi_wrapper = new sample();
	const int world_rank = mpi_wrapper->get_rank();
	const int world_size = mpi_wrapper->get_worldsize();

	if(domain_size < world_size) {
		printf("Domain size must be larger than the number of MPI processes\n");
		exit(EXIT_FAILURE);
	}
	random_walker *rw = new random_walker(world_rank, world_size, domain_size, num_walkers);
	vector<Walker> before, after;

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
