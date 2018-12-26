#ifndef SAMPLE_H
#define SAMPLE_H

class sample 
{
	public:
		sample();
		~sample();
		
		void simple_send_recv();
		void ring_example();
		void test_wrapper();

		void send_wrapper(int* packet, int count, int dst, int tag);
		int recv_wrapper(int* buffer, int src, int tag);

	private:
};

#endif
