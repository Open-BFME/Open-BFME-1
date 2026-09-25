// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/AI/AIPlayerComputeCenterAndRadiusOfBase.cpp
// ?computeCenterAndRadiusOfBase@AIPlayer@@IAEXPAUCoord3D@@PAM@Z
// cl: /O2 /DNDEBUG /MD /EHsc

typedef int Int;
typedef float Real;

#include <math.h>

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct SinglePosition
{
	Real x;
};

struct BfmeAsciiStringData
{
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

class AsciiString
{
public:
	~AsciiString();
	bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}

private:
	BfmeAsciiStringData *m_data;
};

class BuildListInfo
{
public:
	virtual ~BuildListInfo();
	AsciiString getTemplateName() const;
	const Coord3D *getLocation() const { return &m_location; }
	// The link at +0x2c is read through the offset: the layout witness for this
	// class names +0x28 and +0x2c both m_numRebuilds and omits the list link.
	BuildListInfo *getNext() const
	{
		return *(BuildListInfo *const *)((const char *)this + 0x2c);
	}

private:
	unsigned char m_buildingName[4];
	unsigned char m_templateName[4];
	Coord3D m_location;
	unsigned char m_gap18[0x18];
};

class Player
{
public:
	BuildListInfo *getBuildList() const { return m_buildList; }

private:
	unsigned char m_gap00[0x1c0];
	BuildListInfo *m_buildList;
};

class ThingTemplate
{
public:
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }

private:
	unsigned char m_gap00[0x70];
	Real m_boundingCircleRadius;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern BfmeThingFactory *TheThingFactory;

class AIPlayer
{
protected:
	void computeCenterAndRadiusOfBase(Coord3D *baseCenter, Real *baseRadius);

private:
	unsigned char m_gap00[0x0c];
	Player *m_player;
	unsigned char m_gap10[0x30];
	bool m_baseCenterSet;
};

void AIPlayer::computeCenterAndRadiusOfBase(Coord3D *baseCenter, Real *baseRadius)
{
	BuildListInfo *buildListInfo;
	Coord2D totalBuildingPosition;
	totalBuildingPosition.x = 0.0f;
	totalBuildingPosition.y = 0.0f;
	Int buildingCount = 0;

	for (buildListInfo = m_player->getBuildList(); buildListInfo;
		buildListInfo = buildListInfo->getNext())
	{
		AsciiString templateName = buildListInfo->getTemplateName();
		if (templateName.isEmpty())
			continue;
		const ThingTemplate *buildingTemplate = TheThingFactory->findTemplate(templateName);
		if (!buildingTemplate)
			continue;
		Real buildingY = buildListInfo->getLocation()->y;
		SinglePosition buildingX;
		buildingX.x = buildListInfo->getLocation()->x;
		totalBuildingPosition.x += buildingX.x;
		totalBuildingPosition.y += buildingY;
		++buildingCount;
	}

	if (buildingCount > 0)
	{
		totalBuildingPosition.x /= buildingCount;
		totalBuildingPosition.y /= buildingCount;
	}

	m_baseCenterSet = buildingCount > 0;
	baseCenter->x = totalBuildingPosition.x;
	baseCenter->y = totalBuildingPosition.y;

	Real maxRadiusSquared = 0.0f;
	for (buildListInfo = m_player->getBuildList(); buildListInfo;
		buildListInfo = buildListInfo->getNext())
	{
		AsciiString templateName = buildListInfo->getTemplateName();
		if (templateName.isEmpty())
			continue;
		const ThingTemplate *buildingTemplate = TheThingFactory->findTemplate(templateName);
		if (!buildingTemplate)
			continue;
		Coord3D buildingPosition;
		buildingPosition.x = buildListInfo->getLocation()->x;
		buildingPosition.y = buildListInfo->getLocation()->y;
		Real radiusDeltaX = buildingPosition.x - baseCenter->x;
		Real radiusDeltaY = buildingPosition.y - baseCenter->y;
		if (radiusDeltaX < 0.0f)
			radiusDeltaX = -radiusDeltaX;
		if (radiusDeltaY < 0.0f)
			radiusDeltaY = -radiusDeltaY;
		Real buildingRadius = buildingTemplate->getBoundingCircleRadius() * 0.4f;
		radiusDeltaX += buildingRadius;
		radiusDeltaY += buildingRadius;
		Real radiusSquared = radiusDeltaX * radiusDeltaX + radiusDeltaY * radiusDeltaY;
		if (radiusSquared > maxRadiusSquared)
			maxRadiusSquared = radiusSquared;
	}
	*baseRadius = (Real)sqrt(maxRadiusSquared);
}
