// ?bfmeEmitBA@@YAPAGPAGH0@Z (inferred identity, direct caller not recovered)
// partial score=0.98 date=2026-09-09
// Exact shape found. The union keeps the conversion result in a
// volatile dword while the non-volatile word member produces retail's narrow
// read. The body matches both 0x0068D5A0 and its byte-identical twin at
// 0x0068D620.
extern int (__stdcall *g_bfmeConvBA)(int value);	// pin ?g_bfmeConvBA@@3P6GHH@ZA,0x00F5972C

union ConvertedValue
{
	volatile unsigned int storage;
	unsigned short narrow;
};

unsigned short * __cdecl bfmeEmitBA(unsigned short *dst, int value, unsigned short *limit)
{
	ConvertedValue converted;
	converted.storage = (unsigned int)g_bfmeConvBA(value);

	if (limit != 0)
	{
		if (dst > limit)
			return dst;

		if (dst + 1 > limit)
			return dst;
	}

	*dst = converted.narrow;

	return dst + 1;
}
