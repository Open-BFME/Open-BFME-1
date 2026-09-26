// cl: /DNDEBUG /MD /EHsc
//
// The constructor at retail 0x002BE230 installs vtable 0x010C7868.
// Its first slot reaches the scalar deleting destructor at 0x002C1A90;
// that wrapper calls the class destructor through ILT 0x00031ACF.

class AIGiantBirdSwoopState
{
public:
	virtual ~AIGiantBirdSwoopState();
};

__declspec(noinline) AIGiantBirdSwoopState::~AIGiantBirdSwoopState() {}

void Force_AIGiantBirdSwoopState_Deleting_Destructor(
	AIGiantBirdSwoopState *state)
{
	delete state;
}
