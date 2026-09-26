// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object
// stlport
//
// ?rva00371b00@CastleBehavior@@QAE_NXZ
//
// Retail 0x00371B00, 419 bytes.
//
// Owner: the CastleBehavior constructor (0x00376250) installs vftable
// 0x010E9B28 at this+0x10.  Its slot 0 is ILT 0x0001B7AC -> 0x00377740, and
// that body calls this one through ILT 0x0000B7FD at 0x003778DE with
// ecx = its own this-0x10 (the CastleBehavior), then tests AL.  The same
// body hands the same pointer to the landed CastleBehavior::rva00371ee0
// through ILT 0x00026094.  Nothing names the method, so it keeps its address.
//
// The body returns false until TheGameLogic's frame reaches a threshold
// (GlobalData+0x11F8 times 5.0, or 25.0 with no GlobalData).  It then
// recomputes the +0xA5 flag from the object at +0xA0: effectively dead,
// model-condition bits 66 or 59, or bit 67 when its builder (Object+0x7C) is
// gone or is an effectively dead KINDOF_DOZER.  With the flag clear
// it returns false.
// Otherwise it walks the ObjectID vectors at +0xB8 and +0xDC (the destructor
// 0x003728E0 frees vectors at both offsets) and returns false for the first
// object whose template lacks bit 0x200000 at +0xD8 and whose
// ProjectileUpdateInterface answers true from vtable slot +0xC.
//
// Retail's flag test and both walks exit through one shared "return false"
// (EBX saved before the flag test).  Written as one OR-ed condition, with an
// inline scan per vector, VC7.1 reproduces that; separate returns fold the
// flag test's return into the frame test's early exit instead.
//
// Callees (tools/callees.py): __ftol2; GameLogic::findObjectByID via ILT
// 0x0001F253 (x4); Thing::isKindOf via ILT 0x0003251F; Overridable::
// getFinalOverride via ILT 0x000022BB (x2); Object::
// getProjectileUpdateInterface via ILT 0x0000DE9F (x2).

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;
typedef int ObjectID;

// The call site pushes 0xE; BFME's own KindOf name table (.data RVA
// 0x00EAA068: OBSTACLE, SELECTABLE, IMMOBILE, ...) gives index 14 = DOZER,
// as SelectionInfo_addDrawableToList.cpp and AIUpdatePathPriority.cpp use.
enum KindOfType { KINDOF_DOZER = 14 };

class ThingTemplate;
class ProjectileUpdateInterface;

#define BFME_HAVE_OBJECTID
#define THING_TU_MEMBERS \
	const ThingTemplate *getTemplate() const; \
	Bool isKindOf(KindOfType t) const;
#define OBJECT_TU_MEMBERS \
	ProjectileUpdateInterface *getProjectileUpdateInterface() const;
#include "object.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled008[0xD8 - 0x08];
	UnsignedInt m_unmodelledD8;
};

// Same getTemplate as Thing_isKindOf.cpp: null stays null, one level of the
// override chain unrolled.
inline const ThingTemplate *Thing::getTemplate() const
{
	const ThingTemplate *tmpl = m_template;
	if (tmpl == 0)
		return 0;
	if (tmpl->m_nextOverride)
		tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

class ProjectileUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual Bool slot0C();
};

class GlobalData
{
public:
	unsigned char m_unmodelled0000[0x11F8];
	Real m_unmodelled11F8;
};

extern GlobalData *TheWritableGlobalData;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

	unsigned char m_unmodelled00[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class CastleBehavior
{
public:
	Bool rva00371b00();

private:
	unsigned char m_unmodelled00[0xA0];
	ObjectID m_objectID;
	unsigned char m_unmodelledA4;
	Bool m_flagA5;
	unsigned char m_unmodelledA6[0xB8 - 0xA6];
	_STL::vector<ObjectID> m_objectIDsB8;
	unsigned char m_unmodelledC4[0xDC - 0xC4];
	_STL::vector<ObjectID> m_objectIDsDC;
};

static __forceinline Bool rva00371b00AnyQueryTrue(const _STL::vector<ObjectID> &ids)
{
	for (_STL::vector<ObjectID>::const_iterator it = ids.begin(); it != ids.end(); ++it)
	{
		Object *object = TheGameLogic->findObjectByID(*it);
		if (object == 0)
			continue;
		if (object->getTemplate()->m_unmodelledD8 & 0x200000)
			continue;
		ProjectileUpdateInterface *projectile = object->getProjectileUpdateInterface();
		if (projectile && projectile->slot0C())
			return true;
	}
	return false;
}

Bool CastleBehavior::rva00371b00()
{
	GlobalData *data = TheWritableGlobalData;
	GameLogic *logic = TheGameLogic;
	UnsignedInt frame = logic->m_frame;
	UnsignedInt threshold = (UnsignedInt)(Int)(data ? data->m_unmodelled11F8 * 5.0f : 25.0f);
	if (frame < threshold)
		return false;

	Object *object = logic->findObjectByID(m_objectID);
	if (object == 0)
	{
		m_flagA5 = true;
	}
	else
	{
		m_flagA5 = false;
		if (object->m_privateStatus & 1)
			m_flagA5 = true;
		if (object->m_modelConditionFlags[2] & 4)
			m_flagA5 = true;
		if (object->m_modelConditionFlags[2] & 8)
		{
			Object *builder = TheGameLogic->findObjectByID(object->m_builderID);
			if (builder == 0 ||
				((builder->m_privateStatus & 1) && builder->isKindOf(KINDOF_DOZER)))
				m_flagA5 = true;
		}
		if (object->m_modelConditionFlags[1] & 0x8000000)
			m_flagA5 = true;
	}

	if (!m_flagA5 || rva00371b00AnyQueryTrue(m_objectIDsB8) || rva00371b00AnyQueryTrue(m_objectIDsDC))
		return false;
	return true;
}
