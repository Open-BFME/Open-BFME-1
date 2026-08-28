// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ??0StateMachine@@: Code/GameEngine/Source/Common/StateMachine.cpp
// Open-BFME5: StateMachine::StateMachine, retail 0x000A1BD0 (180 bytes).
//
// The pin ??0StateMachine@@QAE@PAVObject@@VAsciiString@@@Z was previously
// refuted on `ret 0xc' against two declared parameters.  It is INCOMPLETE, not
// wrong -- the same shape as ??0TeamPrototype: retail reads a THIRD argument at
// entry+12, as a byte (`mov cl,[esp+0x28]'), and stores it at this+0x42, so the
// true name carries a trailing _N.
//
// Local ABI-slice replica.  BFME's StateMachine carries ONE base vptr where
// MemoryPoolObject + Snapshot give two, so every member sits four bytes early
// (the same -4 the landed defineState needs its retailLayout() helper for).

#include <map>

typedef bool Bool;
class Object;

// Local replica: retail calls the destructor out of line (0x00887940), so the
// vendored header's inline releaseBuffer() body must not be visible here.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();
private:
	void *	m_data;
};

class StateMachineBase
{
public:
	StateMachineBase() {}
	virtual ~StateMachineBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine : public StateMachineBase
{
public:
	StateMachine( Object *owner, AsciiString name, Bool flag );
	virtual ~StateMachine();

private:
	std::map<unsigned int, void *>	m_stateMap;			// this+0x04
	Object *								m_owner;				// this+0x10
	unsigned int						m_sleepTill;		// this+0x14
	unsigned int						m_defaultStateID;	// this+0x18
	unsigned int						m_slot1c;			// this+0x1c
	unsigned int						m_slot20;			// this+0x20
	unsigned int						m_slot24;
	unsigned int						m_slot28;
	unsigned int						m_slot2c;
	unsigned int						m_slot30;
	unsigned int						m_slot34;
	unsigned int						m_slot38;
	unsigned int						m_slot3c;			// this+0x3c
	char									m_slot40;			// this+0x40
	char									m_slot41;			// this+0x41
	char									m_slot42;			// this+0x42
};

// ??0StateMachine@@QAE@PAVObject@@VAsciiString@@_N@Z
StateMachine::StateMachine( Object *owner, AsciiString name, Bool flag )
{
	m_slot42 = flag;
	m_owner = owner;
	m_sleepTill = 0;
	m_defaultStateID = 999999;
	m_slot41 = 0;
	m_slot1c = 0;
	m_slot40 = 0;
	m_slot20 = 0;
	m_slot24 = 0;
	m_slot28 = 0;
	m_slot2c = 0;
	m_slot30 = 0;
	m_slot34 = 0;
	m_slot38 = 0;
	m_slot3c = 0;
}
