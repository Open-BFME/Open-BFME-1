// ?Rva007EBA60Get@@YAPAXXZ
// partial score=0.88 date=2026-09-06
// cl: /O2
// 0x007EBA60: getter twin of Rva007EBAA0 (Code/GameEngine/Source/GameNetwork/
// Rva007EBAA0Create.cpp) -- same 0x14-byte FESL diagnostic singleton at
// 0x0130A5A0, but this entry point returns the pointer instead of void.

void *Gen007F0130(unsigned int size);

extern int vftable_01129D30;
extern void Rva007EB820(void);
extern void *g_Va0130A5A0;

void *Rva007EBA60Get(void)
{
	if (g_Va0130A5A0)
		return g_Va0130A5A0;
	void *p = Gen007F0130(0x14);
	if (p)
	{
		*((int *)p + 2) = 0;
		*((int *)p + 3) = 0;
		*((int *)p + 4) = 0;
		*(int *)p = (int)&vftable_01129D30;
		*((int *)p + 1) = (int)&Rva007EB820;
		g_Va0130A5A0 = p;
		return p;
	}
	g_Va0130A5A0 = p;
	return g_Va0130A5A0;
}
