// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BfmeAptScreenQuitMenu constructor, retail 0x0056A2F0, 1024 bytes.

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
struct UnicodeStringData
{
	unsigned int m_refCount;
	unsigned short m_length;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : m_data( 0 ) {}
	UnicodeString( const unsigned short *text );
	UnicodeString( const UnicodeString &other )
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other );
	}
	~UnicodeString();

	private:
	UnicodeStringData *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

class WindowManager
{
public:
	__declspec( noinline ) void bfme_showBackground( int kind );
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_theWindowManager;

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)( void );

struct FunctorBinding
{
	FunctorBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_method( method ) {}

	FunctorTarget *m_target;
	unsigned int m_unmodelled;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount( 0 ) {}
	virtual void invoke();

	unsigned int m_refCount;
};

class Rva00569C80FunctorWrapper : public FunctorWrapperHead
{
public:
	Rva00569C80FunctorWrapper( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

class Rva0056A280FunctorHolder
{
public:
	__forceinline Rva0056A280FunctorHolder( FunctorBinding binding )
	{
		m_ptr = new Rva00569C80FunctorWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}
	Rva0056A280FunctorHolder( const Rva0056A280FunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	Rva00569C80FunctorWrapper *m_ptr;
};

class QuitMenuHolder
{
public:
	QuitMenuHolder( FunctorBinding binding );

private:
	void *m_ptr;
};

class QuitMenuRegistry
{
public:
	void showAptScreen( const AsciiString &name, QuitMenuHolder callback );
	void showAptScreenWithArg( const AsciiString &name, void *argument,
		Rva0056A280FunctorHolder callback );
};

class _bfme_AptGameWindow
{
public:
	_bfme_AptGameWindow( void *context );
	virtual ~_bfme_AptGameWindow();

private:
	char m_unmodelled[ 0x254 ];
};

class BfmeAptFunctorMarker {};

class BfmeH1065;

class GenActionSink
{
public:
	unsigned char *invokeAtLevel( int level, const char *name, int kind,
		const char *value, int a, int b, int c, int d );
};

extern GenActionSink *TheGenActionSink;

int bfmeAptLevel00465CE0( BfmeH1065 *self );

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD,
	RECORDERMODETYPE_PLAYBACK,
	RECORDERMODETYPE_NONE
};

class RecorderClass
{
public:
	RecorderModeType getMode();
};

extern RecorderClass *TheRecorder;

class GameLogic
{
public:
	char m_unmodelled[ 0x10C ];
	int m_gameMode;
};

extern GameLogic *TheBfmeGameLogic;

class Glo012F1028Type
{
public:
	char m_unmodelled[ 0x2C ];
	unsigned char m_campaignLoaded;
	unsigned char m_campaignActive;
};

extern Glo012F1028Type *Glo012F1028;

class Rva003BF540
{
public:
	bool allowed();
};

class Gen_00609320
{
public:
	char m_unmodelled[ 4 ];
	void *m_at04;
};

extern Gen_00609320 *g_bfmeStateDF;

extern const void *BfmeAptScreenQuitMenuVftable[];
extern const void *BfmeAptScreenQuitMenuSecondaryVftable[];
extern void *g_obj12F4B40;

class __declspec(novtable) __multiple_inheritance BfmeAptScreenQuitMenu
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	BfmeAptScreenQuitMenu( void *context );

	void _bfme_onInitialized( const char *name );
	void _bfme_restartMission();
	void _bfme_exitMission();
	void _bfme_optionsScreen();
	void _bfme_returnToGame();
	void _bfme_saveMenu();
	void _bfme_loadMenu();
	void _bfme_hasFocus();

private:
	bool m_field258;
	bool m_field259;
	bool m_field25A;
	int m_field25C;
};

union QuitMenuMethodBits
{
	FunctorMethod m_method;
	unsigned int m_words[ 2 ];
};

BfmeAptScreenQuitMenu::BfmeAptScreenQuitMenu( void *context )
	: _bfme_AptGameWindow( context )
{
	*(const void ***)( (char *)this ) = BfmeAptScreenQuitMenuVftable;
	*(const void ***)( (char *)this + 0x218 ) =
		BfmeAptScreenQuitMenuSecondaryVftable;
	m_field258 = false;
	m_field259 = false;
	m_field25A = false;
	m_field25C = 0;
	FunctorMethod callback;
	QuitMenuMethodBits methodBits;

	if( g_obj12F4B40 == 0 )
	{
		g_obj12F4B40 = this;
		QuitMenuRegistry *registry =
			(QuitMenuRegistry *)( (char *)this + 0x218 );

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenQuitMenu::_bfme_onInitialized;
			AsciiString name( "AptQuitMenu::OnInitialized" );
			registry->showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenQuitMenu::_bfme_restartMission;
			AsciiString name( "AptQuitMenu::RestartMission" );
			registry->showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenQuitMenu::_bfme_exitMission;
			AsciiString name( "AptQuitMenu::ExitMission" );
			registry->showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenQuitMenu::_bfme_optionsScreen;
			AsciiString name( "AptQuitMenu::OptionsScreen" );
			registry->showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenQuitMenu::_bfme_returnToGame;
			AsciiString name( "AptQuitMenu::ReturnToGame" );
			registry->showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenQuitMenu::_bfme_saveMenu;
			AsciiString name( "AptQuitMenu::SaveMenu" );
			registry->showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenQuitMenu::_bfme_loadMenu;
			AsciiString name( "AptQuitMenu::LoadMenu" );
			registry->showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		{
			methodBits.m_words[ 0 ] = 0x00410B86;
			methodBits.m_words[ 1 ] = 0;
			callback = methodBits.m_method;
			FunctorBinding binding( callback, (FunctorTarget *)this );
			const char *hasFocus = *(const char **)0x012B7E30;
			AsciiString name( hasFocus );
			registry->showAptScreenWithArg( name, (void *)0,
				Rva0056A280FunctorHolder( binding ) );
		}

		g_theWindowManager->bfme_showBackground( 2 );

		struct QuitMenuGameLogic
		{
			char m_unmodelled[ 0x10C ];
			int m_gameMode;
		};
		QuitMenuGameLogic *gameLogic =
			*(QuitMenuGameLogic **)0x012F0898;
		if( gameLogic && ( gameLogic->m_gameMode == 1 ||
			gameLogic->m_gameMode == 5 ) )
		{
			AsciiString pause( "APT:Pause" );
			g_theWindowManager->bfme_setAptText(
				pause, TheGameText->fetch( "GUI:Menu" ) );
		}
	}
}

void BfmeAptScreenQuitMenu::_bfme_onInitialized( const char * )
{
	if( TheBfmeGameLogic &&
		( TheBfmeGameLogic->m_gameMode == 1 ||
		  TheBfmeGameLogic->m_gameMode == 5 ) )
		goto disableRestart;

	if( !TheRecorder || TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK )
	{
		if( !Glo012F1028 || !Glo012F1028->m_campaignLoaded ||
			!Glo012F1028->m_campaignActive )
			return;

		TheGenActionSink->invokeAtLevel(
			bfmeAptLevel00465CE0( (BfmeH1065 *)this ), "disableButton", 1, "Restart",
			0, 0, 0, 0 );

		if( !((Rva003BF540 *)Glo012F1028)->allowed() )
			goto disableSaveLoad;
		if( g_bfmeStateDF->m_at04 )
			return;
		goto disableSaveLoad;
	}

	disableRestart:
	TheGenActionSink->invokeAtLevel(
		bfmeAptLevel00465CE0( (BfmeH1065 *)this ), "disableButton", 1, "Restart",
		0, 0, 0, 0 );

	goto disableSaveLoad;

	disableSaveLoad:
	TheGenActionSink->invokeAtLevel(
		bfmeAptLevel00465CE0( (BfmeH1065 *)this ), "disableButton", 1, "Save",
		0, 0, 0, 0 );
	TheGenActionSink->invokeAtLevel(
			bfmeAptLevel00465CE0( (BfmeH1065 *)this ), "disableButton", 1, "Load",
			0, 0, 0, 0 );
}
