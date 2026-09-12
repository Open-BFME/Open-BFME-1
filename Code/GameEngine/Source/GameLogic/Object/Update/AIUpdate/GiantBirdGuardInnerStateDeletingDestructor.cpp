// cl: /DNDEBUG /MD /EHsc
//
// The constructor at retail 0x002C03F0 installs vtable 0x010C7B28;
// the adjacent name getter identifies GiantBirdGuardInnerState.  Vtable slot
// zero reaches the scalar deleting destructor at 0x002C1C40, which calls the
// complete destructor through ILT 0x000317DC.

class GiantBirdGuardInnerState
{
public:
	virtual ~GiantBirdGuardInnerState();
};

__declspec(noinline) GiantBirdGuardInnerState::~GiantBirdGuardInnerState() {}

void Force_GiantBirdGuardInnerState_Deleting_Destructor(
	GiantBirdGuardInnerState *state)
{
	delete state;
}
