// cl: /DNDEBUG /MD /EHsc
//
// The constructor at retail 0x002BE400 installs vtable 0x010C78D8.
// Its first slot reaches the scalar deleting destructor at 0x002C1AD0;
// that wrapper calls the class destructor through ILT 0x00002EA0.

class AIGiantBirdAttackState
{
public:
	virtual ~AIGiantBirdAttackState();
};

__declspec(noinline) AIGiantBirdAttackState::~AIGiantBirdAttackState() {}

void Force_AIGiantBirdAttackState_Deleting_Destructor(
	AIGiantBirdAttackState *state)
{
	delete state;
}
