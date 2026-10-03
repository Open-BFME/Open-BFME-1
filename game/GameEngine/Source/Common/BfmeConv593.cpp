// stlport
// cl: /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
#include "PreRTS.h"
#include "Common/Player.h"

class BfmeThingCFF;

class BfmeOwnerCFF;

class BfmeThingCFF
{
public:
	void bfmeGoCFF(BfmeOwnerCFF *owner);
	unsigned char m_bfmeHead[8];
	BfmeOwnerCFF *m_bfmeOwner;
};

void BfmeThingCFF::bfmeGoCFF(BfmeOwnerCFF *owner)
{
	if (owner != 0)
	{
		if (m_bfmeOwner != 0)
			reinterpret_cast<Player *>(m_bfmeOwner)->removeTeamFromList(
				reinterpret_cast<TeamPrototype *>(this));
		m_bfmeOwner = owner;
		reinterpret_cast<Player *>(owner)->addTeamToList(
			reinterpret_cast<TeamPrototype *>(this));
	}
}
