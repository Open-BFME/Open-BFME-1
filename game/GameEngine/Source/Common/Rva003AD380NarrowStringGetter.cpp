// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

// A const getter that returns a narrow string member BY VALUE: the caller's
// return slot arrives as the hidden first argument, the member at +0x28 is
// copy-constructed into it, and the exception state word is zeroed for the
// copy that might throw (same shape as Bfme7NarrowStringGetter.cpp).
//
// The one call is 0x00887B60, StringBase<char>'s copy constructor, so the
// member is a narrow string; GameSlot::getName (0x003879C0) copies a wide
// one, which rules out the ZH GameSlot twin this address was landed as.
//
// IDENTITY IS NOT RECOVERED: no direct caller reaches 0x003AD380; the class
// is named for its address and `char m_bfmeHead[0x28]` carries the offset
// and nothing else.

#include "StringInline.h"

class Rva003AD380
{
public:
	AsciiString rva28( void ) const;

private:
	char m_bfmeHead[ 0x28 ];
	AsciiString m_rva28;				// +0x28
};

// ?rva28@Rva003AD380@@QBE?AVAsciiString@@XZ		32B
AsciiString Rva003AD380::rva28( void ) const
{
	return m_rva28;
}
