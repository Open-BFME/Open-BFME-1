// Open-BFME5 conversions.

struct BfmeNode915A
{
	BfmeNode915A *m_bfmeNext;
	BfmeNode915A *m_bfmePrev;
	void *m_bfmeKey;
};

void bfmeFree915A(void *p, unsigned int n);

class BfmeThing915A
{
public:
	void bfmeGo915A(void *k);
	char m_bfmePad[0x288];
	BfmeNode915A *m_bfmeList;
};


// Retail reaches the tail comparison through the five-byte thunk at ILT
// 0x00049EA4, which the ledger defines as ?j_00049ea4@@YAXXZ in
// game/gen_small/thunks_035.cpp and nothing else defines. The element's member
// is therefore spelled as that thunk name; see Thunk915C below for how the
// __thiscall shape is restored.
void j_00049ea4();

class BfmeElem915C
{
public:
	char m_bfmePad[0x24];
};

// VC7 rejects __thiscall on a function pointer (error C4234), so the ecx-passed
// tail call is expressed through a pointer-to-member-function held in a union.
// For a non-virtual member of a single-inheritance class that representation is
// the plain code address, and the call is still __thiscall.
union Thunk915C
{
	void (*f_tail)();
	int (BfmeElem915C::*m_tail)(void *);
};

class BfmeThing915C
{
public:
	int bfmeGo915C(void *a);
	char m_bfmePad[0x2c4];
	BfmeElem915C *volatile m_bfmeBeg;
	BfmeElem915C *m_bfmeEnd;
};

int BfmeThing915C::bfmeGo915C(void *a)
{
	if (m_bfmeEnd - m_bfmeBeg > 0)
	{
		BfmeElem915C *beg = m_bfmeBeg;
		Thunk915C u;
		u.f_tail = j_00049ea4;

		return (beg->*u.m_tail)(a);
	}

	return 0;
}

