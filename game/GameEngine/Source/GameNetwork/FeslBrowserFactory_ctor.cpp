// cl: /O2 /GX-
// FESL browser factory ctor at 0x803820 (104B).
// The matching dtor at 0x803890 and the retail vtables prove this dual-vptr
// owner layout. The secondary base writes the incomplete vtable before the
// owner installs its two final vtables.

#include <new>

// 0x0112B9C0 is the secondary base's own four-slot table, which the table does not name.
extern const void *const g_0112B9C0[];
// Four-entry secondary dispatch table at retail VA 0x0112C728. The next
// primary table begins at 0x0112C738. Each slot names an existing matched
// forwarding body; these declarations take addresses only.
extern "C" void __identifier("?f0@T2FwdHolder@@QAEXXZ")();
extern "C" void __identifier("?f1@T2FwdHolder@@QAEXXZ")();
extern "C" void __identifier("?f2@T2FwdHolder@@QAEXXZ")();
extern "C" void __identifier("?f3@T2FwdHolder@@QAEXXZ")();

void *g_Rva00803890Vt2[4] =
{
	(void *)__identifier("?f0@T2FwdHolder@@QAEXXZ"),
	(void *)__identifier("?f1@T2FwdHolder@@QAEXXZ"),
	(void *)__identifier("?f2@T2FwdHolder@@QAEXXZ"),
	(void *)__identifier("?f3@T2FwdHolder@@QAEXXZ")
};
extern "C" void *bfmeVftRva00803890Owner[];
#pragma comment(linker, "/alternatename:_bfmeVftRva00803890Owner=??_7Rva00803890Owner@@6B@")

struct BfmeOwnerUNC
{
};

class BfmeThingUNC
{
public:
	BfmeThingUNC( int value, BfmeOwnerUNC *owner );
};

class Gen007F0130
{
public:
	static void *operator new( unsigned int size );
};

class __declspec(novtable) Rva00803890Primary
{
public:
	virtual ~Rva00803890Primary();
};

class Rva00803890Secondary
{
public:
	Rva00803890Secondary()
	{
		*(int *)this = (int)g_0112B9C0;
	}

	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
};

class __declspec(novtable) Rva00803890Owner : public Rva00803890Primary, public Rva00803890Secondary
{
public:
	Rva00803890Owner( unsigned char flag, BfmeOwnerUNC *owner );

	unsigned char m_flag;
	unsigned char m_connected;
	unsigned char m_padding[2];
	BfmeOwnerUNC *m_owner;
	int m_registry;
	void *m_peer;
	void *m_child;
};

Rva00803890Owner::Rva00803890Owner( unsigned char flag, BfmeOwnerUNC *owner )
{
	*(int *)this = (int)bfmeVftRva00803890Owner;
	*(int *)( (char *)this + 4 ) = (int)g_Rva00803890Vt2;
	m_registry = 0;
	m_peer = 0;
	m_flag = flag;
	m_connected = 0;
	m_owner = owner;
	void *raw = Gen007F0130::operator new( 0x194 );
	m_child = raw != 0 ?
		(void *)new (raw) BfmeThingUNC( (int)this, owner ) : (void *)0;
}
