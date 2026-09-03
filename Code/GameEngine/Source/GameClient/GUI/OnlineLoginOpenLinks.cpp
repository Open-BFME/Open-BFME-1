// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef void *HWND;
typedef long LPARAM;
typedef int BOOL;
typedef unsigned long DWORD;

extern "C" __declspec(dllimport) DWORD __stdcall GetCurrentThreadId();
extern "C" __declspec(dllimport) BOOL __stdcall EnumThreadWindows(
	DWORD threadId, BOOL (__stdcall *callback)( HWND, LPARAM ), LPARAM context );
extern "C" __declspec(dllimport) BOOL __stdcall ShowWindow( HWND window, int command );
extern "C" __declspec(dllimport) void * __stdcall ShellExecuteA(
	HWND window, const char *operation, const char *file, const char *parameters,
	const char *directory, int showCommand );

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	~StringBase();

protected:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	~UnicodeString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	~AsciiString() {}
	void translate( const UnicodeString &text );
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
};

extern GameTextInterface *TheGameText;
extern void b_00548d90();

static void minimizeCurrentThreadWindow()
{
	HWND window = 0;
	EnumThreadWindows( GetCurrentThreadId(),
		reinterpret_cast<BOOL (__stdcall *)( HWND, LPARAM )>( &b_00548d90 ),
		reinterpret_cast<LPARAM>( &window ) );
	if( window )
		ShowWindow( window, 6 );
}

class BfmeAptScreenOnlineLogin
{
public:
	void bfmeOpenHomePage( const char *argument );
	void bfmeOpenTermsPage( const char *argument );
};

void BfmeAptScreenOnlineLogin::bfmeOpenHomePage( const char * )
{
	AsciiString url;
	url.translate( TheGameText->fetch( "URL:LotrHome" ) );
	ShellExecuteA( 0, "open", "IEXPLORE.EXE", url.str(), 0, 5 );
	minimizeCurrentThreadWindow();
}

void BfmeAptScreenOnlineLogin::bfmeOpenTermsPage( const char * )
{
	AsciiString url;
	url.translate( TheGameText->fetch( "URL:LotrTOS" ) );
	ShellExecuteA( 0, "open", "IEXPLORE.EXE", url.str(), 0, 5 );
	minimizeCurrentThreadWindow();
}
