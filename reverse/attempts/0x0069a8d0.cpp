// ?bfmeToggleLK@@YGXPAVBfmeHolderLK@@@Z (identity unknown)
// partial score=0.93 date=2026-09-09
// 56/60 bytes; structure and content exact. Residue is block ordering: retail
// places the any-flag-set call first (+0x22, ecx) via an inverted last test
// (je), all-clear second (+0x2f, edx). Every C shape that MSVC folds to one
// call site (plain if/else, De Morgan guard, goto-merged) re-canonicalizes to
// all-clear-first, the opposite of retail. An if/elseif/else duplicating the
// any-set call gets the right order/content at +0x22 but leaves it unmerged
// (73B, two call sites). /O1 changes the whole shape (byte cmp, no tail jmp).
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" __declspec(dllimport) void __stdcall bfmeApiOnLK(void *handle);
extern "C" __declspec(dllimport) void __stdcall bfmeApiOffLK(void *handle);

class BfmeThingLK
{
public:
	unsigned char m_bfmeHeadLK[8];
	void *m_bfmeHandleLK;
	unsigned char m_bfmeGapLK[0x2d];
	char m_bfmeALK;
	char m_bfmeBLK;
	char m_bfmeCLK;
	char m_bfmeDLK;
};

class BfmeHolderLK
{
public:
	BfmeThingLK *m_bfmeThingLK;
};

void __stdcall bfmeToggleLK(BfmeHolderLK *holder)
{
	BfmeThingLK *thing = holder->m_bfmeThingLK;
	if (thing->m_bfmeALK || thing->m_bfmeBLK || thing->m_bfmeCLK || thing->m_bfmeDLK)
		bfmeApiOnLK(thing->m_bfmeHandleLK);
	else
		bfmeApiOffLK(thing->m_bfmeHandleLK);
}
