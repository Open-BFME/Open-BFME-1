// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "string_base.h"

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

#include "../../../Include/Common/NameKeyType.h"





class NameKeyGenerator
{
public:
	AsciiString keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Include/Common/Enums/ScienceType.h"




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
