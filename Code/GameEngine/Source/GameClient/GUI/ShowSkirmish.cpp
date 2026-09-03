// cl: /DNDEBUG /MD
//
// Retail 0x00579440: open Skirmish.apt unless its singleton already exists.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void push( AsciiString filename, bool shutdownImmediate = false );
};

extern Shell *TheShell;
extern void *g_obj12F4B54;

// ?_bfme_showSkirmish@@YAXXZ
void _bfme_showSkirmish( void )
{
	if( g_obj12F4B54 == 0 )
		TheShell->push( AsciiString( "Skirmish.apt" ), false );
}
