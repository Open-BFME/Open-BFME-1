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

class BfmeG1211
{
public:
	void bfmeStep1211C(void);
};

void __cdecl bfmeAdvanceCursor8CAE00(int *target, BfmeCursor8CAE00 *cursor)
{
	unsigned char *aligned = (unsigned char *)(((unsigned)cursor->m_next + 3) & ~3u);
	cursor->m_next = aligned + 4;
	cursor->m_next += *(unsigned *)aligned;
	if (g_rva01337810GcRoots->m_count != 0 && *target == 0)
		((BfmeG1211 *)g_rva01337810GcRoots)->bfmeStep1211C();
}
