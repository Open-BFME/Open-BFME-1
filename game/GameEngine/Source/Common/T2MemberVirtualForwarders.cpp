// Wrappers that forward to a virtual on an object held at this+0xC.
struct T2FwdIface
{
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
};

struct T2FwdLead
{
	virtual void lead();
};

// The four rows at 0x008035B0 load the vptr at m_p+4 and then step ecx by 4, so
// the interface is a SECOND base of what m_p points at.
struct T2FwdObj : public T2FwdLead, public T2FwdIface
{
};

struct T2FwdHolder
{
	char m_head[0xC];
	T2FwdObj *m_p;

	void f0();
	void f1();
	void f2();
	void f3();
};

void T2FwdHolder::f0() { m_p->s0(); }
void T2FwdHolder::f1() { m_p->s1(); }
void T2FwdHolder::f2() { m_p->s2(); }
void T2FwdHolder::f3() { m_p->s3(); }

// The two eight-byte rows that used to sit here are slot 3 of the narrow and
// the wide messages vtables at VA 0x0112FB8C and 0x0112FBB8, so they are
// do_close and they now come from
// game/Libraries/Source/WWVegas/WWLib/stlport_messages_do_open.cpp.
