// ?_bfme_refresh@BfmeAptScreenSkirmish@@QAEXXZ
// partial score=0.95 date=2026-09-02
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

void BfmeAptScreenSkirmish::_bfme_refresh( void )
{
	if( !m_state.shouldRefresh() )
		return;

	m_animation.reset();
	m_state.apply( g_bfmeCurrentCB, true );
}
