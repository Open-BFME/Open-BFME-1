// cl: /O2 /EHsc
// CreditsManager::getUnicodeString — ZH twin, BFME StringBase ABI.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const UnicodeString &s) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) { ((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s); return *this; }
template<> inline const char *StringBase<char>::find(char c) const
{
    const char *start = m_data ? &m_data->data[0] : (const char *)"";
    const char *end = start + (m_data ? m_data->length : 0);
    for (const char *p = start; p != end; ++p) {
        if (*p == c) return p;
    }
    return 0;
}

class GameTextInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual UnicodeString fetch(AsciiString label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class CreditsManager
{
	UnicodeString getUnicodeString(AsciiString str);
};

UnicodeString CreditsManager::getUnicodeString(AsciiString str)
{
	UnicodeString uStr;
	if (str.StringBase<char>::compare("<BLANK>") == 0)
		return UnicodeString::TheEmptyString;

	if (str.StringBase<char>::find(':'))
		uStr = TheGameText->fetch(str);
	else
		uStr.translate(str);

	return uStr;
}
