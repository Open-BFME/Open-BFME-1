// ?clearRemovableForConstruction@BuildAssistant@@IAEXPBVThingTemplate@@PBUCoord3D@@M@Z
// partial score=0.8 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// readable body of ?clearRemovableForConstruction@BuildAssistant@@: Code/GameEngine/Source/Common/System/BuildAssistant.cpp

// BuildAssistant::clearRemovableForConstruction, retail 0x000FF4D0 (438 bytes).
//
// BFME inlines the collision iterator query, the whole of
// isRemovableForConstruction (its own out-of-line copy is matched at
// 0x000FE5D0) and the iterator release into this one body, so the vendored
// Zero Hour headers cannot be included: they carry a different Object layout.
// The offsets used here are BFME's own.  ThingTemplate::m_kindof is an array
// of three dwords at +0xc8, so KINDOF_SHRUBBERY is bit 6 of the first word,
// KINDOF_CLEARED_BY_BUILD bit 18 of the second, KINDOF_ALWAYS_SELECTABLE bit
// 25 of the second and KINDOF_INERT bit 24 of the third.  Object's
// effectively-dead flag is the low bit of the status byte at +0x344.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#define NULL 0

class SimpleObjectIterator;

// STLport's node allocator owns every small buffer; the iterator's own vector
// releases through it, and hands anything over 128 bytes to ::operator delete.
namespace _STL
{
	template <bool __threads, int __inst>
	class __node_alloc
	{
		static void _M_deallocate(void *__p, unsigned int __n);
		friend class ::SimpleObjectIterator;
	};
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *_vptr;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GeometryInfo.h
class GeometryInfo
{
public:
	Real getBoundingCircleRadius() const
	{
		return m_boundingCircleRadius;
	}

private:
	unsigned char m_pad[0x14];
	Real m_boundingCircleRadius;
};

enum KindOfMask
{
	KINDOF_SHRUBBERY_MASK = 0x00000040,
	KINDOF_CLEARED_BY_BUILD_MASK = 0x00040000,
	KINDOF_ALWAYS_SELECTABLE_MASK = 0x02000000,
	KINDOF_INERT_MASK = 0x01000000
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	// The kind flags live in three words at +0xc8.  KINDOF_SHRUBBERY is index
	// 6 of the first word, KINDOF_CLEARED_BY_BUILD index 18 and
	// KINDOF_ALWAYS_SELECTABLE index 25 of the second, KINDOF_INERT index 24
	// of the third.  Retail tests the word against the literal mask.
	UnsignedInt getKindOfWord(Int word) const
	{
		return m_kindof[word];
	}

	const GeometryInfo *getTemplateGeometryInfo() const
	{
		return &m_geometryInfo;
	}

private:
	unsigned char m_pad[0x58];
	GeometryInfo m_geometryInfo;
	unsigned char m_pad2[0x50];
	UnsignedInt m_kindof[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl != 0 && tmpl->m_nextOverride != 0)
			tmpl = static_cast<const ThingTemplate *>(
				tmpl->m_nextOverride->getFinalOverride());
		return tmpl;
	}

private:
	void *_vptr;
	const ThingTemplate *m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	UnsignedInt getKindOfWord(Int word) const
	{
		return getTemplate()->getKindOfWord(word);
	}

	UnsignedInt getStatusBits() const
	{
		return *reinterpret_cast<const unsigned char *>(
			reinterpret_cast<const char *>(this) + 0x344);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SimpleObjectIterator.h
// BFME walks a vector of eight-byte entries instead of Zero Hour's clump list.
class SimpleObjectIterator
{
public:
	Object *first(void)
	{
		return next();
	}

	Object *next(void)
	{
		if (m_current == m_end)
			return NULL;

		char *cur = m_current;
		Object *obj = *reinterpret_cast<Object **>(cur);
		cur += 8;
		m_current = cur;
		return obj;
	}

	void deleteInstance(void)
	{
		--m_refCount;
		if (m_refCount == 0)
		{
			char *begin = m_begin;
			if (begin != NULL)
			{
				Int bytes = ((m_capacity - begin) >> 3) << 3;
				if (bytes > 0x80)
					::operator delete(begin);
				else
					_STL::__node_alloc<true, 0>::_M_deallocate(begin, bytes);
			}
			::operator delete(this);
		}
	}

private:
	char *m_begin;
	char *m_end;
	char *m_capacity;
	char *m_current;
	Int m_refCount;
};

// Retail opens an unwind state for the iterator the instant the query returns,
// before the filter it was given is destroyed, and releases it through the
// same inlined deleteInstance at the end of the body.
class MemoryPoolObjectHolder
{
public:
	MemoryPoolObjectHolder(SimpleObjectIterator *iter) : m_mpo(iter) { }

	__forceinline ~MemoryPoolObjectHolder()
	{
		if (m_mpo != NULL)
			m_mpo->deleteInstance();
	}

private:
	SimpleObjectIterator *m_mpo;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
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
	PartitionFilterWouldCollide(const Coord3D &pos, const GeometryInfo *geometry,
		Real angle, Bool desired)
	{
		m_position.x = pos.x;
		m_position.y = pos.y;
		m_position.z = pos.z;
		m_geometry = geometry;
		m_angle = angle;
		m_desired = desired;
	}

	virtual Bool allow(Object *obj)
	{
		return false;
	}

private:
	Coord3D m_position;
	const GeometryInfo *m_geometry;
	Real m_angle;
	Bool m_desired;
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
	void getClosestObjects(SimpleObjectIterator *&result, const Coord3D *pos,
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

// The Zero Hour spelling of the query, inlined into the one caller: the filter
// belongs to this scope, so retail destroys it after the handle it fills is
// already live.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BuildAssistant.h
class BuildAssistant
{
protected:
	void clearRemovableForConstruction(const ThingTemplate *whatToBuild,
		const Coord3D *pos, Real angle);
};

// ?clearRemovableForConstruction@BuildAssistant@@IAEXPBVThingTemplate@@PBUCoord3D@@M@Z
void BuildAssistant::clearRemovableForConstruction(const ThingTemplate *whatToBuild,
	const Coord3D *pos, Real angle)
{
	SimpleObjectIterator *found;
	{
		PartitionFilterWouldCollide filter(*pos,
			whatToBuild->getTemplateGeometryInfo(), angle, true);
		ThePartitionManager->getClosestObjects(found, pos,
			whatToBuild->getTemplateGeometryInfo()->getBoundingCircleRadius() * 1.1f,
			FROM_BOUNDINGSPHERE_3D, &filter, NULL);
	}
	Object *them;
	while ((them = found->next()) != NULL)
	{
		// UI feedback objects (always selectable) never get destroyed by
		// construction, and neither does anything isRemovableForConstruction
		// turns down.
		if ((them->getKindOfWord(2) & KINDOF_INERT_MASK) != 0)
			continue;

		if ((them->getKindOfWord(0) & KINDOF_SHRUBBERY_MASK) == 0
			&& (them->getKindOfWord(1) & KINDOF_CLEARED_BY_BUILD_MASK) == 0
			&& (them->getStatusBits() & 1) == 0)
			continue;

		if ((them->getKindOfWord(1) & KINDOF_ALWAYS_SELECTABLE_MASK) != 0)
			continue;

		TheGameLogic->destroyObject(them);
	}

	found->deleteInstance();
}
