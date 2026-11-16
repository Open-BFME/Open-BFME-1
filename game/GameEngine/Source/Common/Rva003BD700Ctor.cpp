// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: thiscall constructor that writes a 6-slot vftable, copy-constructs
// a 4-byte string member at +4, and stores an int argument at +8. Retail
// 0x003BD700, 83 bytes. A novtable base with an out-of-line destructor makes
// the string copy unwind into the base destructor, which is what emits the
// EH3 frame.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }


class __declspec(novtable) Rva003BD700Base
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	~Rva003BD700Base();
};

class Rva003BD700 : public Rva003BD700Base
{
public:
	Rva003BD700(const UnicodeString &s, int n);

private:
	UnicodeString m_at04;
	int m_at08;
};

Rva003BD700::Rva003BD700(const UnicodeString &s, int n)
	: m_at04(s)
	, m_at08(n)
{
}
