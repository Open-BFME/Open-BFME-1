// ?doNugget@SpawnAndFadeNugget@@UBEXPBVDamageInfo@@PBUCoord3D@@@Z
// partial score=0.93 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc
// SpawnAndFadeNugget::doNugget, retail 0x002DE9B0.
// Parser 0x001E6170, constructor 0x002DE930 (Made001E6170, size 0x6c).

extern "C" double sin(double);
extern "C" double cos(double);
#pragma intrinsic(sin)
#pragma intrinsic(cos)

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AsciiString
{
	void *m_data;
};

class ThingTemplate
{
};

class Team
{
};

class ObjectStatusMaskType
{
public:
	ObjectStatusMaskType()
	{
		m_bits[0] = 0;
		m_bits[1] = 0;
		m_bits[2] = 0;
	}

	UnsignedInt m_bits[3];
};

class Object
{
public:
	Int getLayer() const;
	void setPosition(const Coord3D *position);
	void setOrientation(Real angle);
	void kill(Int damageType, Int deathType);

	char m_pad00[0x38];
	Coord3D m_position;
	Real m_orientation;
	char m_pad48[0x23c - 0x48];
	Team *m_team;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheBfmeGameLogic;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

typedef Object *(__fastcall *ThingFactoryNewObjectCall)(
	ThingFactory *, ObjectStatusMaskType *, ThingTemplate *, Team *,
	const volatile ObjectStatusMaskType &, void *);

extern void j_0004494a();

class TerrainLogic
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual Real getLayerHeight(Real x, Real y, Int layer, void *normal,
		int clip) = 0;
};

extern TerrainLogic *TheTerrainLogic;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	char m_pad00[4];
	Overridable *m_nextOverride;
};

class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
};

class AI
{
public:
	char m_pad00[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

class DamageInfo
{
public:
	char m_pad00[8];
	Int m_sourceID;
};

class SpawnAndFadeNugget
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void doNugget(const DamageInfo *damageInfo,
		const Coord3D *position) const;

	char m_pad04[0x58 - 4];
	char m_objectTargetFilter[4];
	AsciiString m_spawnedObjectName;
	Coord3D m_spawnOffset;
};

void SpawnAndFadeNugget::doNugget(const DamageInfo *damageInfo,
	const Coord3D *) const
{
	Object *source;
	Object *spawned;
	const ThingTemplate *thingTemplate;
	float extra[3];

	source = TheBfmeGameLogic->findObjectByID(damageInfo->m_sourceID);
	thingTemplate = TheThingFactory->findTemplate(m_spawnedObjectName);
	if (!thingTemplate)
		return;

	ObjectStatusMaskType statusMask;
	spawned = ((ThingFactoryNewObjectCall)j_0004494a)(
		TheThingFactory, &statusMask, (ThingTemplate *)thingTemplate,
		source->m_team, statusMask, 0);

	Coord3D position;
	position.x = source->m_position.x;
	position.y = source->m_position.y;
	position.z = source->m_position.z;
	extra[0] = source->m_orientation;
	extra[1] = (Real)sin(extra[0]);
	extra[2] = (Real)cos(extra[0]);
	position.x += m_spawnOffset.x * extra[2] - m_spawnOffset.y * extra[1];
	position.y += m_spawnOffset.x * extra[1] + m_spawnOffset.y * extra[2];
	position.z = TheTerrainLogic->getLayerHeight(
		position.x, position.y, source->getLayer(), 0, 1);

	spawned->setPosition(&position);
	spawned->setOrientation(extra[0]);
	source->kill(8, 22);

	Overridable *link = *(Overridable **)((char *)spawned + 4);
	if (link && link->m_nextOverride)
	{
		const Overridable *result = link->m_nextOverride->getFinalOverride();
		if (*(UnsignedInt *)((char *)result + 0xdc) & 0x400)
			TheAI->m_pathfinder->addObjectToPathfindMap(spawned);
	}
}
