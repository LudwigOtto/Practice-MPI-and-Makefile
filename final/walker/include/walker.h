#ifndef WALKER_H
#define WALKER_H
#include <vector>
#include "sample.h"

using namespace std;

typedef struct {
	int location;
	int left_steps;
} T_Walker;

class walker
{
	public:
		walker(const int world_rank, const int world_size, int domain_size, int num_walkers);
		~walker();
		void init_walker(vector<T_Walker>* buffer, int num_walkers, int max_steps);
		void move_walker(vector<T_Walker>* src, vector<T_Walker>* dst, int domain_size);
		void send_walker(vector<T_Walker>* buffer, sample* wrapper);
		void recv_walker(vector<T_Walker>* buffer, sample* wrapper);
		void dump_walker(vector<T_Walker>* buffer, const int world_rank);

	private:
		int subdomain_size;
		int subdomain_start;
		int _num_walkers;
};
#endif
