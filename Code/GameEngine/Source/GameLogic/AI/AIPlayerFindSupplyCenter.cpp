// cl: /DNDEBUG /MD /EHsc
// ?findSupplyCenter@AIPlayer@@IAEPAVObject@@H@Z
// readable ZH body: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::findSupplyCenter for retail 0x00164C10 (886 B, ret 4 at +0x373,
// int3 pad after). Identity: reloc name, two callers (guardSupplyCenter and
// the isSupplySourceSafe ILT 0x0001E0FB) and the SupplyWarehouseDockUpdate
// module key. Layout from matched siblings: m_player +0x0C, m_baseCenter
// +0x34, Object position +0x38, next +0x88, radius +0xBC, team +0x23C;
// getAiEnemy is vtable slot 0x30.
//
// Shape notes, each measured against the retail bytes: the KindOf mask is
// built with a memset and one bit set (bitset style), the three partition
// filters are declared OnMap, Player, KindOf and live in their own block so
// their destructors run before the supplyCenter test, PartitionFilter's
// base ctor clears m_next, the center is copied member by member, and
// Coord3D::zero/set store in field order. PartitionFilter::link is still the
// dump ?d_009f2ae0@@YAXXZ and is called through a typed cast of it.

extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)
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

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	void set(Real ax, Real ay, Real az)
	{
		x = ax;
		y = ay;
		z = az;
	}
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
	class SupplyWarehouseDockUpdate *findUpdateModule(Int key);
	const ThingTemplate *resolveTemplate() const
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
	Bool isKindOfStructure() const
	{
		return (resolveTemplate()->m_kind0 & 0x80) != 0;
	}
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
	enum BogusInitType
	{
		kInit = 0
	};

	unsigned int bits[6];

	KindOfMaskType()
	{
		bits[0] = 0;
		bits[1] = 0;
		bits[2] = 0;
		bits[3] = 0;
		bits[4] = 0;
		bits[5] = 0;
	}

	KindOfMaskType(BogusInitType, Int bit)
	{
		memset(bits, 0, sizeof(bits));
		bits[bit >> 5] |= (1U << (bit & 31));
	}
};

extern const KindOfMaskType KINDOFMASK_NONE;

extern void d_009f2ae0();

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	PartitionFilter *link(PartitionFilter *next)
	{
		// Retail's PartitionFilter::link is still the dump ?d_009f2ae0@@YAXXZ.
		typedef PartitionFilter *(PartitionFilter::*LinkFunc)(PartitionFilter *);
		union { void (*raw)(); LinkFunc member; } call;
		call.raw = d_009f2ae0;
		return (this->*call.member)(next);
	}
	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear)
	{
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
	}

	Player *m_player;
	Bool m_match;
};

class PartitionFilterOnMap : public PartitionFilter
{
public:
	PartitionFilterOnMap()
	{
	}
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *searchPosition, Real radius, Int from,
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
	// The virtual table pointer occupies the first four bytes; retail m_player is +0x0C.
	unsigned char m_pad00[0x08];
	Player *m_player;
	unsigned char m_pad10[0x34 - 0x10];
	Coord3D m_baseCenter;
};
#undef BFME_VIRTUAL_SLOT

Object *AIPlayer::findSupplyCenter(Int minimumCash)
{
	Object *bestSupplyWarehouse = 0;
	Real bestDistSqr = 0;
	Object *obj;
	Coord3D enemyCenter;
	enemyCenter.zero();
	Region2D bounds;
	Player *enemy = getAiEnemy();
	if (enemy) {
		getPlayerStructureBounds(&bounds, enemy->getPlayerIndex());
		enemyCenter.set((bounds.lo.x + bounds.hi.x) * 0.5f, (bounds.lo.y + bounds.hi.y) * 0.5f, 0);
	}

	do {
		for (obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject())
		{
			if (!obj->isKindOfStructure()) continue;
			if (!(obj->resolveTemplate()->m_kindD0 & 0x200000u)) continue;
			static const NameKeyType key_warehouseUpdate =
				TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
			SupplyWarehouseDockUpdate *warehouseModule = obj->findUpdateModule(key_warehouseUpdate);
			if (warehouseModule) {
				Int availableCash = warehouseModule->getBoxesStored() * TheWritableGlobalData->m_baseValuePerSupplyBox;
				if (availableCash < minimumCash) continue;
				if (m_player->getRelationship(obj->getTeam()) == ENEMIES) {
					continue;
				}

				Coord3D center;
				center.x = obj->getPosition()->x;
				center.y = obj->getPosition()->y;
				center.z = obj->getPosition()->z;
				Real radius = 200.0f + obj->getBoundingCircleRadius();

				Object *supplyCenter;
				{
					PartitionFilterOnMap filterMapStatus;
					PartitionFilterPlayer f2(m_player, true);
					PartitionFilterAcceptByKindOf f1(
						KindOfMaskType(KindOfMaskType::kInit, 34), KINDOFMASK_NONE);

					PartitionFilter *filters = f1.link(f2.link(&filterMapStatus));

					supplyCenter = ThePartitionManager->getClosestObject(&center, radius, 1, filters);
				}
				if (supplyCenter) {
					continue;
				}

				Real dx, dy;
				dx = obj->getPosition()->x - m_baseCenter.x;
				dy = obj->getPosition()->y - m_baseCenter.y;
				Real distSqr = dx * dx + dy * dy;
				if (enemy) {
					dx = obj->getPosition()->x - enemyCenter.x;
					dy = obj->getPosition()->y - enemyCenter.y;
					if (distSqr * 0.4 > (dx * dx + dy * dy) * 0.6f) {
						continue;
					}
				}

				if (bestSupplyWarehouse == 0) {
					bestSupplyWarehouse = obj;
					bestDistSqr = distSqr;
				} else if (bestDistSqr > distSqr) {
					bestSupplyWarehouse = obj;
					bestDistSqr = distSqr;
				}
			}
		}
		if (bestSupplyWarehouse) break;
		minimumCash /= 2;
	} while (minimumCash > 100);

	return bestSupplyWarehouse;
}
