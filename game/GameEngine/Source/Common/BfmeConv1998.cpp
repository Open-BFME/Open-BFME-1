// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Common/Overridable.h"
#include "Common/Player.h"


class BfmeThingEVH
{
public:
	int m_bfmeHeadAEVH;
	Overridable *m_bfmeSubEVH;
	unsigned char m_bfmePadEVH[0x414];
	int m_bfmeDeltaEVH;
};

class BfmeArgEVH
{
public:
	int m_bfmeHeadEVH;
	BfmeThingEVH *m_bfmeThingEVH;
};

class BfmeHostEVH
{
public:
	void bfmeAdvanceEVH(BfmeArgEVH *arg);

	int m_bfmeHeadEVH;
	int m_bfmeValueEVH;
	int m_bfmeLimitEVH;
	Player *m_bfmeSinkEVH;
};

// Retail calls getFinalOverride through ILT 0x000022BB instead of inlining it.
#pragma inline_depth(0)
void BfmeHostEVH::bfmeAdvanceEVH(BfmeArgEVH *arg)
{
	if (arg == 0)
		return;

	BfmeThingEVH *thing = arg->m_bfmeThingEVH;

	if (thing != 0 && thing->m_bfmeSubEVH != 0)
		thing = (BfmeThingEVH *)thing->m_bfmeSubEVH->getFinalOverride();

	m_bfmeValueEVH = m_bfmeValueEVH + thing->m_bfmeDeltaEVH;

	if (m_bfmeSinkEVH != 0)
		m_bfmeSinkEVH->onPowerBrownOutChange(m_bfmeValueEVH < m_bfmeLimitEVH);
}
