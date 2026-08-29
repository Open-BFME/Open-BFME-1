// ?clearRemovableForConstruction@BuildAssistant@@IAEXPBVThingTemplate@@PBUCoord3D@@M@Z
// partial score=0.7 date=2026-08-29
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"

#include "Common/BuildAssistant.h"

class SimpleObjectIterator
{
public:
	Object *first(void)
	{
		return next();
	}

	Object *next(void)
	{
		char *current = m_current;
		char *end = m_end;
		if (end == current)
			return NULL;

		Object *obj = *reinterpret_cast<Object **>(current);
		current += 8;
		m_current = current;
		return obj;
	}

	void deleteInstance(void);

private:
	char *m_begin;
	char *m_end;
	char *m_capacity;
	char *m_current;
	Int m_refCount;
};

class PartitionFilter
{
public:
	PartitionFilter() : m_base(0) { }
	virtual ~PartitionFilter() { }
	virtual Bool allow(Object *obj) = 0;

private:
	UnsignedInt m_base;
};

class PartitionFilterWouldCollide : public PartitionFilter
{
public:
	PartitionFilterWouldCollide(const Coord3D &pos, const void *geometry,
		Real angle, Bool desired)
	{
		m_position.x = pos.x;
		m_position.y = pos.y;
		m_position.z = pos.z;
		m_geometry = geometry;
		m_angle = angle;
		m_desired = desired;
	}

	virtual ~PartitionFilterWouldCollide() { }
	virtual Bool allow(Object *obj)
	{
		return false;
	}

private:
	Coord3D m_position;
	const void *m_geometry;
	Real m_angle;
	Byte m_desired;
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
	void getClosestObjects(SimpleObjectIterator *&iter, const Coord3D *pos,
		Real maxDist, DistanceCalculationType dc, PartitionFilter *filter,
		Object *ignore);
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern PartitionManager *ThePartitionManager;
extern GameLogic *TheGameLogic;

extern void bfmeIteratorDelete(void *object);
extern void bfmeIteratorFreeSmall(void *begin, Int bytes);

class RetailOverridableCall
{
public:
	const Overridable *getFinalOverride(void) const;
};

void SimpleObjectIterator::deleteInstance(void)
{
	if (--m_refCount == 0)
	{
		char *begin = m_begin;
		if (begin)
		{
			Int bytes = (m_capacity - begin) >> 3;
			bytes <<= 3;
			if (bytes > 0x80)
				bfmeIteratorDelete(begin);
			else
				bfmeIteratorFreeSmall(begin, bytes);
		}
		bfmeIteratorDelete(this);
	}
}

static const unsigned char *finalTemplate(const Object *obj)
{
	const Overridable *tmpl = *reinterpret_cast<const Overridable *const *>(
		reinterpret_cast<const char *>(obj) + 4);
	const Overridable *next = tmpl ? *reinterpret_cast<const Overridable *const *>(
		reinterpret_cast<const char *>(tmpl) + 4) : NULL;
	if (next)
		tmpl = reinterpret_cast<const RetailOverridableCall *>(next)->getFinalOverride();
	return reinterpret_cast<const unsigned char *>(tmpl);
}

// ?clearRemovableForConstruction@BuildAssistant@@IAEXPBVThingTemplate@@PBUCoord3D@@M@Z
void BuildAssistant::clearRemovableForConstruction(const ThingTemplate *whatToBuild,
	const Coord3D *pos, Real angle)
{
	SimpleObjectIterator *iter;
	{
		PartitionFilterWouldCollide filter(*pos,
			reinterpret_cast<const char *>(whatToBuild) + 0x60, angle, true);
		ThePartitionManager->getClosestObjects(iter, pos,
			*reinterpret_cast<const Real *>(reinterpret_cast<const char *>(whatToBuild) + 0x74) * 1.1f,
			FROM_BOUNDINGSPHERE_3D, &filter, NULL);
	}

	Object *them;
	while ((them = iter->next()) != NULL)
	{
		const unsigned char *tmpl = finalTemplate(them);
		if ((*reinterpret_cast<const UnsignedInt *>(tmpl + 0xd0) & 0x01000000) != 0)
			continue;

		tmpl = finalTemplate(them);
		if ((tmpl[0xc8] & 0x40) != 0)
			goto destroy;

		tmpl = finalTemplate(them);
		if ((*reinterpret_cast<const UnsignedInt *>(tmpl + 0xcc) & 0x00040000) == 0
			&& (*reinterpret_cast<const Byte *>(reinterpret_cast<const char *>(them) + 0x344) & 1) == 0)
			continue;

		tmpl = finalTemplate(them);
		if ((*reinterpret_cast<const UnsignedInt *>(tmpl + 0xcc) & 0x02000000) != 0)
			continue;

	destroy:
		TheGameLogic->destroyObject(them);
	}

	iter->deleteInstance();
}
