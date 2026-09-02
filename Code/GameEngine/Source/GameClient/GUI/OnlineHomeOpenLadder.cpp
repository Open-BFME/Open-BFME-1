// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef void *HWND;

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

class UnicodeString : private StringBase<unsigned short>
{
public:
	~UnicodeString() {}
};

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
void bfmeMinimizeCurrentThreadWindow();

class BfmeAptScreenOnlineHome
{
public:
	void bfmeOpenLadderPage( const char *argument );
};

void BfmeAptScreenOnlineHome::bfmeOpenLadderPage( const char * )
{
	AsciiString url;
	url.translate( TheGameText->fetch( "URL:LotrLadder" ) );
	ShellExecuteA( 0, "open", "IEXPLORE.EXE", url.str(), 0, 5 );
	bfmeMinimizeCurrentThreadWindow();
}
