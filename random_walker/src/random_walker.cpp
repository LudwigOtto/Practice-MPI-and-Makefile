#include <stdio.h>
#include "random_walker.h"
#include <stdlib.h>
#include <time.h>

random_walker::random_walker(const int world_rank, const int world_size, int domain_size, int num_walkers)
{
	subdomain_size = domain_size / world_size;
	subdomain_start = subdomain_size * world_rank;
	_num_walkers = num_walkers;
	if(world_rank == world_size - 1)
		subdomain_size += domain_size % world_size;
}

random_walker::~random_walker() {}

void random_walker::init_walker(vector<Walker>* buffer,int num_walkers,int max_steps)
{
	srand(time(NULL));
	while(num_walkers-- > 0) {
		Walker walker;
		walker.location = subdomain_start;
		walker.left_steps = (int)((rand()/(float) RAND_MAX) * max_steps);
		buffer->push_back(walker);
	}
}

void random_walker::move_walker(vector<Walker>* src,vector<Walker>* dst,int domain_size)
{
	srand(time(NULL));
	for(vector<Walker>::iterator walker=src->begin(); walker!=src->end();walker++) {
		while(walker->left_steps > 0) {
			int move = (int)((rand()/(float) RAND_MAX) * subdomain_size);
			if(move < walker->left_steps)
				walker->left_steps -= move;
			else
				walker->left_steps = 0;
			int dist_to_end = subdomain_size-(walker->location-subdomain_start)-1;
			if(walker->location + move < domain_size)
				walker->location += move;
			else
				walker->location = move - dist_to_end - 1;
			if(move > dist_to_end) {
				dst->push_back(*walker);
				break;
			}
		}
	}
}

void random_walker::send_walker(vector<Walker>* buffer, sample* wrapper)
{
	 wrapper->send_wrapper((void*)buffer->data(), buffer->size() * sizeof(Walker),
             (wrapper->get_rank() + 1) % wrapper->get_worldsize(), 0);
    buffer->clear();
}

void random_walker::recv_walker(vector<Walker>* buffer, sample* wrapper)
{
	int src = (wrapper->get_rank() == 0)
			? wrapper->get_worldsize() -1 : wrapper->get_rank()-1;
	if(buffer->empty())
		buffer->resize(_num_walkers);
	int num_packets = wrapper->recv_wrapper((void*)buffer->data(), src, 0);
	if(num_packets == 0)
		buffer->clear();
}


void random_walker::dump_walker(vector<Walker>* buffer, const int world_rank)
{
	printf("rank: %d\n", world_rank);
	for(vector<Walker>::iterator walker=buffer->begin(); walker!=buffer->end();walker++) {
		printf("\t location: %d, steps: %d\n", walker->location, walker->left_steps);
	}
}
