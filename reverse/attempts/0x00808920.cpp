// ??0Rva00808920LanGame@@QAE@H@Z
// partial score=0.98 date=2026-09-24
// cl: /O2 /Og /GX- /GS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )

struct Rva007EFFC0Allocator
{
	virtual void v0();
	virtual void v1();
	virtual void *allocate( unsigned int size, int flags );
	virtual void release( void *block, int flags );
};

typedef void *(__fastcall *Rva007EFFC0AllocateSlot)(
	Rva007EFFC0Allocator *, void *, unsigned int, int);

__forceinline void *Rva007EFFC0Allocate(
	Rva007EFFC0Allocator *allocator, unsigned int size, int flags)
{
	void **vtable = *(void ***)allocator;
	return ((Rva007EFFC0AllocateSlot)vtable[2])(allocator, vtable, size, flags);
}

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual int v2();
};

Rva007EFFC0Allocator *Rva007EFFC0Get();
Rva007E9B70Obj *Rva007E9B70Get();

class Gen007F0130
{
public:
	static void *operator new( unsigned int size );
};

class Rva00808920LanGame : public Gen007F0130
{
public:
	Rva00808920LanGame( int maxPlayers );
	__forceinline char *ugid()
	{
		return m_ugid;
	}

	int m_state;
	int m_maxPlayers;
	void **m_players;
	char m_name[ 0x80 ];
	char m_ugid[ 0x25 ];
	char m_tail[ 3 ];
};

Rva00808920LanGame::Rva00808920LanGame( int maxPlayers )
{
	m_state = 1;
	m_maxPlayers = maxPlayers;
	Rva007EFFC0Allocator *allocator = Rva007EFFC0Get();
	unsigned int allocationBytes;
	allocationBytes = m_maxPlayers * 4;
	m_players = (void **)allocator->allocate( allocationBytes, 0 );
	for ( int index = 0; index < m_maxPlayers; ++index )
		m_players[ index ] = 0;

	char text[ 0x24 ];
	int value = Rva007E9B70Get()->v2() * rand() * m_maxPlayers;
	sprintf( text, "%032x", value );
	memset( m_ugid, 0, 0x25 );
	strncpy( m_ugid, text, 8 );
	strcat( m_ugid, "-" );
	strncat( m_ugid, text + 8, 4 );
	strcat( m_ugid, "-" );
	strncat( m_ugid, text + 12, 4 );
	strcat( m_ugid, "-" );
	strncat( m_ugid, text + 16, 4 );
	strcat( m_ugid, "-" );
	strncat( m_ugid, text + 20, 12 );
	m_ugid[ 0x24 ] = 0;
}
