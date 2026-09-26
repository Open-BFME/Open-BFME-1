// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
//
// GameClient's member at +0x17C calls this destructor through ILT 0x00011D42.
// The body removes the twelve SpellBookUI timer callback names from the live
// WindowManager and then removes their Palantir gadgets.

#include <hash_map>

template <typename T> class StringBase
{
	friend class AsciiString;

public:
	void concat( const T *text, int length );

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

AsciiString operator+( AsciiString left, const AsciiString &right );

struct Rva0046AF20Mapped
{
	void *m_callback;
};

namespace rts
{
	template <class T> struct hash;
	template <class T> struct equal_to;

	template <> struct hash<AsciiString>
	{
		unsigned int operator()( AsciiString value ) const;
	};

	template <> struct equal_to<AsciiString>
	{
		int operator()( const AsciiString &left, const AsciiString &right ) const;
	};
}

typedef std::hash_map<AsciiString, Rva0046AF20Mapped,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046AF20Map;

class WindowManager
{
public:
	void removeAptObject( const AsciiString &name );

private:
	unsigned char m_pad[ 0x94 ];
	Rva0046AF20Map m_callbacks;
};

extern WindowManager *g_theWindowManager;

extern void j_0003d54b();

typedef void (WindowManager::*EraseCallback)( const AsciiString * );

union EraseCallbackCast
{
	void (*raw)();
	EraseCallback member;
};

class Rva00591C40GameClientMember
{
public:
	~Rva00591C40GameClientMember();
};

Rva00591C40GameClientMember::~Rva00591C40GameClientMember()
{
	if( g_theWindowManager != 0 )
	{
		int index = 0;
		do
		{
			AsciiString name;
			++index;
			name.format( AsciiString( "SpellBookUI/Spell%d/" ), index );

			g_theWindowManager->removeAptObject(
				AsciiString( "Palantir/" ) + name );

			((StringBase<char> *)&name)->concat( "Timer", 5 );

			EraseCallbackCast cast;
			cast.raw = j_0003d54b;
			(g_theWindowManager->*cast.member)( &name );
		} while( index < 12 );
	}
}
