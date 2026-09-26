// ?d_001012b0@@YAXXZ
// partial score=0.22 date=2026-09-18
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/shims/stlp_nodealloc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define __PLACEMENT_VEC_NEW_INLINE

#include <vector>
#include <math.h>

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef int Int;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

enum Relationship
{
	NEUTRAL = 1,
	ALLIES = 2
};

extern void j_0000125d();
extern void j_000022bb();
extern void j_00003828();
extern void j_00020c2f();
extern void j_0002be77();
extern void j_0003251f();
extern void j_00037b6e();
extern void j_000382fd();
extern void j_0003e77a();
extern void j_00044774();
extern void j_000309f4();
extern void d_009f2ae0();
extern Real GetGameLogicRandomValueReal(Real low, Real high, void *unused, Int frame);

struct Rva001012B0Dispatch
{
};

typedef void (Rva001012B0Dispatch::*Rva001012B0Ctor)(int, Bool, Real, Real, Real);
typedef void (Rva001012B0Dispatch::*Rva001012B0Copy)(const void *);
typedef void (Rva001012B0Dispatch::*Rva001012B0Dtor)();
typedef const void *(Rva001012B0Dispatch::*Rva001012B0FinalOverride)() const;
typedef Bool (Rva001012B0Dispatch::*Rva001012B0KindOf)(int) const;
typedef void *(Rva001012B0Dispatch::*Rva001012B0GetAI)();
typedef int (Rva001012B0Dispatch::*Rva001012B0Relationship)(void *);
typedef Bool (Rva001012B0Dispatch::*Rva001012B0Bool0)();
typedef void (Rva001012B0Dispatch::*Rva001012B0Move)(void *, int);
typedef void *(Rva001012B0Dispatch::*Rva001012B0Pointer0)();
typedef void *(Rva001012B0Dispatch::*Rva001012B0Pointer1)(void *);
typedef void (Rva001012B0Dispatch::*Rva001012B0MaskCtor)(
	int, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt);
typedef void (Rva001012B0Dispatch::*Rva001012B0PairCtor)(
	const void *, const void *);
typedef void *(Rva001012B0Dispatch::*Rva001012B0Link)(void *);

static __forceinline void rva001012B0ConstructGeometry(void *object,
	GeometryType type, Bool small, Real height, Real major, Real minor)
{
	union { void (*raw)(); Rva001012B0Ctor member; } call;
	call.raw = j_00037b6e;
	(reinterpret_cast<Rva001012B0Dispatch *>(object)->*call.member)(
		(int)type, small, height, major, minor);
}

static __forceinline void rva001012B0CopyGeometry(void *object, const void *source)
{
	union { void (*raw)(); Rva001012B0Copy member; } call;
	call.raw = j_00003828;
	(reinterpret_cast<Rva001012B0Dispatch *>(object)->*call.member)(source);
}

static __forceinline void rva001012B0DestroyGeometry(void *object)
{
	union { void (*raw)(); Rva001012B0Dtor member; } call;
	call.raw = j_000309f4;
	(reinterpret_cast<Rva001012B0Dispatch *>(object)->*call.member)();
}

static __forceinline const void *rva001012B0FinalOverride(const void *object)
{
	union { void (*raw)(); Rva001012B0FinalOverride member; } call;
	call.raw = j_000022bb;
	return (reinterpret_cast<const Rva001012B0Dispatch *>(object)->*call.member)();
}

static __forceinline Bool rva001012B0KindOf(const void *object, int kind)
{
	union { void (*raw)(); Rva001012B0KindOf member; } call;
	call.raw = j_0003251f;
	return (reinterpret_cast<const Rva001012B0Dispatch *>(object)->*call.member)(kind);
}

static __forceinline void *rva001012B0GetAI(void *object)
{
	union { void (*raw)(); Rva001012B0GetAI member; } call;
	call.raw = j_0002be77;
	return (reinterpret_cast<Rva001012B0Dispatch *>(object)->*call.member)();
}

static __forceinline Relationship rva001012B0Relationship(void *object, void *team)
{
	union { void (*raw)(); Rva001012B0Relationship member; } call;
	call.raw = j_0003e77a;
	return (Relationship)(reinterpret_cast<Rva001012B0Dispatch *>(object)->*call.member)(team);
}

static __forceinline Bool rva001012B0Bool0(void (*raw)(), void *object)
{
	union { void (*raw)(); Rva001012B0Bool0 member; } call;
	call.raw = raw;
	return (reinterpret_cast<Rva001012B0Dispatch *>(object)->*call.member)();
}

