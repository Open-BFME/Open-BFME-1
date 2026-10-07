// cl: /DNDEBUG /MD /EHsc
//
// AIDockAdvancePositionState complete destructor at retail 0x0014F500
// (5 bytes). ??_GAIDockAdvancePositionState (0x0014F4D0, its own TU) calls it
// through ILT 0x00016F31; the body is one tail jump through ILT 0x0004AAF7
// into ??1AIInternalMoveToState@@UAE@XZ (0x00172430), with no vptr re-seat
// of its own. novtable reproduces the missing re-seat; it lives apart from
// the ??_G TU because a novtable class there would no longer emit its
// vftable and ??_G.

class AIInternalMoveToState
{
public:
	virtual ~AIInternalMoveToState();
};

class __declspec(novtable) AIDockAdvancePositionState : public AIInternalMoveToState
{
public:
	virtual ~AIDockAdvancePositionState();
};

AIDockAdvancePositionState::~AIDockAdvancePositionState()
{
}
