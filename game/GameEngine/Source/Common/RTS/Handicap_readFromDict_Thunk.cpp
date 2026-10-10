// cl: /DNDEBUG /MD /EHsc

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

typedef float Real;
typedef bool Bool;

enum NameKeyType {};

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

template<> inline void StringBase<char>::set(const char *str) { set(str, str ? strlen(str) : 0); }
template<> inline void StringBase<char>::concat(const char *str) { concat(str, str ? strlen(str) : 0); }

class Dict
{
public:
	Real getReal(NameKeyType key, Bool *exists) const;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Handicap
{
public:
	enum HandicapType
	{
		BUILDCOST,
		BUILDTIME,
		HANDICAP_TYPE_COUNT
	};

	void readFromDict(const Dict *d);

private:
	Real m_handicaps[2][2];
};

// ?readFromDict@Handicap@@QAEXPBVDict@@@Z
void Handicap::readFromDict(const Dict *d)
{
	const char *htNames[HANDICAP_TYPE_COUNT] =
	{
		"BUILDCOST",
		"BUILDTIME",
	};

	const char *ttNames[2] =
	{
		"GENERIC",
		"BUILDINGS",
	};

	AsciiString c;
	for (int i = 0; i < HANDICAP_TYPE_COUNT; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			c.StringBase<char>::clear();
			c.StringBase<char>::set("HANDICAP_");
			c.StringBase<char>::concat(htNames[i]);
			c.StringBase<char>::concat("_");
			c.StringBase<char>::concat(ttNames[j]);
			NameKeyType k = TheNameKeyGenerator->nameToKey(c.str());
			Bool exists;
			Real r = d->getReal(k, &exists);
			if (exists)
				m_handicaps[i][j] = r;
		}
	}
}
