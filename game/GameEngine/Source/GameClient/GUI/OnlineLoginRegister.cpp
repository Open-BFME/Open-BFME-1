// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BfmeAptScreenOnlineLogin::_bfme_register, retail 0x0054CC60, 633 bytes. The
// OnlineLogin constructor pushes the selector string
// "AptOnline::Login::Register" at retail 0x00553A45 and loads ILT 0x0002E479
// twenty eight bytes later, and that thunk jumps to this body. The receiver
// view and the four CallChild sink calls are the ones the matched sibling
// _bfme_login at 0x00553520 already proves. The body reads InstallPath out of
// the registry, appends the EA registration tool to it, and hands the result
// to ShellExecute.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct AsciiStringData
{
	unsigned int m_refCount;
	unsigned short m_length;							///< retail this+0x04
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	AsciiStringData *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
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
	AsciiStringData *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void concat( const char *text );

	bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
};

bool GetStringFromRegistry( AsciiString path, AsciiString key, AsciiString &value );
void GSMessageBoxOk( UnicodeString title, UnicodeString message, void ( *callback )( void ) );
void bfmeMinimizeCurrentThreadWindow( void );

extern "C" __declspec(dllimport) void * __stdcall ShellExecuteA( void *owner,
	const char *operation, const char *file, const char *parameters,
	const char *directory, int showCommand );

#define BFME_TEXT_SLOT( n ) virtual void _bfme_slot##n( void ) = 0
class GameTextInterface
{
public:
	BFME_TEXT_SLOT( 0 ); BFME_TEXT_SLOT( 1 ); BFME_TEXT_SLOT( 2 );
	BFME_TEXT_SLOT( 3 ); BFME_TEXT_SLOT( 4 ); BFME_TEXT_SLOT( 5 );
	BFME_TEXT_SLOT( 6 ); BFME_TEXT_SLOT( 7 ); BFME_TEXT_SLOT( 8 );
	BFME_TEXT_SLOT( 9 );
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
};
#undef BFME_TEXT_SLOT

// Matched sibling _bfme_login at 0x00553520 uses this same action sink view.
class WindowManager
{
public:
	void add( void *window, const char *name, int type, void *value,
		int unused0, int unused1, int unused2, int unused3 );
};

struct BfmeOnlineLoginContext
{
	unsigned char m_unmodelled[ 0x250 ];
	void *m_window;										///< retail this+0x250
};

class BfmeAptScreenOnlineLogin
{
public:
	void _bfme_register( const char *argument );

private:
	const void *m_vftable;
	unsigned char m_unmodelled04[ 0x30 ];
	BfmeOnlineLoginContext *m_context;					///< retail this+0x34
};

extern WindowManager *g_theWindowManager;
extern GameTextInterface *TheGameText;
extern BfmeAptScreenOnlineLogin *TheBfmeOnlineLogin;

// ?_bfme_register@BfmeAptScreenOnlineLogin@@QAEXPBD@Z
void BfmeAptScreenOnlineLogin::_bfme_register( const char * )
{
	if( TheBfmeOnlineLogin != 0 )
	{
		{
			void *window = m_context->m_window;
			g_theWindowManager->add( window,
				"CallChild", 1, (void *)"DisableButtonDeleteNickname", 0, 0, 0, 0 );
		}
		{
			void *window = m_context->m_window;
			g_theWindowManager->add( window,
				"CallChild", 1, (void *)"DisableButtonCreate", 0, 0, 0, 0 );
		}
		{
			void *window = m_context->m_window;
			g_theWindowManager->add( window,
				"CallChild", 1, (void *)"DisableButtonLogin", 0, 0, 0, 0 );
		}
		{
			void *window = m_context->m_window;
			g_theWindowManager->add( window,
				"CallChild", 1, (void *)"DisableButtonServiceTerms", 0, 0, 0, 0 );
		}

		AsciiString installPath( "" );
		if( GetStringFromRegistry( "", "InstallPath", installPath ) && !installPath.isEmpty() )
		{
			installPath.concat( "\\SUPPORT\\EREG.EXE" );
			if( (int)ShellExecuteA( 0, "open", installPath.str(), "", 0, 5 ) <= 31 )
			{
				GSMessageBoxOk( TheGameText->fetch( "GUI:GSErrorTitle" ),
					TheGameText->fetch( "GUI:EREGError" ), 0 );
			}
			else
			{
				bfmeMinimizeCurrentThreadWindow();
			}
		}
		else
		{
			GSMessageBoxOk( TheGameText->fetch( "GUI:GSErrorTitle" ),
				TheGameText->fetch( "GUI:EREGError" ), 0 );
		}

		{
			void *window = m_context->m_window;
			g_theWindowManager->add( window,
				"CallChild", 1, (void *)"EnableButtonDeleteNickname", 0, 0, 0, 0 );
		}
		{
			void *window = m_context->m_window;
			g_theWindowManager->add( window,
				"CallChild", 1, (void *)"EnableButtonCreate", 0, 0, 0, 0 );
		}
		{
			void *window = m_context->m_window;
			g_theWindowManager->add( window,
				"CallChild", 1, (void *)"EnableButtonLogin", 0, 0, 0, 0 );
		}
		{
			void *window = m_context->m_window;
			g_theWindowManager->add( window,
				"CallChild", 1, (void *)"EnableButtonServiceTerms", 0, 0, 0, 0 );
		}
	}
}
