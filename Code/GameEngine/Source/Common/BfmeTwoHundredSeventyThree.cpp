// cl: /Od
// A block let go of through one of two paths according to how big it is, built
// without optimisation. Both callees are pinned by address; nothing here names
// them.

void bfmeBigFreePM(void *at);

void bfmeSmallFreePM(void *at, unsigned int bytes);

void bfmeFreePM(void *at, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeBigFreePM(at);
	else
		bfmeSmallFreePM(at, bytes);
}
