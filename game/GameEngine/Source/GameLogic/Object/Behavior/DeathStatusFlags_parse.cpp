// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

typedef bool Bool;

class AsciiString;

#include "string_base.h"

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Rva00204770BitFlagsParser
{
public:
	Bool parseToken(const char *token, Bool *foundNormal, Bool *foundAddOrSub);
};

class DeathStatusFlags
{
public:
	void parse(AsciiString description);

private:
	unsigned int m_words[3];
};

// ?parse@DeathStatusFlags@@QAEXVAsciiString@@@Z
void DeathStatusFlags::parse(AsciiString description)
{
	Bool foundNormal = false;
	Bool foundAddOrSub = false;
	AsciiString token;

	while (description.StringBase<char>::nextToken(&token, 0))
	{
		if (!reinterpret_cast<Rva00204770BitFlagsParser *>(this)->parseToken(
			token.str(), &foundNormal, &foundAddOrSub))
			break;
	}
}
