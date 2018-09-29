/* This is the first-draft version of the code that Betsy and I will use to complete hw1.  
*/


#include <cassert>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include "buffermaker.h"
#include <cmath>

using namespace std; //to make things simpler to write
using namespace std::chrono;

const unsigned ITERATIONS_PER_TEST = 1000;//10000;
//const unsigned iterations0 = 32;
//const unsigned iterations1 = iterations0*2;
//const unsigned iterations2 = iterations1*2;
//const unsigned iterations3 = iterations2*2;
//const unsigned iterations4 = iterations3*2;
//const unsigned iterations5 = iterations4*2;
//hopefully, by making the size of this loop fixed at compile-time, we can get the compiler to remove the loop
// from our compiled code, so that we're only measuring reads.  


// read in column-major form from a 2d array of size (i, j)
/*
double time_read_it0() {
	mat = malloc ()
	const auto start = steady_clock::now();
	for (unsigned i = 0; i < iterations0; i++) {
		//do access
	}
	const auto end = steady_clock_now();
}
*/

// generates an array of i random numbers between 0 and n
/*
unsigned[] create_indices (i, n) {
	to_add = int[]
	
}
*/

//creates a buffer of n chars (because chars are 1 byte).  We don't care what's in them.  

// measures the time it takes to read a byte from a size n buffer i times
duration<double, nano> time_to_read(unsigned buffer_size, unsigned iterations) { /*, unsigned i*/
	u_int32_t correct_type_buffer_size = (u_int32_t) buffer_size;
	u_int32_t *buffer = create_buffer(correct_type_buffer_size);
	//unsigned[] random_indices = create_indices(i);
	volatile u_int32_t curr_val = 0;
	const auto start_time = steady_clock::now();
	for (unsigned i = 0; i < iterations; i++) {

		curr_val = (buffer[curr_val] + curr_val) % buffer_size;
	}
	const auto end_time = steady_clock::now();
	free(buffer);
	//free(random_indices);
	duration<double, nano> elapsed_time = end_time - start_time;
	//cout<<"It took "<<elapsed_time.count()<<" seconds to read a byte from a buffer of " << n << " bytes " << i <<" times\n"; // shoud this really print?  
	return elapsed_time;
}

/* Main takes 3 arguments: a starting size for the buffer to be read out of, a step size by which to increase the 
 *
 */
int main (int argc, char *argv[]) {
// sanity: print sizeof char, sizeof unsigned,
// remember: args are n, step, steps, i
	if (argc != 5) {  // != 5
		cout << "Unexpected number of arguments: " << argc << "\n";
		return -1;
	}
	const unsigned start_buffer_power = stoul(argv[1]);
	const unsigned power_step_size = stoul(argv[2]);
	const unsigned end_buffer_power = stoul(argv[3]);
	const unsigned reads_per_buffer_item = stoul(argv[4]);
	assert(end_buffer_power >= start_buffer_power);
	const unsigned num_steps = (end_buffer_power - start_buffer_power) / power_step_size+ 1;
	//const unsigned iterations = argv[4];

	for (unsigned i = 0; i < num_steps; i++) { 
		unsigned buffer_size = pow(2, i*power_step_size + start_buffer_power)/sizeof(u_int32_t);
		unsigned iterations = reads_per_buffer_item * buffer_size;
		duration<double, nano> test_time = time_to_read(buffer_size, iterations);
		/*
		cout << "It took an average of " << ((double) test_time.count())/ITERATIONS_PER_TEST
		<< " nanoseconds to read a byte out of a buffer of " << buffer_size << " bytes over " 
		<< ITERATIONS_PER_TEST << " tests.\n"; // format this to make a better csv file for plotting?
		*/
		//need to change this message to report number of bytes, not u_int32_t's.  
		cout << "Buffer size: " << "2^" << i*power_step_size + start_buffer_power << " bytes\t\tMean time/read: " 
		<< ((double) test_time.count()) / iterations << " ns\n";
		//cout << "buffer size: " << buffer_size << "\n";
	}

	return 0;
}