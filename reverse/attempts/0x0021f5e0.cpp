// ?addValidObjectsToGarrisonPoints@GarrisonContain@@IAEXXZ
// partial score=0.9 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#include <list>
#define FALSE 0

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
enum ObjectID { INVALID_OBJECT_ID = 0 };
enum WeaponSlotType { BFME_WEAPON_SLOT_ZERO = 0 };
static const ObjectID INVALID_ID = INVALID_OBJECT_ID;
enum { GARRISON_INDEX_INVALID = -1 };

struct Coord3D { float x; float y; float z; };
class Weapon;
class Object
{
};
class AIUpdateInterface
{
};
class GarrisonContain
{
protected:
	void addValidObjectsToGarrisonPoints();
};
class BfmeAddValidObjectCall
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
};
class BfmeAddValidAIUpdateCall
{
public:
	Object *getCurrentVictim() const;
	const Coord3D *getCurrentVictimPos() const;
};
class BfmeAddValidOwnerCall
{
public:
	Int findConditionIndex();
	void putObjectAtBestGarrisonPoint(Object *, Object *, const Coord3D *);
};
#pragma comment(linker, "/alternatename:?getCurrentWeapon@BfmeAddValidObjectCall@@QAEPAVWeapon@@PAW4WeaponSlotType@@@Z=?j_00031a7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentVictim@BfmeAddValidAIUpdateCall@@QBEPAVObject@@XZ=?j_000261a2@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentVictimPos@BfmeAddValidAIUpdateCall@@QBEPBUCoord3D@@XZ=?j_00030634@@YAXXZ")
#pragma comment(linker, "/alternatename:?findConditionIndex@BfmeAddValidOwnerCall@@IAEHXZ=?j_00043405@@YAXXZ")
#pragma comment(linker, "/alternatename:?putObjectAtBestGarrisonPoint@BfmeAddValidOwnerCall@@IAEXPAVObject@@0PBUCoord3D@@@Z=?j_000492fb@@YAXXZ")

class BfmeGarrisonFirePointInterface
{
public:
#define BFME_FIRE_POINT_SLOT(N) virtual void slot##N() = 0
	BFME_FIRE_POINT_SLOT(00); BFME_FIRE_POINT_SLOT(01);
	BFME_FIRE_POINT_SLOT(02); BFME_FIRE_POINT_SLOT(03);
	BFME_FIRE_POINT_SLOT(04); BFME_FIRE_POINT_SLOT(05);
	BFME_FIRE_POINT_SLOT(06); BFME_FIRE_POINT_SLOT(07);
	BFME_FIRE_POINT_SLOT(08); BFME_FIRE_POINT_SLOT(09);
	BFME_FIRE_POINT_SLOT(10); BFME_FIRE_POINT_SLOT(11);
	BFME_FIRE_POINT_SLOT(12); BFME_FIRE_POINT_SLOT(13);
	BFME_FIRE_POINT_SLOT(14); BFME_FIRE_POINT_SLOT(15);
	BFME_FIRE_POINT_SLOT(16); BFME_FIRE_POINT_SLOT(17);
	BFME_FIRE_POINT_SLOT(18); BFME_FIRE_POINT_SLOT(19);
	BFME_FIRE_POINT_SLOT(20); BFME_FIRE_POINT_SLOT(21);
	BFME_FIRE_POINT_SLOT(22); BFME_FIRE_POINT_SLOT(23);
	BFME_FIRE_POINT_SLOT(24); BFME_FIRE_POINT_SLOT(25);
	virtual Int getObjectGarrisonPointIndex(ObjectID objectID) = 0;
#undef BFME_FIRE_POINT_SLOT
};
class BfmeGarrisonFindClosestCall
{
public:
	Int findClosestFreeGarrisonPointIndex(Int conditionIndex,
		const Coord3D *targetPos);
};
class BfmeGarrisonPlacementCall
{
public:
	void putObjectAtGarrisonPoint(Object *object, ObjectID targetID,
		Int conditionIndex, Int pointIndex);
};
#pragma comment(linker, "/alternatename:?findClosestFreeGarrisonPointIndex@BfmeGarrisonFindClosestCall@@QAEHHPBUCoord3D@@@Z=?j_0002130f@@YAXXZ")
#pragma comment(linker, "/alternatename:?putObjectAtGarrisonPoint@BfmeGarrisonPlacementCall@@QAEXPAVObject@@W4ObjectID@@HH@Z=?j_00028cea@@YAXXZ")

