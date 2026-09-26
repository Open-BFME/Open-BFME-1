// Address-derived reconstruction of a member that resolves a nested object and
// returns the combined sizes of its two four-byte spans.

struct Rva003BDF70Span
{
	void **m_begin;
	void **m_end;
	int size() const { return m_end - m_begin; }
};

#include "ascii_string.h"

class LivingWorldRegion
{
public:
	char m_pad00[ 0x54 ];
	Rva003BDF70Span m_first;             // +0x54
	char m_pad5C[ 0x4 ];
	Rva003BDF70Span m_second;            // +0x60
};

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8A50( const AsciiString &key );
};

class Rva003BDF70Owner
{
public:
	int combinedSpanCount();

private:
	char m_pad00[ 0x28 ];
	LivingWorldRegionManager *m_resolver; // +0x28
	char m_pad2C[ 0x4 ];
	AsciiString m_key;                   // +0x30
};

int Rva003BDF70Owner::combinedSpanCount()
{
	if (!m_resolver)
		return 0;

	LivingWorldRegion *result = m_resolver->rva003C8A50( m_key );
	if (!result)
		return 0;

	return result->m_first.size() + result->m_second.size();
}

// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
