// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
// Retail 0x001695B0, 828 bytes. The owner remains address-derived until a
// caller, vtable slot, or literal proves the semantic AISkirmishPlayer name.

#include "StringInline.h"
#include <math.h>

#define PI 3.14159265358979323846f

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
	Real x;
	Real y;
	Real z;
};

struct Coord2D
{
	Real x;
	Real y;
};

struct Region3D
{
	Coord3D lo;
	Coord3D hi;

	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }
};

class Object;

class Player
{
public:
	void onStructureUndone(Object *object);
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(Int kind) const
	{
		return (m_kindof[(UnsignedInt)kind >> 5]
			& (1 << (kind & 31))) != 0;
	}

private:
	unsigned char m_unmodelled008[0xC8 - 0x08];
	UnsignedInt m_kindof[3];
};

class Object
{
public:
	Player *getControllingPlayer() const;

	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}

	Bool isCommandCenter() const
	{
		return getTemplate()->isKindOf(17);
	}

	const Coord3D *getPosition() const { return &m_position; }
	Object *getNextObject() const { return m_next; }

private:
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_unmodelled008[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_unmodelled044[0x88 - 0x44];
	Object *m_next;
};

class BuildListInfo
{
public:
	virtual ~BuildListInfo();
	AsciiString getTemplateName() const;
	BuildListInfo *getNext() const { return m_next; }
	const Coord3D *getLocation() const { return &m_location; }
	void setInitiallyBuilt(Bool built) { m_isInitiallyBuilt = built; }
	void setLocation(Coord3D location) { m_location = location; }
	Real getAngle() const { return m_angle; }
	void setAngle(Real angle) { m_angle = angle; }

private:
	AsciiString m_buildingName;
	AsciiString m_templateName;
	Coord3D m_location;
	Coord2D m_rallyPointOffset;
	Real m_angle;
	Bool m_isInitiallyBuilt;
	UnsignedInt m_numRebuilds;
	BuildListInfo *m_next;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *object);
};

class GameLogic
{
public:
	Object *getFirstObject();
	void destroyObject(Object *object);
};

class TAiData
{
public:
	unsigned char m_unmodelled00[0x66];
	Bool m_rotateSkirmishBases;
};

class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }
	TAiData *getAiData() const { return m_aiData; }

private:
	unsigned char m_unmodelled00[0x0C];
	Pathfinder *m_pathfinder;
	unsigned char m_unmodelled10[4];
	TAiData *m_aiData;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void getMaximumPathfindExtent(Region3D *extent) const;
};

class Rva001695B0
{
public:
	void adjustBuildList(BuildListInfo *list);

private:
	unsigned char m_unmodelled00[0x0C];
	Player *m_player;
};

extern GameLogic *TheGameLogic;
extern AI *TheAI;
extern BfmeThingFactory *TheThingFactory;
extern TerrainLogic *TheTerrainLogic;
extern void j_0002717e();

static void bfmeOnStructureUndone(Player *player, Object *object)
{
	typedef void (Player::*Call)(Object *);
	union
	{
		void (*raw)();
		Call member;
	} call;
	call.raw = j_0002717e;
	(player->*call.member)(object);
}

void Rva001695B0::adjustBuildList(BuildListInfo *list)
{
	Bool foundStart = false;
	Coord3D startPos;

	Object *obj;
	for (obj = TheGameLogic->getFirstObject(); obj;
		obj = obj->getNextObject())
	{
		Player *owner = obj->getControllingPlayer();
		if (owner == m_player)
		{
			if (obj->isCommandCenter())
			{
				foundStart = true;
				startPos = *obj->getPosition();
				bfmeOnStructureUndone(m_player, obj);
				TheAI->pathfinder()->removeObjectFromPathfindMap(obj);
				TheGameLogic->destroyObject(obj);
				break;
			}
		}
	}
	if (!foundStart)
		return;

	Bool foundInBuildList = false;
	Coord3D buildPos;
	BuildListInfo *cur = list;
	while (cur)
	{
		const ThingTemplate *tTemplate =
			TheThingFactory->findTemplate(cur->getTemplateName());
		if (tTemplate && tTemplate->isKindOf(17))
		{
			foundInBuildList = true;
			buildPos = *cur->getLocation();
			cur->setInitiallyBuilt(true);
		}
		cur = cur->getNext();
	}

	Region3D bounds;
	TheTerrainLogic->getMaximumPathfindExtent(&bounds);

	Int gridIndex = 0;
	if (startPos.x > bounds.lo.x + bounds.width() / 3)
		gridIndex++;
	if (startPos.x > bounds.lo.x + 2 * bounds.width() / 3)
		gridIndex++;
	if (startPos.y > bounds.lo.y + bounds.height() / 3)
		gridIndex += 3;
	if (startPos.y > bounds.lo.y + 2 * bounds.height() / 3)
		gridIndex += 3;

	Real angle = 0;
	if (TheAI->getAiData()->m_rotateSkirmishBases)
	{
		switch (gridIndex)
		{
		case 0: angle = 0; break;
		case 1: angle = PI / 4; break;
		case 2: angle = PI / 2; break;
		case 3: angle = -PI / 4; break;
		case 4: angle = 0; break;
		case 5: angle = 3 * PI / 4; break;
		case 6: angle = -PI / 2; break;
		case 7: angle = -3 * PI / 4; break;
		case 8: angle = PI; break;
		}
	}

	angle += 3 * PI / 4;
	Real s = sin(angle);
	Real c = cos(angle);

	cur = list;
	while (cur)
	{
		const ThingTemplate *tTemplate =
			TheThingFactory->findTemplate(list->getTemplateName());
		if (tTemplate && tTemplate->isKindOf(17))
		{
			foundInBuildList = true;
			Coord3D curPos = *cur->getLocation();
			curPos.x -= buildPos.x;
			curPos.y -= buildPos.y;
			Real newX = curPos.x * c - curPos.y * s;
			Real newY = curPos.y * c + curPos.x * s;
			curPos.x = newX + startPos.x;
			curPos.y = newY + startPos.y;
			cur->setLocation(curPos);
		}
		cur = cur->getNext();
	}
}
