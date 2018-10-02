/* This is the final-draft version of the code that Betsy and I will use to complete hw1.  
*/


#include <cassert>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;
using namespace std::chrono;

/* This function takes in a single parameter size, which is a 32-bit unsigned integer, and returns a pointer to an array
 * containing 'size' unsigned 32-bit integers.  Each of these integers is a valid index into the array, constituting a
 * complete cycle through the array.  
*/
u_int32_t *create_buffer (u_int32_t size) {

	u_int32_t *newBuffer = (u_int32_t*) calloc(size, sizeof(u_int32_t)); // allocate an array
	//This for-loop builds a path through the array, by storing at each index the value of the next array-index in the path.  It does so in such a
	// way that there is one cycle through the array, which touches every element in the array.  
	if (newBuffer) {
	unsigned tracker = 0; //start the cycle at 0
		for (unsigned jump_num = 1; jump_num < size; jump_num++) {
			newBuffer[tracker] = size;
			unsigned proposed_jump = rand() % size; 
			while (newBuffer[proposed_jump] != 0) { // if we've been here before
				proposed_jump = (proposed_jump + 1) % size; // move on
			}
			newBuffer[tracker] = proposed_jump; //now we're at a spot we haven't visited before.  We make this the next stop in our cycle.  
			tracker = proposed_jump; //then, we start looking looking for where to go next.  
		}
	} else {
		throw "Memory allocation failed!";
	}
	return newBuffer;
}
/* This function takes in two arguments - an unsigned integer 'buffer_size' and an unsigned integer 'iterations'.  It then creates a buffer
 * of size 'buffer_size' using create_buffer and measures the time it takes to read elements from it 'iterations' times.  It does this in a
 * way which prevents the data from being prefetched.  
*/
duration<double, nano> time_to_read(unsigned buffer_size, unsigned iterations) { /*, unsigned i*/
	u_int32_t *buffer = create_buffer((u_int32_t) buffer_size); //casting because create_buffer specifically requires u_int32_t, and we want to be sure
	volatile u_int32_t curr_val = 0;
	const auto start_time = steady_clock::now();
	for (unsigned i = 0; i < iterations; i++) {
		curr_val = buffer[curr_val];
	}
	const auto end_time = steady_clock::now();
	free(buffer);
	duration<double, nano> elapsed_time = end_time - start_time;  
	return elapsed_time;
}

/* Main takes 4 command-line arguments: an unsigned integer 'start_buffer_power', an unsigned integer 'power_step_size', an unsigned integer 
 * end_buffer_power, and an unsigned integer 'reads_per_buffer_item'.  Power_step_size must be greater than 0, and end_buffer_power must be 
 * greater than or equal to 'tart_buffer_power.  
 *
 * After checking to make sure that it has received valid arguments, main uses time_to_read to measure the average time it takes to read
 * an item out of a buffer of increasing size (starting at 2^start_buffer_power bytes, and finishing at 2^end_buffer_power bytes, with the
 * power of 2 increasing by power_step_size every time), averaging over reads_per_buffer_item memory reads for each item in the buffer.  Each 
 * time it does this, it prints the time recorded to the terminal.  
 */
int main (int argc, char *argv[]) {

	if (argc != 5) {
		cout << "Unexpected number of arguments: " << argc << "\n";
		return -1;
	}
	const unsigned start_buffer_power = stoul(argv[1]);
	const unsigned power_step_size = stoul(argv[2]);
	const unsigned end_buffer_power = stoul(argv[3]);
	const unsigned reads_per_buffer_item = stoul(argv[4]);

	assert (power_step_size > 0);
	assert (end_buffer_power >= start_buffer_power);
	
	const unsigned num_steps = (end_buffer_power - start_buffer_power) / power_step_size + 1;

	cout << "#Kilobytes:\tMean time to read byte (ns):\n";

	for (unsigned i = 0; i < num_steps; i++) { 
		unsigned buffer_size = pow(2, i*power_step_size + start_buffer_power)/sizeof(u_int32_t);
		unsigned iterations = reads_per_buffer_item * buffer_size;
		duration<double, nano> test_time = time_to_read(buffer_size, iterations);
		cout << ( buffer_size * sizeof(u_int32_t)) / 1000 << "\t\t\t" << test_time.count() / iterations << "\n";
	}
	return 0;
}