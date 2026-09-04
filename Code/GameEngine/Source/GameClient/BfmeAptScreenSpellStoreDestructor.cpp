// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenSpellStore destructor, retail 0x00599330 (264 bytes).
// The constructor and the callback thunks establish the SpellStore.apt
// identity; this body owns the twelve generated button gadget names.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
};

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	char m_unmodelled[ 0x214 ];
};

class BfmeAptFunctorMarker
{
public:
	virtual void marker() = 0;
};

class __multiple_inheritance BfmeAptScreenSpellStore
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~BfmeAptScreenSpellStore();

private:
	char m_unmodelledBetweenBasesAndFields[ 0x3C ];
	bool m_field258;
	bool m_field259;
	bool m_field25A;
	bool m_field25B;
	int m_field25C;
	struct SpellStorePair
	{
		int first;
		int second;
	};
	SpellStorePair m_fields260[ 12 ];
	int m_fields2C0[ 4 ];
	bool m_field2D0;
	bool m_field2D1;
};

class WindowManager
{
public:
	void _bfme_removeNamedAptGadget( const AsciiString &name );
	void bfme_hideBackground( bool hide );
};

class InGameUISpellStoreView
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0;
	virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0;
	virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0;
	virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0;
	virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0;
	virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0;
	virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0;
	virtual void slot62() = 0; virtual void slot63() = 0;
	virtual void slot64() = 0; virtual void slot65() = 0;
	virtual void slot66() = 0; virtual void slot67() = 0;
	virtual void slot68() = 0; virtual void slot69() = 0;
	virtual void slot70() = 0; virtual void slot71() = 0;
	virtual void slot72() = 0; virtual void slot73() = 0;
	virtual void slot74() = 0; virtual void slot75() = 0;
	virtual void slot76() = 0; virtual void slot77() = 0;
	virtual void slot78() = 0; virtual void slot79() = 0;
	virtual void slot80() = 0; virtual void slot81() = 0;
	virtual void slot82() = 0; virtual void slot83() = 0;
	virtual void slot84( int value ) = 0;
};

class Shell
{
public:
	void hideShell( bool immediate );
};

extern const void *BfmeAptScreenSpellStoreVftable[];
extern const void *BfmeAptScreenSpellStoreSecondaryVftable[];
extern WindowManager *g_theWindowManager;
extern InGameUISpellStoreView *TheInGameUI;
extern Shell *TheShell;
extern void *g_obj12F4C38;

BfmeAptScreenSpellStore::~BfmeAptScreenSpellStore()
{
	int zero = 0;
	InGameUISpellStoreView *ui = TheInGameUI;

	if( ui )
		ui->slot84( zero );

	if( g_theWindowManager )
	{
		for( int index = 0; index < 12; ++index )
		{
			if( m_fields260[ index ].first )
			{
				AsciiString name;
				name.format( AsciiString( "SpellStore/Buttons/Spell%d" ), index + 1 );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
		}

		if( m_field25B == zero )
		{
			g_theWindowManager->bfme_hideBackground( zero );
			m_field25B = true;
		}
	}

	if( TheShell )
		TheShell->hideShell( zero );

	g_obj12F4C38 = (void *)zero;
}
