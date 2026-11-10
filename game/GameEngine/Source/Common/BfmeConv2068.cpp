class BfmeSubGQ
{
public:
	unsigned char m_bfmeGapGQ[8];
};

// The sub swap goes through ILT 0x00025176, the ledger's 5-byte row
// ?j_00025176@@YAXXZ (game/gen_small/thunks_017.cpp), as tools/callees.py
// 0x6a060 129 prints.  Nothing defines the pinned
// ?bfmeSwapSubGQ@@YAXPAVBfmeSubGQ@@0@Z, so the call names the thunk through a
// function pointer cast that keeps the two-argument cdecl shape.
void j_00025176();
typedef void (*BfmeSwapSubGQFn)(BfmeSubGQ *a, BfmeSubGQ *b);

class BfmeStateGQ
{
public:
	void swap(BfmeStateGQ *o);

	int m_bfmeA0GQ;
	int m_bfmeA1GQ;
	int m_bfmeA2GQ;
	int m_bfmeA3GQ;
	BfmeSubGQ m_bfmeSubGQ;
	int m_bfmeA4GQ;
	float m_bfmeF0GQ;
	float m_bfmeF1GQ;
	float m_bfmeF2GQ;
	float m_bfmeF3GQ;
};

void BfmeStateGQ::swap(BfmeStateGQ *other)
{
	volatile BfmeStateGQ *v = other;

	int t0 = m_bfmeA0GQ;
	m_bfmeA0GQ = v->m_bfmeA0GQ;
	v->m_bfmeA0GQ = t0;

	int t1 = m_bfmeA1GQ;
	m_bfmeA1GQ = v->m_bfmeA1GQ;
	v->m_bfmeA1GQ = t1;

	int t4 = m_bfmeA4GQ;
	m_bfmeA4GQ = v->m_bfmeA4GQ;
	v->m_bfmeA4GQ = t4;

	float f0 = m_bfmeF0GQ;
	m_bfmeF0GQ = other->m_bfmeF0GQ;
	other->m_bfmeF0GQ = f0;

	float f1 = m_bfmeF1GQ;
	m_bfmeF1GQ = other->m_bfmeF1GQ;
	other->m_bfmeF1GQ = f1;

	float f2 = m_bfmeF2GQ;
	m_bfmeF2GQ = other->m_bfmeF2GQ;
	other->m_bfmeF2GQ = f2;

	float f3 = m_bfmeF3GQ;
	m_bfmeF3GQ = other->m_bfmeF3GQ;
	other->m_bfmeF3GQ = f3;

	int t2 = m_bfmeA2GQ;
	m_bfmeA2GQ = v->m_bfmeA2GQ;
	v->m_bfmeA2GQ = t2;

	int t3 = m_bfmeA3GQ;
	m_bfmeA3GQ = v->m_bfmeA3GQ;
	v->m_bfmeA3GQ = t3;

	((BfmeSwapSubGQFn)&j_00025176)(&m_bfmeSubGQ, &other->m_bfmeSubGQ);
}
