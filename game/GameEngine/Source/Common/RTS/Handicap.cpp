// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	unsigned char m_beforeKindFlags[0xC8];
	unsigned char m_otherKindFlags : 7;
	unsigned char m_isBuilding : 1;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Handicap.h
class Handicap
{
public:
	enum HandicapType
	{
		BUILDCOST,
		BUILDTIME
	};

	Handicap();
	Real getHandicap(HandicapType type, const ThingTemplate *thingTemplate) const;

private:
	enum ThingType
	{
		GENERIC,
		BUILDINGS
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
