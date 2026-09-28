// stlport
#include <vector>

class BfmeBaseETC
{
public:
	void bfmeAETC(void *a, void *b, void *c);
	void bfmeCETC(void *a, void *b, void *c, void *d);
};

class BfmeHostETC
{
public:
	virtual void bfmeSlot00ETC();
	virtual void bfmeSlot01ETC();
	virtual void bfmeSlot02ETC();
	virtual void bfmeSlot03ETC();
	virtual void bfmeSlot04ETC();
	virtual void bfmeSlot05ETC();
	virtual void bfmeSlot06ETC();
	virtual void *bfmeSlot07ETC(void *a, void *b, void *c, void *d, int zero, void *e);

	void *bfmeRunETC(void *unused, void *a, void *b, void *c, void *d, void *e);
};

void *BfmeHostETC::bfmeRunETC(void *unused, void *a, void *b, void *c, void *d,
	void *e)
{
	if (a == 0 || b == 0 || d == 0)
		return 0;

	BfmeBaseETC *base = (BfmeBaseETC *)((char *)this - 0x20);

	base->bfmeAETC(a, b, c);

	void *result = bfmeSlot07ETC(a, b, c, d, 0, e);

	base->bfmeCETC(a, b, c, d);

	return result;
}

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vptr;
	Overridable *m_nextOverride;
};

class GeometryInfo
{
public:
	Real getBoundingSphereRadius() const
	{
		return m_boundingSphereRadius;
	}

private:
	unsigned char m_pad[0x14];
	Real m_boundingSphereRadius;
};

enum KindOfMask
{
	KINDOF_SHRUBBERY_MASK = 0x00000040,
	KINDOF_CLEARED_BY_BUILD_MASK = 0x00040000,
	KINDOF_ALWAYS_SELECTABLE_MASK = 0x02000000,
	KINDOF_INERT_MASK = 0x01000000
};

// Retail stores geometry at +0x60 and the three kind words at +0xC8.
class ThingTemplate : public Overridable
{
public:
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

// Retail stores the template pointer at +0x04 and the status byte at +0x344.
class Object
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

	UnsignedInt getKindOfWord(Int word) const
	{
		return getTemplate()->getKindOfWord(word);
	}

	UnsignedInt getStatusBits() const
	{
		return *reinterpret_cast<const unsigned char *>(
			reinterpret_cast<const char *>(this) + 0x344);
	}

private:
	void *m_vptr;
	const ThingTemplate *m_template;
};

// Each result entry stores an object pointer and a distance as two dwords.
struct SimpleObjectIteratorClump
{
	Int m_valueBits;
	Int m_distanceBits;
};

struct SimpleObjectIterator
{
	_STL::vector<SimpleObjectIteratorClump> m_entries;
	SimpleObjectIteratorClump *m_cursor;
	Int m_refCount;
};

struct BfmeWideResult
{
	SimpleObjectIterator *m_mpo;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);

	Object *next() const
	{
		if (m_mpo->m_cursor == m_mpo->m_entries.end())
			return 0;
		SimpleObjectIteratorClump *cursor = m_mpo->m_cursor;
		Object *object = reinterpret_cast<Object *>(cursor->m_valueBits);
		++cursor;
		m_mpo->m_cursor = cursor;
		return object;
	}

	~BfmeWideResult()
	{
		if (--m_mpo->m_refCount == 0)
			delete m_mpo;
	}
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

	operator Int()
	{
		return (Int)this;
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
};

class BfmeWideForwardC
{
private:
	unsigned char m_pad[0x0c];
	void *m_source;

public:
	BfmeWideResult bfmeForwardWideC(Int a, Real b, Int c, Int d, Int e);
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern PartitionManager *ThePartitionManager;
extern GameLogic *TheBfmeGameLogic;

void BfmeBaseETC::bfmeAETC(void *a, void *b, void *c)
{
	const ThingTemplate *whatToBuild = (const ThingTemplate *)a;
	const Coord3D *pos = (const Coord3D *)b;
	Real angle = *(Real *)&c;
	const BfmeWideResult &found =
		((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
			(Int)pos,
			whatToBuild->getTemplateGeometryInfo()->
				getBoundingSphereRadius() * 1.1f,
			FROM_BOUNDINGSPHERE_3D,
			PartitionFilterWouldCollide(*pos,
				whatToBuild->getTemplateGeometryInfo(), angle, true),
			0);
	Object *them;
	while ((them = found.next()) != 0)
	{
		if ((them->getKindOfWord(2) & KINDOF_INERT_MASK) != 0)
			continue;

		if ((them->getKindOfWord(0) & KINDOF_SHRUBBERY_MASK) == 0
			&& (them->getKindOfWord(1) & KINDOF_CLEARED_BY_BUILD_MASK) == 0
			&& (them->getStatusBits() & 1) == 0)
			continue;

		if ((them->getKindOfWord(1) & KINDOF_ALWAYS_SELECTABLE_MASK) != 0)
			continue;

		TheBfmeGameLogic->destroyObject(them);
	}
}
