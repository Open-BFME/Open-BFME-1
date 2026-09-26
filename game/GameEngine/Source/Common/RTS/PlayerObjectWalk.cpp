// cl: /DNDEBUG /DWIN32 /MD /EHs-c-
// The Player object walk and the caller that reaches it by name:
//
//   0x000CDCF0  Player::iterateObjects                 77 bytes
//   0x000EE770  BfmeIterableObject::bfmeIterate        70 bytes  (the inner walk)
//   0x000CFD20  Player::findClosestByKindOf           163 bytes
//
// iterateObjects walks the list at Player+0x288, handing each element to
// bfmeIterate, which walks that element's own list at +0x274 and calls the
// visitor for every object in it. findClosestByKindOf is one of its callers.
//
// It is here rather than with the other object counters because
// Player::iterateObjects exists under TWO decorations at TWO addresses:
//
//   ?iterateObjects@Player@@QBEHP6AXPAVObject@@PAX@Z1@Z  body,  0x000CDCF0
//   ?iterateObjects@Player@@QBEXP6AXPAVObject@@PAX@Z1@Z  thunk, 0x0002F1CB
//
// They differ only in the return type, which C++ will not let one translation
// unit hold both of, so the spelling a caller uses decides which address its
// call reaches. findClosestByKindOf takes the int spelling, which is the one
// defined here, so the definition and this caller belong in the same file and
// the void-spelling callers cannot join them. See PlayerObjectCounts.cpp for
// the other half.
//
// On the return type itself: targets/game/reverse/reloc_names.csv names the row with the
// void decoration and the parameters in that name are right -- the
// back-reference only comes out as Z1@Z if the second argument really is the
// void * the function pointer already mentioned. The return is not, and
// neither is it bool. Each visit's result is tested with test eax,eax and both
// exits set the whole register, so this function and the one it calls return
// an int-width value; declaring either bool narrows the test to test al,al and
// shortens the exits by three bytes.
//
// The member at +0x288 is a pointer to a list header, not the header itself:
// the walk starts at what it points at and stops when the node comes back
// round to it. Node next is at +0x00 and the element at +0x08. The header is
// re-read from the member on every turn because the visit call could have
// moved it.
//
// BfmeIterableObject keeps its placeholder name: it is spelled into its own
// row, ?bfmeIterate@BfmeIterableObject@@QAEHP6AXPAVObject@@PAX@Z1@Z, so the
// name is load-bearing. It is very likely the same class the hasAny family
// calls TeamPrototype -- both are the element of the list at Player+0x288 --
// but nothing here proves that, and renaming it would delete the row.

#include <float.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];

	void clear()
	{
		m_bits[0] = 0;
		m_bits[1] = 0;
		m_bits[2] = 0;
		m_bits[3] = 0;
		m_bits[4] = 0;
		m_bits[5] = 0;
	}
};

typedef BitFlags<192> KindOfMaskType;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool isKindOfMulti(const KindOfMaskType &setMask,
		const KindOfMaskType &clearMask) const;

	char m_pad[0x38];
	Coord3D m_position;					// this+0x38
};

typedef void (*ObjectIterateFunc)(Object *object, void *userData);

class BfmeInnerIterable
{
public:
	Int bfmeVisit(ObjectIterateFunc func, void *userData);
};

class Gen_000c8a30
{
public:
	Int m(void);
};

class BfmeIterableObject
{
public:
	Int bfmeIterate(ObjectIterateFunc func, void *userData);	// ILT 0x0003DB68

private:
	char m_bfmeHead[0x274];
	BfmeInnerIterable *m_bfmeInnerList;				// +0x274
};

// ?bfmeIterate@BfmeIterableObject@@QAEHP6AXPAVObject@@PAX@Z1@Z		70 bytes
Int BfmeIterableObject::bfmeIterate(ObjectIterateFunc func, void *userData)
{
	BfmeInnerIterable *node = m_bfmeInnerList;

	while (node)
	{
		if (!node->bfmeVisit(func, userData))
			return 0;

		if (node)
			node = (BfmeInnerIterable *)((Gen_000c8a30 *)node)->m();
	}

	return 1;
}

class BfmeObjectListNode
{
public:
	BfmeObjectListNode *m_bfmeNext;					// +0x00
	BfmeObjectListNode *m_bfmePrev;					// +0x04
	BfmeIterableObject *m_bfmeObject;				// +0x08
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int iterateObjects(ObjectIterateFunc func, void *userData) const;
	Object *findClosestByKindOf(const Coord3D *queryPosition,
		KindOfMaskType setMask, KindOfMaskType clearMask);

private:
	char m_bfmeHead[0x288];
	BfmeObjectListNode *m_bfmeObjectList;				// +0x288
};

// ?iterateObjects@Player@@QBEHP6AXPAVObject@@PAX@Z1@Z
Int Player::iterateObjects(ObjectIterateFunc func, void *userData) const
{
	for (BfmeObjectListNode *node = m_bfmeObjectList->m_bfmeNext;
		node != m_bfmeObjectList;
		node = node->m_bfmeNext)
	{
		if (!node->m_bfmeObject->bfmeIterate(func, userData))
			return 0;
	}

	return 1;
}

class ClosestKindOfData
{
public:
	KindOfMaskType m_setKindOf;
	KindOfMaskType m_clearKindOf;
	Coord3D m_source;
	Object *m_closest;
	Real m_closestDistSq;
};

extern void j_00037fe7(void);

static void findClosestKindOf(Object *obj, void *userData)
{
	ClosestKindOfData *closestData = (ClosestKindOfData *)userData;

	if (!obj->isKindOfMulti(closestData->m_setKindOf,
		closestData->m_clearKindOf))
		return;

	Real dx = obj->m_position.x - closestData->m_source.x;
	Real dy = obj->m_position.y - closestData->m_source.y;
	Real distSq = dx * dx + dy * dy;
	if (distSq < closestData->m_closestDistSq)
	{
		closestData->m_closest = obj;
		closestData->m_closestDistSq = distSq;
	}
}

// ?findClosestByKindOf@Player@@QAEPAVObject@@PBUCoord3D@@V?$BitFlags@$0MA@@@1@Z
Object *Player::findClosestByKindOf(const Coord3D *queryPosition,
	KindOfMaskType setMask, KindOfMaskType clearMask)
{
	ClosestKindOfData data;
	typedef void (ClosestKindOfData::*Constructor)(void);
	union
	{
		void (*raw)(void);
		Constructor member;
	} constructor;
	constructor.raw = j_00037fe7;
	(data.*constructor.member)();
	register Player *self = this;
	data.m_setKindOf = setMask;
	data.m_clearKindOf = clearMask;
	data.m_source = *queryPosition;
	self->iterateObjects(findClosestKindOf, &data);
	return data.m_closest;
}
