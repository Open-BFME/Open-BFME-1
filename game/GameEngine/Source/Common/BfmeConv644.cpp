// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Common/StateMachine.h"

class BfmeOutCTA
{
public:
	virtual void bfmeSpareCTA_0();
	virtual void bfmeSpareCTA_1();
	virtual void bfmeSpareCTA_2();
	virtual void bfmeSpareCTA_3();
	virtual void bfmeSpareCTA_4();
	virtual void bfmeBeginCTA();
	virtual void bfmeSpareCTA_6();
	virtual void bfmeSpareCTA_7();
	virtual void bfmeSendCTA(int code);
	virtual void bfmeSpareCTA_9();
	virtual void bfmeSpareCTA_10();
	virtual void bfmeSpareCTA_11();
	virtual void bfmeSpareCTA_12();
	virtual void bfmeSpareCTA_13();
	virtual void bfmeWriteVCTA(void *what);
};

class ObjectIsMobileBody;

class BfmeThingCTA
{
public:
	unsigned char m_bfmeHead[8];
	ObjectIsMobileBody *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCTA *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCTA(void *one, void *two);
};

class ObjectIsMobileBody
{
public:
	bool isMobile() const;
};

void BfmeThingCTA::bfmeGoCTA(void *one, void *two)
{
	if (m_bfmeSub->isMobile())
	{
		m_bfmeOut->bfmeBeginCTA();
		// ILT 0x0000314D resolves to StateMachine::setGoalPosition at 0x000A0880.
		reinterpret_cast<StateMachine *>(m_bfmeOut)->setGoalPosition(static_cast<const Coord3D *>(one));
		m_bfmeVal = two;
		m_bfmeOut->bfmeSendCTA(0x2f);
	}
}
