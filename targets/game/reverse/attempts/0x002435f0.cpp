// ?run@Rva002435F0View@@QAEXXZ
// partial score=0.3 date=2026-09-23
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <math.h>
// Opaque HordeContain formation-slot rebalance at retail 0x002435F0.

typedef bool Bool;
typedef int Int;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva002435F0MemberNode
{
	Rva002435F0MemberNode *next;
	Rva002435F0MemberNode *previous;
	void *value;
};

struct Rva002435F0MemberList
{
	Rva002435F0MemberNode *node;
};

class Rva002435F0OpenContainInterface
{
public:
#define RVA002435F0_SLOT(N) virtual void slot##N() = 0
	RVA002435F0_SLOT(00); RVA002435F0_SLOT(01); RVA002435F0_SLOT(02); RVA002435F0_SLOT(03);
	RVA002435F0_SLOT(04); RVA002435F0_SLOT(05); RVA002435F0_SLOT(06); RVA002435F0_SLOT(07);
	RVA002435F0_SLOT(08); RVA002435F0_SLOT(09); RVA002435F0_SLOT(10); RVA002435F0_SLOT(11);
	RVA002435F0_SLOT(12); RVA002435F0_SLOT(13); RVA002435F0_SLOT(14); RVA002435F0_SLOT(15);
	RVA002435F0_SLOT(16); RVA002435F0_SLOT(17); RVA002435F0_SLOT(18); RVA002435F0_SLOT(19);
	RVA002435F0_SLOT(20); RVA002435F0_SLOT(21); RVA002435F0_SLOT(22); RVA002435F0_SLOT(23);
	RVA002435F0_SLOT(24); RVA002435F0_SLOT(25); RVA002435F0_SLOT(26); RVA002435F0_SLOT(27);
	RVA002435F0_SLOT(28); RVA002435F0_SLOT(29); RVA002435F0_SLOT(30); RVA002435F0_SLOT(31);
	RVA002435F0_SLOT(32); RVA002435F0_SLOT(33); RVA002435F0_SLOT(34); RVA002435F0_SLOT(35);
	RVA002435F0_SLOT(36); RVA002435F0_SLOT(37); RVA002435F0_SLOT(38); RVA002435F0_SLOT(39);
	RVA002435F0_SLOT(40); RVA002435F0_SLOT(41); RVA002435F0_SLOT(42); RVA002435F0_SLOT(43);
	RVA002435F0_SLOT(44); RVA002435F0_SLOT(45); RVA002435F0_SLOT(46); RVA002435F0_SLOT(47);
	RVA002435F0_SLOT(48); RVA002435F0_SLOT(49); RVA002435F0_SLOT(50); RVA002435F0_SLOT(51);
	RVA002435F0_SLOT(52); RVA002435F0_SLOT(53); RVA002435F0_SLOT(54); RVA002435F0_SLOT(55);
	RVA002435F0_SLOT(56); RVA002435F0_SLOT(57); RVA002435F0_SLOT(58); RVA002435F0_SLOT(59);
	RVA002435F0_SLOT(60); RVA002435F0_SLOT(61); RVA002435F0_SLOT(62); RVA002435F0_SLOT(63);
	RVA002435F0_SLOT(64);
	virtual const Rva002435F0MemberList *getContainedItemsList() const = 0;
#undef RVA002435F0_SLOT
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

private:
	char pad000[4];
};

class Rva002435F0Link
{
public:
	char pad000[4];
	Overridable *overrideValue;
};

enum WeaponSlotType
{
	Rva002435F0WeaponSlotUnknown = 0
};

class Weapon
{
public:
	char pad000[4];
	int value;
};

class Object
{
public:
	char pad000[4];
	Rva002435F0Link *link;
	char pad008[0x38 - 8];
	Coord3D position;
	char pad044[0x74 - 0x44];
	Int id;

	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	const Coord3D *getPosition() const { return &position; }
};

class BfmeSubDSU
{
public:
	void **bfmeTwoDSU(void **key);

	unsigned char body[0xc];
};

class Rva002435F0Owner
{
public:
	Coord3D *fillFormationPosition(Coord3D *out, Int index);
};

#pragma comment(linker, "/alternatename:?fillFormationPosition@Rva002435F0Owner@@QAEPAVCoord3D@@PAV2@H@Z=?j_00019736@@YAXXZ")

class Rva002435F0View
{
public:
	void run();

	char pad000[0x3c];
	BfmeSubDSU m_indices;
	unsigned char *slotBegin;
	unsigned char *slotEnd;
};

