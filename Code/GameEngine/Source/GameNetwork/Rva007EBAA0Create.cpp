// cl: /O2
// 0x007EBAA0: allocate the 0x14-byte FESL diagnostic singleton at
// 0x0130A5A0 if it is still null.

void *Gen007F0130(unsigned int size);

extern int vftable_01129D30;
extern void Rva007EB820(void);
extern void *g_Va0130A5A0;

void Rva007EBAA0(void)
{
	if (g_Va0130A5A0)
		return;
	void *p = Gen007F0130(0x14);
	if (p)
	{
		*((int *)p + 2) = 0;
		*((int *)p + 3) = 0;
		*((int *)p + 4) = 0;
		*(int *)p = (int)&vftable_01129D30;
		*((int *)p + 1) = (int)&Rva007EB820;
		g_Va0130A5A0 = p;
	}
	else
		g_Va0130A5A0 = 0;
}
