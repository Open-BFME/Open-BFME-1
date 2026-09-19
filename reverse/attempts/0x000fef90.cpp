// ?run@Rva000FEF90Task@@QAE_NPAUResultData@@PAX1PAVObjectRelationView@@1@Z
// partial score=0.4 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x000FEF90 candidate retained with its result-vector and filter ABI.

typedef int Int;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class ThingTemplate;

struct ResultEntry
{
	Object *object;
	unsigned int unknown;
};

struct ResultData
{
	ResultEntry *begin;
	ResultEntry *end;
	ResultEntry *capacity;
	ResultEntry *current;
	Int references;
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask() { return 0; }

	PartitionFilter *link(PartitionFilter *next)
	{
		m_next = next;
		return this;
	}

	PartitionFilter *m_next;
};

class Rva000FEF90Filter : public PartitionFilter
{
public:
	Rva000FEF90Filter() : m_head(0), m_context(0), m_relation(0),
		m_match(true), m_state(0) {}
	virtual ~Rva000FEF90Filter() {}
	virtual Bool allow(Object *) { return false; }

	void *m_head;
	void *m_context;
	void *m_relation;
	Bool m_match;
	Int m_state;
};

class PartitionManager
{
public:
	ResultData bfmeForwardWideC(const Coord3D *, Real, Int,
		PartitionFilter *, Bool);
};

class ObjectView
{
public:
	const ThingTemplate *getTemplate() const
	{
		return *(const ThingTemplate **)((const char *)this + 4);
	}

	ObjectView *next() const
	{
		return *(ObjectView **)((const char *)this + 0x88);
	}

	const Coord3D *position() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	Bool held() const
	{
		return (*(const unsigned char *)((const char *)this + 0x90) & 1) != 0;
	}
};

class ThingTemplateView
{
public:
	const ThingTemplate *finalOverride() const;
};

class ProjectileInterface
{
public:
	virtual void slot00() = 0;
	virtual Bool isRecruitable() = 0;
};

class ObjectRelationView
{
public:
	Int relationship(const Object *other) const;
	ProjectileInterface *projectileUpdate() const;
};

extern PartitionManager *ThePartitionManager;
extern "C" void j_000022bb();
extern "C" void j_00004a719();
extern "C" void j_0000de9f();

static const ThingTemplate *finalOverride(const ThingTemplate *value)
{
	typedef const ThingTemplate *(ThingTemplateView::*Call)() const;
	union
	{
		void (*raw)();
		Call member;
	} call;
	call.raw = j_000022bb;
	return (((ThingTemplateView *)value)->*call.member)();
}

static Int relationship(const ObjectRelationView *value, const Object *other)
{
	typedef Int (ObjectRelationView::*Call)(const Object *) const;
	union
	{
		void (*raw)();
		Call member;
	} call;
	call.raw = j_00004a719;
	return (((ObjectRelationView *)value)->*call.member)(other);
}

static ProjectileInterface *projectileUpdate(const Object *value)
{
	typedef ProjectileInterface *(ObjectRelationView::*Call)() const;
	union
	{
		void (*raw)();
		Call member;
	} call;
	call.raw = j_0000de9f;
	return (((ObjectRelationView *)value)->*call.member)();
}

static void destroyResult(ResultData *result)
{
	if (--result->references == 0)
	{
		if (result->begin != 0)
			::operator delete(result->begin);
		result->begin = 0;
		result->end = 0;
		result->capacity = 0;
	}
}

class Rva000FEF90Task
{
public:
	Bool run(ResultData *, void *, void *, ObjectRelationView *, void *);
};

// ?run@Rva000FEF90Task@@QAE_NPAUResultData@@PAX1PAVObjectRelationView@@1@Z
Bool Rva000FEF90Task::run(ResultData *result, void *context, void *unused,
	ObjectRelationView *relationOwner, void *unused2)
{
	Rva000FEF90Filter filter;
	filter.m_context = context;
	filter.m_relation = relationOwner;
	filter.m_match = true;
	*result = ThePartitionManager->bfmeForwardWideC(
		(const Coord3D *)((const char *)context + 0x60),
		*(const Real *)((const char *)context + 0x74), 3,
		filter.link(0), true);

	while (result->current != result->end)
	{
		ObjectView *object = (ObjectView *)result->current->object;
		++result->current;
		if (object == 0 || object->held())
			continue;

		const ThingTemplate *templateValue = object->getTemplate();
		if (templateValue == 0)
			continue;
		const ThingTemplate *overrideValue = finalOverride(templateValue);
		if (overrideValue == 0)
			continue;
		if (relationship(relationOwner, (const Object *)object) != 2)
			continue;
		ProjectileInterface *projectile = projectileUpdate(
			(const Object *)object);
		if (projectile != 0 && projectile->isRecruitable())
			continue;

		const Coord3D *position = object->position();
		Real dx = position->x - ((const Coord3D *)context)->x;
		Real dy = position->y - ((const Coord3D *)context)->y;
		Real dz = position->z - ((const Coord3D *)context)->z;
		Real distance = dx * dx + dy * dy + dz * dz;
		if (distance > *(Real *)unused2)
			continue;
		*(Real *)unused2 = distance;
		--result->references;
		if (result->references == 0)
			destroyResult(result);
		return true;
	}

	destroyResult(result);
	return false;
}
