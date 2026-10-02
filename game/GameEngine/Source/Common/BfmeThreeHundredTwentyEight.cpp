struct BfmeDeepRZ
{
	unsigned char m_bfmeHead[0x40];
	unsigned int m_bfmeFlags;
};

struct BfmeMidRZ
{
	unsigned char m_bfmeHead[0x1cc];
	BfmeDeepRZ *m_bfmeDeep;
};

struct BfmeInnerRZ
{
	unsigned char m_bfmeHead[0x204];
	BfmeMidRZ *m_bfmeMid;
};

struct BfmeOuterRZ
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerRZ *m_bfmeInner;
};

// Retail's callee at 0x00029311 is the AIInternalMoveToState::onExit ILT,
// defined as the cdecl no-arg body
// game/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateOnExitShim.cpp.
// Retail's call site pushes one argument and does no caller cleanup, which a
// cdecl spelling cannot express, so the declared cdecl name is reinterpreted
// through a union as a one-argument member-function view: MSVC folds the
// constant member pointer back into the same direct rel32 call retail has.
void Rva00029311AIInternalMoveToStateOnExitThunk(void);

struct Rva00029311ThunkHolder
{
	void step(void *what);
};

typedef void (Rva00029311ThunkHolder::*Rva00029311ThisCall)(void *what);

class BfmeThingRZ
{
public:
	void bfmeGoRZ(void *what);
	unsigned char m_bfmeHead[0x1c];
	BfmeOuterRZ *m_bfmeOuter;
};

void BfmeThingRZ::bfmeGoRZ(void *what)
{
	union Rva00029311Call
	{
		Rva00029311ThisCall member;
		void (__cdecl *plain)(void);
	};
	Rva00029311Call call;
	call.plain = &Rva00029311AIInternalMoveToStateOnExitThunk;
	(((Rva00029311ThunkHolder *)this)->*call.member)(what);
	BfmeMidRZ *mid = m_bfmeOuter->m_bfmeInner->m_bfmeMid;
	if (mid != 0)
	{
		BfmeDeepRZ *deep = mid->m_bfmeDeep;
		if (deep != 0)
			deep->m_bfmeFlags &= 0xfffffff7;
	}
}
