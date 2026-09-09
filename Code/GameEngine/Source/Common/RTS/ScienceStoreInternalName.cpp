// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
    static const AsciiString TheEmptyString;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	AsciiString keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class ScienceStore
{
public:
	AsciiString getInternalNameForScience(ScienceType science) const;
};

AsciiString ScienceStore::getInternalNameForScience(ScienceType science) const
{
	if (science == SCIENCE_INVALID)
		return AsciiString::TheEmptyString;
	return TheNameKeyGenerator->keyToName((NameKeyType)science);
}
