// cl: /DNDEBUG /MD /EHsc
//
// The constructor at retail 0x002BEFA0 installs vtable 0x010C79E0.
// Its first slot reaches the scalar deleting destructor at 0x002C1B50;
// that wrapper calls the class destructor through ILT 0x00015C8A.

class GiantBirdFollowWaypointPathState
{
public:
	virtual ~GiantBirdFollowWaypointPathState();
};

__declspec(noinline) GiantBirdFollowWaypointPathState::~GiantBirdFollowWaypointPathState() {}

void Force_GiantBirdFollowWaypointPathState_Deleting_Destructor(
	GiantBirdFollowWaypointPathState *state)
{
	delete state;
}
