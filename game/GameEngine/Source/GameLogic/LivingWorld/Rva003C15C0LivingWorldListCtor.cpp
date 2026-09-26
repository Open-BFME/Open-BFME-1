// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x003C15C0 is the sized-list constructor called by the neutral
// physical owner at 0x003C2FC0 after it loads this+0xC0.  No named
// LivingWorldLogic identity is claimed here.  The caller passes zero as the
// count, while the constructor still materializes one default value before
// delegating to STLport's 12-byte-payload fill-insert (20-byte node).
//
// The element's domain name is not present in the surviving declarations, so
// its type stays address-derived.  Its first word is the wide StringBase
// handle proven by the cleanup call at 0x008881D0; the two trailing words are
// initialized by the retail default value to 0 and 3.

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#include <list>

class UnicodeString
{
public:
	UnicodeString() : m_text(0) {}
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
			*(const StringBase<wchar_t> *)&that);
	}
	~UnicodeString()
	{
		((StringBase<wchar_t> *)this)->releaseBuffer();
	}

private:
	void *m_text;
};

struct Rva003C15C0Element
{
	UnicodeString m_text;
	int m_word4;
	int m_word8;

	Rva003C15C0Element()
		: m_text()
		, m_word4(0)
		, m_word8(3)
	{
	}

	~Rva003C15C0Element() {}
};

bool operator==(const Rva003C15C0Element &, const Rva003C15C0Element &);
bool operator<(const Rva003C15C0Element &, const Rva003C15C0Element &);

template class _STL::list<Rva003C15C0Element>;
