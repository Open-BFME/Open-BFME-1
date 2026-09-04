// ?findSupplyCenter@AIPlayer@@IAEPAVObject@@H@Z
// partial score=0.82 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// AIPlayer::findSupplyCenter — retail 0x00164C10 / 883B.
// Reloc-named identity=real (call-sites=2); ILT 0x0001E0FB from
// isSupplySourceSafe; string-anchored on "SupplyWarehouseDockUpdate".
// ZH twin: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
// Layout from matched siblings: m_player@+0x0C (checkForSupplyCenter),
// m_baseCenter@+0x34 (this body), Object pos@+0x38 / next@+0x88 /
// radius@+0xBC / team@+0x23C (guardSupplyCenter). getAiEnemy is vslot 0x30.

typedef bool Bool;
typedef int Int;
typedef float Real;

enum Relationship
{
	ENEMIES = 0
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

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

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

class Team;
class Player;
class Object;
class PartitionFilter;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vtable;
	const Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_kindPad[0xC8 - 8];
	unsigned char m_kind0;
	unsigned char m_kind1[0xD0 - 0xC9];
	unsigned int m_kindD0;
};

class Object
{
public:
	class SupplyWarehouseDockUpdate *findUpdateModule(NameKeyType key);
	const ThingTemplate *resolveTemplate() const;
	Bool isKindOfStructure() const;
	Bool isKindOfSupplySource() const;
	const Coord3D *getPosition() const { return &m_position; }
	Object *getNextObject() const { return m_next; }
	Team *getTeam() const { return m_team; }
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }

private:
	void *m_vptr;
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x38 - 8];
	Coord3D m_position;
	unsigned char m_pad44[0x88 - 0x44];
	Object *m_next;
	unsigned char m_pad8C[0xBC - 0x8C];
	Real m_boundingCircleRadius;
	unsigned char m_padC0[0x23C - 0xC0];
	Team *m_team;
};

class SupplyWarehouseDockUpdate
{
public:
	Int getBoxesStored() const { return m_boxesStored; }

private:
	unsigned char m_pad[0x88];
	Int m_boxesStored;
};

class Player
{
public:
	Relationship getRelationship(const Team *team) const;
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_pad[0x24];
	Int m_playerIndex;
};

class GameLogic
{
public:
	Object *getFirstObject();
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GlobalData
{
public:
	unsigned char m_pad[0xB24];
	Int m_baseValuePerSupplyBox;
};

struct KindOfMaskType
{
	unsigned int bits[6];
};

extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
public:
	virtual ~PartitionFilter() {}
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(unsigned cashGeneratorBit)
	{
		m_next = 0;
		m_mustBeSet.bits[0] = 0;
		m_mustBeSet.bits[1] = cashGeneratorBit;
		m_mustBeSet.bits[2] = 0;
		m_mustBeSet.bits[3] = 0;
		m_mustBeSet.bits[4] = 0;
		m_mustBeSet.bits[5] = 0;
		m_mustBeClear = KINDOFMASK_NONE;
	}

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

class PartitionFilterPlayer : public PartitionFilter
{
public:
	PartitionFilterPlayer(Player *player, Bool match)
		: m_player(player), m_match(match)
	{
		m_next = 0;
	}

	Player *m_player;
	Bool m_match;
};

class PartitionFilterOnMap : public PartitionFilter
{
public:
	PartitionFilterOnMap()
	{
		m_next = 0;
		m_pad0 = 0;
		m_pad1 = 0;
	}

	int m_pad0;
	int m_pad1;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, Real radius, Int from,
		PartitionFilter *filters);
};

extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GlobalData *TheWritableGlobalData;
extern PartitionManager *ThePartitionManager;

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n()
class AIPlayer
{
public:
	BFME_VIRTUAL_SLOT(00);
	BFME_VIRTUAL_SLOT(04);
	BFME_VIRTUAL_SLOT(08);
	BFME_VIRTUAL_SLOT(0C);
	BFME_VIRTUAL_SLOT(10);
	BFME_VIRTUAL_SLOT(14);
	BFME_VIRTUAL_SLOT(18);
	BFME_VIRTUAL_SLOT(1C);
	BFME_VIRTUAL_SLOT(20);
	BFME_VIRTUAL_SLOT(24);
	BFME_VIRTUAL_SLOT(28);
	BFME_VIRTUAL_SLOT(2C);
	virtual Player *getAiEnemy();
	static void getPlayerStructureBounds(Region2D *bounds, Int playerIndex);

protected:
	Object *findSupplyCenter(Int minimumCash);

private:
	unsigned char m_pad00[0x0C];
	Player *m_player;
	unsigned char m_pad10[0x34 - 0x10];
	Coord3D m_baseCenter;
};
#undef BFME_VIRTUAL_SLOT

const ThingTemplate *Object::resolveTemplate() const
{
	const ThingTemplate *d = m_template;
	const ThingTemplate *f;
	if (d == 0)
		f = d;
	else
		f = (const ThingTemplate *)(d->m_nextOverride
			? d->m_nextOverride->getFinalOverride()
			: d);
	return f;
}

Bool Object::isKindOfStructure() const
{
	return (resolveTemplate()->m_kind0 & 0x80) != 0;
}

Bool Object::isKindOfSupplySource() const
{
	return (resolveTemplate()->m_kindD0 & 0x200000u) != 0;
}

Object *AIPlayer::findSupplyCenter(Int minimumCash)
{
	AIPlayer *self = this;
	void *vptr = *(void **)self;
	int z = 0;
	Object *bestSupplyWarehouse = 0;
	Real bestDistSqr = 0;
	Real enemyX = 0;
	Real enemyY = 0;
	Player *enemy = self->getAiEnemy();
	(void)vptr;
	if (enemy != (Player *)z)
	{
		Region2D bounds;
		getPlayerStructureBounds(&bounds, enemy->getPlayerIndex());
		enemyY = (bounds.lo.y + bounds.hi.y) * 0.5f;
		enemyX = (bounds.lo.x + bounds.hi.x) * 0.5f;
	}

	do
	{
		for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject())
		{
			if (!obj->isKindOfStructure())
				continue;
			if (!obj->isKindOfSupplySource())
				continue;

			static const NameKeyType key_warehouseUpdate =
				TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
			SupplyWarehouseDockUpdate *warehouseModule = obj->findUpdateModule(key_warehouseUpdate);
			if (warehouseModule == (SupplyWarehouseDockUpdate *)z)
				continue;

			Int availableCash = warehouseModule->getBoxesStored() *
				TheWritableGlobalData->m_baseValuePerSupplyBox;
			if (availableCash < minimumCash)
				continue;
			if (self->m_player->getRelationship(obj->getTeam()) == ENEMIES)
				continue;

			const Coord3D *pos = obj->getPosition();
			Coord3D center;
			center.x = pos->x;
			center.y = pos->y;
			center.z = pos->z;
			Real radius = 200.0f + obj->getBoundingCircleRadius();

			PartitionFilterAcceptByKindOf f1(4);
			PartitionFilterPlayer f2(self->m_player, true);
			PartitionFilterOnMap filterMapStatus;
			PartitionFilter *filters = filterMapStatus.link(f2.link(&f1));
			Object *supplyCenter = ThePartitionManager->getClosestObject(&center, radius, 1, filters);
			if (supplyCenter != (Object *)z)
				continue;

			Real dx = obj->getPosition()->x - self->m_baseCenter.x;
			Real dy = obj->getPosition()->y - self->m_baseCenter.y;
			Real distSqr = dx * dx + dy * dy;
			if (enemy != (Player *)z)
			{
				dx = obj->getPosition()->x - enemyX;
				dy = obj->getPosition()->y - enemyY;
				if (distSqr * 0.4 > (dx * dx + dy * dy) * 0.6f)
					continue;
			}

			if (bestSupplyWarehouse == (Object *)z)
			{
				bestSupplyWarehouse = obj;
				bestDistSqr = distSqr;
			}
			else if (bestDistSqr > distSqr)
			{
				bestSupplyWarehouse = obj;
				bestDistSqr = distSqr;
			}
		}
		if (bestSupplyWarehouse != (Object *)z)
			break;
		minimumCash /= 2;
	} while (minimumCash > 100);

	return bestSupplyWarehouse;
}
