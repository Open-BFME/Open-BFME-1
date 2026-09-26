// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIFollowWaypointPathState scalar-deleting destructor at retail
// RVA 0x001854D0 (30 bytes). The exact constructor at 0x0017F980 installs
// vtable 0x0109A7B0, whose slot zero routes through ILT 0x0000A556 to this
// wrapper; the wrapper calls the complete destructor through ILT 0x00007D1F.

class AIFollowWaypointPathState
{
protected:
	virtual ~AIFollowWaypointPathState();
private:
	friend void forceAIFollowWaypointPathStateDeletingDestructor();
};

void forceAIFollowWaypointPathStateDeletingDestructor()
{
	AIFollowWaypointPathState value;
}
