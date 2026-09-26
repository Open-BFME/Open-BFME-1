// Retail 0x004C47E0, full 171 bytes. Matched InGameUI::popupMessage at
// 0x00442040 passes const AsciiString&, not the legacy by-value spelling.
// This wrapper translates a label and delegates to the Unicode list updater
// at 0x004C4630; it does not itself manipulate the briefing list.
// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "string_base.h"
#include "ascii_string.h"
#include "unicode_string.h"

template<> inline bool StringBase<char>::isEmpty() const
{
	return !m_data || m_data->length == 0;
}
inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}
inline UnicodeString::UnicodeString(const wchar_t *text)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		(const unsigned short *)text);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(AsciiString label, bool *exists = 0);
};
extern GameTextInterface *TheGameText;
void UpdateDiplomacyBriefingText(const UnicodeString &text, bool clear);

void UpdateDiplomacyBriefingText(const AsciiString &text, bool clear)
{
	if (text.isEmpty())
		UpdateDiplomacyBriefingText(UnicodeString(L""), clear);
	else
	{
		UnicodeString translated = TheGameText->fetch(text);
		UpdateDiplomacyBriefingText(translated, clear);
	}
}

