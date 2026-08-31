// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

typedef float Real;

class ThingTemplate
{
public:
	unsigned char m_beforeKindFlags[0xC8];
	unsigned char m_otherKindFlags : 7;
	unsigned char m_isBuilding : 1;
};

class Handicap
{
public:
	enum HandicapType
	{
		BUILDCOST,
		BUILDTIME
	};

	Real getHandicap(HandicapType type, const ThingTemplate *thingTemplate) const;

private:
	enum ThingType
	{
		GENERIC,
		BUILDINGS
	};

	Real m_handicaps[2][2];
};

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
