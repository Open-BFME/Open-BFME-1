// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int NameKeyType;
typedef unsigned int WindowMsgData;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

class GameWindow;

class WinInstanceData
{
	public:
	unsigned char m_unmodelled[ 0x14 ];
	GameWindow *m_owner;
};

class GameWindow
{
public:
	WinInstanceData *winGetInstanceData();
	int winGetWindowId();
};

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52();
	virtual int winSendSystemMsg( GameWindow *window, unsigned int message,
		WindowMsgData data1, WindowMsgData data2 );
	virtual void slot54();
	virtual GameWindow *winGetWindowFromId( GameWindow *parent, NameKeyType id );
};

class WindowManager
{
public:
	unsigned char m_unmodelled[ 0x1b4 ];
	int m_windowMode;
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern WindowManager *g_theWindowManager;

class AptPalantir
{
public:
	void showSpellStore();

private:
	unsigned char m_unmodelled[ 0x4c4 ];
	unsigned char m_spellStoreVisible;
};

// ?showSpellStore@AptPalantir@@QAEXXZ
void AptPalantir::showSpellStore()
{
	static NameKeyType buttonGeneralID =
		TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonGeneral" );

	GameWindow *button =
		TheWindowManager->winGetWindowFromId( 0, buttonGeneralID );
	if( button )
	{
		WinInstanceData *instance = button->winGetInstanceData();
		if( instance )
		{
			int windowMode = g_theWindowManager->m_windowMode;
			GameWindow *owner = instance->m_owner;
			TheWindowManager->winSendSystemMsg( owner,
				0x4008 + ( windowMode == 2 ),
				(WindowMsgData)button, button->winGetWindowId() );
			m_spellStoreVisible = 0;
		}
	}
}
