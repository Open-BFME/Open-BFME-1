// ?d_00529be0@@YAXXZ
// partial score=0.41 date=2026-09-04
// cl: /O2 /DNDEBUG /MD /EHsc

int bfmeMake_00529B60( int first, int second );
unsigned int bfmeHash0002A473( unsigned int value, unsigned int type );
unsigned int bfmeHashCombineA( unsigned int value, unsigned int salt );
short skirmishControlIndex( int first, int second );

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

class SkirmishScreenControls
{
public:
	bool isInitialized( void );

private:
	unsigned char m_unmodelled[ 0x40 ];
};

class SkirmishScreenState
{
public:
	bool shouldRefresh( void );

private:
	unsigned char m_unmodelled00[ 0x28 ];
	SkirmishScreenControls m_controls;
	void *m_playerTypeControls[ 8 ];
	void *m_colorControls[ 8 ];
	void *m_factionControls[ 8 ];
	void *m_teamControls[ 8 ];
	void *m_startPositionControls[ 8 ];
	void *m_refreshTarget;
};

// A refresh is safe only after every control in all four slot columns exists;
// the retail iterator visits the eight slot keys in its hashed order.
// ?shouldRefresh@SkirmishScreenState@@QAE_NXZ
bool SkirmishScreenState::shouldRefresh( void )
{
	if( !m_controls.isInitialized() )
		goto notReady;
	if( !m_refreshTarget )
		goto notReady;

	{
		int key = bfmeMake_00529B60( 0, 0 );
		_ReadWriteBarrier();
checkKey:
		if( bfmeHash0002A473( key, 0xB9DC8031 ) == 0x66DE9C79 )
			return true;

		{
			int index = skirmishControlIndex( key, key );
			if( !m_playerTypeControls[ index ] )
				return false;
			index = skirmishControlIndex( key, key );
			if( !m_colorControls[ index ] )
				return false;
			index = skirmishControlIndex( key, key );
			if( !m_factionControls[ index ] )
				return false;
			index = skirmishControlIndex( key, key );
			if( !m_teamControls[ index ] )
				return false;
		}
		key = bfmeHashCombineA( key, 0xE4CD9C42 );
		goto checkKey;
	}

notReady:
	_ReadWriteBarrier();
	return false;
}
