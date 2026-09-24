// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Walks the entry vector at this+0x48, matches entry names at +0xAC and applies
// the flag plus one of three state setters fed from g_bfmeGameCW +0x170..+0x184.

#include <vector>
#include "ascii_string.h"

class Rva003A48B0Entry
{
public:
	char m_pad00[0xac];
	AsciiString m_name;
};

// Ledger declarations of the setters each entry receives in ECX (0x0061D210,
// 0x0061D0E0, 0x0061D0A0, 0x0061D060); retail reaches them through ILT thunks.
class BfmeThingNB
{
public:
	void bfmeGoNB(char value);
};

class BfmeThingDY
{
public:
	void bfmeSetDY(int value, int one);
	void bfmeSetRectDY(int x, int y, int z, int w, int one);
};

class BfmeThingDK
{
public:
	void bfmeSetDK(int value, int one);
};

// View of the g_bfmeGameCW fields this body reads.
struct BfmeLivingWorldManagerA48
{
	char m_pad00[0x170];
	int m_mode3a;
	int m_mode3b;
	int m_mode3c;
	int m_mode3d;
	int m_mode1;
	int m_mode2;
};

class BfmeGameCW;
extern BfmeGameCW *g_bfmeGameCW;

class Rva003A48B0Owner
{
public:
	void applyByName(const AsciiString *name, char value, int mode);

	char m_pad00[0x48];
	std::vector<Rva003A48B0Entry *> m_entries;
};

void Rva003A48B0Owner::applyByName(const AsciiString *name, char value, int mode)
{
	for (unsigned int i = 0; i < m_entries.size(); ++i)
	{
		if (m_entries[i]->m_name.compare(*name) != 0)
			continue;

		((BfmeThingNB *)m_entries[i])->bfmeGoNB(value);
		BfmeLivingWorldManagerA48 *manager = (BfmeLivingWorldManagerA48 *)g_bfmeGameCW;
		if (mode == 3)
		{
			((BfmeThingDY *)m_entries[i])->bfmeSetRectDY(manager->m_mode3a,
				manager->m_mode3b, manager->m_mode3c,
				manager->m_mode3d, 0);
		}
		else if (mode == 1)
		{
			((BfmeThingDY *)m_entries[i])->bfmeSetDY(manager->m_mode1, 0);
		}
		else if (mode == 2)
		{
			((BfmeThingDK *)m_entries[i])->bfmeSetDK(manager->m_mode2, 0);
		}
	}
}
