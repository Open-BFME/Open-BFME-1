// cl: /O2 /Ob0 /Igame/Libraries/Source/WWVegas/WWLib

// Retail's reset (0x00385180) pushes the immediate 0x01336E50 and calls the
// out-of-line copy through ecx = this+4, so the source global is the one-word
// empty-string object at RVA 0x00F36E50. That is AsciiString::TheEmptyString,
// which the real WWLib header declares (and NameKeyGenerator.cpp,
// Common/System/AsciiString.cpp and BoneFXUpdate_initTimes.cpp define), so the
// link has a definition to bind instead of an invented extern. Both bodies
// call 0x00887C90 with ecx = this+4, the out-of-line
// StringBase<char>::set (0x00887C90, game/Libraries/Source/string/
// StringBase.cpp), so the member is the real StringBase<char> (AsciiString
// adds no data) and the invented local operator= reference disappears with
// the invented global. Spelling the member AsciiString would instead make cl
// emit its own `?set@AsciiString@@QAEXABV1@@Z` scope-alias COMDAT, and the
// link would then keep a body that is not retail's.
#include "ascii_string.h"

// The one-word string view the public signature is spelled with; the member it
// is passed to is the real StringBase<char> above (AsciiString adds no data).
class Rva0036CA00Str
{
private:
	void *m_item;
};

struct Rva00385150Extra
{
	int a;
	int b;
};

class Rva00385150
{
	virtual void handle();
	StringBase<char> m_04;
	int m_08;
	int m_0C;

public:
	void set(const Rva0036CA00Str &s, const Rva00385150Extra *extra);
	void reset();
};

void Rva00385150::set(const Rva0036CA00Str &s, const Rva00385150Extra *extra)
{
	m_04.set(*reinterpret_cast<const StringBase<char> *>(&s));
	m_08 = extra->a;
	m_0C = extra->b;
}

void Rva00385150::reset()
{
	m_04.set(*reinterpret_cast<const StringBase<char> *>(&AsciiString::TheEmptyString));
	m_08 = 0;
	m_0C = 0;
}
