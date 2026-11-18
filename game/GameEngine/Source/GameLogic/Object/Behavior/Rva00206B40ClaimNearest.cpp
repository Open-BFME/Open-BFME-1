// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc- /Igame/Libraries/Include /Igame/GameEngine/Source/GameLogic/Object
// stlport
//
// Retail 0x00206890 (156 B, ret 4 at +0x99) and 0x00206B40 (295 B, ret 4
// at +0x124): slots 3 and 2 of vtable 0x010A626C, the secondary vtable the
// matched SiegeDockingBehavior constructor (0x002062C0) stores at +0x20.
// Both find the Object by id and sweep the primary at this-0x20
// (bfmeSweepERP 0x00206460). query reports whether an unclaimed slot of the
// item vector at this+4 is usable; claimNearest claims the nearest one and
// returns its index. Owner class and methods are unproven, so the names
// keep the address. The early `count == 0` return of -1 shares the epilogue with the
// final return; writing it as an if-block over the loop moves the
// bestIndex spill ahead of the branch.
#include <vector>
#include "../../../../Include/Common/ScalarTypes.h"




#include <math.h>
#pragma intrinsic(sqrt)

#include "Lib/Coord3D.h"

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
};

class Rva00206B40Template : public Overridable
{
public:
	unsigned char m_pad008[0xd8 - 0x08];
	UnsignedInt m_flagsD8;
};

template <class T>
class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}

	T *m_overridable;
};

#define BFME_HAVE_COORD3D
#define OBJECT_TU_MEMBERS \
	const Rva00206B40Template *getTemplate00206B40() const \
	{ \
		return ((const OVERRIDE<Rva00206B40Template> *)&m_template)->operator->(); \
	}
#include "object.h"
#undef OBJECT_TU_MEMBERS

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};
extern GameLogic *TheGameLogic;

class BfmeHostERP
{
public:
	void bfmeSweepERP();
};

struct ArrayItem
{
	void *m_vtable;
	Int m_occupied;
	Coord3D m_pos;
	unsigned char m_pad14[0x20 - 0x14];
	Int m_claimantID;
};

class Rva00206B40Owner
{
public:
	Bool query(Int objectID);
	Int claimNearest(Int objectID);

	void *m_vtable;
	_STL::vector<ArrayItem *> m_items;
};

Bool Rva00206B40Owner::query(Int objectID)
{
	Object *obj = TheGameLogic->findObjectByID(objectID);
	if (obj == 0)
		return false;

	((BfmeHostERP *)((char *)this - 0x20))->bfmeSweepERP();

	UnsignedInt count = m_items.size();
	if (count == 0)
		return false;

	for (UnsignedInt i = 0; i < count; ++i)
	{
		ArrayItem *item = m_items[i];
		if (item->m_claimantID != 0)
			continue;
		if ((obj->getTemplate00206B40()->m_flagsD8 & 0x400) || item->m_occupied == 0)
			return true;
	}
	return false;
}

Int Rva00206B40Owner::claimNearest(Int objectID)
{
	Object *obj = TheGameLogic->findObjectByID(objectID);
	if (obj == 0)
		return -1;

	((BfmeHostERP *)((char *)this - 0x20))->bfmeSweepERP();

	UnsignedInt count = m_items.size();
	if (count == 0)
		return -1;

	Int bestIndex = -1;
	Real bestDist = 99999.0f;
	for (UnsignedInt i = 0; i < count; ++i)
	{
		ArrayItem *item = m_items[i];
		if (item->m_claimantID != 0)
			continue;
		if (!(obj->getTemplate00206B40()->m_flagsD8 & 0x400) && item->m_occupied != 0)
			continue;

		Coord3D delta;
		delta.x = item->m_pos.x;
		delta.y = item->m_pos.y;
		delta.z = item->m_pos.z;
		delta.x -= obj->m_cachedPos.x;
		delta.y -= obj->m_cachedPos.y;
		delta.z -= obj->m_cachedPos.z;
		Real dist = (Real)sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
		if (dist < bestDist)
		{
			bestDist = dist;
			bestIndex = i;
		}
	}

	if (bestIndex >= 0)
		m_items[bestIndex]->m_claimantID = objectID;
	return bestIndex;
}
