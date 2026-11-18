// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
// BFME layout view for the anonymous 0x00178AE0 state-enter body.

#include "../../../Include/Common/ScalarTypes.h"

#include "../../../Include/Common/Enums/StateReturnType.h"




class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

template <int NUMBITS>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, int bitIndex)
	{
		m_bits.set(bitIndex);
	}
	BitFlags() {}

	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &, Bool);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
protected:
	unsigned char m_pad00[0x18];
	StateMachine *m_machine;
};

extern void j_00004629();

class Rva00178AE0State : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType Rva00178AE0State::onEnter()
{
	Object *owner = m_machine->m_owner;
	int result = ((int (__cdecl *)())j_00004629)();
	owner->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 28), result == -1);
	return (StateReturnType)result;
}
