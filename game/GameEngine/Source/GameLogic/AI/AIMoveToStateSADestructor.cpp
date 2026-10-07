// cl: /O2 /DNDEBUG /MD /EHsc
//
// Retail 0x00182180: AIMoveToStateSA's public complete destructor. The
// matched ??_G (0x00182150) reaches it through ILT 0x0004B475, pinned as
// ??1AIMoveToStateSA@@UAE@XZ. The class adds nothing to destroy and the base
// destructor re-seats the vptr at once, so retail drops this class's own
// store (novtable here): the body is a single tail jump to the
// AIInternalMoveToState destructor (ILT 0x0004AAF7 -> matched 0x00172430).

struct AIInternalMoveToState
{
	virtual ~AIInternalMoveToState();
};

class __declspec(novtable) AIMoveToStateSA : public AIInternalMoveToState
{
public:
	virtual ~AIMoveToStateSA();
};

AIMoveToStateSA::~AIMoveToStateSA()
{
}
