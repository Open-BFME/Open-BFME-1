// ?rva00518610@BfmeAptScreenLanLobby@@QAEHIPAX0@Z
// partial score=0.31 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenLanLobby primary APT callback, retail 0x00518610 (367 bytes).
// The primary vtable at 0x01105A78 puts this callback in slot 2.  Its
// address-derived name is intentional: the slot's semantic name is not
// recovered, while the owning class and ABI are witnessed by the vtable and
// constructor at BfmeAptScreenLanLobbyConstructor.cpp.

class BfmeMsgHandler
{
public:
	int defaultHandler( int message, void *control, void *data );
};

extern void j_00041ee3();

class Rva00529EC0State
{
public:
	int dispatch( unsigned int message, void *control, void *data )
	{
		typedef int (Rva00529EC0State::*Method)(
			unsigned int, void *, void *);
		union Bits
		{
			Method member;
			void (*code)();
		} bits;
		bits.code = j_00041ee3;
		return (this->*bits.member)( message, control, data );
	}

private:
	char m_unmodelled[ 0x134 ];
};

class Gen00038951
{
public:
	void handle( int value );
};

class Gen_00516AE0
{
public:
	void bfmeStop( int value );
};

extern void SignalUIInteraction( int value );
extern const char g_Rva0107301CEmptyString[];

class BfmeAptScreenLanLobby
{
public:
	int rva00518610( unsigned int message, void *control, void *data );
	void submitNameRva00516C50();
	void sendChatRva00518350();
	bool getGameInfoRva00516850( int index, void **game );

private:
	char m_beforeScreenState[ 0x25c ];
	Rva00529EC0State m_screenState;
	char m_beforeLanPreferences[ 0x24 ];
	void *m_customGamesList;
	void *m_customPlayerList;
	void *m_chatEntry;
	char m_beforeInitComplete[ 0x18 ];
	unsigned char m_initComplete;
};

// ?rva00518610@BfmeAptScreenLanLobby@@QAEHIPAX0@Z
int BfmeAptScreenLanLobby::rva00518610(
	unsigned int message, void *control, void *data )
{
	if ( m_initComplete )
		return 0;

	int result = ((BfmeMsgHandler *)this)->defaultHandler(
		message, control, data);
	int stateResult = ((Rva00529EC0State *)((char *)this + 0x25c))
		->dispatch(message, control, data);
	if ( result == 0 )
		result = stateResult;

	if ( message <= 0x4015 )
	{
		if ( message == 0x4015 )
		{
			if ( control != m_customGamesList )
				return result;
			void *game = 0;
			getGameInfoRva00516850( (int)data, &game );
			if ( game )
				((Gen_00516AE0 *)this)->bfmeStop(
					(int)g_Rva0107301CEmptyString );
			return 1;
		}
		--message;
		if ( message == 0x4014 )
		{
			SignalUIInteraction( 0x1b );
			return 1;
		}
		--message;
		if ( message == 0x4013 )
		{
			SignalUIInteraction( 0x1a );
			return 1;
		}
		message -= 0x4012;
		if ( message != 0 )
			return result;
		if ( control != m_customGamesList )
			return result;
		void *game = 0;
		getGameInfoRva00516850( (int)data, &game );
		if ( game )
			((Gen00038951 *)control)->handle( (int)game );
		return 1;
	}

	message -= 0x4030;
	if ( message == 0 )
	{
		if ( control != m_chatEntry || data != 0 )
			return result;
		sendChatRva00518350();
		return 1;
	}
	--message;
	if ( message == 0 )
	{
		submitNameRva00516C50();
		return 1;
	}
	return result;
}
