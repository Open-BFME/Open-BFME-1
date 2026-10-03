// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: clean C++ conversion of GameWindowManager::winTextLabelToText.

#include "ascii_string.h"
#include "unicode_string.h"

// This caller inlines the canonical null/length test and wide construction.
template <> inline bool StringBase<char>::isEmpty() const
{
	return !m_data || m_data->length == 0;
}

inline UnicodeString::UnicodeString() : m_text(0) {}
inline UnicodeString::UnicodeString(const UnicodeString &source)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&source);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	UnicodeString winTextLabelToText(AsciiString label);
};

UnicodeString GameWindowManager::winTextLabelToText(AsciiString label)
{
	if (label.isEmpty()) {
		return UnicodeString::TheEmptyString;
	}

	UnicodeString text;
	text.translate(label);
	return text;
}
