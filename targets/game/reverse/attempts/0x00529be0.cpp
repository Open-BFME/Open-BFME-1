// ?d_00529be0@@YAXXZ
// partial score=1.0 date=2026-11-02
// ?shouldRefresh@SkirmishScreenState@@QAE_NXZ
// EXACT 2026-11-02 (a1/536) via foldable searching term; landing blocked on ILT pin retire: see targets/game/reverse/attempt_support/00529be0-exact-pin-retire-20261102.md
// cl: /DNDEBUG /MD /EHsc

class Rva00520460
{
	char m_pad00[ 4 ];
	int m_value04;
	char m_pad08[ 0xc ];
	int m_values[ 8 ];

public:
	bool has();
};

class GameWindow;

int __cdecl Rva005277B0( int a, int b );
int __cdecl Rva00527730( int a, int b );
int __cdecl Rva005278B0( int a, int b );
int __cdecl Rva00527830( int a, int b );

class SkirmishScreenState
{
public:
	bool shouldRefresh( void );

private:
	unsigned char m_head[ 0x28 ];
	Rva00520460 m_slotRecord;
	unsigned char m_slotRecordTail[ 0xc ];
	GameWindow *m_first[ 8 ];
	GameWindow *m_elements[ 8 ];
	GameWindow *m_second[ 8 ];
	GameWindow *m_third[ 8 ];
	GameWindow *m_fourth[ 8 ];
	int m_unmodelled108;
};

bool SkirmishScreenState::shouldRefresh( void )
{
	if ( !m_slotRecord.has() )
		return false;
	if ( !m_unmodelled108 )
		return false;

	int key = Rva005277B0( 0, 0 );
	bool searching = true;
	while ( searching && Rva00527730( key, (int)0xB9DC8031 ) != (int)0x66DE9C79 )
	{
		if ( !m_first[ (short)Rva005278B0( key, key ) ] )
			return false;
		GameWindow **slot = &m_elements[ (short)Rva005278B0( key, key ) ];
		if ( !*slot )
			return false;
		if ( !m_second[ (short)Rva005278B0( key, key ) ] )
			return false;
		if ( !m_third[ (short)Rva005278B0( key, key ) ] )
			return false;
		key = Rva00527830( key, (int)0xE4CD9C42 );
	}
	return true;
}