struct Gen_t_001cb160_p4cd
{
	Object *object;
};
class BfmeGarrisonContainedNode
{
public:
	BfmeGarrisonContainedNode *next;
	BfmeGarrisonContainedNode *previous;
	Object *object;
};
class BfmeGarrisonHordeContainInterface;
class BfmeGarrisonContainModuleInterface
{
public:
#define BFME_GARRISON_CONTAIN_SLOT(N) virtual void slot##N() = 0
	BFME_GARRISON_CONTAIN_SLOT(00); BFME_GARRISON_CONTAIN_SLOT(01);
	BFME_GARRISON_CONTAIN_SLOT(02); BFME_GARRISON_CONTAIN_SLOT(03);
	BFME_GARRISON_CONTAIN_SLOT(04); BFME_GARRISON_CONTAIN_SLOT(05);
	BFME_GARRISON_CONTAIN_SLOT(06); BFME_GARRISON_CONTAIN_SLOT(07);
	BFME_GARRISON_CONTAIN_SLOT(08); BFME_GARRISON_CONTAIN_SLOT(09);
	BFME_GARRISON_CONTAIN_SLOT(10); BFME_GARRISON_CONTAIN_SLOT(11);
	BFME_GARRISON_CONTAIN_SLOT(12); BFME_GARRISON_CONTAIN_SLOT(13);
	BFME_GARRISON_CONTAIN_SLOT(14); BFME_GARRISON_CONTAIN_SLOT(15);
	BFME_GARRISON_CONTAIN_SLOT(16); BFME_GARRISON_CONTAIN_SLOT(17);
	BFME_GARRISON_CONTAIN_SLOT(18); BFME_GARRISON_CONTAIN_SLOT(19);
	BFME_GARRISON_CONTAIN_SLOT(20); BFME_GARRISON_CONTAIN_SLOT(21);
	BFME_GARRISON_CONTAIN_SLOT(22); BFME_GARRISON_CONTAIN_SLOT(23);
	BFME_GARRISON_CONTAIN_SLOT(24); BFME_GARRISON_CONTAIN_SLOT(25);
	virtual BfmeGarrisonHordeContainInterface *getHordeContainInterface() = 0;
#undef BFME_GARRISON_CONTAIN_SLOT
};
class BfmeGarrisonHordeContainInterface
{
public:
#define BFME_GARRISON_HORDE_SLOT(N) virtual void slot##N() = 0
	BFME_GARRISON_HORDE_SLOT(00); BFME_GARRISON_HORDE_SLOT(01);
	BFME_GARRISON_HORDE_SLOT(02); BFME_GARRISON_HORDE_SLOT(03);
	BFME_GARRISON_HORDE_SLOT(04); BFME_GARRISON_HORDE_SLOT(05);
	BFME_GARRISON_HORDE_SLOT(06); BFME_GARRISON_HORDE_SLOT(07);
	BFME_GARRISON_HORDE_SLOT(08); BFME_GARRISON_HORDE_SLOT(09);
	BFME_GARRISON_HORDE_SLOT(10); BFME_GARRISON_HORDE_SLOT(11);
	BFME_GARRISON_HORDE_SLOT(12); BFME_GARRISON_HORDE_SLOT(13);
	BFME_GARRISON_HORDE_SLOT(14); BFME_GARRISON_HORDE_SLOT(15);
	BFME_GARRISON_HORDE_SLOT(16); BFME_GARRISON_HORDE_SLOT(17);
	BFME_GARRISON_HORDE_SLOT(18); BFME_GARRISON_HORDE_SLOT(19);
	BFME_GARRISON_HORDE_SLOT(20); BFME_GARRISON_HORDE_SLOT(21);
	BFME_GARRISON_HORDE_SLOT(22); BFME_GARRISON_HORDE_SLOT(23);
	BFME_GARRISON_HORDE_SLOT(24); BFME_GARRISON_HORDE_SLOT(25);
	BFME_GARRISON_HORDE_SLOT(26); BFME_GARRISON_HORDE_SLOT(27);
	BFME_GARRISON_HORDE_SLOT(28); BFME_GARRISON_HORDE_SLOT(29);
	BFME_GARRISON_HORDE_SLOT(30); BFME_GARRISON_HORDE_SLOT(31);
	BFME_GARRISON_HORDE_SLOT(32); BFME_GARRISON_HORDE_SLOT(33);
	BFME_GARRISON_HORDE_SLOT(34); BFME_GARRISON_HORDE_SLOT(35);
	BFME_GARRISON_HORDE_SLOT(36); BFME_GARRISON_HORDE_SLOT(37);
	BFME_GARRISON_HORDE_SLOT(38); BFME_GARRISON_HORDE_SLOT(39);
	BFME_GARRISON_HORDE_SLOT(40); BFME_GARRISON_HORDE_SLOT(41);
	BFME_GARRISON_HORDE_SLOT(42); BFME_GARRISON_HORDE_SLOT(43);
	BFME_GARRISON_HORDE_SLOT(44); BFME_GARRISON_HORDE_SLOT(45);
	BFME_GARRISON_HORDE_SLOT(46); BFME_GARRISON_HORDE_SLOT(47);
	BFME_GARRISON_HORDE_SLOT(48); BFME_GARRISON_HORDE_SLOT(49);
	BFME_GARRISON_HORDE_SLOT(50); BFME_GARRISON_HORDE_SLOT(51);
	BFME_GARRISON_HORDE_SLOT(52); BFME_GARRISON_HORDE_SLOT(53);
	BFME_GARRISON_HORDE_SLOT(54); BFME_GARRISON_HORDE_SLOT(55);
	BFME_GARRISON_HORDE_SLOT(56); BFME_GARRISON_HORDE_SLOT(57);
	BFME_GARRISON_HORDE_SLOT(58);
	virtual _STL::list<Gen_t_001cb160_p4cd> &getMemberList() = 0;
#undef BFME_GARRISON_HORDE_SLOT
};
class BfmeGarrisonObjectLayout
{
public:
	unsigned char m_unmodelled_000[0x74];
	UnsignedInt m_id;
	unsigned char m_unmodelled_078[0x1c];
	unsigned char m_status94;
	unsigned char m_unmodelled_095[0x1fc - 0x95];
	BfmeGarrisonContainModuleInterface *m_contain;
	unsigned char m_unmodelled_200[4];
	BfmeAddValidAIUpdateCall *m_ai;
};
struct BfmeGarrisonStatusTriple
{
	UnsignedInt first;
	UnsignedInt second;
	UnsignedInt third;
};
class BfmeGarrisonStatusInterface
{
public:
#define BFME_GARRISON_STATUS_SLOT(N) virtual void slot##N() = 0
	BFME_GARRISON_STATUS_SLOT(00); BFME_GARRISON_STATUS_SLOT(01);
	BFME_GARRISON_STATUS_SLOT(02); BFME_GARRISON_STATUS_SLOT(03);
	BFME_GARRISON_STATUS_SLOT(04); BFME_GARRISON_STATUS_SLOT(05);
	BFME_GARRISON_STATUS_SLOT(06); BFME_GARRISON_STATUS_SLOT(07);
	BFME_GARRISON_STATUS_SLOT(08); BFME_GARRISON_STATUS_SLOT(09);
	BFME_GARRISON_STATUS_SLOT(10); BFME_GARRISON_STATUS_SLOT(11);
	BFME_GARRISON_STATUS_SLOT(12); BFME_GARRISON_STATUS_SLOT(13);
	BFME_GARRISON_STATUS_SLOT(14); BFME_GARRISON_STATUS_SLOT(15);
	BFME_GARRISON_STATUS_SLOT(16); BFME_GARRISON_STATUS_SLOT(17);
	BFME_GARRISON_STATUS_SLOT(18); BFME_GARRISON_STATUS_SLOT(19);
	BFME_GARRISON_STATUS_SLOT(20); BFME_GARRISON_STATUS_SLOT(21);
	BFME_GARRISON_STATUS_SLOT(22); BFME_GARRISON_STATUS_SLOT(23);
	BFME_GARRISON_STATUS_SLOT(24); BFME_GARRISON_STATUS_SLOT(25);
	BFME_GARRISON_STATUS_SLOT(26); BFME_GARRISON_STATUS_SLOT(27);
	BFME_GARRISON_STATUS_SLOT(28); BFME_GARRISON_STATUS_SLOT(29);
	BFME_GARRISON_STATUS_SLOT(30); BFME_GARRISON_STATUS_SLOT(31);
	BFME_GARRISON_STATUS_SLOT(32); BFME_GARRISON_STATUS_SLOT(33);
	BFME_GARRISON_STATUS_SLOT(34); BFME_GARRISON_STATUS_SLOT(35);
	BFME_GARRISON_STATUS_SLOT(36); BFME_GARRISON_STATUS_SLOT(37);
	BFME_GARRISON_STATUS_SLOT(38);
	virtual BfmeGarrisonStatusTriple *getStatus(BfmeGarrisonStatusTriple *result, Object *object) const = 0;
#undef BFME_GARRISON_STATUS_SLOT
};
class BfmeOutOfWeaponRangeTemplate
{
public:
	Bool isLeechRangeWeapon() const;
};
class BfmeGarrisonWeaponLayout
{
public:
	unsigned char m_unmodelled_000[4];
	BfmeOutOfWeaponRangeTemplate *m_template;
};

