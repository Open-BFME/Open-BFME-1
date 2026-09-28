// ?rva006AF840@MilesAudioManager@@QAEXXZ
// partial score=0.99 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006AF840 (973 bytes).  A MilesAudioManager method: its two callers
// (0x006B4590 and the manager update at 0x006B9C90) pass the manager through
// ILT 0x00017F85, and like its siblings it holds the manager mutex at +0x95C
// (MilesAudioManagerConstructor.cpp layout) for the whole body.  It drains the
// pending UnicodeString list at +0x980 into the handler at 0x00695B80, then
// for each pending file name at +0x98C looks up "DIALOGEVENT:<file>SubTitle"
// in TheGameText, records the text under the file name in the map at +0x96C
// and hands non-empty text to the same handler.  A leading '*' marks a line
// that is kept (without the marker) only when the GlobalData flag at +0xA72
// is set.  The method name stays address-derived.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject( void *handle,
	unsigned long milliseconds );
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex( void *handle );
#include <stdlib.h>
#include <string.h>

void __cdecl operator delete( void * ) throw();
#include <vector>
#include <hash_map>

typedef bool Bool;
typedef int Int;
typedef unsigned short WideChar;

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	Int getLength() const { return m_data ? m_data->length : 0; }
	Bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	T getCharAt( Int index ) const { return m_data ? m_data->data[ index ] : 0; }
	const T *str() const { return m_data ? m_data->data : (const T *)""; }
	void set( const StringBase<T> &src );
	void concat( const T *str, Int len );
	void clear() { releaseBuffer(); }

	void swap( StringBase<T> &other )
	{
		Header *temp = m_data;
		m_data = other.m_data;
		other.m_data = temp;
	}

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *str );
	StringBase( const StringBase<T> &src );
	StringBase( const StringBase<T> &src, Int start, Int len );
	~StringBase() { releaseBuffer(); }

	void releaseBuffer();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};

	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString( const char *str ) : StringBase<char>( str ) {}
	AsciiString( const AsciiString &that ) : StringBase<char>( that ) {}
	AsciiString( const AsciiString &that, Int start, Int len ) : StringBase<char>( that, start, len ) {}
	~AsciiString() {}

	AsciiString &operator=( const AsciiString &that )
	{
		set( that );
		return *this;
	}

	void concat( const char *str ) { StringBase<char>::concat( str, strlen( str ) ); }
};

class UnicodeString : public StringBase<WideChar>
{
public:
	UnicodeString() {}
	UnicodeString( const UnicodeString &that ) : StringBase<WideChar>( that ) {}
	UnicodeString( const UnicodeString &that, Int start, Int len ) : StringBase<WideChar>( that, start, len ) {}
	~UnicodeString() {}

	UnicodeString &operator=( const UnicodeString &that )
	{
		set( that );
		return *this;
	}

	static UnicodeString TheEmptyString;
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 ) = 0;
	virtual UnicodeString fetch( AsciiString label, Bool *exists = 0 ) = 0;
};

extern GameTextInterface *TheGameText;

namespace rts
{
	template <typename T> struct hash;
	template <typename T> struct equal_to;
	template <> struct hash<AsciiString>
	{
		size_t operator()( AsciiString ast ) const;
	};
	template <> struct equal_to<AsciiString>
	{
		Bool operator()( const AsciiString &left, const AsciiString &right ) const;
	};
}

typedef _STL::hash_map< AsciiString, UnicodeString, rts::hash<AsciiString>,
	rts::equal_to<AsciiString> > Rva006AF840RealMap;

struct Rva006C9270GlobalData
{
	unsigned char m_beforeA72[ 0xa72 ];
	Bool m_boolA72;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class MilesAudioScopedMutex
{
public:
	__forceinline MilesAudioScopedMutex( void *mutex )
	{
		m_held = 0;
		m_mutex = mutex;
		if( WaitForSingleObject( m_mutex, 0xFFFFFFFFu ) != 0x102u )
			m_held = 1;
	}

	__forceinline ~MilesAudioScopedMutex( void )
	{
		if( m_held )
		{
			ReleaseMutex( m_mutex );
			m_held = 0;
		}
	}

private:
	void *m_mutex;
	unsigned char m_held;
};

// The file-name -> subtitle map at +0x96C.  Its insert is the STLport
// hash_map one (resize to one more element, then insert without resizing);
// both hashtable bodies are reached only through their ILT thunks, whose
// ledger rows still carry other instantiations' names.
struct Rva006AF840SubtitleEntry
{
	AsciiString first;
	UnicodeString second;

