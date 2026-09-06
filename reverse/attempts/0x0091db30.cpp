// ?d_0091db30@@YAXXZ
// partial score=0.75 date=2026-09-05
// cl: /DNDEBUG /MD

// Address-derived recovery for the BFME body at 0x0091DB30.  Retail resets
// the sorting renderer's dynamic-vertex-array bookkeeping when told to: a
// 16-bit array offset at 0x013467E4, seven consecutive dword slots from
// 0x01346794 to 0x013467AC (vertex-buffer pointer/offset bookkeeping), and a
// trailing 16-bit slot at 0x013467B0.  Called from
// ?Flush@SortingRendererClass@@SAXXZ and one more dump (d_008fa4b0.asm).

extern short g_Va013467E4;
extern int g_Va01346794;
extern int g_Va01346798;
extern int g_Va0134679C;
extern int g_Va013467A0;
extern int g_Va013467A4;
extern int g_Va013467A8;
extern int g_Va013467AC;
extern short g_Va013467B0;

void Rva0091DB30ResetSortingVertexArray(bool resetIt)
{
	g_Va013467E4 = 0;

	if (resetIt)
	{
		g_Va01346794 = 0;
		g_Va01346798 = 0;
		g_Va0134679C = 0;
		g_Va013467A0 = 0;
		g_Va013467A4 = 0;
		g_Va013467A8 = 0;
		g_Va013467AC = 0;
		g_Va013467B0 = 0;
	}
}
