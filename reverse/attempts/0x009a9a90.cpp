// ?bfmeCopyColAA90@@YAXPAEHHH0HHH@Z
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /MD /O2

// ?bfmeCopyColAA90@@YAXPAEHHH0HHH@Z
void __cdecl bfmeCopyColAA90(
	unsigned char *pSrc,
	int pSrcPitch,
	int pUnused2,
	int pUnused3,
	unsigned char *pDst,
	int pDstPitch,
	int pUnused6,
	int pCount)
{
	int pitch = pDstPitch;
	unsigned int limit = (unsigned int)pitch * (unsigned int)pCount;
	int step = pSrcPitch;
	int srcDelta = step + step;
	unsigned int off = 0;

	if (limit > 0)
	{
		unsigned char *d = pDst;
		unsigned char *s = pSrc;
		do
		{
			*(unsigned char *)(off + (unsigned int)d) = *s;
			off += (unsigned int)pitch;
			s += srcDelta;
		} while (off < limit);
	}
}
