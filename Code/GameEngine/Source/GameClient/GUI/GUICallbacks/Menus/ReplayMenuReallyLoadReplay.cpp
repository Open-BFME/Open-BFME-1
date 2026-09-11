// cl: /DNDEBUG /MD /EHsc
// reallyLoadReplay, retail 0x004E08D0, 323 bytes.  The StringBase-backed
// BFME string ABI is the one used by ReplayMenuGetReplayFilenameFromListbox.cpp.

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase();
	void set( const StringBase<T> &other );

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void translate( const class UnicodeString &source );
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}
	UnicodeString &operator=( const UnicodeString &other )
	{
		StringBase<WideChar>::set( other );
		return *this;
	}
};

class GameWindow
{
public:
	int winHide( Bool hide );
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );
};

class RecorderClass
{
public:
	Bool playbackFile( AsciiString filename );
};

class Shell
{
public:
	void pop();
	void hide( Bool shutdownImmediate );
};

extern GameTextInterface *TheGameText;
extern RecorderClass *TheRecorder;
extern Shell *TheShell;

// ReplayMenu.cpp's two file-local cells are at these proven retail globals.
#define listboxReplayFiles (*(GameWindow **)0x012F4118)
#define parentReplayMenu (*(GameWindow **)0x012F410C)

void GadgetListBoxGetSelected( GameWindow *listbox, Int *selected );
UnicodeString GetReplayFilenameFromListbox( GameWindow *listbox, Int index );
GameWindow *MessageBoxOk( UnicodeString title, UnicodeString message,
	void (*callback)( void ) );

void reallyLoadReplay( void )
{
	UnicodeString filename;
	Int selected;
	GadgetListBoxGetSelected( listboxReplayFiles, &selected );
	if( selected < 0 )
	{
		MessageBoxOk( TheGameText->fetch( "GUI:NoFileSelected" ),
			TheGameText->fetch( "GUI:PleaseSelectAFile" ), 0 );
		return;
	}

	filename = GetReplayFilenameFromListbox( listboxReplayFiles, selected );

	AsciiString asciiFilename;
	asciiFilename.translate( filename );

	TheRecorder->playbackFile( asciiFilename );

	if( parentReplayMenu != 0 )
	{
		parentReplayMenu->winHide( true );
	}
	TheShell->pop();
	TheShell->hide( true );
}
