// cl: /DNDEBUG /MD /EHsc
//
// The constructor at retail 0x002C04D0 installs vtable 0x010C7C28, and its
// adjacent exact name getter identifies GiantBirdGuardOuterState.  Slot zero
// reaches the scalar deleting destructor at 0x002C1CC0, which calls the
// complete destructor through ILT 0x00038118.

class GiantBirdGuardOuterState
{
public:
	virtual ~GiantBirdGuardOuterState();
};

__declspec(noinline) GiantBirdGuardOuterState::~GiantBirdGuardOuterState() {}

void Force_GiantBirdGuardOuterState_Deleting_Destructor(
	GiantBirdGuardOuterState *state)
{
	delete state;
}
