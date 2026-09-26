// cl: /DNDEBUG /MD /EHsc
//
// The constructor at retail 0x002BE000 installs vtable 0x010C77F0.
// Its first slot reaches the scalar deleting destructor at 0x002C1A60;
// that wrapper calls the class destructor through ILT 0x00022CE6.

class GiantBirdNormalFlightState
{
public:
	virtual ~GiantBirdNormalFlightState();
};

__declspec(noinline) GiantBirdNormalFlightState::~GiantBirdNormalFlightState() {}

void Force_GiantBirdNormalFlightState_Deleting_Destructor(
	GiantBirdNormalFlightState *state)
{
	delete state;
}
