// Retail's call at 0x0016CC5A targets the ILT entry 0x0004AB4C, the 5-byte
// thunk in front of the body at 0x00673960; that thunk symbol is the only
// name defined at the call target, so this TU references it directly.  The
// member-pointer view in the body types the call thiscall (ecx = sub, the int
// pushed and popped by the callee) without defining BfmeSubAHA.
class BfmeSubAHA
{
};
extern "C" void __identifier("?j_0004ab4c@@YAXXZ")();

class BfmeKillAHA
{
public:
	virtual void bfmeReleaseAHA(int what);
};

struct BfmeMidAHA
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubAHA *m_bfmeSub;
	unsigned char m_bfmeGap[0x19c];
	int m_bfmeFlag;
};

struct BfmeOwnerAHA
{
	unsigned char m_bfmeHead[0x10];
	BfmeMidAHA *m_bfmeMid;
};

class BfmeThingAHA
{
public:
	void bfmeGoAHA(void *what);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerAHA *m_bfmeOwner;
	unsigned char m_bfmeGapTwo[4];
	BfmeKillAHA *m_bfmeKill;
};

void BfmeThingAHA::bfmeGoAHA(void *what)
{
	BfmeSubAHA *sub = m_bfmeOwner->m_bfmeMid->m_bfmeSub;
	if (sub != 0)
	{
		union {
			void (*thunk)();
			void (BfmeSubAHA::*method)(int);
		} stop;
		stop.thunk = &__identifier("?j_0004ab4c@@YAXXZ");
		(sub->*stop.method)(0);
	}
	m_bfmeOwner->m_bfmeMid->m_bfmeFlag = 0;
	BfmeKillAHA *kill = m_bfmeKill;
	if (kill != 0)
	{
		kill->bfmeReleaseAHA(1);
		m_bfmeKill = 0;
	}
}
