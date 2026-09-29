// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Water polygon initializer 0x007A4D40: copies the source record, converts its points and collects six texture prototypes.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <new>
#include <set>
#include "ascii_string.h"

typedef int Int;

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	__forceinline void set(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
};

class AABoxClass
{
public:
	AABoxClass(void) {}
	AABoxClass(Vector3 *points, Int count);

	Vector3 Center;
	Vector3 Extent;
};

class BfmeOtherDOA;

// 0x00190560 copy-constructs the AsciiString at this+0x48+index*4 into the
// hidden return slot and returns it (ret 8).
class BfmeThingDOA
{
public:
	BfmeOtherDOA *bfmeGoDOA(BfmeOtherDOA *other, Int index);
};

typedef AsciiString (BfmeThingDOA::*Rva007A4D40TextureGetter)(Int index);

enum WaterTextureIndex
{
	WATER_TEXTURE_0 = 0
};

class Rva007A1230ArrayOwner
{
public:
	virtual ~Rva007A1230ArrayOwner(void);
	void rva007A4D40(void *source);
	void setTexture(const AsciiString &name, WaterTextureIndex index);

private:
	void releaseOwnedState(void);

	unsigned char m_flag04;
	unsigned char m_padding05[3];
	void *m_field08;
	AsciiString m_textureNames[6];
	unsigned char m_textureReferences[0x18];
	unsigned char m_flag3c;
	unsigned char m_padding3d[3];
	Vector3 m_position40;
	unsigned int m_value4c;
	unsigned int m_value50;
	Vector3 *m_pointStorage;
	Int m_pointCount;
	unsigned int m_value5c;
	unsigned int m_value60;
	unsigned char m_boundsValid;
	unsigned char m_padding65[3];
	AABoxClass m_bounds;
};

typedef char Rva007A1230ArrayOwnerSizeCheck[
	(sizeof(Rva007A1230ArrayOwner) == 0x80) ? 1 : -1];

struct Rva007A4D40Point
{
	Int X;
	Int Y;
	Int Z;
};

struct Rva007A4D40Source
{
	unsigned char m_padding00[0x10];
	Rva007A4D40Point *m_points;
	Int m_pointCount;
	unsigned char m_padding18[0x28];
	unsigned char m_flag40;
	unsigned char m_padding41[3];
	void *m_field44;
	unsigned char m_padding48[0x18];
	unsigned char m_flag60;
	unsigned char m_padding61[3];
	Vector3 m_position64;
	unsigned int m_value70;
	unsigned int m_value74;
	unsigned char m_padding78[4];
	unsigned int m_value7c;

	__forceinline unsigned char getFlag40(void) const { return m_flag40; }
	__forceinline void *getField44(void) const { return m_field44; }
	__forceinline unsigned char getFlag60(void) const { return m_flag60; }

	// Clamped point access, as Zero Hour's PolygonTrigger::getPoint.
	__forceinline const Rva007A4D40Point *getPoint(Int index) const
	{
		if (index < 0)
			index = 0;
		if (index >= m_pointCount)
			index = m_pointCount - 1;
		return m_points + index;
	}
};

extern void *bfmeGoEMEb(void *name);
extern void Rva009EBAC0(Int assets);

struct Rva0013FA60Target;
typedef Rva0013FA60Target *Rva0013FA60Key;

typedef _STL::_Rb_tree<Rva0013FA60Key,
	Rva0013FA60Key,
	_STL::_Identity<Rva0013FA60Key>,
	_STL::less<Rva0013FA60Key>,
	_STL::allocator<Rva0013FA60Key> > Rva0013FA60Tree;

typedef _STL::pair<Rva0013FA60Tree::iterator, bool> Rva007A4D40InsertResult;

// Matched out of line at 0x0013FA60; declared so this TU calls it.
template <>
Rva007A4D40InsertResult Rva0013FA60Tree::insert_unique(const Rva0013FA60Key &key);

struct Rva007A4D40TreeHeader
{
	unsigned char m_color;
	unsigned char m_padding01[3];
	void *m_parent;
	void *m_left;
	void *m_right;
};

