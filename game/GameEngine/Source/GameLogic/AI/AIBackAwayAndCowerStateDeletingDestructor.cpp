// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIBackAwayAndCowerState.
// Vtable 0x00C97AF8 slots name this class (?onEnter@AIBackAwayAndCowerState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00014CF9 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000061CC reaches cleanup body 0x00173F30.

// The protected scalar-deleting destructor (??_G, matched 30B row) must call
// the rowed complete destructor ??1Rva00173F30 (0x00173F30, defined in
// R4OwnedPointerDestructors.cpp) rather than an AIBackAwayAndCowerState
// complete destructor nothing defines. An implicit derived destructor
// inlines into the generated ??_G wrapper, leaving the direct base call.
struct State { virtual ~State(); };
class __declspec( novtable ) R4Base000A1B30
{
public:
	virtual ~R4Base000A1B30()
	{
		reinterpret_cast<State *>(this)->State::~State();
	}
};
struct GenOwned { virtual ~GenOwned(); };
struct Rva00173F30 : public R4Base000A1B30
{
	char m_pad[0x20];
	GenOwned *m_owned;
	virtual ~Rva00173F30();
};

class AIBackAwayAndCowerState : public Rva00173F30
{
protected:
	virtual ~AIBackAwayAndCowerState();
private:
	friend void forceAIBackAwayAndCowerStateDeletingDestructor();
};

// ??1AIBackAwayAndCowerState@@MAE@XZ present-unmatched
AIBackAwayAndCowerState::~AIBackAwayAndCowerState()
{
}

void forceAIBackAwayAndCowerStateDeletingDestructor()
{
	AIBackAwayAndCowerState value;
}
