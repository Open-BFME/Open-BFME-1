// ?process@Gen003BDE80Element@@QAEXXZ
// partial score=0.95 date=2026-09-18
// The caller and pin-consistency evidence identify this body as the element
// process reached by Rva003BDE80Owner::processAll.  The two byte fields are
// retained as offsets only; no semantic class or member name is asserted.
extern void j_0000285b(void);

class Rva012F1028
{
public:
	void j_00003ab7();
};

extern Rva012F1028 *g_012F1028;

class Gen003BDE80Element
{
public:
	void process();
	void j_00049355();
	void j_00020509(bool on);

	unsigned char m_prefix1C[0x1c];
	unsigned char m_byte1C;
	unsigned char m_gap1D[2];
	unsigned char m_byte1F;
};

// Keep the source-level thiscall receiver/argument shape while routing each
// call to the exact retail ILT thunk reported by tools/callees.py.
#pragma comment(linker, "/alternatename:?j_00049355@Gen003BDE80Element@@QAEXXZ=?j_00049355@@YAXXZ")
#pragma comment(linker, "/alternatename:?j_00020509@Gen003BDE80Element@@QAEX_N@Z=?j_00020509@@YAXXZ")
#pragma comment(linker, "/alternatename:?j_00003ab7@Rva012F1028@@QAEXXZ=?j_00003ab7@@YAXXZ")

void Gen003BDE80Element::process()
{
	if (m_byte1C == 0)
		j_0000285b();

	unsigned char b = m_byte1C;
	int prev = b;

	if (b != 0)
		j_00049355();

	unsigned char cur = m_byte1C;

	if (prev != 0 && cur == 0 && m_byte1F != 0)
	{
		g_012F1028->j_00003ab7();
		m_byte1F = 0;
	}

	j_00020509((bool)!!(prev || cur));
}
