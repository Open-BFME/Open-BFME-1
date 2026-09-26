// ?d_0045c080@@YAXXZ
// partial score=0.85 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"

extern const float BfmeZeroRange;   // 0x01075350
extern const Real BfmeShadowScale;  // 0x0109BF3C

// Unidentified retail leaf: clamps/scales a float and accumulates it into a
// this-relative field at +0x98. No built emitter or named caller establishes
// the owner, so this address-derived shim isolates the body for probing.
class Rva0045C080Owner
{
public:
	char m_pad[0x98];
	float m_field98;
	void bfmeAdd(Real value);
};

void Rva0045C080Owner::bfmeAdd(Real value)
{
	if (value < BfmeZeroRange)
		value = value * BfmeShadowScale;
	m_field98 += value;
}
