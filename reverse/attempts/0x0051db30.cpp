// ?_bfme_multiplayerButtonPressed@BfmeAptScreenMainMenu@@QAEXPBD@Z
// partial score=0.96 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// MainMenu.apt multiplayer button callback, retail 0x0051DB30. The main menu
// constructor pushes the selector string "AptMainMenu::MultiplayerButtonPressed"
// at retail 0x0051FB59 and loads this body's ILT thunk right after, so the name
// is read off the binary rather than guessed.

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

struct UnicodeStringData
{
	unsigned int m_refCount;
	unsigned short m_length;
};

class UnicodeString
{
public:
	UnicodeString() : m_data( 0 ) {}
	UnicodeString( const UnicodeString &other )
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other );
	}
	~UnicodeString();

private:
	UnicodeStringData *m_data;
};

class BfmeStringLiteralBase
{
	friend class BFMERetailAsciiString;

private:
	BfmeStringLiteralBase( const char *text );
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text )
	{
		((BfmeStringLiteralBase *)this)->BfmeStringLiteralBase::BfmeStringLiteralBase(
			text );
	}
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

class BfmeMainMenuState
{
public:
	bool isReady();

private:
	char m_unmodelled[ 8 ];
};

class Rva00579160Manager
{
public:
	void bfme_setAptText( const BFMERetailAsciiString &name, const UnicodeString &text );
	void fire( void *target, const char *name, int a, int b, int c, int d, int e, int f );
};

extern Rva00579160Manager *Rva00579160TheManager;

class BfmeAptScreenMainMenu
{
public:
	void _bfme_multiplayerButtonPressed( const char *name );

private:
	char m_unmodelled[ 0x250 ];
	void *m_target;
	char m_padding[ 0x14 ];
	BfmeMainMenuState m_state;
	bool m_enabled;
};

void BfmeAptScreenMainMenu::_bfme_multiplayerButtonPressed( const char *name )
{
	(void)name;
	if( !m_enabled || m_state.isReady() )
	{
		Rva00579160TheManager->fire(
			m_target, "StartMultiplayerNav", 0, 0, 0, 0, 0, 0 );
	}
	else
	{
		{
			BFMERetailAsciiString name( "APT:FirewallPopUpMessage" );
			Rva00579160TheManager->bfme_setAptText(
				name, TheGameText->fetch( "GUI:FirewallPopUpMessage" ) );
		}
		{
			BFMERetailAsciiString name( "APT:FirewallPopUpTitle" );
			Rva00579160TheManager->bfme_setAptText(
				name, TheGameText->fetch( "GUI:FirewallPopUpTitle" ) );
		}
		Rva00579160TheManager->fire(
			m_target, "FirewallMessageOpen", 0, 0, 0, 0, 0, 0 );
	}
}
