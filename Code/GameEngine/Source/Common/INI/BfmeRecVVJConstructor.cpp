// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Retail 0x00094860: the two-string INI definition record constructor.
// The caller at 0x00094300 constructs this 16-byte record from two token
// strings.  Each four-byte string view is the same AsciiString representation
// used by the parser, so its copy constructor reaches the shared
// StringBase<char> body at 0x00887B60.

#include "StringInline.h"

class BfmeStrVVJ
{
private:
	AsciiString m_string;
};

class BfmeFirstKindVVJ
{
public:
	BfmeFirstKindVVJ( const BfmeStrVVJ &first )
		: m_first( first )
		, m_kind( 3 )
	{
	}

private:
	BfmeStrVVJ m_first;
	int m_kind;
};

class BfmeRecVVJ
{
public:
	BfmeRecVVJ( const BfmeStrVVJ &first, const BfmeStrVVJ &second );

private:
	BfmeFirstKindVVJ m_firstKind;
	BfmeStrVVJ m_second;
	BfmeStrVVJ m_secondCopy;
};

BfmeRecVVJ::BfmeRecVVJ( const BfmeStrVVJ &first, const BfmeStrVVJ &second )
	: m_firstKind( first )
	, m_second( second )
	, m_secondCopy( second )
{
}
