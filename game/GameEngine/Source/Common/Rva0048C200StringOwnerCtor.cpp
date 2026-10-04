// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// Address-derived owner of two inline StringBase-compatible members.
//
// Both members are StringBase<char>-compatible and retail's two out-of-line
// calls -- 0x00887940, ?releaseBuffer@?$StringBase@D@@AAEXXZ, reached through
// the inline StringBase destructor -- are the whole identity of this body. The
// zeros before them are the members' own construction: retail's AsciiString
// default constructor stores the single null inline (see the entry ctor at
// 0x009A1390), which is what the StringInline AsciiString models.
//
// releaseBuffer() on that null buffer is a no-op, which is why retail can
// reach it here and again from the owner's own destructor; both bodies are the
// same release of an unshared, empty string.

#include "StringInline.h"

class Rva0048C200Owner
{
public:
	Rva0048C200Owner();

private:
	void *m_head;			// +0x00
	AsciiString m_first;		// +0x04
	AsciiString m_second;		// +0x08
	int m_count;			// +0x0C
	unsigned char m_active;		// +0x10
};

Rva0048C200Owner::Rva0048C200Owner()
	: m_head( 0 ), m_count( 0 ), m_active( 0 )
{
	m_second.~AsciiString();
	m_first.~AsciiString();
}