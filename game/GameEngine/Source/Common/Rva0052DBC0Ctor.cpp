// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib

// The four-byte member at +4 is a StringBase<char>, the narrow STLport base
// AsciiString inherits (StringBase<char> copy ctor, 0x00887B60). BfmeString52DBC0
// is this translation unit's view of that member, so the member initializer
// casts at the use instead of spelling a private StringBase constructor.

#include "ascii_string.h"

class BfmeString52DBC0
{
public:
	BfmeString52DBC0( const BfmeString52DBC0 &other );

private:
	void *m_data;
};

class Rva0052DBC0
{
public:
	Rva0052DBC0( unsigned int value, const BfmeString52DBC0 &text, bool enabled );

private:
	bool m_enabled;
	AsciiString m_text;
	unsigned int m_value;
};

Rva0052DBC0::Rva0052DBC0( unsigned int value, const BfmeString52DBC0 &text, bool enabled )
	: m_enabled( enabled ), m_text( *(const AsciiString *)&text ), m_value( value )
{
}