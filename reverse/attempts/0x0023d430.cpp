// ?rva0023d430@Rva0023D430Owner@@QAEXPAUCoord3D@@0@Z
// partial score=0.24 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// Retail 0x0023D430, 598 bytes. The owner and operation remain address-derived.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class BfmeCalc919G
{
public:
	Int bfmeCalc919G();
};

class Object
{
public:
#define OBJECT_SLOT(N) virtual Int slot##N() = 0
	OBJECT_SLOT(00); OBJECT_SLOT(01); OBJECT_SLOT(02); OBJECT_SLOT(03);
	OBJECT_SLOT(04); OBJECT_SLOT(05); OBJECT_SLOT(06); OBJECT_SLOT(07);
	OBJECT_SLOT(08); OBJECT_SLOT(09);
	virtual BfmeCalc919G *getDrawable() const;
#undef OBJECT_SLOT

	unsigned char m_pad[0x8c];
	UnsignedInt m_status;
};

typedef _STL::list<Object *> BfmeMemberList;

struct BfmeMemberIndexNode
{
	UnsignedInt m_color;
	BfmeMemberIndexNode *m_parent;
	BfmeMemberIndexNode *m_next;
	BfmeMemberIndexNode *m_right;
	UnsignedInt m_key;
};

namespace _STL
{
struct _Rb_tree_node_base
{
};

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;

class BfmeGameLogic
{
public:
	__forceinline Object *findObjectByID(UnsignedInt key)
	{
		BfmeObjectPtrHash::iterator it = m_objectHash.find(key);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

	char m_head[0xb0];
	BfmeObjectPtrHash m_objectHash;
};

extern BfmeGameLogic *TheBfmeGameLogic;
extern Real g_bfmeDefaultBU;
extern Real g_bfmeUint32Scale;

class Rva0023D430MemberView
{
public:
#define MEMBER_SLOT(N) virtual Int slot##N() = 0
	MEMBER_SLOT(00); MEMBER_SLOT(01); MEMBER_SLOT(02); MEMBER_SLOT(03);
	MEMBER_SLOT(04); MEMBER_SLOT(05); MEMBER_SLOT(06); MEMBER_SLOT(07);
	MEMBER_SLOT(08); MEMBER_SLOT(09); MEMBER_SLOT(10); MEMBER_SLOT(11);
	MEMBER_SLOT(12); MEMBER_SLOT(13); MEMBER_SLOT(14); MEMBER_SLOT(15);
	MEMBER_SLOT(16); MEMBER_SLOT(17); MEMBER_SLOT(18); MEMBER_SLOT(19);
	MEMBER_SLOT(20); MEMBER_SLOT(21); MEMBER_SLOT(22); MEMBER_SLOT(23);
	MEMBER_SLOT(24); MEMBER_SLOT(25); MEMBER_SLOT(26); MEMBER_SLOT(27);
	MEMBER_SLOT(28); MEMBER_SLOT(29); MEMBER_SLOT(30); MEMBER_SLOT(31);
	MEMBER_SLOT(32); MEMBER_SLOT(33); MEMBER_SLOT(34); MEMBER_SLOT(35);
	MEMBER_SLOT(36); MEMBER_SLOT(37); MEMBER_SLOT(38); MEMBER_SLOT(39);
	MEMBER_SLOT(40); MEMBER_SLOT(41); MEMBER_SLOT(42); MEMBER_SLOT(43);
	MEMBER_SLOT(44); MEMBER_SLOT(45); MEMBER_SLOT(46); MEMBER_SLOT(47);
	MEMBER_SLOT(48); MEMBER_SLOT(49); MEMBER_SLOT(50); MEMBER_SLOT(51);
	MEMBER_SLOT(52); MEMBER_SLOT(53); MEMBER_SLOT(54); MEMBER_SLOT(55);
	MEMBER_SLOT(56); MEMBER_SLOT(57); MEMBER_SLOT(58); MEMBER_SLOT(59);
	MEMBER_SLOT(60); MEMBER_SLOT(61); MEMBER_SLOT(62); MEMBER_SLOT(63);
	MEMBER_SLOT(64);
	virtual const BfmeMemberList &getMemberList() const = 0;
#undef MEMBER_SLOT
};

enum PathfindLayerEnum
{
	Rva0023D430LayerInvalid = 0,
	Rva0023D430LayerGround = 1
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual Real getGroundHeight(Real, Real, Coord3D *);
	virtual Real getLayerHeight(Real, Real, PathfindLayerEnum, Coord3D *, Bool);
	PathfindLayerEnum getLayerForDestination(Object *, const Coord3D *);
};

extern TerrainLogic *TheTerrainLogic;

class Rva0023D430Owner
{
public:
	void rva0023d430(Coord3D *, Coord3D *);

private:
	char m_head[0x30];
	BfmeMemberIndexNode *m_memberIndex;
};

static void rva0023d430Accumulate(Coord3D &average, Int &count,
	Object *object)
{
	BfmeCalc919G *drawable = object->getDrawable();
	if (drawable != 0)
	{
		Real *matrix = (Real *)drawable->bfmeCalc919G();
		average.x += matrix[3];
		average.y += matrix[7];
		average.z += matrix[11];
		++count;
	}
}

// ?rva0023d430@Rva0023D430Owner@@QAEXPAUCoord3D@@0@Z
void Rva0023D430Owner::rva0023d430(Coord3D *result, Coord3D *normal)
{
	Int count = 0;
	const BfmeMemberList &members =
		((Rva0023D430MemberView *)((char *)this - 0xc4))->getMemberList();
	Coord3D average = {0.0f, 0.0f, 0.0f};
	Bool hasSpecial = false;

	for (BfmeMemberList::const_iterator it = members.begin();
		it != members.end(); ++it)
	{
		Object *object = *it;
		if (object != 0)
		{
			rva0023d430Accumulate(average, count, object);
			if (!hasSpecial && (object->m_status & 0x40) != 0)
				hasSpecial = true;
		}
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt key = entry->m_key;
		if (key != 0)
		{
			Object *object = TheBfmeGameLogic->findObjectByID(key);
			if (object != 0)
			{
				rva0023d430Accumulate(average, count, object);
				if (!hasSpecial && (object->m_status & 0x40) != 0)
					hasSpecial = true;
			}
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}

	Real scale = (Real)count;
	if (count < 0)
		scale += g_bfmeUint32Scale;
	scale = g_bfmeDefaultBU / scale;
	average.x *= scale;
	average.y *= scale;
	average.z *= scale;

	if (hasSpecial)
	{
		PathfindLayerEnum layer =
			TheTerrainLogic->getLayerForDestination(0, &average);
		average.z = TheTerrainLogic->getLayerHeight(average.x, average.y,
			layer, normal, true);
	}
	else if (normal != 0)
	{
		PathfindLayerEnum layer =
			TheTerrainLogic->getLayerForDestination(0, &average);
		average.z = TheTerrainLogic->getLayerHeight(average.x, average.y,
			layer, normal, true);
	}

	result->x = average.x;
	result->y = average.y;
	result->z = average.z;
}
