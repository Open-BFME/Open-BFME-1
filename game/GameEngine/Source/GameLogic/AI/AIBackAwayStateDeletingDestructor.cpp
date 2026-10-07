// cl: /DNDEBUG /MD /EHsc
//
// The exact constructor at 0x001804B0 passes the AIBackAwayState literal and
// installs vtable 0x0109AE00. Its slot-zero ILT 0x00025E19 identifies the
// retail scalar-deleting wrapper at 0x00185890; the wrapper calls complete-
// destructor ILT 0x0004915C.

// That ILT reaches 0x001858C0, a five-byte jump to the matched
// ??1AIInternalMoveToState (ILT 0x0004AAF7 -> 0x00172430): the derived
// complete destructor has nothing of its own to tear down.
class AIInternalMoveToState
{
public:
	virtual ~AIInternalMoveToState();
};

// The derived destructor is implicit: the compiler emits it as that jump.
// ??1AIBackAwayState@@UAE@XZ
class AIBackAwayState : public AIInternalMoveToState
{
private:
	friend void forceAIBackAwayStateDeletingDestructor();
};

void forceAIBackAwayStateDeletingDestructor()
{
	AIBackAwayState value;
}
