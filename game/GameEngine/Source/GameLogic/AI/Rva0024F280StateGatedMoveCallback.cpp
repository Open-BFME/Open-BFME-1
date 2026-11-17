// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob2
// ?Rva0024F280@@YAXPAVObject@@PAX@Z
//
// Retail 0x0024F280 (64 bytes): an __cdecl (Object *, void *userData) iterate
// callback. Its only reference is the function pointer bfmeNotifyYT
// (0x0024F2D0, BfmeConv1793.cpp) passes to two container visits, so the
// owning file and the callback's own name are unknown: address-derived.
//
// Layout witnesses: Object+0x204 is m_ai and AIUpdateInterface+0x30 is
// m_stateMachine (W3DWaypointBufferDrawWaypoints.cpp); 999999 is ZH's
// INVALID_STATE_ID, returned by StateMachine::getCurrentStateID() when
// m_currentState (+0x1C) is null, otherwise State::m_ID (+0x04). The call
// goes through the AICommandInterface base at AIUpdateInterface+0x20 to the
// ILT 0x0001C26A, which jumps to 0x00152B20 (callees.py), the ledgered
// AICommandInterface::aiBfmeCommand42(Object *, CommandSourceType); the twin
// aiMoveToObject body at 0x002A8060 is a different retail copy. State ids 0x38
// and 0x0F are left numeric: BFME's AIStateType numbering is not witnessed.

#include "../command_source_type.h"

typedef unsigned int StateID;
enum { INVALID_STATE_ID = 999999 };

class Object;

class State
{
public:
	StateID getID() const { return m_ID; }

	void *m_vtable;
	StateID m_ID;
};

class StateMachine
{
public:
	StateID getCurrentStateID() const { return m_currentState ? m_currentState->getID() : INVALID_STATE_ID; }

	unsigned char m_unreconstructed_000[0x1C];
	State *m_currentState;
};

class AICommandInterface
{
public:
	void aiBfmeCommand42(Object *obj, CommandSourceType cmd);
};

class Rva0024F280UpdateBase
{
	unsigned char m_unreconstructed_000[0x20];
};

class AIUpdateInterface : public Rva0024F280UpdateBase, public AICommandInterface
{
public:
	StateMachine *getStateMachine() const { return m_stateMachine; }

	unsigned char m_unreconstructed_021[0x30 - 0x21];
	StateMachine *m_stateMachine;
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }

	unsigned char m_unreconstructed_000[0x204];
	AIUpdateInterface *m_ai;
};

void Rva0024F280(Object *obj, void *userData)
{
	if (!obj)
		return;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return;
	StateID id = ai->getStateMachine()->getCurrentStateID();
	if (id == 0x38 || id == 0xF)
		return;
	ai->aiBfmeCommand42((Object *)userData, CMD_FROM_AI);
}
