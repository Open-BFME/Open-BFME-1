// ?d_00239e00@@YAXXZ
// partial score=0.9668 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source
// stlport
// Retail 0x00239E00 (603 bytes): a HordeContain virtual reached through the
// interface subobject at +0xE4.
//
// Owner: ??0HordeContain (0x0023EAF0) installs vtable VA 0x010AED58 at
// this+0xE4; its slot 118 is ILT 0x00003008 -> 0x00239E00. AODHordeContain
// (VA 0x010AE230) and HorseHordeContain (VA 0x010B07E0) keep the same slot.
// The body reads the owning Object at interface-0xDC (module +0x08), sets the
// interface's byte at +0x04 (HordeContain +0xE8) and ends with
// UpdateModule::setWakeFrame on interface-0xE4. No caller or string names the
// method, so it keeps an address-derived name.
//
// What it does, read from the retail body: when the object stands on ground
// the pathfinder accepts, or on a bridge, it looks for the closest
// WALK_ON_TOP_OF_WALL object (KindOf name table VA 0x012AA068, index 59)
// within 150. If that object has a SiegeDockingBehavior module with dock
// points, the object turns to face away from the nearest one (0.25 octagonal
// distance); otherwise, off a bridge, it takes the wall's orientation plus a
// template angle at ThingTemplate+0x404. Either way the flag is set, and the
// module is woken.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <math.h>

typedef bool Bool;
typedef float Real;

#define NULL 0

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};
#define BFME_HAVE_COORD3D

struct Coord2D
{
	Real x;
	Real y;

	Real toAngle() const;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum KindOfType
{
	KINDOF_WALK_ON_TOP_OF_WALL = 59
};

class Module;

// Zero Hour Common/Override.h: Thing reaches its template through the final
// override of the chain.
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Real getReal404() const { return m_real404; }

private:
	unsigned char m_unmodelled008[0x404 - 0x08];
	Real m_real404;										///< +0x404, unnamed
};

#define THING_TU_MEMBERS \
	const Coord3D *getPosition() const { return &m_cachedPos; } \
	Real getOrientation() const { return m_cachedAngle; } \
	void setOrientation(Real angle); \
	const ThingTemplate *getTemplate() const \
	{ \
		if (!m_template) \
			return NULL; \
		return (const ThingTemplate *)m_template->getFinalOverride(); \
	}
#define OBJECT_TU_MEMBERS \
	Module *findModule(NameKeyType key) const;
#include "GameLogic/Object/object.h"

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags() {}
	BitFlags(BogusInitType k, Int idx1);
	void set(Int i) { m_bits.set(i); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *obj) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	// throw() lets VC7.1 put the mask and the loop's delta on separate slots.
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear) throw();
	virtual Bool allow(Object *obj);

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0,
	FROM_CENTER_3D = 1,
	FROM_BOUNDINGSPHERE_2D = 2,
	FROM_BOUNDINGSPHERE_3D = 3
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, Real maxDist,
		DistanceCalculationType dc, PartitionFilter *filter);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class Pathfinder
{
public:
	Bool bfmeGroundCellThreshold(const Coord3D *pos, Bool flag);
};

// 0x003D5DA0 is ledgered under this address-derived owner; retail calls it on
// the same TheAI pathfinder pointer.
class Bfme5BridgeList
{
public:
	char bfmeAnyBridgeAt(const Coord3D *pos);
};

class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }

private:
	unsigned char m_unmodelled00[0x0c];
	Pathfinder *m_pathfinder;							///< +0x0C
};

extern AI *TheAI;
extern PartitionManager *ThePartitionManager;
extern NameKeyGenerator *TheNameKeyGenerator;

// The SiegeDockingBehavior module's dock-point helpers, ledgered under
// address-derived owners: 0x00207230 (point count), 0x002060B0 and
// 0x00206100 (a point by index, returned by value).
class BfmeThingBQA
{
public:
	// throw() lets the dock direction share the best distance's slot.
	Int bfmeGoBQA() throw();
};

class Rva002060B0Triple
{
public:
	Real x;
	Real y;
	Real z;
};

class Rva002060B0Owner
{
public:
	Rva002060B0Triple copyAt(Int index);
};

class Rva00206100Point
{
public:
	Real x;
	Real y;
	Real z;
};

class Rva00206100Owner
{
public:
	Rva00206100Point point(Int index);
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	Object *getObject() const { return m_object; }

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);

private:
	unsigned char m_unmodelled04[0x04];
	Object *m_object;									///< +0x08
};

// Whatever HordeContain's primary chain adds up to its +0xE4 interface.
class Rva00239E00HordeHead : public UpdateModule
{
private:
	unsigned char m_unmodelled0C[0xE4 - 0x0C];
};

// The interface HordeContain carries at +0xE4 (vtable VA 0x010AED58).
class Rva00239E00HordeInterface
{
public:
	virtual void rva00239E00() = 0;

protected:
	Bool m_flag04;										///< +0x04 (HordeContain +0xE8)
};

class Rva00239E00HordeContain : public Rva00239E00HordeHead, public Rva00239E00HordeInterface
{
public:
	virtual void rva00239E00();
};

void Rva00239E00HordeContain::rva00239E00()
{
	Object *obj = getObject();
	const Coord3D *pos = obj->getPosition();
	Bool onBridge = false;
	if (!TheAI->pathfinder()->bfmeGroundCellThreshold(pos, false))
	{
		if (!((Bfme5BridgeList *)TheAI->pathfinder())->bfmeAnyBridgeAt(pos))
			return;
		onBridge = true;
	}

	Object *wall;
	{
		KindOfMaskType mask;
		mask.set(KINDOF_WALK_ON_TOP_OF_WALL);
		wall = ThePartitionManager->getClosestObject(pos, 150.0f, FROM_CENTER_3D,
			&PartitionFilterAcceptByKindOf(mask, KINDOFMASK_NONE));
	}
	if (wall)
	{
		static NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
		Module *dock = wall->findModule(key);
		if (dock && ((BfmeThingBQA *)dock)->bfmeGoBQA())
		{
			Int best = 0;
			{
				Real bestDist = 1000000.0f;
				for (Int i = 0; i < ((BfmeThingBQA *)dock)->bfmeGoBQA(); ++i)
				{
					Rva002060B0Triple delta = ((Rva002060B0Owner *)dock)->copyAt(i);
					delta.x -= pos->x;
					delta.y -= pos->y;
					delta.z -= pos->z;
					Real dx = fabs(delta.x);
					Real dy = fabs(delta.y);
					Real dist;
					if (dx > dy)
						dist = dx + dy * 0.25f;
					else
						dist = dy + dx * 0.25f;
					if (dist < bestDist)
					{
						bestDist = dist;
						best = i;
					}
				}
			}
			{
				Coord2D dir;
				dir.x = -((Rva00206100Owner *)dock)->point(best).x;
				dir.y = -((Rva00206100Owner *)dock)->point(best).y;
				obj->setOrientation(dir.toAngle());
			}
		}
		else if (!onBridge)
		{
			obj->setOrientation(wall->getOrientation() + wall->getTemplate()->getReal404());
		}
		m_flag04 = true;
	}
	setWakeFrame(obj, UPDATE_SLEEP_NONE);
}
