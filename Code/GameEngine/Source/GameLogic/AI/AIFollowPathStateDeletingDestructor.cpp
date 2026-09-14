// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIFollowPathState scalar-deleting destructor at retail RVA
// 0x00185600 (30 bytes). The exact constructor at 0x0017FC60 installs vtable
// 0x0109A9F0. Its slot zero routes through ILT 0x00014B0A to this wrapper;
// its name, update, and onExit slots plus the shipped class declaration prove
// identity. The complete destructor chains to AIInternalMoveToState.

class AIFollowPathState
{
protected:
	virtual ~AIFollowPathState();

private:
	friend void forceAIFollowPathStateDeletingDestructor();
};

void forceAIFollowPathStateDeletingDestructor()
{
	AIFollowPathState value;
}
