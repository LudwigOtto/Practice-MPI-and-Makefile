#include <stdio.h>
#include "mean_std.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

rdm_num_set::rdm_num_set(int num_per_proc) {
	size_rdm_num = num_per_proc;
	srand(time(NULL));
	while(num_per_proc-- > 0)
		set.push_back(((rand()/(float) RAND_MAX) * 100.0));
}

rdm_num_set::~rdm_num_set() {}

float rdm_num_set::compute_mean(sample* wrapper) {
	float local_sum = 0, global_sum;
	for(vector<float>::iterator num=set.begin(); num!=set.end();num++)
		local_sum += *num;
	wrapper->all_rduc_wrapper(&local_sum, 1, &global_sum);
	mean = global_sum / (size_rdm_num * wrapper->get_worldsize());
	return mean;
}

float rdm_num_set::compute_std(sample* wrapper, int root) {
	float local_diff = 0, global_diff;
	for(vector<float>::iterator num=set.begin(); num!=set.end();num++)
		local_diff += (*num-mean)*(*num-mean);
	wrapper->rduc_wrapper(&local_diff, 1, &global_diff, root);
	return (wrapper->get_rank() == root) ?
		sqrt(global_diff / (size_rdm_num * wrapper->get_worldsize())) : -1.0;
}
void rdm_num_set::dump() {
	for(vector<float>::iterator num=set.begin(); num!=set.end();num++)
		printf("Numbers; %f\n", *num);
}
