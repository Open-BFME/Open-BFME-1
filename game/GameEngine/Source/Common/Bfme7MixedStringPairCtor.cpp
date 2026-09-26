// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

// A two-string constructor whose two members are DIFFERENT widths: a narrow
// string at +0x00 copy-constructed from the first argument, a wide one at
// +0x04 from the second.
//
// The two callees are the whole identity.  0x00887B60 is StringBase<char>'s
// copy constructor and 0x00888400 is StringBase<unsigned short>'s, so this is
// not the pair<UnicodeString,UnicodeString> constructor it was landed as --
// that one would call 0x00888400 twice.
//
// The exception frame exists only to destroy the narrow member if the wide
// copy throws; nothing in the normal path unwinds.
//
// IDENTITY IS NOT RECOVERED: the class is named for its address.

#include "StringInline.h"

class Gen0069DD40
{
public:
	Gen0069DD40( const AsciiString &first, const UnicodeString &second );

private:
	AsciiString m_bfmeFirst;			// +0x00
	UnicodeString m_bfmeSecond;			// +0x04
};

// ??0Gen0069DD40@@QAE@ABVAsciiString@@ABVUnicodeString@@@Z		80B
Gen0069DD40::Gen0069DD40( const AsciiString &first, const UnicodeString &second )
	: m_bfmeFirst( first ), m_bfmeSecond( second )
{
}
