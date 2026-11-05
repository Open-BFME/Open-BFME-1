// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: clean C++ conversion of GameWindowManager::winTextLabelToText.

#include "ascii_string.h"
#include "unicode_string.h"

// Retail inlines ~UnicodeString at every scope exit and calls
// StringBase<unsigned short>::releaseBuffer (0x008881D0) directly, never
// the 0x0005EEA0 jmp body the out-of-line declaration would bind to.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

// AsciiString::isEmpty, expanded in place.  Calling the member would emit
// ?isEmpty@AsciiString@@QBE_NXZ and ?isEmpty@?$StringBase@D@@QBE_NXZ COMDATs
// that are not retail's bodies.  The buffer pointer is the string's first
// word; its length is at +4.
static __forceinline bool asciiIsEmpty( const AsciiString &string )
{
	const char *data = *reinterpret_cast<const char * const *>(&string);
	return !data || *reinterpret_cast<const unsigned short *>(data + 4) == 0;
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
	if (asciiIsEmpty(label)) {
		return UnicodeString::TheEmptyString;
	}

	UnicodeString text;
	text.translate(label);
	return text;
}
