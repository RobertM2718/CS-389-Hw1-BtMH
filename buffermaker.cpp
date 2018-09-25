u_int32_t* create_buffer (unsigned size) {
	u_int32_t* newBuffer = malloc(sizeof(u_int32_t) * size ); // allocate an array
	for(index = 0; index < size; index++) {
		newBuffer[index] = rand() % size; // mod this with something?
	}
	return newBuffer;
}