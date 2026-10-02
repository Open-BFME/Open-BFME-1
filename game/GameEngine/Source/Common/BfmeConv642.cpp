// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "GameLogic/AIStateMachine.h"

class BfmeOutCSG
{
public:
	virtual void bfmeSpareCSG_0();
	virtual void bfmeSpareCSG_1();
	virtual void bfmeSpareCSG_2();
	virtual void bfmeSpareCSG_3();
	virtual void bfmeSpareCSG_4();
	virtual void bfmeBeginCSG();
	virtual void bfmeSpareCSG_6();
	virtual void bfmeSpareCSG_7();
	virtual void bfmeSendCSG(int code);
	virtual void bfmeSpareCSG_9();
	virtual void bfmeSpareCSG_10();
	virtual void bfmeSpareCSG_11();
	virtual void bfmeSpareCSG_12();
	virtual void bfmeSpareCSG_13();
	virtual void bfmeSpareCSG_14();
};

class ObjectIsMobileBody
{
public:
	bool isMobile() const;
};

class BfmeThingCSG
{
public:
	unsigned char m_bfmeHead[8];
	ObjectIsMobileBody *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSG *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSG(void *one, void *two);
};

void BfmeThingCSG::bfmeGoCSG(void *one, void *two)
{
	if (m_bfmeSub->isMobile())
	{
		m_bfmeOut->bfmeBeginCSG();
		m_bfmeVal = two;
		// ILT 0x00036192 resolves to AIStateMachine::setGoalWaypoint at 0x0016AEB0.
		reinterpret_cast<AIStateMachine *>(m_bfmeOut)->setGoalWaypoint(static_cast<const Waypoint *>(one));
		m_bfmeOut->bfmeSendCSG(0x12);
	}
}
