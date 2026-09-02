// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class Rva0058BE30FourString
{
public:
	Rva0058BE30FourString( const Rva0058BE30FourString &other );

private:
	UnicodeString  m_first;
	UnicodeString  m_second;
	UnicodeString  m_third;
	UnicodeString  m_fourth;
	unsigned short m_value;
};

Rva0058BE30FourString::Rva0058BE30FourString( const Rva0058BE30FourString &other ) :
	m_first( other.m_first ),
	m_second( other.m_second ),
	m_third( other.m_third ),
	m_fourth( other.m_fourth ),
	m_value( other.m_value )
{
}
