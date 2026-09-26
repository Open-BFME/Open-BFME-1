// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?addValidObjectsToGarrisonPoints@GarrisonContain@@IAEXXZ
// Retail RVA 0x0021F5E0, 489 bytes.
//
// Identity: GarrisonContain::update (0x0021F920) and
// GarrisonContain::redeployOccupants (0x0021F850) both call this body by
// name; the Zero Hour twin is GarrisonContain::addValidObjectsToGarrisonPoints.
// BFME adds a branch the Zero Hour body lacks: when a contained object's
// Object::m_contain (+0x1FC) answers slot 26, the Object list that interface
// returns from slot 59 is copied and each listed object with a current weapon
// (whose +0x04 target reports a zero byte from 0x001E1770) is placed instead.
// The other branch inlines the "not yet at a point" half of
// putObjectAtBestGarrisonPoint for a bare victim position.
//
// Object::m_status (+0x90, witnessed) is a 96-bit STLport bitset: the byte
// test at +0x94 mask 0x10 is test(36).  The +0x20 interface's slot 39
// returns the same 12-byte mask by value (the frame reserves exactly 12
// bytes for it) and the body tests bit 60, the bit Rva00225960ListDrain reads
// from Object::m_status.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <bitset>

typedef int Int;
typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};

enum WeaponSlotType
{
	FORCE_WEAPONSLOTTYPE_TO_LONG_SIZE = 0x7ffffff
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
typedef _STL::list<Object *> ContainedItemsList;

template <Int NUMBITS>
class BitFlags
{
public:
	Bool test(Int bit) const { return m_bits.test(bit); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<96> ObjectStatusMaskType;

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
	const Coord3D *getCurrentVictimPos() const;
};

// Retail 0x001E1770: the byte at +0x4ED of the object Weapon +0x04 points to.
class Rva001E1770ByteField
{
public:
	unsigned char get() const;
};

class Weapon
{
public:
	const Rva001E1770ByteField *getField04() const { return m_field04; }

private:
	unsigned char m_unmodelled_00[4];
	const Rva001E1770ByteField *m_field04;			///< +0x04
};

#define RVA0021F5E0_SLOTS(N) virtual void slot##N()
#define RVA0021F5E0_SLOTS_10(D) \
	RVA0021F5E0_SLOTS(D##0); RVA0021F5E0_SLOTS(D##1); RVA0021F5E0_SLOTS(D##2); \
	RVA0021F5E0_SLOTS(D##3); RVA0021F5E0_SLOTS(D##4); RVA0021F5E0_SLOTS(D##5); \
	RVA0021F5E0_SLOTS(D##6); RVA0021F5E0_SLOTS(D##7); RVA0021F5E0_SLOTS(D##8); \
	RVA0021F5E0_SLOTS(D##9)

// Returned by contain slot 26; slot 59 (+0xEC) hands back an Object list.
class Rva0021F5E0Slot26Interface
{
public:
	RVA0021F5E0_SLOTS_10(0); RVA0021F5E0_SLOTS_10(1); RVA0021F5E0_SLOTS_10(2);
	RVA0021F5E0_SLOTS_10(3); RVA0021F5E0_SLOTS_10(4);
	RVA0021F5E0_SLOTS(50); RVA0021F5E0_SLOTS(51); RVA0021F5E0_SLOTS(52);
	RVA0021F5E0_SLOTS(53); RVA0021F5E0_SLOTS(54); RVA0021F5E0_SLOTS(55);
	RVA0021F5E0_SLOTS(56); RVA0021F5E0_SLOTS(57); RVA0021F5E0_SLOTS(58);
	virtual const ContainedItemsList &slot59() = 0;
};

class ContainModuleInterface
{
public:
	RVA0021F5E0_SLOTS_10(0); RVA0021F5E0_SLOTS_10(1);
	RVA0021F5E0_SLOTS(20); RVA0021F5E0_SLOTS(21); RVA0021F5E0_SLOTS(22);
	RVA0021F5E0_SLOTS(23); RVA0021F5E0_SLOTS(24); RVA0021F5E0_SLOTS(25);
	virtual Rva0021F5E0Slot26Interface *slot26() = 0;
};

// GarrisonContain's interface at +0x20 (vtable 0x010AB598).
class Rva0021F5E0Interface20
{
public:
	RVA0021F5E0_SLOTS_10(0); RVA0021F5E0_SLOTS_10(1); RVA0021F5E0_SLOTS_10(2);
	RVA0021F5E0_SLOTS(30); RVA0021F5E0_SLOTS(31); RVA0021F5E0_SLOTS(32);
	RVA0021F5E0_SLOTS(33); RVA0021F5E0_SLOTS(34); RVA0021F5E0_SLOTS(35);
	RVA0021F5E0_SLOTS(36); RVA0021F5E0_SLOTS(37); RVA0021F5E0_SLOTS(38);
	virtual ObjectStatusMaskType slot39(Object *obj) const;
};

#undef RVA0021F5E0_SLOTS_10
#undef RVA0021F5E0_SLOTS

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);

	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}
	Bool testStatus(Int bit) const { return m_status.test(bit); }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }

private:
	unsigned char m_unmodelled_000[0x74];
	ObjectID m_id;									///< +0x74
	unsigned char m_unmodelled_078[0x90 - 0x78];
	ObjectStatusMaskType m_status;					///< +0x90
	unsigned char m_unmodelled_09c[0x1fc - 0x9c];
	ContainModuleInterface *m_contain;				///< +0x1FC
	unsigned char m_unmodelled_200[0x204 - 0x200];
	AIUpdateInterface *m_ai;						///< +0x204
};

class GarrisonContain
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual Int getObjectGarrisonPointIndex(ObjectID objectID);

protected:
	Int findConditionIndex();
	Int findClosestFreeGarrisonPointIndex(Int conditionIndex, const Coord3D *targetPos);
	void putObjectAtGarrisonPoint(Object *obj, ObjectID targetID, Int conditionIndex, Int pointIndex);
	void putObjectAtBestGarrisonPoint(Object *obj, Object *target, const Coord3D *targetPos);
	void addValidObjectsToGarrisonPoints();

private:
	unsigned char m_unmodelled_04[0x20 - 0x04];
	Rva0021F5E0Interface20 m_interface20;			///< +0x20
	unsigned char m_unmodelled_24[0x38 - 0x24];
	ContainedItemsList m_containList;				///< +0x38, OpenContain::m_containList
};

void GarrisonContain::addValidObjectsToGarrisonPoints()
{
	const ContainedItemsList &containList = m_containList;
	if (containList.empty())
		return;

	for (ContainedItemsList::const_iterator it = containList.begin(); it != containList.end(); ++it)
	{
		Object *obj = *it;
		if (obj->testStatus(36))
			continue;

		ContainModuleInterface *contain = obj->getContain();
		if (contain != 0)
		{
			Rva0021F5E0Slot26Interface *view = contain->slot26();
			if (view == 0)
				continue;

			ContainedItemsList listed(view->slot59());
			for (ContainedItemsList::iterator listIt = listed.begin(); listIt != listed.end(); ++listIt)
			{
				Object *entry = *listIt;
				Weapon *weapon = entry->getCurrentWeapon();
				if (weapon == 0 || weapon->getField04()->get() != 0)
					continue;

				AIUpdateInterface *ai = entry->getAIUpdateInterface();
				if (ai != 0)
				{
					Object *victim = ai->getCurrentVictim();
					const Coord3D *victimPos = ai->getCurrentVictimPos();
					if (victim != 0)
						putObjectAtBestGarrisonPoint(entry, victim, 0);
					else if (victimPos != 0)
						putObjectAtBestGarrisonPoint(entry, 0, victimPos);
					else if (!m_interface20.slot39(0).test(60))
						putObjectAtBestGarrisonPoint(entry, 0, entry->getPosition());
				}
			}
			continue;
		}

		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (ai == 0)
			continue;

		Object *victim = ai->getCurrentVictim();
		const Coord3D *victimPos = ai->getCurrentVictimPos();
		if (victim != 0)
			putObjectAtBestGarrisonPoint(obj, victim, 0);
		else if (victimPos != 0 && getObjectGarrisonPointIndex(obj->getID()) == -1)
		{
			Int conditionIndex = findConditionIndex();
			Int pointIndex = findClosestFreeGarrisonPointIndex(conditionIndex, victimPos);
			if (pointIndex != -1)
				putObjectAtGarrisonPoint(obj, INVALID_ID, conditionIndex, pointIndex);
		}
	}
}
