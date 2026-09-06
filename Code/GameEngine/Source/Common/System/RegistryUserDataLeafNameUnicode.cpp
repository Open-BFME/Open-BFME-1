// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_downloadmanager /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "string_base.h"

class UnicodeString
{
public:
	UnicodeString() : m_text(0) {}
	UnicodeString(const wchar_t *value)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			(const unsigned short *)value);
	}
	UnicodeString(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other);
	}
	~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

private:
	unsigned short *m_text;
};

bool GetStringFromRegistry(UnicodeString path, UnicodeString key, UnicodeString &val);

UnicodeString GetRegistryUserDataLeafNameUnicode(void)
{
	UnicodeString val;
	GetStringFromRegistry(L"", L"UserDataLeafName", val);
	return val;
}
