// cl: /O2
//
// AIAttackMeleeApproachState complete destructor, retail RVA 0x00185480 (5 bytes).
// The matched scalar-deleting destructor 0x00185450 calls it through ILT
// 0x0002CB56 (ilt_oracle: CONFIRMED for this name). Its body is a single jump
// through ILT 0x0004AAF7 to the matched AIInternalMoveToState destructor
// (0x00172430, ilt_oracle CONFIRMED): the state adds nothing to destroy.
// novtable here only drops the dead derived-vptr store retail does not have.

class AIInternalMoveToState
{
public:
	virtual ~AIInternalMoveToState();
};

class __declspec(novtable) AIAttackMeleeApproachState : public AIInternalMoveToState
{
public:
	virtual ~AIAttackMeleeApproachState();
};

AIAttackMeleeApproachState::~AIAttackMeleeApproachState()
{
}