	Rva006AF840SubtitleEntry( const AsciiString &key, const UnicodeString &value )
		: first( key ), second( value ) {}
};

struct Rva006AF840InsertResult
{
	void *node;
	void *table;
	Bool inserted;
};

extern void j_0001547e();
extern void j_00038555();
extern void j_0003f6fc();

class Rva006AF840Call
{
};

class Rva006AF840SubtitleMap
{
public:
	void insert( Rva006AF840InsertResult *result, const Rva006AF840SubtitleEntry &entry )
	{
		resize( m_numElements + 1 );
		insertUniqueNoResize( result, entry );
	}

private:
	void resize( unsigned int hint )
	{
		typedef void ( Rva006AF840Call::*Function )( unsigned int );
		union { void ( *raw )(); Function member; } fn;
		fn.raw = j_0001547e;
		( reinterpret_cast<Rva006AF840Call *>( this )->*fn.member )( hint );
	}

	void insertUniqueNoResize( Rva006AF840InsertResult *result, const Rva006AF840SubtitleEntry &entry )
	{
		typedef void ( Rva006AF840Call::*Function )( Rva006AF840InsertResult *,
			const Rva006AF840SubtitleEntry & );
		union { void ( *raw )(); Function member; } fn;
		fn.raw = j_00038555;
		( reinterpret_cast<Rva006AF840Call *>( this )->*fn.member )( result, entry );
	}

	unsigned char m_hashers[ 4 ];
	void *m_buckets[ 3 ];
	unsigned int m_numElements;
};

class MilesAudioManager
{
public:
	void rva006AF840();

private:
	// Handler at 0x00695B80 (ILT 0x0003F6FC) for one line of text.
	void rva00695B80( const UnicodeString &text )
	{
		typedef void ( Rva006AF840Call::*Function )( const UnicodeString & );
		union { void ( *raw )(); Function member; } fn;
		fn.raw = j_0003f6fc;
		( reinterpret_cast<Rva006AF840Call *>( this )->*fn.member )( text );
	}

	char m_pad000[ 0x95c ];
	void *m_mutex;									// +0x95c
	unsigned int m_960, m_964, m_968;
	Rva006AF840RealMap m_subtitles;				// +0x96c
	_STL::vector<UnicodeString> m_pendingText;		// +0x980
	_STL::vector<AsciiString> m_pendingFiles;		// +0x98c
};

void MilesAudioManager::rva006AF840()
{
	MilesAudioScopedMutex lock( m_mutex );

	_STL::vector<UnicodeString>::iterator text;
	for( text = m_pendingText.begin(); text != m_pendingText.end(); ++text )
		rva00695B80( *text );
	m_pendingText.clear();

	_STL::vector<AsciiString>::iterator file;
	for( file = m_pendingFiles.begin(); file != m_pendingFiles.end(); ++file )
	{
		AsciiString fileName( *file );
		if( fileName.getLength() > 260 )
		{
			AsciiString truncated( fileName, 0, 260 );
			fileName.swap( truncated );
		}

		char fileBase[ 260 ];
		_splitpath( fileName.str(), 0, 0, fileBase, 0 );

		AsciiString label( "DIALOGEVENT:" );
		label.concat( fileBase );
		label.concat( "SubTitle" );

		Bool exists = false;
		UnicodeString subtitle = TheGameText == 0 ? UnicodeString::TheEmptyString
			: TheGameText->fetch( label, &exists );
		if( !exists )
			subtitle.clear();
		else if( subtitle.getCharAt( 0 ) == L'*' )
		{
			if( TheWritableGlobalData->m_boolA72 )
			{
				UnicodeString unmarked( subtitle, 1, subtitle.getLength() - 1 );
				subtitle.swap( unmarked );
			}
			else
				subtitle.clear();
		}

		m_subtitles.insert( Rva006AF840RealMap::value_type( *file, subtitle ) );

		if( !subtitle.isEmpty() )
			rva00695B80( subtitle );
	}
	m_pendingFiles.clear();
}
