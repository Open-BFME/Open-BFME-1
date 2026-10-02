// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "GameLogic/AIStateMachine.h"

class BfmeOutCSH
{
public:
	virtual void bfmeSpareCSH_0();
	virtual void bfmeSpareCSH_1();
	virtual void bfmeSpareCSH_2();
	virtual void bfmeSpareCSH_3();
	virtual void bfmeSpareCSH_4();
	virtual void bfmeBeginCSH();
	virtual void bfmeSpareCSH_6();
	virtual void bfmeSpareCSH_7();
	virtual void bfmeSendCSH(int code);
	virtual void bfmeSpareCSH_9();
	virtual void bfmeSpareCSH_10();
	virtual void bfmeSpareCSH_11();
	virtual void bfmeSpareCSH_12();
	virtual void bfmeSpareCSH_13();
	virtual void bfmeSpareCSH_14();
};

class ObjectIsMobileBody
{
public:
	bool isMobile() const;
};

class BfmeThingCSH
{
public:
	unsigned char m_bfmeHead[8];
	ObjectIsMobileBody *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSH *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSH(void *one, void *two);
};

void BfmeThingCSH::bfmeGoCSH(void *one, void *two)
{
	if (m_bfmeSub->isMobile())
	{
		m_bfmeOut->bfmeBeginCSH();
		m_bfmeVal = two;
		// ILT 0x00036192 resolves to AIStateMachine::setGoalWaypoint at 0x0016AEB0.
		reinterpret_cast<AIStateMachine *>(m_bfmeOut)->setGoalWaypoint(static_cast<const Waypoint *>(one));
		m_bfmeOut->bfmeSendCSH(0x13);
	}
}