static __forceinline void rva001012B0Move(void *object, void *position, int command)
{
	union { void (*raw)(); Rva001012B0Move member; } call;
	call.raw = j_00020c2f;
	(reinterpret_cast<Rva001012B0Dispatch *>(object)->*call.member)(position, command);
}

static __forceinline void rva001012B0ConstructMask(void *object, int tag,
	UnsignedInt a02, UnsignedInt a03, UnsignedInt a04, UnsignedInt a05)
{
	union { void (*raw)(); Rva001012B0MaskCtor member; } call;
	call.raw = j_0000125d;
	(reinterpret_cast<Rva001012B0Dispatch *>(object)->*call.member)(
		tag, a02, a03, a04, a05);
}

static __forceinline void rva001012B0ConstructKindFilter(void *object,
	const void *mustSet, const void *mustClear)
{
	union { void (*raw)(); Rva001012B0PairCtor member; } call;
	call.raw = j_000382fd;
	(reinterpret_cast<Rva001012B0Dispatch *>(object)->*call.member)(
		mustSet, mustClear);
}

static __forceinline void *rva001012B0Link(void *object, void *next)
{
	union { void (*raw)(); Rva001012B0Link member; } call;
	call.raw = d_009f2ae0;
	return (reinterpret_cast<Rva001012B0Dispatch *>(object)->*call.member)(next);
}

class BfmeThingTemplateShadowSelector
{
public:
	Bool usePluralShadowName() const;
};

// The five-argument body at 0x00100580 and the cleanup at 0x000FFCA0 show
// this BFME object as a 0x5c-byte local.  The scalar fields used here are the
// witnessed +0x10/+0x14 radius pair; its vector tail is intentionally opaque.
class Rva001012B0Geometry
{
public:
	Rva001012B0Geometry(GeometryType type, Bool small, Real height,
		Real major, Real minor)
	{
		rva001012B0ConstructGeometry(this, type, small, height, major, minor);
	}
	Rva001012B0Geometry &operator=(const Rva001012B0Geometry &other)
	{
		rva001012B0CopyGeometry(this, &other);
		return *this;
	}
	~Rva001012B0Geometry()
	{
		rva001012B0DestroyGeometry(this);
	}

	Real getMajorRadius() const
	{
		return *(const Real *)((const char *)this + 0x10);
	}
	Real getMinorRadius() const
	{
		return *(const Real *)((const char *)this + 0x14);
	}

	void *m_vptr;
	unsigned char m_data[0x58];
};

class ThingTemplate
{
public:
	const Rva001012B0Geometry &getTemplateGeometryInfo() const
	{
		return *(const Rva001012B0Geometry *)((const char *)this + 0x60);
	}
};

class Player
{
};

struct Rva001012B0Object
{
	void *m_vptr;
	ThingTemplate *m_template;
	unsigned char m_pad[0x23c - 8];
	void *m_team;
};

struct Rva001012B0Filter
{
	Rva001012B0Filter(const Coord3D *position, Real radius)
	{
		m_next = 0;
		m_vptr = (void *)0x010860C4;
		m_position = position;
		m_radius = radius;
	}

	void *m_vptr;
	void *m_next;
	const Coord3D *m_position;
	Real m_radius;
};

struct Rva001012B0Mask
{
	UnsignedInt m_bits[6];
};

struct Rva001012B0KindFilter
{
	void *m_vptr;
	void *m_next;
	Rva001012B0Mask m_mustSet;
	Rva001012B0Mask m_mustClear;
};

struct Rva001012B0RootFilter
{
	void *m_vptr;
	void *m_next;
};

struct Rva001012B0SecondaryFilter
{
	void *m_vptr;
	void *m_next;
	UnsignedInt m_dword08;
	UnsignedInt m_dword0c;
	UnsignedInt m_dword10;
	void *m_first;
	Real m_second;
	Bool m_flag;
};

struct Rva001012B0Entry
{
	Rva001012B0Object *object;
	UnsignedInt unused;
};

struct Rva001012B0ResultData
{
	std::vector<Rva001012B0Entry> entries;
	Rva001012B0Entry *current;
	Int references;
};

struct BfmeResultA
{
	Rva001012B0ResultData *value;
	BfmeResultA();
	BfmeResultA(const BfmeResultA &other)
		: value(other.value)
	{
		++value->references;
	}
	~BfmeResultA()
	{
		if (--value->references == 0)
			delete value;
	}

