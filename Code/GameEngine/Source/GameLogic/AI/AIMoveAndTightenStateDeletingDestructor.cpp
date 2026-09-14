// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIMoveAndTightenState's scalar-deleting destructor at retail
// 0x00185260 (30 bytes).  Its named constructor at 0x0017F390 installs the
// dedicated vtable 0x0109A2F0, whose slot zero routes through ILT 0x00035BB1.
// The wrapper's complete-dtor ILT 0x000174A9 reaches the existing
// AIInternalMoveToState teardown through the 5-byte thunk at 0x0017F440.
//
// The nearby 54-byte constructor at 0x0017F3F0 has the same vtable and the
// same +0x50/+0x54 field stores, but takes the shipped header's second
// (StateMachine *, const char *) overload.  It is not an address-derived
// base/derived alias: the derived AIMoveAwayFromRepulsorsState constructor at
// 0x0017F450 installs its distinct vtable 0x0109A368.

class State
{
public:
	virtual ~State();
};

class AIInternalMoveToState : public State
{
public:
	virtual ~AIInternalMoveToState();
};

class AIMoveAndTightenState : public AIInternalMoveToState
{
	friend void forceAIMoveAndTightenStateDeletingDestructor();

protected:
	virtual ~AIMoveAndTightenState();
};

void forceAIMoveAndTightenStateDeletingDestructor()
{
	AIMoveAndTightenState value;
}
