// cl: /GX- /GS
// jabba gamebrowserdemangler.cpp constructor at 0x00800920 (210B).

extern int vftable_0112B89C;
extern int vftable_011296B0;

class Rva7F4CC0Child
{
public:
	Rva7F4CC0Child();                                                // 0x007E86B0
	virtual void v0();
	int m_04;
};

class Rva00800920Addr : public Rva7F4CC0Child
{
public:
	Rva00800920Addr()
	{
		*(int *)this = (int)&vftable_011296B0;
		m_08 = 0;
		m_0C = 0;
		*(int *)( (char *)this + 4 ) = 0;
	}

	void *m_08;
	void *m_0C;
};

struct Rva00800920Slot
{
	int m_00;
	int m_04;
	char m_08;
	char m_pad09[3];
	int m_0C;
	Rva00800920Addr m_addr;
	int m_20;

	Rva00800920Slot()
	{
		m_00 = 0;
		m_04 = 0;
		m_0C = 0;
		m_20 = 0;
		m_08 = 0;
	}
};

class Rva00800920Primary
{
public:
	virtual void v0();
};

// Secondary subobject at +4 writes the incomplete-object vftable before the
// owner vftables are installed.
class Rva00800920Sec
{
public:
	Rva00800920Sec()
	{
		*(int *)this = (int)&vftable_0112B89C;
	}
	virtual void v0();
};

struct Rva00800920Listener
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void onAttach( void *self, int flag );
};

class Rva00803080;
class Rva007EAServiceList
{
public:
	void add( Rva00803080 *owner );
	char m_pad[0x2A0];
	Rva00800920Listener *m_listener;
};

struct Rva00800920Host
{
	char m_pad[0x0C];
	Rva007EAServiceList *m_hub;
};

class Rva00800920Owner : public Rva00800920Primary, public Rva00800920Sec
{
public:
	Rva00800920Owner( Rva00800920Host *host );

	Rva00800920Host *m_host;
	void *m_0C;
	Rva00800920Listener *m_listener;
	char m_14;
	char m_pad15[3];
	int m_18;
	char m_1C;
	char m_pad1D[0x24];
	char m_41;
	char m_pad42[0x82];
	int m_c4;
	int m_c8;
	int m_cc;
	char m_padD0[4];
	Rva00800920Slot m_slots[8];
	int m_1f4;
};

Rva00800920Owner::Rva00800920Owner( Rva00800920Host *host )
{
	int z;

	z = 0;
	m_host = host;
	m_0C = (void *)z;
	m_14 = (char)z;
	m_listener = host->m_hub->m_listener;
	m_listener->onAttach( this, 1 );
	m_1C = (char)z;
	m_41 = (char)z;
	m_18 = 1;
	m_c8 = z;
	m_c4 = z;
	m_cc = z;
	m_1f4 = z;
	host->m_hub->add( (Rva00803080 *)static_cast<Rva00800920Sec *>( this ) );
}
