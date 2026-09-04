// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: SetLookAtPlayer, retail 0x004DBB50, 120 bytes. Converted from
// gen-dump d_004dbb50. ZH twin stores lookAtPlayerID then assigns
// lookAtPlayerName from the by-value AsciiString's str(). BFME keeps the
// name as STLport std::string (assign first/last after a strlen walk) and
// the id as a TU-scope Int. Callers: WOLWelcomeMenu.cpp and WOLBuddyOverlay.cpp.

#include <string>

typedef int Int;

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	const char *str( void ) const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
};

Int lookAtPlayerID = 0;
std::string lookAtPlayerName;

void SetLookAtPlayer( Int id, AsciiString nick )
{
	lookAtPlayerID = id;
	lookAtPlayerName = nick.str();
}
