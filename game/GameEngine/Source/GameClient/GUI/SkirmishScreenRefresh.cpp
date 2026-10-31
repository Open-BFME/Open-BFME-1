// cl: /O2 /Ob0 /DNDEBUG /MD
// Retail 0x005792A0: refresh the Skirmish APT after its state object permits it.
//
// Returns the state's verdict: the slot-5 mode dispatch at 0x0057EDB0 tests AL
// after its call through ILT 0x00040E7B, and both exits leave the callee's AL
// (the predicate's false, or apply's result) in EAX.

extern "C" void __cdecl __identifier("?d_00529be0@@YAXXZ")();
class SkirmishScreenState
{
public:
	bool shouldRefresh() {
	 // retail body is still the gen-dump row ?d_00529be0@@YAXXZ (no C++ row yet); call it by that defined name
	 union { void (__cdecl *symbol)(); bool (SkirmishScreenState::*member)(); } c;
	 c.symbol = &__identifier("?d_00529be0@@YAXXZ");
	 return (this->*c.member)();
	}
	bool apply( void *info, int flag );
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
	bool _bfme_refresh( void );

private:
	char m_pad0[ 0x25C ];
	SkirmishScreenState m_state;
	char m_pad25D[ 0x14F ];
	SkirmishScreenAnimation m_animation;
};

class SkirmishGameInfo;
extern SkirmishGameInfo *TheSkirmishGameInfo;

// ?_bfme_refresh@BfmeAptScreenSkirmish@@QAE_NXZ
bool BfmeAptScreenSkirmish::_bfme_refresh( void )
{
	if( !m_state.shouldRefresh() )
		return false;

	m_animation.reset();
	return m_state.apply( TheSkirmishGameInfo, 1 );
}
