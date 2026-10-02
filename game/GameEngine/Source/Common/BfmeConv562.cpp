// cl: -Igame/Libraries/Source/WWVegas/WW3D2 -Igame/Libraries/Source/WWVegas/WWMath -Igame/Libraries/Source/WWVegas/WWLib

#include "seglinerenderer.h"

// SegLineTileFactorAltClass has no recovered header of its own yet, so only
// the method this caller names is declared here; retail's 0x0095C4C0 body is
// matched from game/Libraries/Source/WWVegas/WW3D2/SegLineTileFactorAltClass.cpp.
// That body is the 8.0f-cap twin of SegLineRendererClass's 50.0f-cap one, so
// retail calls two different classes' Set_Texture_Tile_Factor from here.
class SegLineTileFactorAltClass
{
public:
	void Set_Texture_Tile_Factor(float factor);
};

class BfmeThingCBA
{
public:
	void bfmeGoCBA(void *what);
	unsigned char m_bfmeHead[0x104];
	SegLineRendererClass m_bfmeA;
	SegLineTileFactorAltClass m_bfmeB;
};

void BfmeThingCBA::bfmeGoCBA(void *what)
{
	// Retail pushes this caller's own stack argument straight through as the
	// float parameter, so the bit pattern must travel unchanged.
	union { void *p; float f; } bits;
	bits.p = what;
	m_bfmeA.Set_Texture_Tile_Factor(bits.f);
	m_bfmeB.Set_Texture_Tile_Factor(bits.f);
}