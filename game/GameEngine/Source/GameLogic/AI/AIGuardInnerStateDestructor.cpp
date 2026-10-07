// cl: /O2 /DNDEBUG /MD /EHsc
//
// Retail 0x0015D140: AIGuardInnerState's public complete destructor. The
// matched ??_G (0x0015D110) reaches it through ILT 0x000434CD, pinned as
// ??1AIGuardInnerState@@UAE@XZ. The class adds nothing to destroy and the base
// destructor re-seats the vptr at once, so retail drops this class's own
// store (novtable here): the body is a single tail jump to the
// State destructor (ILT 0x00016725, pinned ??1State@@UAE@XZ).

struct State
{
	virtual ~State();
};

class __declspec(novtable) AIGuardInnerState : public State
{
public:
	virtual ~AIGuardInnerState();
};

AIGuardInnerState::~AIGuardInnerState()
{
}
