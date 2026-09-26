// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

// A const getter that returns a narrow string member BY VALUE: the caller's
// return slot arrives as the hidden first argument, the member at +0x78 is
// copy-constructed into it, and the exception state word is zeroed for the
// copy that might throw.
//
// The one call is 0x00887B60, StringBase<char>'s copy constructor -- retail
// inlines the AsciiString forwarder, so only an INLINE forwarding copy ctor
// over `: private StringBase<char>` puts the base body at the call site.
// That callee is also what rules out the PSPlayerStats getter this address
// was landed as; returning a PSPlayerStats would call its own copy ctor.
//
// IDENTITY IS NOT RECOVERED: the class is named for its address and
// `char m_bfmeHead[0x78]` carries the offset and nothing else.

#include "StringInline.h"

class Gen006372D0
{
public:
	AsciiString bfmeGet( void ) const;

private:
	char m_bfmeHead[ 0x78 ];
	AsciiString m_bfmeText;				// +0x78
};

// ?bfmeGet@Gen006372D0@@QBE?AVAsciiString@@XZ		32B
AsciiString Gen006372D0::bfmeGet( void ) const
{
	return m_bfmeText;
}
