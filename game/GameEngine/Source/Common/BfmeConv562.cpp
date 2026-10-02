// cl: -Igame/Libraries/Source/WWVegas/WW3D2 -Igame/Libraries/Source/WWVegas/WWMath -Igame/Libraries/Source/WWVegas/WWLib

#include "seglinerenderer.h"

// SegLineTileFactorAltClass has no recovered header of its own yet, so its
// stand-in stays TU-local; retail's 0x0095C4C0 body is matched from
// game/Libraries/Source/WWVegas/WW3D2/SegLineTileFactorAltClass.cpp.
class BfmeOtherCBA
{
public:
	void bfmeTwoCBA(void *what);
};

class BfmeThingCBA
{
public:
	void bfmeGoCBA(void *what);
	unsigned char m_bfmeHead[0x104];
	SegLineRendererClass m_bfmeA;
	BfmeOtherCBA m_bfmeB;
};

void BfmeThingCBA::bfmeGoCBA(void *what)
{
	// Retail pushes this caller's own stack argument straight through as the
	// float parameter, so the bit pattern must travel unchanged.
	union { void *p; float f; } bits;
	bits.p = what;
	m_bfmeA.Set_Texture_Tile_Factor(bits.f);
	m_bfmeB.bfmeTwoCBA(what);
}