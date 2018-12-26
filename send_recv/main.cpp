#include <stdio.h>
#include "sample.h"

int main(int argc, char** argv) {
	sample *func = new sample();
	//Practice 1.
	//func->simple_send_recv();

	//Practice 2.
	//func->ring_example();

	//Practice 3.
	func->test_wrapper();

	delete func;
}
