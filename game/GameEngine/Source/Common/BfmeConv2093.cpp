#include "../GameLogic/Object/object.h"

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadXW[0x3c];
	int m_bfme3CXW;
};

// Retail 0x012F0898 is EA's game-logic singleton, whose one canonical
// spelling is ?TheGameLogic@@3PAVGameLogic@@A.  Rva00367E30Logic above is this
// TU's own view of that address, so the read below casts at the use.
class GameLogic;

extern GameLogic *TheGameLogic;

class BfmeHostXW
{
public:
	void bfmeSetXW(int when);
	void bfmeApplyXW(Object *obj, int value);

	unsigned char m_bfmeHeadXW[8];
	Object *m_bfme08XW;
};

void BfmeHostXW::bfmeSetXW(int when)
{
	Object *obj = m_bfme08XW;

	if (reinterpret_cast<const unsigned char *>(obj->m_status)[0] & 1)
		return;

	int v;

	if (when != 0 && when != 0x3fffffff)
		v = when - ((Rva00367E30Logic *)TheGameLogic)->m_bfme3CXW;
	else
		v = 0x3fffffff;

	bfmeApplyXW(obj, v);
}
