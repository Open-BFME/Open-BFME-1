// cl: /DNDEBUG /MD /EHsc
//
// The constructor at retail 0x002BEC00 installs vtable 0x010C7968.
// Its first slot reaches the scalar deleting destructor at 0x002C1B10;
// that wrapper calls the class destructor through ILT 0x0003EFC2.

class AIGiantBirdFollowThruState
{
public:
	virtual ~AIGiantBirdFollowThruState();
};

__declspec(noinline) AIGiantBirdFollowThruState::~AIGiantBirdFollowThruState() {}

void Force_AIGiantBirdFollowThruState_Deleting_Destructor(
	AIGiantBirdFollowThruState *state)
{
	delete state;
}