#define RVA002435F0_THRESHOLD (*(const float *)0x01095F98)

static __forceinline Int getIndex(Rva002435F0View *view, Object *object)
{
	Int key = object->id;
	return *(Int *)view->m_indices.bfmeTwoDSU((void **)&key);
}

static __forceinline Overridable *resolveOverride(Object *object)
{
	Rva002435F0Link *link = object->link;
	if (link == 0)
		return 0;
	Overridable *value = link->overrideValue;
	if (value != 0)
		value = (Overridable *)value->getFinalOverride();
	return value;
}

void Rva002435F0View::run()
{
	const Rva002435F0MemberList *members =
		((Rva002435F0OpenContainInterface *)((char *)this - 0xc4))
			->getContainedItemsList();
	Rva002435F0MemberNode *sentinel = members->node;
	Rva002435F0MemberNode *first = sentinel->next;
	Rva002435F0MemberNode *outer = first;

	if (first == sentinel)
		return;

	const Coord3D *basePosition =
		(const Coord3D *)(*(char **)((char *)this - 0xdc) + 0x38);

	for (;;)
	{
		Object *member = (Object *)outer->value;
		Int index = getIndex(this, member);
		unsigned char *slotBegin = this->slotBegin;
		unsigned char *slotEnd = this->slotEnd;
		unsigned int count = (unsigned int)((slotEnd - slotBegin) >> 4);
		if ((unsigned int)index <= count)
		{
			Coord3D memberFormationPosition;
			Coord3D memberSlot;
			((Rva002435F0Owner *)((char *)this - 0xe4))
				->fillFormationPosition(&memberFormationPosition, index);
			memberSlot.x = memberFormationPosition.x + basePosition->x;
			memberSlot.y = memberFormationPosition.y + basePosition->y;

			for (Rva002435F0MemberNode *inner = outer->next;
				inner != first; inner = inner->next)
			{
				Object *other = (Object *)inner->value;
				if (resolveOverride(other) != resolveOverride(member))
					continue;

				Weapon *otherWeapon = other->getCurrentWeapon(0);
				if (otherWeapon == 0)
					continue;
				Weapon *memberWeapon = member->getCurrentWeapon(0);
				if (memberWeapon == 0)
					continue;
				otherWeapon = other->getCurrentWeapon(0);
				memberWeapon = member->getCurrentWeapon(0);
				if (otherWeapon->value != memberWeapon->value)
					continue;

			Int otherIndex = getIndex(this, other);
				if ((unsigned int)otherIndex > count)
					continue;

				Coord3D otherFormationPosition;
				Coord3D otherSlot;
				((Rva002435F0Owner *)((char *)this - 0xe4))
					->fillFormationPosition(&otherFormationPosition, otherIndex);
				otherSlot.x = otherFormationPosition.x + basePosition->x;
				otherSlot.y = otherFormationPosition.y + basePosition->y;

				const Coord3D *otherPosition = other->getPosition();
				const Coord3D *memberPosition = member->getPosition();
				float memberDistance = (float)sqrt(
					(memberPosition->x - memberSlot.x) *
					(memberPosition->x - memberSlot.x) +
					(memberPosition->y - memberSlot.y) *
					(memberPosition->y - memberSlot.y));
				float otherDistance = (float)sqrt(
					(otherPosition->x - otherSlot.x) *
					(otherPosition->x - otherSlot.x) +
					(otherPosition->y - otherSlot.y) *
					(otherPosition->y - otherSlot.y));
				float otherToMemberSlot = (float)sqrt(
					(otherPosition->x - memberSlot.x) *
					(otherPosition->x - memberSlot.x) +
					(otherPosition->y - memberSlot.y) *
					(otherPosition->y - memberSlot.y));
				float memberToOtherSlot = (float)sqrt(
					(memberPosition->x - otherSlot.x) *
					(memberPosition->x - otherSlot.x) +
					(memberPosition->y - otherSlot.y) *
					(memberPosition->y - otherSlot.y));
				if ((otherDistance - memberDistance) * RVA002435F0_THRESHOLD +
					memberToOtherSlot > otherToMemberSlot)
				{
					Int key = other->id;
					*(Int *)m_indices.bfmeTwoDSU((void **)&key) = index;
					key = member->id;
					*(Int *)m_indices.bfmeTwoDSU((void **)&key) = otherIndex;
					index = otherIndex;
				}
			}
		}
		outer = outer->next;
		if (outer == first)
			break;
	}
}
