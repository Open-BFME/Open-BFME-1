// cl: /Od
// A block asked for through one of two paths according to how big it is, built
// without optimisation. Both callees are pinned by address; nothing here names
// them.

// The large path calls ILT 0x00037C54 -> 0x00060800, the 5-byte jump thunk
// ?j_00060800@@YAXXZ to 0x00881F30 (global operator new, mem_ops.cpp).
void j_00060800();
typedef void *(*BfmeBigAllocPRFn)(unsigned int bytes);

void *bfmeSmallAllocPR(unsigned int bytes);

void *bfmeAllocPR(unsigned int bytes)
{
	void *got;

	if (bytes > 0x80)
		got = reinterpret_cast<BfmeBigAllocPRFn>(j_00060800)(bytes);
	else
		got = bfmeSmallAllocPR(bytes);

	return got;
}
