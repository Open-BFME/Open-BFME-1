// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Igame/GameEngine/Source /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// The matched HordeContain constructor at RVA 0x0023EAF0 installs vtable
// 0x010AED58 at this+0xE4. Vtable slot 118 points through ILT 0x00003008
// to this body at RVA 0x00239E00. AODHordeContain and HorseHordeContain use
// the same slot. No caller or string names the method, so it keeps its
// address-derived name.
//
// The body checks whether the owning object stands on walkable ground or a
// bridge. It then finds the closest WALK_ON_TOP_OF_WALL object within 150
// units. If that object has a SiegeDockingBehavior module with dock points,
// the body turns away from the nearest point using an octagonal distance
// weighted by 0.25. Otherwise, the body adds the wall's orientation to the
// owning template's angle at offset 0x404 when the object is off a bridge.
// The body sets the interface flag and wakes the module after it finds a wall.
//
// The shared UpdateModule accessor reads the Object pointer at this-0xD8.
// Retail reads the module's Object pointer at module+0x08, or interface-0xDC.
// The local accessor reads that measured retail field.

#define _STLP_NO_EXCEPTIONS 1
#include <math.h>
#include "GameLogic/Module/UpdateModule.h"
#include "Common/Overridable.h"
#include "Common/BitFlags.h"

#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS \
	const Coord3D *getPosition() const { return &m_cachedPos; } \
	Real getOrientation() const { return m_cachedAngle; } \
	void setOrientation(Real angle); \
	const ThingTemplate *getTemplate() const \
	{ \
		if (!m_template) \
			return 0; \
		return (const ThingTemplate *)((const Overridable *)m_template)->getFinalOverride(); \
	} \
	Real getTemplateReal404() const { return *(const Real *)((const char *)getTemplate() + 0x404); }
#define OBJECT_TU_MEMBERS \
	Module *findModule(NameKeyType key) const;
#include "GameLogic/Object/object.h"


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

// Whatever HordeContain's primary chain adds up to its +0xE4 interface.
class Rva00239E00HordeHead : public UpdateModule
{
protected:
	Object *getObject() const { return *(Object **)((const char *)this + 8); }

private:
	unsigned char m_unmodelled[0xE4 - sizeof(UpdateModule)];
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
	Bool onBridge = false;
	if (!TheAI->pathfinder()->bfmeGroundCellThreshold(obj->getPosition(), false))
	{
		if (!((Bfme5BridgeList *)TheAI->pathfinder())->bfmeAnyBridgeAt(obj->getPosition()))
			return;
		onBridge = true;
	}
	const Coord3D *pos = obj->getPosition();

	Object *wall;
	{
		KindOfMaskType mask;
		mask.set(59);
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
			obj->setOrientation(wall->getOrientation() + wall->getTemplateReal404());
		}
		m_flag04 = true;
	}
	setWakeFrame(obj, UPDATE_SLEEP_NONE);
}
