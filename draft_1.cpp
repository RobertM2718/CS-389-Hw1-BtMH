/* This is the first-draft version of the code that Betsy and I will use to complete hw1.  
*/


#include <cassert>
#include <chrono>
#include <iostream>
#include <stdlib.h>

using namespace std; //to make things simpler to write
using namespace std::chrono;

const unsigned ITERATIONS_PER_TEST = 10000;
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
unsigned[] create_indices (i, n) {
	to_add = int[]
	
}

//creates a buffer of n chars (because chars are 1 byte).  We don't care what's in them.  
char[] create_buffer (unsigned n) {

}

// measures the time it takes to read a byte from a size n buffer i times
duration<double> time_to_read(unsigned n) { /*, unsigned i*/
	unsigned[] buffer = create_buffer (n);
	//unsigned[] random_indices = create_indices(i);
	volatile unsigned curr_val = 0;
	const auto start = steady_clock::now();
	for (unsigned j = 0; j < ITERATIONS_PER_TEST; j++) {
		curr_val = buffer[random_indices[j]]; // buffer[curr_val]
	}
	const auto end = steady_clock::now();
	free(buffer);
	//free(random_indices);
	duration<double> elapsed_time = end - start;
	//cout<<"It took "<<elapsed_time.count()<<" seconds to read a byte from a buffer of " << n << " bytes " << i <<" times\n"; // shoud this really print?  
	return elapsed_time;
}

int main (int argc, char *argv[]) {
// sanity: print sizeof char, sizeof unsigned,
// remember: args are n, step, steps, i
	if (argc != 5) {
		cout << "Unexpected number of arguments: " << argc << "\n";
		return -1;
	}
	const unsigned start_buffer_size = argv[1];
	const unsigned step_size = argv[2];
	const unsigned num_steps = argv[3];
	const unsigned iterations = argv[4];

	for (unsigned i = 0; i < iterations; i++) {
		
	}

	return 0;
}