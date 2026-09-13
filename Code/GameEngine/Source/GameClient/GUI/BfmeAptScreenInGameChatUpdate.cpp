// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BfmeAptScreenInGameChat::update, retail 0x00515DD0.

typedef int Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	virtual void runInit( void *userData );
	virtual ~WindowLayout();
	virtual void runUpdate( void *userData );
	virtual void runShutdown( void *userData );
	void deleteInstance( void ) { delete this; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
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

extern Glo012F3344Type *Glo012F3344;
extern void HideInGameChat( void );
extern void j_00023cc7( void );

class BfmeAptScreenInGameChat
{
public:
	virtual int update( void );

private:
	char m_unmodelled[ 0x254 ];
	int m_state;
};

int BfmeAptScreenInGameChat::update( void )
{
	if( ++*(int *)0x012F4994 > 20 )
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

				if( Glo012F3344 )
					Glo012F3344->bfmeNotifyHidden();
			}
	}

	return 1;
}
