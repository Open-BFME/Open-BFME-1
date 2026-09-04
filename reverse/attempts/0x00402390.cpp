// ?bfmeFlagsCompatible@@YA_NPBVPathfindCell@@0@Z
// partial score=0.82 date=2026-09-04
// partial score=0.82 date=2026-09-04
// cl: /DNDEBUG /MD
//
// Retail 0x00402390 (90B): free cdecl bool wrapping bfmeLayersCompatible and
// then comparing PathfindCell flag bits 20, 21 and 22-23.
//
// Wall: retail emits jne-over early-fail (5f/32c0/5e/c3) then mov eax,[edi+0xc]
// / mov esi,[esi+0xc] / ecx=fb edx=fa shr/xor cl,dl / test cl,1 / jne back;
// MSVC 7.1 coalesces all return-false to a trailing block (je forward) and
// either CSEs bits 20+21 into test 0x300000 or assigns fa to ecx instead of
// eax so xor/test use al. Best non-/O shape was 84 vs 90 with separate shr.

typedef bool Bool;

class PathfindCell
{
public:
	unsigned char m_pad[0x0c];
	unsigned int m_flags;
};

Bool bfmeLayersCompatible(const PathfindCell *a, const PathfindCell *b);

Bool bfmeFlagsCompatible(const PathfindCell *a, const PathfindCell *b)
{
	if (!bfmeLayersCompatible(a, b))
		return false;

	unsigned int fa = a->m_flags;
	unsigned int fb = b->m_flags;

	unsigned int c = fb;
	unsigned int d = fa;
	c >>= 20;
	d >>= 20;
	if (((c ^ d) & 1) != 0)
		return false;

	c = fb;
	d = fa;
	c >>= 21;
	d >>= 21;
	if (((c ^ d) & 1) != 0)
		return false;

	return ((fa ^ fb) & 0xc00000) == 0;
}
