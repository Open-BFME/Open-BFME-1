// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

struct Rva009AF490Context
{
	unsigned char m_pad0[0x34];
	int *m_boundingBase;
};

int *Rva009AF490SetupBounding(Rva009AF490Context *ctx, int flimit)
{
	int *base = ctx->m_boundingBase;
	int *bounding = base + 256;
	int i;

	memset(base, 0, 512 * sizeof(int));

	for (i = 0; i < flimit; i++) {
		bounding[-flimit - i] = i - flimit;
		bounding[-i] = -i;
		bounding[i] = i;
		bounding[flimit + i] = flimit - i;
	}

	return bounding;
}
