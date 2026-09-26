void __cdecl operator delete(void *);
void __cdecl rva784C30SmallDeallocate(void *block, unsigned int bytes);

void __stdcall rva784C30Deallocate(void *block, unsigned int count)
{
	if (block != 0) {
		const unsigned int bytes = count * 16;
		if (bytes > 128) {
			operator delete(block);
		} else {
			rva784C30SmallDeallocate(block, bytes);
		}
	}
}
