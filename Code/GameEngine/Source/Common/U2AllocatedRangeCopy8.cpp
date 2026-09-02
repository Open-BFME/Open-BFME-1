// Sibling of U2AllocatedRangeCopies.cpp at 0x0083F2F0 / 0x0083F330, same
// allocator import slot, but eight-byte elements copied inline instead of
// through the three-argument copy import.  Retail shifts the count by three
// for the allocation, arithmetic-shifts it back, and walks the destination
// with the source-minus-destination offset hoisted out of the loop.

extern "C" __declspec(dllimport) void *__cdecl u2_import_0135944C(unsigned int bytes);

struct U2Elem8
{
	int m_a;
	int m_b;
};

void *Rva0083F3B0Duplicate(const U2Elem8 *src, int count)
{
	unsigned int bytes = (unsigned int)count << 3;
	U2Elem8 *p = (U2Elem8 *)u2_import_0135944C(bytes);
	if (p != 0)
	{
		int n = (int)bytes >> 3;
		unsigned int dst = (unsigned int)p;
		if (n > 0)
		{
			int off = (int)src - (int)p;
			do
			{
				*(U2Elem8 *)dst = *(U2Elem8 *)(off + dst);
				dst += 8;
				--n;
			}
			while (n);
		}
	}
	return p;
}
