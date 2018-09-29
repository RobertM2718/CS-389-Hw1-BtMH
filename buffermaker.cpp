
#include <stdlib.h>
#include "buffermaker.h"
u_int32_t *create_buffer (u_int32_t size) {
	/*
	u_int32_t *newBuffer = (u_int32_t*) calloc((sizeof(u_int32_t)) * size); // allocate an array
	for(unsigned index = 0; index < size; index++) {
		newBuffer[index] = rand() % size; // mod this with something?
	}
	return newBuffer;
	//(u_int32_t*) calloc(size, sizeof(u_int32_t))
	*/
	
	u_int32_t *newBuffer = (u_int32_t*) calloc(size, sizeof(u_int32_t)); // allocate an array
	//This for-loop builds a path through the array, by storing at each index the value of the next array-index in the path.  It does so in such a
	// way that there is one cycle through the array, which touches every element in the array.  
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
	return newBuffer;
}
