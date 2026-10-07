// cl: /DNDEBUG /MD /EHsc
//
// AIDockMoveToRallyState complete destructor at retail 0x0014F680
// (5 bytes). ??_GAIDockMoveToRallyState (0x0014F650, its own TU) calls it
// through ILT 0x00031C9B; the body is one tail jump through ILT 0x0004AAF7
// into ??1AIInternalMoveToState@@UAE@XZ (0x00172430), with no vptr re-seat
// of its own. novtable reproduces the missing re-seat; it lives apart from
// the ??_G TU because a novtable class there would no longer emit its
// vftable and ??_G.

class AIInternalMoveToState
{
public:
	virtual ~AIInternalMoveToState();
};

class __declspec(novtable) AIDockMoveToRallyState : public AIInternalMoveToState
{
public:
	virtual ~AIDockMoveToRallyState();
};

AIDockMoveToRallyState::~AIDockMoveToRallyState()
{
}
