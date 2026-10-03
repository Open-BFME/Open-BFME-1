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

// Retail's callee at 0x00029311 is the AIInternalMoveToState::onExit ILT
// (game/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateOnExitShim.cpp);
// the call site pushes one word and reaches it through ECX.
enum StateExitType
{
};

class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);
};

class BfmeThingRZ
{
public:
	void bfmeGoRZ(void *what);
	unsigned char m_bfmeHead[0x1c];
	BfmeOuterRZ *m_bfmeOuter;
};

void BfmeThingRZ::bfmeGoRZ(void *what)
{
	((AIInternalMoveToState *)this)->AIInternalMoveToState::onExit((StateExitType)(int)what);
	BfmeMidRZ *mid = m_bfmeOuter->m_bfmeInner->m_bfmeMid;
	if (mid != 0)
	{
		BfmeDeepRZ *deep = mid->m_bfmeDeep;
		if (deep != 0)
			deep->m_bfmeFlags &= 0xfffffff7;
	}
}
