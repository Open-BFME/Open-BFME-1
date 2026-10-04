#ifndef BFME_RVA000A1310_STATE_LOOKUP_H
#define BFME_RVA000A1310_STATE_LOOKUP_H

#include <map>

class State;

// Native lookup ABI at RVA 000A1310. This is only the witnessed prefix:
// one existing vptr at +0 and the unsigned-StateID map at +4..+0x0f.
// It constructs no object or vtable and is not a canonical StateMachine.
// State is deliberately incomplete: native caller-local views must not be
// confused with the incompatible State declaration in the sweep header.
class Rva000A1310StateMachine
{
public:
	State *lookup(unsigned int stateID);

private:
	void *m_vptr00;
	std::map<unsigned int, State *> m_stateMap;
};

typedef char Rva000A1310PrefixSizeCheck[sizeof(Rva000A1310StateMachine) == 0x10 ? 1 : -1];

#endif
