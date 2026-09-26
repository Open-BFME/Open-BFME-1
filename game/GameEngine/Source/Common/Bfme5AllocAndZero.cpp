// Two allocations that hand back cleared memory.
//
// The first is the array form of operator new followed by the compiler's
// memset and two fields written into the head of the block; the second is a
// calloc -- count times size, allocate, and clear only if something came back.

extern "C" void * __cdecl memset(void *block, int value, unsigned int bytes);

#pragma intrinsic(memset)

void * __cdecl operator new[](unsigned int bytes);		// retail 0x00881F70

// ?bfmeMakeBlock@@YAPAXHI@Z
void * __cdecl bfmeMakeBlock(int tag, unsigned int size)
{
	char *block = new char[size];

	memset(block, 0, size);

	((int *)block)[1] = size;
	((int *)block)[0] = tag;

	return block;
}

void * __cdecl bfmeAllocBlock(unsigned int bytes);		// retail 0x009A5920

// ?bfmeCallocBlock@@YAPAXII@Z
void * __cdecl bfmeCallocBlock(unsigned int count, unsigned int size)
{
	unsigned int bytes = count * size;

	void *block = bfmeAllocBlock(bytes);

	if (block)
		memset(block, 0, bytes);

	return block;
}
