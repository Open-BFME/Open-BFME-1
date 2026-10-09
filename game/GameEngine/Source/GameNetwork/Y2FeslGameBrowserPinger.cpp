// cl: /O2 /Oi /Ob0 /GS
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

class Rva00803320Reply;
class Rva00803320Callback
{
public:
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual void v0c(); virtual void v10(); virtual void v14();
	virtual void v18(); virtual void v1c(); virtual void notify(int, int);
};

class Rva00803320Reply
{
public:
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual void v0c(); virtual void v10(); virtual void v14();
	virtual void v18(); virtual void v1c(); virtual void v20();
	virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34();
	virtual Rva00803320Reply *get(int);
	char m_pad[0x48]; int m_elapsed;
};

struct Rva007EAServiceHub
{
public:
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual void v0c(); virtual void v10(); virtual void v14();
	virtual void v18(); virtual void v1c(); virtual void v20();
	virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38();
	virtual void v3c(); virtual void v40(); virtual void v44();
	virtual void v48(); virtual void v4c(); virtual void v50();
	virtual Rva00803320Reply *find(int);
	char m_pad[0x08];
	Rva007EAServiceList *m_services;
	char m_pad10[0x0C];
	Rva00803320Callback *m_callback;
};

struct Rva00803080Request
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

struct Rva00807BA0Ping;
struct Rva00808660Result
{
	char m_text[0x14]; unsigned int m_from; int m_elapsed; int m_sequence;
	int m_icmpType; int m_server; int m_pad28;
};
int Rva00808660(Rva00807BA0Ping *, void *, int *, Rva00808660Result *);


class Rva00803080
{
	void *m_00;
	Rva007EAServiceHub *m_04;
	Rva00807BA0Ping *m_08;
	Rva00803080Request *m_0C;
	int m_10;

public:
	void removePendingRequest( int index );
	void update( unsigned int now );
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

// ?update@Rva00803080@@QAEXI@Z
// Open BFME 2: Code/GameEngine/Source/GameNetwork/Y2FeslGameBrowserPinger.cpp.
void Rva00803080::update( unsigned int now )
{
	int payload[ 2 ];
	int length;
	Rva00808660Result result;
	int i;

	payload[ 0 ] = 0;
	payload[ 1 ] = 0;
	length = sizeof( payload );
	memset( &result, 0, sizeof( result ) );
	result.m_sequence = 0x7FFFFFFF;
	Rva00808660( m_08, payload, &length, &result );

	while( result.m_sequence != 0x7FFFFFFF )
	{
		bool found = false;
		for( i = 0; i < *(volatile int *)&m_10; ++i )
		{
			Rva00803080Request *requests = m_0C;
			if( requests[ i ].m_00 == result.m_sequence )
			{
				found = true;
				break;
			}
		}

		if( found )
		{
			removePendingRequest( i );
			if( length != sizeof( payload ) )
			{
				Rva007EB810Get()->fail( "FALSE",
					"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp",
					0xD6 );
				continue;
			}

			Rva00803320Reply *game = m_04->find( payload[ 0 ] );
			if( game != 0 )
			{
				Rva00803320Reply *entry = game->get( payload[ 1 ] );
				if( entry != 0 )
				{
					entry->m_elapsed = result.m_elapsed;
					Rva00803320Callback *listener = m_04->m_callback;
					if( listener != 0 )
						listener->notify( payload[ 0 ], payload[ 1 ] );
				}
			}
		}

		memset( &result, 0, sizeof( result ) );
		result.m_sequence = 0x7FFFFFFF;
		Rva00808660( m_08, payload, &length, &result );
	}

	unsigned int expire = now - 5000;
	for( i = 0; i < m_10; ++i )
	{
		if( m_0C[ i ].m_04 >= expire )
			break;

		Rva00803320Reply *game = m_04->find( m_0C[ i ].m_08 );
		if( game != 0 )
		{
			Rva00803080Request *requests = m_0C;
			Rva00803320Reply *entry = game->get( requests[ i ].m_0C );
			if( entry != 0 )
			{
				entry->m_elapsed = -3;
				Rva00803320Callback *listener = m_04->m_callback;
				if( listener != 0 )
					listener->notify( m_0C[ i ].m_08, m_0C[ i ].m_0C );
			}
		}
		removePendingRequest( i );
	}
}
