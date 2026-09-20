// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

typedef int Int;
typedef float Real;

class BObj;

// The object at this+0x08. Only the two vtable slots the body reaches
// (0x3C = index 15, 0x20 = index 8) and the +0x08 sub-object pointer are
// witnessed; everything else is a neutral placeholder slot.
class AObj
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual Int query8(Real p1, Real p2, Real p3, Real p4);
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual Int query15(void);

	unsigned char m_unmodelled_000[0x4];
	BObj *m_sub;
};

// Retail's still-dump direct callee at 0x0081D520: thiscall, one Int
// stack arg, no named owner.
class Handler
{
public:
	void handle(Int value);
};

class BObj
{
public:
	unsigned char m_unmodelled_000[0x18];
	Handler *m_handler;
};

// Local Display view: only the one slot this body reaches (0xE0 = index
// 56) is witnessed; everything before it is a neutral placeholder.
class Display
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void drawHandleAt(Int flag, Real x0, Real y0, Real x1, Real y1,
		void *handle);
};

extern Display *TheDisplay;

// Retail 0x004942C0: a thiscall member with no owning class, source
// declaration or unique exported symbol recoverable (blocked once
// already). Every name below keeps the body's own address token.
class Rva004942C0Owner
{
public:
	void run(void);

private:
	unsigned char m_unmodelled_000[0x8];
	AObj *m_a;
	Int m_rectA;
	Int m_rectB;
	Int m_rectC;
	Int m_rectD;
	unsigned char m_unmodelled_01c[0x20 - 0x1c];
	unsigned char m_flags;
	unsigned char m_unmodelled_021[0x24 - 0x21];
	void *m_handle;
};

void Rva004942C0Owner::run(void)
{
	if (!(m_flags & 1))
		return;
	if (!m_a)
		return;

	Int flag = m_a->query15();
	if (!flag)
		return;

	if (TheDisplay)
	{
		TheDisplay->drawHandleAt(flag, (Real)m_rectA, (Real)m_rectB,
			(Real)m_rectC, (Real)m_rectD, m_handle);
	}

	Handler *handler = m_a->m_sub->m_handler;
	if (!handler)
		return;

	Int value = m_a->query8((Real)m_rectA, (Real)m_rectB, (Real)m_rectC, (Real)m_rectD);
	handler->handle(value);
}
