// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for
// AIHarvestApproachSiteState at retail RVA 0x0015FD70. AIHarvestMachine's
// constructor at 0x0015FD00 passes the exact state name and installs vtable
// 0x010966F8; that table's slot zero routes through ILT 0x0000F8D5.
// The complete destructor route is ILT 0x000240FA, which reaches the
// canonical AIInternalMoveToState cleanup path.

// That ILT reaches 0x0015FDA0, a five-byte jump to the matched
// ??1AIInternalMoveToState (ILT 0x0004AAF7 -> 0x00172430). The derived
// destructor is implicit: the compiler emits it as that jump.
class AIInternalMoveToState
{
public:
	virtual ~AIInternalMoveToState();
};

// ??1AIHarvestApproachSiteState@@UAE@XZ
class AIHarvestApproachSiteState : public AIInternalMoveToState
{
private:
	friend void forceAIHarvestApproachSiteStateDeletingDestructor();
};

void forceAIHarvestApproachSiteStateDeletingDestructor()
{
	AIHarvestApproachSiteState value;
}
