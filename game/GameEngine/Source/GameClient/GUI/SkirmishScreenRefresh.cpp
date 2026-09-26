// cl: /O2 /Ob0 /DNDEBUG /MD
// Retail 0x005792A0: refresh the Skirmish APT after its state object permits it.

class SkirmishScreenState
{
public:
	bool shouldRefresh( void );
	void apply( void *gameInfo, bool force );
};

class SkirmishScreenAnimation
{
public:
	virtual void slot0( void );
	virtual void slot1( void );
	virtual void slot2( void );
	virtual void reset( void );
};

class BfmeAptScreenSkirmish
{
public:
	void _bfme_refresh( void );

private:
	char m_pad0[ 0x25C ];
	SkirmishScreenState m_state;
	char m_pad260[ 0x14C ];
	SkirmishScreenAnimation m_animation;
};

extern void *g_bfmeCurrentCB;

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

void BfmeAptScreenSkirmish::_bfme_refresh( void )
{
	if( !m_state.shouldRefresh() )
	{
		_ReadWriteBarrier();
		return;
	}

	m_animation.reset();
	m_state.apply( g_bfmeCurrentCB, true );
}
