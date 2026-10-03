// 0x00031507 is retail's 5-byte ILT thunk (?j_00031507@@YAXXZ); the callee's
// own identity is not recovered, so the __thiscall is routed through the
// thunk's address.
extern void j_00031507();

class BfmeOtherDPH
{
	unsigned char m_bfmeHead[4];
};

class BfmeSubDPH
{
};

class BfmeThingDPH
{
public:
	BfmeOtherDPH *bfmeGoDPH(BfmeOtherDPH *other);
	unsigned char m_bfmeHead[0x170];
	BfmeSubDPH m_bfmeSub;
};

BfmeOtherDPH *BfmeThingDPH::bfmeGoDPH(BfmeOtherDPH *other)
{
	volatile int tmp = 0;
	typedef void (BfmeSubDPH::*Call)(BfmeOtherDPH *);
	union { void (*address)(); Call member; } call = { j_00031507 };
	(m_bfmeSub.*call.member)(other);
	return other;
}
