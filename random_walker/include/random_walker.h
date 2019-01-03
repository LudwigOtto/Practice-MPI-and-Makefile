#ifndef RANDOM_WALKER_H
#define RANDOM_WALKER_H
#include <vector>
#include "sample.h"

using namespace std;

typedef struct {
	int location;
	int left_steps;
} Walker;

class random_walker
{
	public:
		random_walker(const int world_rank, const int world_size, int domain_size, int num_walkers);
		~random_walker();
		void init_walker(vector<Walker>* buffer, int num_walkers, int max_steps);
		void move_walker(vector<Walker>* src, vector<Walker>* dst, int domain_size);
		void send_walker(vector<Walker>* buffer, sample* wrapper);
		void recv_walker(vector<Walker>* buffer, sample* wrapper);
		void dump_walker(vector<Walker>* buffer, const int world_rank);

	private:
		int subdomain_size;
		int subdomain_start;
		int _num_walkers;
};
#endif
