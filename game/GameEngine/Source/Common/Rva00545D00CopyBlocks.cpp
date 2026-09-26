// cl: /DNDEBUG /MD /O2 /Ob2

extern "C" void *__cdecl memcpy(void *destination, const void *source, unsigned int count);

void rva00545d00CopyBlocks(
	const unsigned int *block0,
	const unsigned int *block1,
	const unsigned int *block2,
	const unsigned int *block3)
{
	// These four retail globals are consecutive fixed 32-byte blocks. Their
	// identities are not recovered; the addresses are therefore kept explicit.
	memcpy(reinterpret_cast<void *>(0x012F4A10), block0, 32);
	memcpy(reinterpret_cast<void *>(0x012F4A30), block1, 32);
	memcpy(reinterpret_cast<void *>(0x012F4A50), block2, 32);
	memcpy(reinterpret_cast<void *>(0x012F4A70), block3, 32);
}
