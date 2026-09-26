// cl: /GX-
// jabba gamebrowserdemangler.cpp connect @ 0x008006C0 (178B).
// Asserts mGameBrowser->IsInternetConnected() at demangler.cpp:115.
// Copies name/addr via strncpy into fixed buffers then stamps txn fields.

#include <string.h>

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual unsigned tick();
};

extern Rva007E9B70Obj *Rva007E9B70Get();

struct Rva008006C0Sink
{
	virtual void v0();
	virtual void notify( int a, int b, int c );
};

struct Rva008006C0Browser
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual bool isInternetConnected();
};

class Rva008006C0Owner
{
public:
	int connect( const char *name, const char *addr, int cookie );

	void *m_00;
	void *m_04;
	Rva008006C0Browser *m_browser;
	Rva008006C0Sink *m_sink;
	char m_10[4];
	char m_busy;
	char m_15[3];
	int m_seq;
	char m_name[0x25];
	char m_addr[0x80];
	char m_pad[0xC4 - 0xC1];
	unsigned m_c4;
	int m_c8;
	int m_cc;
	int m_d0;
};

int Rva008006C0Owner::connect( const char *name, const char *addr, int cookie )
{
	if( m_busy )
	{
		m_sink->notify( 0, 0, cookie );
		return 0;
	}

	if( !m_browser->isInternetConnected() )
	{
		Rva007EB810Get()->fail(
			"mGameBrowser->IsInternetConnected()",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserdemangler.cpp",
			0x73 );
	}

	if( name )
	{
		strncpy( m_name, name, 0x25 );
		strncpy( m_addr, addr, 0x80 );
	}
	else
	{
		m_name[0] = 0;
		m_addr[0] = 0;
	}

	m_c4 = Rva007E9B70Get()->tick();
	m_c8 = m_seq;
	m_seq = m_seq + 1;
	m_d0 = cookie;
	m_cc = 0;
	return 0;
}