	Rva001012B0Object *next(Rva001012B0Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}
};

class BfmeResultForwardB
{
	char m_pad[0x0c];
	void *m_source;

public:
	BfmeResultA bfmeForwardResultB(int value);
};

struct BfmeWideResultEntry
{
	Rva001012B0Object *object;
	UnsignedInt unused;
};

struct BfmeWideResultData
{
	std::vector<BfmeWideResultEntry> entries;
	BfmeWideResultEntry *current;
	Int references;
};

struct BfmeWideResult
{
	BfmeWideResultData *value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &other)
		: value(other.value)
	{
		++value->references;
	}
	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}

	Rva001012B0Object *next(Rva001012B0Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int a, int b, int c, int d, int e);
};

static __forceinline void *rva001012B0GetTeam(Rva001012B0Object *object)
{
	return *(void **)((char *)object + 0x23c);
}

static __forceinline Bool rva001012B0IsKindOf(Rva001012B0Object *object, int kind)
{
	ThingTemplate *templ = object->m_template;
	if (templ != 0)
	{
		void *next = *(void **)((char *)templ + 4);
		if (next != 0)
			templ = (ThingTemplate *)rva001012B0FinalOverride(next);
	}
	return rva001012B0KindOf(templ, kind);
}

static __forceinline Bool rva001012B0TemplateBit04(Rva001012B0Object *object)
{
	ThingTemplate *templ = object->m_template;
	if (templ != 0)
	{
		void *next = *(void **)((char *)templ + 4);
		if (next != 0)
			templ = (ThingTemplate *)rva001012B0FinalOverride(next);
	}
	return (*(const unsigned char *)((const char *)templ + 0xc8) & 4) != 0;
}

static __forceinline Bool rva001012B0TemplateBit02000000(
	Rva001012B0Object *object)
{
	ThingTemplate *templ = object->m_template;
	if (templ != 0)
	{
		void *next = *(void **)((char *)templ + 4);
		if (next != 0)
			templ = (ThingTemplate *)rva001012B0FinalOverride(next);
	}
	return (*(const UnsignedInt *)((const char *)templ + 0xcc) & 0x02000000) != 0;
}

static __forceinline Bool rva001012B0TemplateBit01000000(
	Rva001012B0Object *object)
{
	ThingTemplate *templ = object->m_template;
	if (templ != 0)
	{
		void *next = *(void **)((char *)templ + 4);
		if (next != 0)
			templ = (ThingTemplate *)rva001012B0FinalOverride(next);
	}
	return (*(const UnsignedInt *)((const char *)templ + 0xd0) & 0x01000000) != 0;
}

static __forceinline Bool rva001012B0TemplateBit40(Rva001012B0Object *object)
{
	ThingTemplate *templ = object->m_template;
	if (templ != 0)
	{
		void *next = *(void **)((char *)templ + 4);
		if (next != 0)
			templ = (ThingTemplate *)rva001012B0FinalOverride(next);
	}
	return (*(const unsigned char *)((const char *)templ + 0xc8) & 0x40) != 0;
}

class BuildAssistant
{
	protected:
	Bool moveObjectsForConstruction(const ThingTemplate *whatToBuild,
		const Coord3D *pos, Real angle, Player *playerToBuild);
};

