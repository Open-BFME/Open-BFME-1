// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" __declspec(dllimport) int __cdecl atoi( const char * );
extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *, const char *, unsigned int );

typedef unsigned int WindowMsgData;

class GameWindow;

class WinInstanceData
{
public:
	GameWindow *getOwner() const { return m_owner; }

private:
	char m_unmodelled[ 0x14 ];
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
};

extern GameWindowManager *TheWindowManager;

class BfmeAptScreenSpellStore
{
public:
	void _bfme_onBttnClose( const char *name );
	void _bfme_onClosed( const char *name );

private:
	char m_unmodelled[ 0x258 ];
	bool m_field258;
	bool m_field259;
	bool m_field25A;
	bool m_field25B;
	int m_field25C;
	struct SpellStorePair
	{
		GameWindow *first;
		int second;
	};
	SpellStorePair m_fields260[ 12 ];
	int m_fields2C0[ 3 ];
	int m_spell;
	char m_field2D0;
	char m_field2D1;
};

// @?_bfme_onBttnClose@BfmeAptScreenSpellStore@@QAEXPBD@Z 0x005990E0
void BfmeAptScreenSpellStore::_bfme_onBttnClose( const char *name )
{
	if( strncmp( name, "Spell", 5 ) == 0 )
	{
		int spell = atoi( name + 5 ) - 1;
		if( spell >= 0 && spell < 12 && !m_field25A )
		{
			GameWindow *button = m_fields260[ spell ].first;
			if( button )
			{
				WinInstanceData *instance = button->winGetInstanceData();
				if( instance )
				{
					TheWindowManager->winSendSystemMsg( instance->getOwner(),
						0x4008, (WindowMsgData)button, button->winGetWindowId() );
				}
			}
		}
	}
}

// @?_bfme_onClosed@BfmeAptScreenSpellStore@@QAEXPBD@Z 0x00599180
void BfmeAptScreenSpellStore::_bfme_onClosed( const char *name )
{
	if( strncmp( name, "Spell", 5 ) == 0 )
	{
		int spell = atoi( name + 5 ) - 1;
		if( spell >= 0 && spell < 12 )
		{
			m_spell = spell;
			m_field2D1 = false;
		}
	}
}
