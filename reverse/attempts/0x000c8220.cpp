// ?readFromDict@Handicap@@QAEXPBVDict@@@Z
// partial score=0.8 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

#pragma intrinsic(strlen)
#include <string.h>
// Handicap, both of it:
//
//   0x000C8200  Handicap::Handicap    21 bytes  fill the table with 1.0f
//   0x000C8410  Handicap::getHandicap 27 bytes  index the table
//
// One 2x2 table of Reals written twice, once by the constructor that fills it
// and once by the accessor that reads it. The constructor's file declared the
// array and nothing else, so the two axes were anonymous; the accessor's file
// declared HandicapType and ThingType but only as far as reading them. Stated
// together, the loop bounds in the constructor are the two enums.

typedef float Real;

typedef bool Bool;

enum NameKeyType {};

class Handicap;

template <typename T> class StringBase;
template <> class StringBase<char>
{
	friend class Handicap;

public:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	void set(const char *text, int length);
	void concat(const char *text, int length);
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : "";
	}

private:
	StringBase() {}
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

public:
	Header *m_data;
};

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	unsigned char m_beforeKindFlags[0xC8];
	unsigned char m_otherKindFlags : 7;
	unsigned char m_isBuilding : 1;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Handicap.h
class Handicap
{
public:
	enum HandicapType
	{
		BUILDCOST,
		BUILDTIME,
		HANDICAP_TYPE_COUNT
	};

	Handicap();
	void readFromDict(const Dict *d);
	Real getHandicap(HandicapType type, const ThingTemplate *thingTemplate) const;

	private:
	enum ThingType
	{
		GENERIC,
		BUILDINGS,
		THING_TYPE_COUNT
	};

	Real m_handicaps[2][2];
};

// ??0Handicap@@QAE@XZ
Handicap::Handicap()
{
	for (int handicap = 0; handicap < 2; ++handicap)
	{
		for (int thing = 0; thing < 2; ++thing)
		{
			m_handicaps[handicap][thing] = 1.0f;
		}
	}
}

// ?getHandicap@Handicap@@QBEMW4HandicapType@1@PBVThingTemplate@@@Z
Real Handicap::getHandicap(HandicapType type, const ThingTemplate *thingTemplate) const
{
	ThingType thingType;
	if (thingTemplate->m_isBuilding)
	{
		thingType = BUILDINGS;
	}
	else
	{
		thingType = GENERIC;
	}
	return m_handicaps[type][thingType];
}

// ?readFromDict@Handicap@@QAEXPBVDict@@@Z
// Identity is fixed by Player::load's named caller, the HANDICAP_ literal
// xref, and the reference Handicap::readFromDict loop.  The explicit
// StringBase<char> view is intentional: retail uses the one-pointer BFME
// string layout, including the eight-byte header before its text.
void Handicap::readFromDict(const Dict *d)
{
	const char *htNames[HANDICAP_TYPE_COUNT] =
	{
		"BUILDCOST",
		"BUILDTIME",
	};

	const char *ttNames[THING_TYPE_COUNT] =
	{
		"GENERIC",
		"BUILDINGS",
	};
	const char **ht = htNames;
	const char **tt = ttNames;

	StringBase<char> c;
	c.m_data = 0;

	for (int i = 0; i < HANDICAP_TYPE_COUNT; ++i)
	{
		for (int j = 0; j < THING_TYPE_COUNT; ++j)
		{
			c.releaseBuffer();
			c.set("HANDICAP_", 9);
			c.concat(ht[i], (int)strlen(ht[i]));
			c.concat("_", 1);
			c.concat(tt[j], (int)strlen(tt[j]));
			NameKeyType k = TheNameKeyGenerator->nameToKey(c.str());
			Bool exists;
			Real r = d->getReal(k, &exists);
			if (exists)
				m_handicaps[i][j] = r;
		}
	}
}
