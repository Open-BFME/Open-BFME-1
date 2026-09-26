// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/languagefilter /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

#include "Common/UnicodeString.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LanguageFilter.h
struct UnicodeStringLessThan
{
	Bool operator()(UnicodeString a, UnicodeString b) const;
};

// UnicodeString::compareNoCase is inline in the shim and folds to _wcsicmp.
// Retail calls StringBase<G>::compareNoCase out of line so go through the base
// the same way the shim routes the copy ctor.
static int compareNoCase(const UnicodeString& self, const UnicodeString& other)
{
	return ((const StringBase<wchar_t> *)&self)->compareNoCase(
		*(const StringBase<wchar_t> *)&other);
}

// ??RUnicodeStringLessThan@@QBE_NVUnicodeString@@0@Z
Bool UnicodeStringLessThan::operator()(UnicodeString a, UnicodeString b) const
{
	return (compareNoCase(a, b) < 0);
}