class Rva001012B0AIView
{
public:
#define RVA001012B0_AI_SLOT(n) virtual void slot##n();
	RVA001012B0_AI_SLOT(0)
	RVA001012B0_AI_SLOT(1)
	RVA001012B0_AI_SLOT(2)
	RVA001012B0_AI_SLOT(3)
	RVA001012B0_AI_SLOT(4)
	RVA001012B0_AI_SLOT(5)
	RVA001012B0_AI_SLOT(6)
	RVA001012B0_AI_SLOT(7)
	RVA001012B0_AI_SLOT(8)
	RVA001012B0_AI_SLOT(9)
	RVA001012B0_AI_SLOT(10)
	RVA001012B0_AI_SLOT(11)
	RVA001012B0_AI_SLOT(12)
	RVA001012B0_AI_SLOT(13)
	RVA001012B0_AI_SLOT(14)
	RVA001012B0_AI_SLOT(15)
	RVA001012B0_AI_SLOT(16)
	RVA001012B0_AI_SLOT(17)
	RVA001012B0_AI_SLOT(18)
	RVA001012B0_AI_SLOT(19)
	RVA001012B0_AI_SLOT(20)
	RVA001012B0_AI_SLOT(21)
	RVA001012B0_AI_SLOT(22)
	RVA001012B0_AI_SLOT(23)
	RVA001012B0_AI_SLOT(24)
	RVA001012B0_AI_SLOT(25)
	RVA001012B0_AI_SLOT(26)
	RVA001012B0_AI_SLOT(27)
	RVA001012B0_AI_SLOT(28)
	RVA001012B0_AI_SLOT(29)
	RVA001012B0_AI_SLOT(30)
	RVA001012B0_AI_SLOT(31)
	RVA001012B0_AI_SLOT(32)
	RVA001012B0_AI_SLOT(33)
	RVA001012B0_AI_SLOT(34)
	RVA001012B0_AI_SLOT(35)
	RVA001012B0_AI_SLOT(36)
	RVA001012B0_AI_SLOT(37)
	RVA001012B0_AI_SLOT(38)
	RVA001012B0_AI_SLOT(39)
	RVA001012B0_AI_SLOT(40)
	RVA001012B0_AI_SLOT(41)
	RVA001012B0_AI_SLOT(42)
	RVA001012B0_AI_SLOT(43)
	RVA001012B0_AI_SLOT(44)
	RVA001012B0_AI_SLOT(45)
	RVA001012B0_AI_SLOT(46)
	RVA001012B0_AI_SLOT(47)
	RVA001012B0_AI_SLOT(48)
	RVA001012B0_AI_SLOT(49)
	RVA001012B0_AI_SLOT(50)
	RVA001012B0_AI_SLOT(51)
	RVA001012B0_AI_SLOT(52)
	RVA001012B0_AI_SLOT(53)
	RVA001012B0_AI_SLOT(54)
	RVA001012B0_AI_SLOT(55)
	RVA001012B0_AI_SLOT(56)
	RVA001012B0_AI_SLOT(57)
	RVA001012B0_AI_SLOT(58)
	RVA001012B0_AI_SLOT(59)
	RVA001012B0_AI_SLOT(60)
	RVA001012B0_AI_SLOT(61)
	RVA001012B0_AI_SLOT(62)
	RVA001012B0_AI_SLOT(63)
	RVA001012B0_AI_SLOT(64)
	RVA001012B0_AI_SLOT(65)
	RVA001012B0_AI_SLOT(66)
	RVA001012B0_AI_SLOT(67)
	RVA001012B0_AI_SLOT(68)
	RVA001012B0_AI_SLOT(69)
	RVA001012B0_AI_SLOT(70)
	RVA001012B0_AI_SLOT(71)
	RVA001012B0_AI_SLOT(72)
	RVA001012B0_AI_SLOT(73)
	RVA001012B0_AI_SLOT(74)
	RVA001012B0_AI_SLOT(75)
	RVA001012B0_AI_SLOT(76)
	RVA001012B0_AI_SLOT(77)
	RVA001012B0_AI_SLOT(78)
	RVA001012B0_AI_SLOT(79)
	RVA001012B0_AI_SLOT(80)
	RVA001012B0_AI_SLOT(81)
	RVA001012B0_AI_SLOT(82)
	RVA001012B0_AI_SLOT(83)
	RVA001012B0_AI_SLOT(84)
	RVA001012B0_AI_SLOT(85)
	RVA001012B0_AI_SLOT(86)
	RVA001012B0_AI_SLOT(87)
	RVA001012B0_AI_SLOT(88)
	RVA001012B0_AI_SLOT(89)
	RVA001012B0_AI_SLOT(90)
	RVA001012B0_AI_SLOT(91)
	RVA001012B0_AI_SLOT(92)
	RVA001012B0_AI_SLOT(93)
	RVA001012B0_AI_SLOT(94)
	RVA001012B0_AI_SLOT(95)
	RVA001012B0_AI_SLOT(96)
	RVA001012B0_AI_SLOT(97)
	RVA001012B0_AI_SLOT(98)
	RVA001012B0_AI_SLOT(99)
	RVA001012B0_AI_SLOT(100)
	RVA001012B0_AI_SLOT(101)
	RVA001012B0_AI_SLOT(102)
	RVA001012B0_AI_SLOT(103)
	virtual Bool slot104();
#undef RVA001012B0_AI_SLOT
};

