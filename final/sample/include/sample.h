#ifndef SAMPLE_H
#define SAMPLE_H

class sample 
{
	public:
		sample();
		~sample();
		
		void simple_send_recv();
		void ring_example();

		void send_wrapper(void* packet, int count, int dst, int tag);
		int recv_wrapper(void* buffer, int src, int tag);
		void sync_wrapper();
		void bcst_wrapper(void* data, int count, int root);
		void sctr_wrapper(void* src, int s_cnt, void* dst, int r_cnt, int root);
		void gatr_wrapper(void* src, int s_cnt, void* dst, int r_cnt, int root);
		void rduc_wrapper(void* src, int cnt, void* dst, int root);
		void all_rduc_wrapper(void* src, int cnt, void* dst);

		int get_typesize();
		const int get_rank();
		const int get_worldsize();
		void stop();

	private:
};

#endif
