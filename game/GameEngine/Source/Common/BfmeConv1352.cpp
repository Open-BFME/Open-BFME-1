// cl: /DNDEBUG /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5 conversions.

#include "unicode_string.h"
#include <new>

inline UnicodeString::UnicodeString(const UnicodeString &source)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&source);
}

class BfmeStrVGB
{
public:
	char m_bfmePad[4];
	int m_bfme04;
	int m_bfme08;
};

class BfmeThingVGB
{
public:
	BfmeStrVGB *bfmeGetVGB(BfmeStrVGB *out);
	char m_bfmePad[0x2e8];
	BfmeStrVGB m_bfmeStr;
};

BfmeStrVGB *BfmeThingVGB::bfmeGetVGB(BfmeStrVGB *out)
{
	volatile int m_bfmeDead = 0;
	BfmeStrVGB *s = &m_bfmeStr;
	__assume(out != 0);
	new (out) UnicodeString(*(const UnicodeString *)s);
	out->m_bfme04 = s->m_bfme04;
	out->m_bfme08 = s->m_bfme08;
	return out;
}
