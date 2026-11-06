// cl: /DNDEBUG /MD /EHsc
//
// GiantBirdFollowPathState complete destructor at retail 0x002BDDB0
// (5 bytes). ??_GGiantBirdFollowPathState (0x002BDD80, its own TU) calls it
// through ILT 0x0002824A; the body is one tail jump through ILT 0x0004AAF7
// into ??1AIInternalMoveToState@@UAE@XZ (0x00172430), with no vptr re-seat
// of its own. novtable reproduces the missing re-seat; it lives apart from
// the ??_G TU because a novtable class there would no longer emit its
// vftable and ??_G.

class AIInternalMoveToState
{
public:
	virtual ~AIInternalMoveToState();
};

class __declspec(novtable) GiantBirdFollowPathState : public AIInternalMoveToState
{
public:
	virtual ~GiantBirdFollowPathState();
};

GiantBirdFollowPathState::~GiantBirdFollowPathState()
{
}
