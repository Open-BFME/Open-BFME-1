// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/bfmeobjectlayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "GameLogic/Object.h"

class BfmeOwnerDJ
{
public:
	unsigned char m_bfmeHeadDJ[0x29];
	unsigned char m_bfmeAllowDJ;
};

class BfmeItemDJ
{
public:
	unsigned char m_bfmeHeadDJ[4];
	BfmeOwnerDJ *m_bfmeOwnerDJ;
	unsigned char m_bfmeMidDJ[0x1d];
	unsigned char m_bfmeFlagDJ;
};

class BfmeThingDJ
{};

int __cdecl bfmeCheckDJ(BfmeThingDJ *thing)
{
	static NameKeyType key = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");

	BfmeItemDJ *it = reinterpret_cast<BfmeItemDJ *>(
		reinterpret_cast<Object *>(thing)->findUpdateModule(key));

	if (it != 0 && it->m_bfmeFlagDJ != 0 && it->m_bfmeOwnerDJ->m_bfmeAllowDJ != 0)
		return 0;

	return 1;
}
