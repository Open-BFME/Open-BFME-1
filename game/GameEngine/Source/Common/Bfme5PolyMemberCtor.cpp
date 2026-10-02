// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// Constructor paired with the polymorphic member destructor at retail
// 0x004B1670. The last member is the inline BFME buffer constructor.

// Retail's base here is SubsystemInterface: the constructor at 0x004B18B0
// calls 0x009A1A30 (??0SubsystemInterface@@QAE@XZ) and Gen_004B1670's vtable
// at 0x010FD1D8 inherits slots 2, 3, 6, 7 and 8 of SubsystemInterface's own
// vtable at 0x01141640 unchanged. Use the real header, not a stand-in base.
#include "PreRTS.h"
#include "System/subsystem_interface.h"

void *bfmeAllocNode(unsigned int bytes);             // retail 0x0082E540

struct BfmeTailT
{
	BfmeTailT(unsigned int bytes)
	{
		m_bfmeData = 0;
		m_bfmeData = (char *)bfmeAllocNode(bytes);
		m_bfmeLength = 0;
		m_bfmeData[0] = 0;
		*(int *)(m_bfmeData + 4) = 0;
		*(char **)(m_bfmeData + 8) = m_bfmeData;
		*(char **)(m_bfmeData + 12) = m_bfmeData;
	}
	~BfmeTailT(void);

	char *m_bfmeData;
	int m_bfmeLength;
};

class BfmeOpaqueZeroMember
{
public:
	BfmeOpaqueZeroMember(void)
	{
		m_bfmeValue = 0;
	}
	~BfmeOpaqueZeroMember(void);

	int m_bfmeValue;
};

class Gen_004B1670 : public SubsystemInterface
{
public:
	Gen_004B1670(void);
	virtual ~Gen_004B1670(void);

private:
	char m_bfme08;
	int m_bfmeVectorStart;
	int m_bfmeVectorFinish;
	BfmeOpaqueZeroMember m_bfmeVectorEnd;
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	int m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
	int m_bfme3c;
	int m_bfme40;
	BfmeTailT m_bfmeBuffer;
};

// ??0Gen_004B1670@@QAE@XZ
Gen_004B1670::Gen_004B1670(void) :
	SubsystemInterface(),
	m_bfme08(0),
	m_bfmeVectorStart(0),
	m_bfmeVectorFinish(0),
	m_bfmeVectorEnd(),
	m_bfme18(0),
	m_bfme1c(0),
	m_bfme30(0),
	m_bfme34(0),
	m_bfme38(0),
	m_bfme3c(0),
	m_bfme40(0),
	m_bfmeBuffer(0x18)
{
}
