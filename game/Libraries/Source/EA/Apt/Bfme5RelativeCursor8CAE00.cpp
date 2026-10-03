// Advance an aligned cursor by a length encoded in its leading dword.
struct BfmeCursor8CAE00
{
	unsigned char *m_next;
};

struct Rva00899560Pool
{
	int m_reserved;
	int m_count;
};
extern Rva00899560Pool *g_rva01337810GcRoots;

// 0x008A30C0 is the Apt idle hook. It is owned by the MASM dump
// game/gen_asm/d_008a0830.asm as the address-derived cdecl symbol
// ?d_008a30c0@@YAXXZ; matched TUs reach it through that symbol (see
// game/Libraries/Source/EA/Apt/Rva008D19C0PopAfterStep.cpp). Retail passes the
// pool pointer in ECX only, so call it through a thiscall view.
extern void d_008a30c0();
typedef void (__fastcall *Rva8CAE00IdleHook)(void *);

void __cdecl bfmeAdvanceCursor8CAE00(int *target, BfmeCursor8CAE00 *cursor)
{
	unsigned char *aligned = (unsigned char *)(((unsigned)cursor->m_next + 3) & ~3u);
	cursor->m_next = aligned + 4;
	cursor->m_next += *(unsigned *)aligned;
	if (g_rva01337810GcRoots->m_count != 0 && *target == 0)
		(reinterpret_cast<Rva8CAE00IdleHook>(d_008a30c0))(g_rva01337810GcRoots);
}
