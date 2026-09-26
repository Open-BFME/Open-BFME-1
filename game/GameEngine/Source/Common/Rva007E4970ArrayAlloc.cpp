// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME5: retail 0x007E4970 (16 bytes), array-allocation forwarder.

void * __cdecl operator new[](unsigned int bytes);

void *__stdcall rva007e4970_allocate(unsigned int bytes, void *unused)
{
	return ::operator new[](bytes);
}
