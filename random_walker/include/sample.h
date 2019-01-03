#ifndef SAMPLE_H
#define SAMPLE_H

class sample 
{
	public:
		sample();
		~sample();
		
		void simple_send_recv();
		void ring_example();
		//void test_wrapper();

		void send_wrapper(void* packet, int count, int dst, int tag);
		int recv_wrapper(void* buffer, int src, int tag);
		const int get_rank();
		const int get_worldsize();
		void stop();

	private:
};

#endif
