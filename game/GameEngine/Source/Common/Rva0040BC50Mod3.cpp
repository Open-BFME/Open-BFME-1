// cl: /O2 /Ob0 /I game/Libraries/Source/WWVegas/WWLib /I game/Libraries/Source/WWVegas/WWMath /I game/Libraries/Source/WWVegas/WWDebug /I game/Libraries/Source/WWVegas/WWSaveLoad /I game/Libraries/Source/WWVegas/WW3D2

// Retail 0x0040BC50 reaches the real WWMath::Random_Float body (0x008D8E00)
// through this call; the TU-local getter that used to spell it was a
// placeholder for that same address.
#include "wwmath.h"

// The operand this body scales Random_Float by is not a game global: retail
// reads the compiler's own float literal __real@42c80000 (dir32_addresses.csv
// places it at VA 0x0107FAC4, holding 100.0f) at this instruction.  Naming it
// as the literal keeps the reference defined by this object instead of leaving
// an unresolved external for a global the retail image never had.
struct BfmeVecBC
{
	float x;
	float y;
	float z;
};

void bfmeFillBC(BfmeVecBC *out, int a, int b);

class BfmeObjBC
{
public:
	BfmeVecBC *bfmeGoBC(BfmeVecBC *out);
	char m_00[0x84];
	int m_84;
	int m_88;
	int m_8C;
	int m_90;
	int m_94;
	int m_98;
};

BfmeVecBC *BfmeObjBC::bfmeGoBC(BfmeVecBC *out)
{
	int r = (int)(WWMath::Random_Float() * 100.0f) % 3;
	if (r == 0)
	{
		bfmeFillBC(out, m_84, m_88);
		return out;
	}
	if (r == 1)
	{
		bfmeFillBC(out, m_8C, m_90);
		return out;
	}
	if (r == 2)
	{
		bfmeFillBC(out, m_94, m_98);
		return out;
	}
	out->x = 1000.0f;
	out->y = 1000.0f;
	out->z = 1000.0f;
	return out;
}
