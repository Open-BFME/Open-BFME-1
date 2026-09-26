// cl: /O2 /Oi /Ob0
// EA FESL client SDK ("jabba") -- pending-request removal from
// gamebrowserpinger.cpp.  The assertion text and source path are retained in
// the retail image; the class and member names below remain address-derived.

#include <string.h>
#pragma intrinsic( memcpy )

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

struct Rva00803080;

struct Rva007EAServiceList
{
	void add( Rva00803080 *owner );
	void remove( Rva00803080 *owner );
};

struct Rva007EAServiceHub
{
	char m_pad[ 0x0C ];
	Rva007EAServiceList *m_services;
};

struct Rva00803080Request
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

class Rva00803080
{
	void *m_00;
	Rva007EAServiceHub *m_04;
	int m_08;
	Rva00803080Request *m_0C;
	int m_10;

public:
	void removePendingRequest( int index );
};

void Rva00803080::removePendingRequest( int index )
{
	if( index < 0 || index >= m_10 )
	{
		Rva007EB810Get()->fail(
			"index >= 0 && index < mNumPendingRequests",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp",
			0x11F );
	}

	if( index < m_10 - 1 )
	{
		memcpy( &m_0C[ index ], &m_0C[ index + 1 ],
			( m_10 - index - 1 ) * sizeof( Rva00803080Request ) );
	}

	memset( &m_0C[ m_10 - 1 ], 0, sizeof( Rva00803080Request ) );
	int new_count = m_10 - 1;
	if( new_count > 0 )
	{
		if( m_10 == 0 )
		{
			m_04->m_services->add( this );
			m_10 = new_count;
			return;
		}
	}
	if( new_count != 0 || m_10 <= 0 )
		goto store_count;
	m_04->m_services->remove( this );

store_count:
	m_10 = new_count;
	return;
}
