// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GetReplayFilenameFromListbox, retail 0x004E0740, 319 bytes.
// Converted from gen-dump d_004e0740. ZH twin is in ReplayMenu.cpp; that TU
// already owns PopulateReplayFileListbox unwind labels, so this lives here.
// BFME UnicodeString is StringBase-backed: compare is out of line, concat
// inlines the word-at-+4 / text-at-+8 payload, and getReplayExtention is
// static (no TheRecorder reload).

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
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void set( const StringBase<T> &other );

public:
	int compare( const StringBase<T> &other ) const throw();
	void concat( const T *text, Int length );

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
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}

	int compare( const UnicodeString &other ) const throw()
	{
		return StringBase<WideChar>::compare( *(const StringBase<WideChar> *)&other );
	}

	void concat( const UnicodeString &other )
	{
		const Int length = other.m_data ? other.m_data->m_length : 0;
		const WideChar *text = other.m_data
			? other.m_data->m_text
			: (const WideChar *)0x0107388C;
		StringBase<WideChar>::concat( text, length );
	}

	void translate( const AsciiString &src );
};

inline Bool operator==( const UnicodeString &left, const UnicodeString &right )
{
	return left.compare( right ) == 0;
}

class GameWindow;

UnicodeString GadgetListBoxGetText( GameWindow *listbox, Int row, Int column = 0 );

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
	AsciiString getLastReplayFileName();
	static AsciiString getReplayExtention();
};

extern GameTextInterface *TheGameText;
extern RecorderClass *TheRecorder;

// ?GetReplayFilenameFromListbox@@YA?AVUnicodeString@@PAVGameWindow@@H@Z
UnicodeString GetReplayFilenameFromListbox( GameWindow *listbox, Int index )
{
	UnicodeString fname = GadgetListBoxGetText( listbox, index );

	if ( fname == TheGameText->fetch( "GUI:LastReplay" ) )
	{
		fname.translate( TheRecorder->getLastReplayFileName() );
	}

	UnicodeString ext;
	ext.translate( RecorderClass::getReplayExtention() );
	fname.concat( ext );

	return fname;
}
