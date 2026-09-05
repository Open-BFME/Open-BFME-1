// cl: /DNDEBUG /MD /EHsc
// Open-BFME: copyReplay, retail 0x004E1090, 760 bytes; deleteReplay, retail
// 0x004E2100, 623 bytes. Converted from gen-dump d_004e1090.asm. ZH twin is
// ReplayMenu.cpp's copyReplay/deleteReplay; this TU keeps its own statics
// (listboxReplayFiles, callCopy, callDelete) rather than sharing
// ReplayMenuInit.cpp's, since DIR32 relocations are patched to the real
// retail address independently of which C++ symbol names them.
// getReplayDir() compiles as a plain static call (no TheRecorder deref).
// GetReplayFilenameFromListbox is ReplayMenuGetReplayFilenameFromListbox.cpp's
// matched twin; only its prototype is needed here.

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen( const WideChar *text );
extern "C" unsigned int __cdecl strlen( const char *text );

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
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

public:
	void set( const StringBase<T> &other );
	void set( const T *text, Int length );
	void concat( const T *text, Int length );
	void trim();

private:
	Header *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	AsciiString &operator=( const AsciiString &other )
	{
		StringBase<char>::set( other );
		return *this;
	}

	void set( const char *text )
	{
		Int length = text ? (Int)strlen( text ) : 0;
		StringBase<char>::set( text, length );
	}

	void concat( const char *text, Int length ) { StringBase<char>::concat( text, length ); }

	void concat( const AsciiString &other )
	{
		const Int length = other.m_data ? other.m_data->m_length : 0;
		const char *text = other.m_data ? other.m_data->m_text : (const char *)0x0107388B;
		StringBase<char>::concat( text, length );
	}

	void translate( class UnicodeString const &src );

	const char *str() const { return m_data ? m_data->m_text : (const char *)0x0107388B; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}

	void set( const WideChar *text )
	{
		StringBase<WideChar>::set( text, text ? (Int)wcslen( text ) : 0 );
	}

	void trim() { StringBase<WideChar>::trim(); }

	void translate( const AsciiString &src );
};

class GameWindow;

// ?GetReplayFilenameFromListbox@@YA?AVUnicodeString@@PAVGameWindow@@H@Z
UnicodeString GetReplayFilenameFromListbox( GameWindow *listbox, Int index );

// ?GadgetListBoxGetSelected@@YAXPAVGameWindow@@PAH@Z
void GadgetListBoxGetSelected( GameWindow *listbox, Int *selected );

// ?GadgetListBoxReset@@YAXPAVGameWindow@@@Z
void GadgetListBoxReset( GameWindow *listbox );
void PopulateReplayFileListbox( GameWindow *listbox );

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
public:
	static AsciiString getReplayDir();
};

extern GameTextInterface *TheGameText;

GameWindow *MessageBoxOk( UnicodeString title, UnicodeString body, void ( *callback )( void ) );

extern "C" __declspec(dllimport) int __stdcall DeleteFileA( const char *fileName );
extern "C" __declspec(dllimport) int __stdcall CopyFileA( const char *existing, const char *newFile, int failIfExists );
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError();
extern "C" __declspec(dllimport) unsigned long __stdcall FormatMessageA(
	unsigned long flags, const void *source, unsigned long messageId, unsigned long languageId,
	char *buffer, unsigned long size, void *args );
extern "C" __declspec(dllimport) unsigned long __stdcall FormatMessageW(
	unsigned long flags, const void *source, unsigned long messageId, unsigned long languageId,
	WideChar *buffer, unsigned long size, void *args );
extern "C" __declspec(dllimport) int __stdcall SHGetSpecialFolderLocation( void *hwndOwner, int folder, void *pidl );
extern "C" __declspec(dllimport) int __stdcall SHGetPathFromIDListA( void *pidl, char *path );
#pragma comment(lib, "shell32.lib")

enum
{
	CSIDL_DESKTOPDIRECTORY = 0x10,
	FORMAT_MESSAGE_FROM_SYSTEM = 0x1000
};

static GameWindow *listboxReplayFiles = 0;
static Bool callCopy = false;
static Bool callDelete = false;

// ?copyReplay@@YAXXZ
void copyReplay( void )
{
	callCopy = false;
	Int selected;
	GadgetListBoxGetSelected( listboxReplayFiles, &selected );
	if ( selected < 0 )
	{
		MessageBoxOk( TheGameText->fetch( "GUI:NoFileSelected" ), TheGameText->fetch( "GUI:PleaseSelectAFile" ), 0 );
		return;
	}

	AsciiString filename, translate;
	filename = RecorderClass::getReplayDir();
	translate.translate( GetReplayFilenameFromListbox( listboxReplayFiles, selected ) );
	filename.concat( translate );

	char path[ 1024 ];
	void *pidl;
	SHGetSpecialFolderLocation( 0, CSIDL_DESKTOPDIRECTORY, &pidl );
	SHGetPathFromIDListA( pidl, path );
	AsciiString newFilename;
	newFilename.set( path );
	newFilename.concat( "\\", 1 );
	newFilename.concat( translate );

	if ( CopyFileA( filename.str(), newFilename.str(), 0 ) == 0 )
	{
		WideChar buffer[ 1024 ];
		FormatMessageW( FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, buffer, sizeof( buffer ), 0 );
		UnicodeString errorStr;
		errorStr.set( buffer );
		errorStr.trim();
		MessageBoxOk( TheGameText->fetch( "GUI:Error" ), errorStr, 0 );
	}
}

// ?deleteReplay@@YAXXZ
void deleteReplay( void )
{
	callDelete = false;
	Int selected;
	GadgetListBoxGetSelected( listboxReplayFiles, &selected );
	if ( selected < 0 )
	{
		MessageBoxOk( TheGameText->fetch( "GUI:NoFileSelected" ), TheGameText->fetch( "GUI:PleaseSelectAFile" ), 0 );
		return;
	}

	AsciiString filename, translate;
	filename = RecorderClass::getReplayDir();
	translate.translate( GetReplayFilenameFromListbox( listboxReplayFiles, selected ) );
	filename.concat( translate );

	if ( DeleteFileA( filename.str() ) == 0 )
	{
		char buffer[ 1024 ];
		FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, buffer, sizeof( buffer ), 0 );
		UnicodeString errorStr;
		translate.set( buffer );
		errorStr.translate( translate );
		MessageBoxOk( TheGameText->fetch( "GUI:Error" ), errorStr, 0 );
	}

	GadgetListBoxReset( listboxReplayFiles );
	PopulateReplayFileListbox( listboxReplayFiles );
}
