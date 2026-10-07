// cl: /O2 /DNDEBUG /MD /EHsc
//
// Retail 0x0015ECD0: AIGuardRetaliateReturnState's complete destructor. The
// matched ??_G (0x0015ECA0) reaches it through ILT 0x0002FD83, pinned as
// ??1AIGuardRetaliateReturnState@@UAE@XZ. The class adds nothing to destroy,
// and the base destructor re-seats
// the vptr at once, so retail drops this class's own store (novtable here):
// the body is a single tail jump to the AIInternalMoveToState destructor
// (ILT 0x0004AAF7 -> matched 0x00172430).

struct AIInternalMoveToState
{
	virtual ~AIInternalMoveToState();
};

class __declspec(novtable) AIGuardRetaliateReturnState : public AIInternalMoveToState
{
public:
	virtual ~AIGuardRetaliateReturnState();
};

AIGuardRetaliateReturnState::~AIGuardRetaliateReturnState()
{
}
