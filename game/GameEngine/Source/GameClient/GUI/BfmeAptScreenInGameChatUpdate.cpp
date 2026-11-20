// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BfmeAptScreenInGameChat::update, retail 0x00515DD0.



// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	virtual void runInit( void *userData );
	virtual ~WindowLayout();
	virtual void runUpdate( void *userData );
	virtual void runShutdown( void *userData );
	void deleteInstance( void ) { delete this; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	WindowLayout *winGetLayout( void );
};

class Glo012F3344Type
{
public:
	virtual void slot00( void );
	virtual void slot04( void );
	virtual void slot08( void );
	virtual void slot0C( void );
	virtual void slot10( void );
	virtual void slot14( void );
	virtual void slot18( void );
	virtual void slot1C( void );
	virtual void slot20( void );
	virtual void slot24( void );
	virtual void bfmeNotifyHidden( void );
};

class IMEManagerInterface;
extern IMEManagerInterface *TheIMEManager;
extern void HideInGameChat( void );
extern void j_00023cc7( void );
// Retail VA 0x012F4994: shared zero-initialized chat update counter.
int g_012F4994 = 0;

class AptInGameChat
{
public:
	virtual ~AptInGameChat();
	virtual int update( void );

private:
	char m_unmodelled[ 0x254 ];
	int m_state;
};

void forceBfmeAptScreenInGameChatDeletingDestructor()
{
	AptInGameChat value;
}

int AptInGameChat::update( void )
{
	if( ++g_012F4994 > 20 )
		j_00023cc7();

	if( m_state == 2 )
	{
		HideInGameChat();
		return 1;
	}

	if( m_state == 4 )
	{
		WindowLayout *layout = ( (GameWindow *)this )->winGetLayout();
			if( layout )
			{
				layout->runShutdown( 0 );
				layout->deleteInstance();

				if( TheIMEManager )
					((Glo012F3344Type *)TheIMEManager)->bfmeNotifyHidden();
			}
	}

	return 1;
}