#pragma comment(linker, "/alternatename:?isLeechRangeWeapon@BfmeOutOfWeaponRangeTemplate@@QBE_NXZ=?j_00028f74@@YAXXZ")

void GarrisonContain::addValidObjectsToGarrisonPoints(void)
{
	if ((*reinterpret_cast<BfmeGarrisonContainedNode **>(reinterpret_cast<char *>(this) + 0x38))->next == *reinterpret_cast<BfmeGarrisonContainedNode **>(reinterpret_cast<char *>(this) + 0x38))
		return;

	BfmeAddValidAIUpdateCall *ai;
	Object *victim;
	const Coord3D *victimPos;
	for (BfmeGarrisonContainedNode *it = (*reinterpret_cast<BfmeGarrisonContainedNode **>(reinterpret_cast<char *>(this) + 0x38))->next; it != *reinterpret_cast<BfmeGarrisonContainedNode **>(reinterpret_cast<char *>(this) + 0x38); it = it->next)
	{
		Object *object = it->object;
		BfmeGarrisonObjectLayout *objectLayout = reinterpret_cast<BfmeGarrisonObjectLayout *>(object);
		if ((objectLayout->m_status94 & 0x10) != 0)
			continue;

		BfmeGarrisonContainModuleInterface *contain = objectLayout->m_contain;
		if (contain != 0)
		{
			BfmeGarrisonHordeContainInterface *horde = contain->getHordeContainInterface();
			if (horde == 0)
				continue;
			else
			{
				_STL::list<Gen_t_001cb160_p4cd> members(horde->getMemberList());
				for (_STL::list<Gen_t_001cb160_p4cd>::iterator memberIt = members.begin(); memberIt != members.end(); ++memberIt)
				{
					Object *object = (*memberIt).object;
					Weapon *weapon = reinterpret_cast<BfmeAddValidObjectCall *>(object)->getCurrentWeapon(0);
					if (weapon == 0 || (reinterpret_cast<BfmeGarrisonWeaponLayout *>(weapon)->m_template->isLeechRangeWeapon() != FALSE))
						continue;

					BfmeGarrisonObjectLayout *memberLayout = reinterpret_cast<BfmeGarrisonObjectLayout *>(object);
					ai = memberLayout->m_ai;
					if (ai != 0)
					{
						victim = ai->getCurrentVictim();
						victimPos = ai->getCurrentVictimPos();
						if (victim != 0)
							reinterpret_cast<BfmeAddValidOwnerCall *>(this)->putObjectAtBestGarrisonPoint(object, victim, 0);
						else if (victimPos != 0)
							reinterpret_cast<BfmeAddValidOwnerCall *>(this)->putObjectAtBestGarrisonPoint(object, 0, victimPos);
						else
						{
							BfmeGarrisonStatusTriple statusStorage;
							BfmeGarrisonStatusTriple *status = reinterpret_cast<BfmeGarrisonStatusInterface *>(reinterpret_cast<char *>(this) + 0x20)->getStatus(&statusStorage, 0);
							if ((status->second & 0x10000000) == 0)
								reinterpret_cast<BfmeAddValidOwnerCall *>(this)->putObjectAtBestGarrisonPoint(object, 0, reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(object) + 0x38));
						}
					}
				}
				continue;
			}
		}

		ai = objectLayout->m_ai;
		if (ai == 0)
			continue;
		victim = ai->getCurrentVictim();
		victimPos = ai->getCurrentVictimPos();
		if (victim != 0)
			reinterpret_cast<BfmeAddValidOwnerCall *>(this)->putObjectAtBestGarrisonPoint(object, victim, 0);
		else if (victimPos != 0)
		{
			BfmeGarrisonFirePointInterface *firePoint = reinterpret_cast<BfmeGarrisonFirePointInterface *>(this);
			const ObjectID objectID = *reinterpret_cast<const ObjectID *>(reinterpret_cast<const char *>(object) + 0x74);
			if (firePoint->getObjectGarrisonPointIndex(objectID) == GARRISON_INDEX_INVALID)
			{
				Int conditionIndex = reinterpret_cast<BfmeAddValidOwnerCall *>(this)->findConditionIndex();
				BfmeGarrisonFindClosestCall *pointFinder = reinterpret_cast<BfmeGarrisonFindClosestCall *>(this);
				Int pointIndex = pointFinder->findClosestFreeGarrisonPointIndex(conditionIndex, victimPos);
				if (pointIndex != GARRISON_INDEX_INVALID)
				{
					BfmeGarrisonPlacementCall *placement = reinterpret_cast<BfmeGarrisonPlacementCall *>(this);
					placement->putObjectAtGarrisonPoint(object, INVALID_ID, conditionIndex, pointIndex);
				}
			}
		}
	}
}
