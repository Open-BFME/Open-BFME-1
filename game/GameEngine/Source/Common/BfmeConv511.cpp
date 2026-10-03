// Retail's call at 0x0020723A rides the class's ILT thunk at 0x0000F966, defined
// as ?j_0000f966@@YAXXZ in game/gen_small/thunks_007.cpp (tail body 0x00206CB0).
// That thunk is a bare `jmp`, so it is called as a free cdecl function; `this` is
// already spilled to esi here, so no other instruction changes.
extern void j_0000f966(void);

class BfmeThingBQA
{
public:
	int bfmeGoBQA();
	unsigned char m_bfmeHead[0x24];
	int *m_bfmeBegin;
	int *m_bfmeEnd;
	unsigned char m_bfmeGap[4];
	bool m_bfmeReady;
};

int BfmeThingBQA::bfmeGoBQA()
{
	if (!m_bfmeReady)
	{
		j_0000f966();
		m_bfmeReady = true;
	}
	return m_bfmeEnd - m_bfmeBegin;
}
