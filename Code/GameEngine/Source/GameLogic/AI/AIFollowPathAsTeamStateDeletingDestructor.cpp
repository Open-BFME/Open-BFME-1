// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AIFollowPathAsTeamState scalar-deleting destructor at retail
// RVA 0x00183AC0 (30 bytes).  The exact three-argument constructor at
// 0x00183990 installs dedicated vtable 0x01099C08; its slot-zero ILT
// 0x00001D43 reaches this wrapper.  The wrapper calls complete-dtor ILT
// 0x00013F66, whose body is 0x00179550.  That body deletes the owned
// AIAttackMoveStateMachine at +0x60, then calls AIInternalMoveToState's
// destructor through ILT 0x0004AAF7.

class AIFollowPathAsTeamState
{
public:
	virtual ~AIFollowPathAsTeamState();
};

void forceAIFollowPathAsTeamStateDeletingDestructor()
{
	AIFollowPathAsTeamState value;
}