struct Rva0013FA60Set
{
	__forceinline Rva007A4D40InsertResult insert(const Rva0013FA60Key &key)
	{
		return reinterpret_cast<Rva0013FA60Tree *>(this)->insert_unique(key);
	}

	Rva007A4D40TreeHeader *m_header;
	unsigned int m_nodeCount;
	unsigned int m_keyCompare;
};

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;

typedef _STL::_Rb_tree<Rva001408C0Key,
	Rva001408C0Key,
	_STL::_Identity<Rva001408C0Key>,
	_STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Tree;

// Matched out of line at 0x00140950; declared so this TU calls it.
template <>
Rva001408C0Tree::~_Rb_tree();

typedef char Rva0013FA60SetSizeCheck[
	(sizeof(Rva0013FA60Set) == 12) ? 1 : -1];

struct Rva007A4D40AssetList
{
	__forceinline Rva007A4D40AssetList(void)
	{
		m_prototypes.m_header = 0;
		m_prototypes.m_header = (Rva007A4D40TreeHeader *)
			_STL::__node_alloc<true, 0>::allocate(0x14);
		m_prototypes.m_nodeCount = 0;
		m_prototypes.m_header->m_color = 0;
		m_prototypes.m_header->m_parent = 0;
		m_prototypes.m_header->m_left = m_prototypes.m_header;
		m_prototypes.m_header->m_right = m_prototypes.m_header;
		m_treeLayoutPad = 0;
		m_changed = true;
	}

	__forceinline ~Rva007A4D40AssetList(void)
	{
		reinterpret_cast<Rva001408C0Tree *>(&m_prototypes)->~Rva001408C0Tree();
	}

	__forceinline void addName(const char *name)
	{
		Rva0013FA60Key prototype = (Rva0013FA60Key)bfmeGoEMEb(
			(void *)name);
		Rva007A4D40InsertResult inserted = m_prototypes.insert(prototype);
		if (inserted.second)
			m_changed = true;
	}

	Rva0013FA60Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

void Rva007A1230ArrayOwner::rva007A4D40(void *source)
{
	Rva007A4D40Source *record = (Rva007A4D40Source *)source;

	releaseOwnedState();

	m_flag04 = record->getFlag40();
	m_field08 = record->getField44();
	m_flag3c = record->getFlag60();
	m_position40 = record->m_position64;
	m_value4c = record->m_value70;
	m_value50 = record->m_value74;
	m_value60 = record->m_value7c;

	Int pointCount = record->m_pointCount;
	m_pointCount = pointCount;
	m_pointStorage = new Vector3[pointCount];

	for (Int pointIndex = 0;
		m_pointStorage != 0 && pointIndex < m_pointCount;
		++pointIndex)
	{
		const Rva007A4D40Point *point = record->getPoint(pointIndex);
		m_pointStorage[pointIndex].set((float)point->X, (float)point->Y,
			(float)point->Z);
	}

	if (!m_boundsValid)
	{
		AABoxClass bounds(m_pointStorage, m_pointCount);
		unsigned int *bits = (unsigned int *)&m_bounds;
		const unsigned int *boundsBits = (const unsigned int *)&bounds;
		bits[0] = boundsBits[0];
		bits[1] = boundsBits[1];
		bits[2] = boundsBits[2];
		bits[3] = boundsBits[3];
		bits[4] = boundsBits[4];
		bits[5] = boundsBits[5];
		m_boundsValid = 1;
	}

	Rva007A4D40AssetList assets;
	for (Int index = 0; index < 6; ++index)
	{
		BfmeThingDOA *textures = reinterpret_cast<BfmeThingDOA *>(record);
		Rva007A4D40TextureGetter getTexture =
			reinterpret_cast<Rva007A4D40TextureGetter>(&BfmeThingDOA::bfmeGoDOA);
		setTexture((textures->*getTexture)(index), (WaterTextureIndex)index);
		assets.addName((textures->*getTexture)(index).str());
	}

	Rva009EBAC0((Int)&assets);
}
