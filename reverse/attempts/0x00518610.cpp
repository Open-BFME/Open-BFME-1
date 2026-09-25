// ?rva00518610@BfmeAptScreenLanLobby@@UAEHIII@Z
// partial score=0.34 date=2026-09-25
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

class SkirmishScreenState
{
public:
    int dispatch(unsigned int message, void *control, void *data);
private:
    char m_unmodelled[0x134];
};

// ILT 0x00038951 reaches 0x00526040; its receiver identity remains unverified.
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
	virtual int rva00518610( unsigned int message, unsigned int control, unsigned int data );
	void submitNameRva00516C50();
	void sendChatRva00518350();
	bool getGameInfoRva00516850( int index, void **game );

private:
	char m_beforeScreenState[ 0x258 ];
	SkirmishScreenState m_screenState;
	char m_beforeLanPreferences[ 0x24 ];
	void *m_customGamesList;
	void *m_customPlayerList;
	void *m_chatEntry;
	char m_beforeInitComplete[ 0x18 ];
	unsigned char m_initComplete;
};

// ?rva00518610@BfmeAptScreenLanLobby@@UAEHIII@Z
int BfmeAptScreenLanLobby::rva00518610(
	unsigned int message, unsigned int control, unsigned int data )
{
	if ( m_initComplete )
		return 0;

	unsigned int savedControl = control;
	int result = ((BfmeMsgHandler *)this)->defaultHandler(
		message, (void *)savedControl, (void *)data);
	SkirmishScreenState *state = (SkirmishScreenState *)((char *)this + 0x25c);
	control = (unsigned int)state;
	int stateResult = state->dispatch(message, (void *)savedControl, (void *)data);
	if ( result == 0 )
		result = stateResult;

	if ( message <= 0x4015 )
	{
		if ( message == 0x4015 )
		{
			if ( savedControl != (unsigned int)m_customGamesList )
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
		if ( savedControl != (unsigned int)m_customGamesList )
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
		if ( savedControl != (unsigned int)m_chatEntry || data != 0 )
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
