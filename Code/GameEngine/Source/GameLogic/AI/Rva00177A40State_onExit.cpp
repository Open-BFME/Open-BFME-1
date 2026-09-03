// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME layout view for the anonymous 0x00177A40 state-exit body.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

enum StateExitType
{
	STATE_EXIT_NORMAL = 0
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);

protected:
	unsigned char m_pad00[0x18];
	StateMachine *m_machine;
};

template <int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, int index)
	{
		m_bits.set(index);
	}
	BitFlags() {}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &, bool);
};

class Rva00177A40State : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);
};

void Rva00177A40State::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	m_machine->m_owner->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 28), false);
}
