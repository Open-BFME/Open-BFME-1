// cl: /Od
// A block asked for through one of two paths according to how big it is, built
// without optimisation. Both callees are pinned by address; nothing here names
// them.

void *bfmeBigAllocPR(unsigned int bytes);

void *bfmeSmallAllocPR(unsigned int bytes);

void *bfmeAllocPR(unsigned int bytes)
{
	void *got;

	if (bytes > 0x80)
		got = bfmeBigAllocPR(bytes);
	else
		got = bfmeSmallAllocPR(bytes);

	return got;
}
