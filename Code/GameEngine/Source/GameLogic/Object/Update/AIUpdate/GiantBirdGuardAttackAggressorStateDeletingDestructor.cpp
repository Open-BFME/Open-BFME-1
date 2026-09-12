// cl: /DNDEBUG /MD /EHsc
//
// The constructor at retail 0x002C11E0 names
// GiantBirdGuardAttackAggressorState and installs vtable 0x010C7D88.
// Its first slot reaches the scalar deleting destructor at 0x002C1D40;
// that wrapper calls the complete destructor through ILT 0x0000FDC1.

class GiantBirdGuardAttackAggressorState
{
public:
	virtual ~GiantBirdGuardAttackAggressorState();
};

__declspec(noinline)
GiantBirdGuardAttackAggressorState::~GiantBirdGuardAttackAggressorState() {}

void Force_GiantBirdGuardAttackAggressorState_Deleting_Destructor(
	GiantBirdGuardAttackAggressorState *state)
{
	delete state;
}
