
#include <stdlib.h>
#include "buffermaker.h"
u_int32_t *create_buffer (u_int32_t size) {
	u_int32_t *newBuffer = (u_int32_t*) malloc((sizeof(u_int32_t)) * size); // allocate an array
	for(unsigned index = 0; index < size; index++) {
		newBuffer[index] = rand() % size; // mod this with something?
	}
	return newBuffer;
}