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
	void computeCenterAndRadiusOfBase(Coord3D *center, Real *radius);

private:
	unsigned char m_gap00[0x0c];
	Player *m_player;
	unsigned char m_gap10[0x30];
	bool m_baseCenterSet;
};

void AIPlayer::computeCenterAndRadiusOfBase(Coord3D *center, Real *radius)
{
	BuildListInfo *info;
	Coord2D totalPos;
	totalPos.x = 0.0f;
	totalPos.y = 0.0f;
	Int numBldg = 0;

	for (info = m_player->getBuildList(); info; info = info->getNext())
	{
		AsciiString name = info->getTemplateName();
		if (name.isEmpty())
			continue;
		const ThingTemplate *bldgPlan = TheThingFactory->findTemplate(name);
		if (!bldgPlan)
			continue;
		Real posY = info->getLocation()->y;
		SinglePosition posX;
		posX.x = info->getLocation()->x;
		totalPos.x += posX.x;
		totalPos.y += posY;
		++numBldg;
	}

	if (numBldg > 0)
	{
		totalPos.x /= numBldg;
		totalPos.y /= numBldg;
	}

	m_baseCenterSet = numBldg > 0;
	center->x = totalPos.x;
	center->y = totalPos.y;

	Real maxRadSqr = 0.0f;
	for (info = m_player->getBuildList(); info; info = info->getNext())
	{
		AsciiString name = info->getTemplateName();
		if (name.isEmpty())
			continue;
		const ThingTemplate *bldgPlan = TheThingFactory->findTemplate(name);
		if (!bldgPlan)
			continue;
		Coord3D pos;
		pos.x = info->getLocation()->x;
		pos.y = info->getLocation()->y;
		Real dx = pos.x - center->x;
		Real dy = pos.y - center->y;
		if (dx < 0.0f)
			dx = -dx;
		if (dy < 0.0f)
			dy = -dy;
		Real bldgRadius = bldgPlan->getBoundingCircleRadius() * 0.4f;
		dx += bldgRadius;
		dy += bldgRadius;
		Real radSqr = dx * dx + dy * dy;
		if (radSqr > maxRadSqr)
			maxRadSqr = radSqr;
	}
	*radius = (Real)sqrt(maxRadSqr);
}


