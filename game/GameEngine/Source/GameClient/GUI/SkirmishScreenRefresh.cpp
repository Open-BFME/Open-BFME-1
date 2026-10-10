// cl: /O2 /Ob0 /DNDEBUG /MD
// Retail 0x005792A0: refresh the Skirmish APT after its state object permits it.

class SkirmishScreenState
{
};

extern "C" void __cdecl __identifier("?j_0003029c@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_0003ab48@@YAXXZ")();

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

class SkirmishGameInfo;
extern SkirmishGameInfo *TheSkirmishGameInfo;

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

void BfmeAptScreenSkirmish::_bfme_refresh( void )
{
	union { void (*raw)(); bool (SkirmishScreenState::*member)(); }
		query = { __identifier("?j_0003029c@@YAXXZ") };
	union { void (*raw)(); bool (SkirmishScreenState::*member)(void *, int); }
		apply = { __identifier("?j_0003ab48@@YAXXZ") };
	if( !(m_state.*query.member)() )
	{
		_ReadWriteBarrier();
		return;
	}

	m_animation.reset();
	(m_state.*apply.member)( TheSkirmishGameInfo, 1 );
}
