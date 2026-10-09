// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Include
// Primary APT slot 2; owner and ABI evidence: identity_evidence/00518610-system-message.md.

#include "GameClient/BfmeAptScreenBaseLayout.h"

class GameInfo;
class MpGameSetup
{
public:
    void bfmeSetSecondGame(GameInfo *game);
};

class Rva00529EC0State
{
public:
    int dispatch(int message, void *control, void *data);
};

class BfmeMsgHandler
{
public:
	int defaultHandler( int message, void *control, void *data );
};

class SkirmishScreenState
{
public:
    // ?dispatch@SkirmishScreenState@@QAEHIPAX0@Z absent-from-retail
    int dispatch(unsigned int message, void *control, void *data)
    {
        return ((Rva00529EC0State *)this)->dispatch((int)message, control, data);
    }
private:
    char m_unmodelled[0x134];
};

// This state receiver shares the +0x0C game and +0x28 preview with MpGameSetup.
class Gen00038951
{
public:
	// ?handle@Gen00038951@@QAEXH@Z absent-from-retail
    void handle( int value )
    {
        ((MpGameSetup *)this)->bfmeSetSecondGame((GameInfo *)value);
    }
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
	virtual ~BfmeAptScreenLanLobby();
	virtual int aptSlot1(unsigned int, unsigned int, unsigned int);
	virtual int rva00518610( unsigned int message, unsigned int control, unsigned int data );
	void submitNameRva00516C50();
	void sendChatRva00518350();
	bool getGameInfoRva00516850( int index, void **game );

private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
	char m_beforeScreenState[ 0x44 ];
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
    int result = ((BfmeMsgHandler *)this)->defaultHandler(message, (void *)savedControl, (void *)data);
    SkirmishScreenState *state = (SkirmishScreenState *)((char *)this + 0x25c);
    control = (unsigned int)state;
    int stateResult = state->dispatch(message, (void *)savedControl, (void *)data);
    if ( result == 0 )
        result = stateResult;

    switch ( message )
    {
    case 1:
        SignalUIInteraction( 0x1a );
        return 1;
    case 2:
        SignalUIInteraction( 0x1b );
        return 1;
    case 0x4014:
        if ( savedControl == (unsigned int)m_customGamesList )
        {
            void *game = 0;
            getGameInfoRva00516850( (int)data, &game );
            if ( game )
                ((Gen00038951 *)control)->handle( (int)game );
            else
                ((Gen00038951 *)control)->handle( 0 );
        }
        return 1;
    case 0x4015:
        if ( savedControl == (unsigned int)m_customGamesList )
        {
            void *game = 0;
            getGameInfoRva00516850( (int)data, &game );
            if ( game )
                ((Gen_00516AE0 *)this)->bfmeStop( (int)g_Rva0107301CEmptyString );
        }
        return 1;
    case 0x4030:
        if ( savedControl == (unsigned int)m_chatEntry && data == 0 )
            sendChatRva00518350();
        return 1;
    case 0x4031:
        submitNameRva00516C50();
        return 1;
    default:
        return result;
    }
}
