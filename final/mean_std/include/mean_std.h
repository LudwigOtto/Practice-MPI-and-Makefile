#ifndef MEAN_STD_H
#define MEAN_STD_H
#include <vector>
#include "sample.h"

using namespace std;

class rdm_num_set
{
	public:
		rdm_num_set(int num_per_proc);
		~rdm_num_set();
		float compute_mean(sample* wrapper);
		float compute_std(sample* wrapper, int root);
		void dump();

	private:
		int size_rdm_num;
		float mean;
		vector<float> set;
};
#endif
