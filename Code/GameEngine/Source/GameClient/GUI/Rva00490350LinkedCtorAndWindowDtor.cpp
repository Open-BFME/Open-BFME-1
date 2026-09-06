// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: two more members of the address-derived linked-object family
// whose base destructor landed in Rva00490350LinkedDestructor.cpp. The base
// keeps every instance on a singly linked list headed by Rva00490350Head
// (m_link = previous head, head = this) and unlinks itself in its destructor.
//   0x004902C0 (110 B): Rva00490350Derived(int arg, int token) -- base ctor,
//     token, derived vtable, arg stored at +8, then the previous head is told
//     about the new arg through its vtable slot 1 (EH frame around that call).
//   0x00490470 (107 B): the destructor of a sibling that keeps a GameWindow at
//     +8: destroy it through TheWindowManager (vtable slot 0x1e), null it,
//     then the inlined base destructor.
class Rva00490350Base;
extern Rva00490350Base *Rva00490350Head;

class Rva00490350Link
{
public:
	virtual void slot0();
	virtual void notify( int token );
};

class Rva00490350Base
{
public:
	Rva00490350Base() : m_link( (Rva00490350Link *)Rva00490350Head )
	{
		Rva00490350Head = this;
	}
	// The table owner's base subobject: no payload, flag set.
	Rva00490350Base( bool flag )
		: m_link( (Rva00490350Link *)Rva00490350Head )
	{
		Rva00490350Head = this;
		m_unused = 0;
		m_flag = flag;
	}
	virtual ~Rva00490350Base()
	{
		if( Rva00490350Head == this )
			Rva00490350Head = (Rva00490350Base *)m_link;
	}
	virtual void slot1();
protected:
	Rva00490350Link *m_link;
	int m_unused;
	union
	{
		int m_token;
		bool m_flag;
	};
};

class Rva00490350Derived : public Rva00490350Base
{
public:
	Rva00490350Derived( int arg, int token );
	virtual ~Rva00490350Derived();
	virtual void slot1();
};

Rva00490350Derived::Rva00490350Derived( int arg, int token )
{
	m_token = token;
	m_unused = arg;
	if( m_link )
		m_link->notify( arg );
}

class GameWindow;
class GameWindowManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s0a(); virtual void s0b(); virtual void s0c(); virtual void s0d(); virtual void s0e();
	virtual void s0f(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
	virtual void s19(); virtual void s1a(); virtual void s1b(); virtual void s1c(); virtual void s1d();
	virtual int winDestroy( GameWindow *window );
};
extern GameWindowManager *TheWindowManager;

class Rva00490470 : public Rva00490350Base
{
public:
	virtual ~Rva00490470();
	virtual void slot1();
};

Rva00490470::~Rva00490470()
{
	GameWindow *window = (GameWindow *)m_unused;
	if( window )
		TheWindowManager->winDestroy( window );
	m_unused = 0;
}

// 0x00490A30 (108 B): the constructor of a third sibling, a table owner: base
// link-in, its own +8/+0xc scalars, the derived vtable, one flag at +0x130,
// then eleven 8-entry tables reset in one loop (ten zeroed, one set to -1).
class Rva00490A30 : public Rva00490350Base
{
public:
	Rva00490A30();
	virtual void slot1();
private:
	int m_table0[8];
	int m_table1[8];
	int m_table2[8];
	int m_table3[8];
	int m_table4[8];
	int m_table5[8];
	int m_table6[8];
	int m_table7[8];
	int m_table8[8];
	int m_count130;
	int m_table9[8];
	int m_table10[8];
};

Rva00490A30::Rva00490A30()
	: Rva00490350Base( true )
{
	m_count130 = 0;
	for( int i = 0; i < 8; i++ )
	{
		m_table9[i] = 0;
		m_table7[i] = 0;
		m_table8[i] = 0;
		m_table0[i] = 0;
		m_table1[i] = 0;
		m_table2[i] = 0;
		m_table10[i] = -1;
		m_table3[i] = 0;
		m_table4[i] = 0;
		m_table5[i] = 0;
		m_table6[i] = 0;
	}
}
