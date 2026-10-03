struct BfmeSrcDPD
{
	int m_bfmeA;
	int m_bfmeB;
};

// 0x0001AB86 is retail's 5-byte ILT thunk (?j_0001ab86@@YAXXZ); the
// __thiscall member behind it is routed through the thunk's address.
extern void j_0001ab86();

class BfmeOtherDPD
{
public:
	unsigned char m_bfmeHead[8];
	int m_bfmeA;
	int m_bfmeB;
};

BfmeOtherDPD *bfmeGoDPD(BfmeOtherDPD *other, void *value, BfmeSrcDPD *src)
{
	volatile int tmp = 0;
	typedef void (BfmeOtherDPD::*Call)(void *);
	union { void *raw; Call method; } u;
	u.raw = (void *)j_0001ab86;
	(other->*u.method)(value);
	other->m_bfmeA = src->m_bfmeA;
	other->m_bfmeB = src->m_bfmeB;
	return other;
}