// cl: /DNDEBUG /MD /O2 /Ob2

extern "C" void *__cdecl memcpy(void *destination, const void *source, unsigned int count);
unsigned int g_Va012F4A10[8];
unsigned int g_Va012F4A30[8];
unsigned int g_Va012F4A50[8];
unsigned int g_Va012F4A70[8];

void rva00545d00CopyBlocks(
	const unsigned int *block0,
	const unsigned int *block1,
	const unsigned int *block2,
	const unsigned int *block3)
{
	// These four retail globals are consecutive fixed 32-byte blocks whose
	// identities are not recovered, hence the address-derived names.
	memcpy(g_Va012F4A10, block0, 32);
	memcpy(g_Va012F4A30, block1, 32);
	memcpy(g_Va012F4A50, block2, 32);
	memcpy(g_Va012F4A70, block3, 32);
}
