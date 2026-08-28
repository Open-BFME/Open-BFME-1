// cl: /DNDEBUG /MD /EHsc
// readable body of ??0BaikonurLaunchPowerModuleData@@: Code/GameEngine/Source/GameLogic/Object/SpecialPower/BaikonurLaunchPower.cpp

// BaikonurLaunchPowerModuleData's constructor, retail 0x00212C10.
//
// The base constructor is 0x002149D0, byte-identical to and folded with
// RespawnBodyModuleData's, so the address cannot name the class; it is pinned
// under a stand-in and runs to +0x64.
//
// Five fields, three zero and two true, and retail emits them grouped by value
// rather than by offset - the three zeroes off a cleared register, then the
// vftable pointer, then the two flags off a register holding 1. That is the
// scheduler, and declaring them in offset order reproduces it.

class BaikonurLaunchPowerModuleDataBase
{
public:
	BaikonurLaunchPowerModuleDataBase();

	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[ 0x64 - 4 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BaikonurLaunchPower.h
class BaikonurLaunchPowerModuleData : public BaikonurLaunchPowerModuleDataBase
{
public:
	BaikonurLaunchPowerModuleData();

private:
	int m_unmodelled_64;					// +0x64
	bool m_unmodelled_68;					// +0x68
	int m_unmodelled_6C;					// +0x6C
	bool m_unmodelled_70;					// +0x70
	int m_unmodelled_74;					// +0x74
};

BaikonurLaunchPowerModuleData::BaikonurLaunchPowerModuleData()
	: m_unmodelled_64( 0 ),
	  m_unmodelled_68( true ),
	  m_unmodelled_6C( 0 ),
	  m_unmodelled_70( true ),
	  m_unmodelled_74( 0 )
{
}
