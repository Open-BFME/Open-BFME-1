// cl: /DNDEBUG /MD
//
// Retail 0x00579440: open Skirmish.apt unless its singleton already exists.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase() { releaseBuffer(); }

	void releaseBuffer();

	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void push( AsciiString filename, bool shutdownImmediate = false );
};

extern Shell *TheShell;
class BfmeAptScreenSkirmish;
extern BfmeAptScreenSkirmish *Rva012F4B54Skirmish;

// ?_bfme_showSkirmish@@YAXXZ
void _bfme_showSkirmish( void )
{
	if( reinterpret_cast<void * &>(Rva012F4B54Skirmish) == 0 )
		TheShell->push( AsciiString( "Skirmish.apt" ), false );
}
