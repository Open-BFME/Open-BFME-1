// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
#include "string_base.h"

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	// Retail's AsciiString adds no members to StringBase<char>: a copy of one
	// encodes the base copy ctor at 0x00887B60 directly, so the delegation has
	// to be visible here.
	AsciiString( const AsciiString &other ) : m_data( other.m_data ) {}
	~AsciiString();

	void concat( const char *text, Int length );
	void concat( char ch ) { concat( &ch, 1 ); }

	Int getLength( void ) const
	{
		return m_data.m_data ? m_data.m_data->length : 0;
	}

	const char *str( void ) const
	{
		return m_data.m_data ? &m_data.m_data->data[ 0 ] : "";
	}

private:
	StringBase<char> m_data;
};

AsciiString Rva00195FC0JoinPath( const AsciiString &left, const AsciiString &right )
{
	AsciiString path( left );
	path.concat( '/' );
	path.concat( right.str(), right.getLength() );
	return path;
}
