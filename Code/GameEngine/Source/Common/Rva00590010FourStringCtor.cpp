// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class Rva00590010FourString;
unsigned short __cdecl rva0058FE60Compute( Rva00590010FourString *record );

class Rva00590010FourString
{
public:
	Rva00590010FourString(
		const UnicodeString &first,
		const UnicodeString &second,
		const UnicodeString &third,
		const UnicodeString &fourth );

private:
	UnicodeString  m_first;
	UnicodeString  m_second;
	UnicodeString  m_third;
	UnicodeString  m_fourth;
	unsigned short m_value;
};

Rva00590010FourString::Rva00590010FourString(
	const UnicodeString &first,
	const UnicodeString &second,
	const UnicodeString &third,
	const UnicodeString &fourth ) :
	m_first( first ),
	m_second( second ),
	m_third( third ),
	m_fourth( fourth )
{
	m_value = rva0058FE60Compute( this );
}
