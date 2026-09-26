// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"
#include "Common/Errors.h"

// BFME-only setter: matched GiantBirdGuardMachine constructor at RVA
// 0x0055F060 calls setDefaultState(0xB79B). The retail map occupies +4..+0x0F,
// owner is +0x10, sleep deadline +0x14, and default state ID +0x18.
// The Zero Hour StateMachine header lacks this BFME method; this TU declares
// only the witnessed prefix. Retail ThrowInfo VA 0x011E0004 points through
// CatchableTypeArray 0x011DFFFC to ErrorCode RTTI at VA 0x012A716C.
class State;
typedef unsigned int StateID;

class StateMachine
{
protected:
	void setDefaultState(StateID id);

private:
	int *m_vftable;
	std::map<StateID, State *> m_stateMap;
	void *m_owner;
	unsigned int m_sleepTill;
	StateID m_defaultStateID;
};

void StateMachine::setDefaultState(StateID id)
{
	std::map<StateID, State *>::iterator i = m_stateMap.find(id);
	if (i == m_stateMap.end())
	{
		throw ERROR_BAD_ARG;
	}
	m_defaultStateID = id;
}
