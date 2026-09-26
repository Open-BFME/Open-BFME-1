// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/stringbaseunicode

// The exact 181-byte shape is preserved while adopting the covered WWLib
// AsciiString type and the existing StringBase-backed UnicodeString shim.
// MSVC 7.1 uses a non-native wchar_t in this build; the shim's wchar_t is the
// same unsigned-short StringBase specialization as retail's @G ABI.
typedef unsigned short wchar_t;
#include "ascii_string.h"
#include "Common/UnicodeString.h"

struct PreferenceNode
{
	char m_pad[0x14];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const throw();
	PreferenceNode *end() const { return m_end; }

private:
	PreferenceNode *m_end;
};

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
};

class Rva00086750Owner : public UserPreferences
{
public:
	UnicodeString getStartingSuppliesText(void);
};

UnicodeString Rva00086750Owner::getStartingSuppliesText(void)
{
	UnicodeString ret;
	PreferenceNode *it = find("StartingSupplies");

	if (it == end())
		return UnicodeString::TheEmptyString;

	ret.translate(it->m_value);
	return ret;
}
