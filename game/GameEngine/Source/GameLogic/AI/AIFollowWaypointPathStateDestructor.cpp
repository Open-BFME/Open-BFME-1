// cl: /DNDEBUG /MD /EHsc
//
// AIFollowWaypointPathState complete destructor at retail 0x0017FA80
// (5 bytes). ??_GAIFollowWaypointPathState (0x001854D0, its own TU) calls it
// through ILT 0x00007D1F; the body is one tail jump through ILT 0x0004AAF7
// into ??1AIInternalMoveToState@@UAE@XZ (0x00172430), with no vptr re-seat
// of its own. novtable reproduces the missing re-seat; it lives apart from
// the ??_G TU because a novtable class there would no longer emit its
// vftable and ??_G.

class AIInternalMoveToState
{
public:
	virtual ~AIInternalMoveToState();
};

class __declspec(novtable) AIFollowWaypointPathState : public AIInternalMoveToState
{
public:
	virtual ~AIFollowWaypointPathState();
};

AIFollowWaypointPathState::~AIFollowWaypointPathState()
{
}
