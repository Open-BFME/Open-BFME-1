// cl: /DNDEBUG /MD /EHsc
//
// The constructor at retail 0x002BF6D0 installs vtable 0x010C7A60.
// Its first slot reaches the scalar deleting destructor at 0x002C1B90;
// that wrapper calls the complete destructor through ILT 0x00030FD0.

class GiantBirdAttackMoveToState
{
public:
	virtual ~GiantBirdAttackMoveToState();
};

__declspec(noinline) GiantBirdAttackMoveToState::~GiantBirdAttackMoveToState() {}

void Force_GiantBirdAttackMoveToState_Deleting_Destructor(
	GiantBirdAttackMoveToState *state)
{
	delete state;
}
