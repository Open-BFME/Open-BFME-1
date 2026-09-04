// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// The small BFME deque wrapper at retail 0x00596B60 appends a 12-byte
// payload.  The payload's first word is the empty StringBase member used by
// the retail construct/copy helper; its second word is the caller's value.

#define _STLP_NO_EXCEPTIONS 1
#include <deque>

class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	AsciiString( const AsciiString &other );
	~AsciiString();

private:
	void *m_data;
};

struct Gen_t_00595870_p12cd
{
	AsciiString m_name;
	int m_value;
	int m_unmodelled;
};

class Gen00596B60
{
public:
	void handle( int value );

private:
	char m_pad[ 0x20 ];
	_STL::deque<Gen_t_00595870_p12cd> m_values;
};

void Gen00596B60::handle( int value )
{
	if( value >= 2 )
		return;

	Gen_t_00595870_p12cd payload;
	payload.m_value = value;
	m_values.push_back( payload );
}
