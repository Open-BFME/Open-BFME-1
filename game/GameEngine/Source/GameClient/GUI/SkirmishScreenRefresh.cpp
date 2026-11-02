// cl: /O2 /Ob0 /DNDEBUG /MD
// Retail 0x005792A0: refresh the Skirmish APT after its state object permits it.
//
// Returns the state's verdict: the slot-5 mode dispatch at 0x0057EDB0 tests AL
// after its call through ILT 0x00040E7B, and both exits leave the callee's AL
// (the predicate's false, or apply's result) in EAX.

class SkirmishScreenState;
// 0x00529BE0's pinned ILT spelling shouldRefresh is contradicted by
// ilt_oracle; the call goes through the self-addressed caller view of
// ILT 0x0003029C (a fastcall receiver in ECX, as retail's thiscall site).
bool __fastcall j_0003029c(SkirmishScreenState *self);
class SkirmishScreenState
{
public:
	bool shouldRefresh() { return j_0003029c(this); }
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
	if( !j_0003029c( &m_state ) )
		return false;

	m_animation.reset();
	return m_state.apply( TheSkirmishGameInfo, 1 );
}