// ?moveObjectsForConstruction@BuildAssistant@@IAE_NPBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@@Z
Bool BuildAssistant::moveObjectsForConstruction(const ThingTemplate *whatToBuild,
	const Coord3D *pos, Real angle, Player *playerToBuild)
{
	Real major = whatToBuild->getTemplateGeometryInfo().getMajorRadius();
	Real minor = whatToBuild->getTemplateGeometryInfo().getMajorRadius();
	Rva001012B0Geometry geometry(GEOMETRY_BOX, false, 10.0f, major, minor);
	const Rva001012B0Geometry &templateGeometry =
		whatToBuild->getTemplateGeometryInfo();
	if (((const BfmeThingTemplateShadowSelector *)&templateGeometry)->usePluralShadowName())
		geometry = templateGeometry;

	Real radius = geometry.getMajorRadius();
	radius *= *(const Real *)0x010861AC;

	{
		Rva001012B0Filter queryFilter(pos, radius);
		BfmeResultA initialIterator =
			((BfmeResultForwardB *)*(void **)0x012ED5B8)->bfmeForwardResultB(
				(int)&queryFilter);
	}

	// BFME keeps a second, filtered partition result alive while it walks the
	// first result.  The filter chain is spelled with the retail vptrs because
	// those four classes are not yet named independently in this tree.
	Rva001012B0SecondaryFilter secondaryFilter;
	secondaryFilter.m_vptr = (void *)0x010860A0;
	secondaryFilter.m_next = 0;
	secondaryFilter.m_dword10 = *(const UnsignedInt *)&pos->z;
	secondaryFilter.m_first = &geometry;
	secondaryFilter.m_second = angle;
	secondaryFilter.m_flag = true;
	Rva001012B0Mask mustSet;
	rva001012B0ConstructMask(&mustSet, 0, 0x58, 0x85, 0x67, 0x3b);
	Rva001012B0Mask mustClear;
	Rva001012B0KindFilter kindFilter;
	rva001012B0ConstructKindFilter(&kindFilter, &mustSet, &mustClear);
	Rva001012B0RootFilter tailFilter;
	tailFilter.m_vptr = (void *)0x010860B0;
	tailFilter.m_next = 0;
	Rva001012B0RootFilter rootFilter;
	rootFilter.m_vptr = (void *)0x01083B80;
	rootFilter.m_next = 0;
	void *filterChain = rva001012B0Link(&rootFilter, &tailFilter);
	filterChain = rva001012B0Link(filterChain, &secondaryFilter);
	filterChain = rva001012B0Link(filterChain, &kindFilter);
	Real queryRadius = geometry.getMinorRadius() * *(const Real *)0x01086134;
	BfmeWideResult filteredIterator =
		((BfmeWideForwardC *)*(void **)0x012ED5B8)->bfmeForwardWideC(
			(int)pos, *(int *)&queryRadius, 3, (int)filterChain, 0);

	Bool anyUnmovables = false;
	Rva001012B0Object *them;
	while (filteredIterator.next(them) != 0)
	{
		if (rva001012B0TemplateBit04(them))
			continue;
		if (rva001012B0TemplateBit02000000(them))
			continue;
		if (rva001012B0TemplateBit01000000(them))
			continue;
		if (rva001012B0TemplateBit40(them))
			continue;
		if (rva001012B0KindOf(them, 50))
			continue;
		if (*((const unsigned char *)them + 0x344) & 1)
			continue;

		Relationship relationship = rva001012B0Relationship(
			(Rva001012B0Dispatch *)playerToBuild, rva001012B0GetTeam(them));
		if (relationship != NEUTRAL && relationship != ALLIES)
		{
			anyUnmovables = true;
			continue;
		}

		void *ai = rva001012B0GetAI(them);
		if (ai == 0)
		{
			anyUnmovables = true;
			continue;
		}

		if (((Rva001012B0AIView *)ai)->slot104())
			continue;

		void *moveTarget = *(void **)((char *)them + 0x204);
		if (moveTarget == 0)
			continue;

		Real variedRadius =
			GetGameLogicRandomValueReal(0.5f, 1.5f, (void *)0x01086160, 0x721) * radius;
		Real direction =
			GetGameLogicRandomValueReal(-3.14159265358979323846f,
				3.14159265358979323846f, (void *)0x01086160, 0x724);
		Real sine = (Real)sin(direction);
		Real cosine = (Real)cos(direction);
		Coord3D destination;
		destination.x = pos->x + variedRadius * cosine;
		destination.y = pos->y + variedRadius * sine;
		destination.z = pos->z;

		if (rva001012B0Bool0(j_00044774, them))
			continue;
		rva001012B0Move((char *)moveTarget + 0x20, &destination, 2);
	}

	rva001012B0DestroyGeometry(&geometry);
	return !anyUnmovables;
}
