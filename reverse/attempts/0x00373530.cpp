// ?method@Rva00373530@@QAEXH@Z
// partial score=0.08 date=2026-09-17
// Scratch reconstruction for retail RVA 0x00373530.
// Boundary: 0x00373530..0x003739F2, 1221 bytes; final instruction is ret 4.
// Identity remains opaque: evidence proves the range/query behavior below,
// not an owning class.  Keep the address in the temporary owner name.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1

typedef float Real;
typedef unsigned int UnsignedInt;
typedef int Bool;

struct Coord3D { Real x, y, z; };

struct Rva00373530Object
{
	unsigned char pad00[0x38];
	Coord3D position;
	unsigned char pad44[0xBC - 0x44];
	void *related;
};

struct Rva00373530Template
{
	void *vtable;
	Rva00373530Template *nextOverride;
};

struct Rva00373530Related
{
	void *vtable;
	Rva00373530Template *thingTemplate;
	unsigned char pad08[0x38 - 8];
	Coord3D position;
	unsigned char pad44[0xCC - 0x44];
};

struct Rva00373530HashNode
{
	Rva00373530HashNode *next;
	Rva00373530Object *key;
	Rva00373530Related *value;
};

struct Rva00373530GameLogic
{
	unsigned char pad00[0xB4];
	Rva00373530HashNode **buckets;
	Rva00373530HashNode **bucketEnd;
};

extern Rva00373530GameLogic *TheBfmeGameLogic;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")

class PartitionFilter
{
public:
	PartitionFilter *link(PartitionFilter *next);
	unsigned int vtable;
	PartitionFilter *next;
};

struct Rva00373530Entry { Rva00373530Object *object; unsigned int value; };
struct Rva00373530ResultData
{
	Rva00373530Entry *begin, *end, *capacity, *current;
	int references;
	~Rva00373530ResultData() { delete [] begin; }
};

class Rva00373530WideResult
{
public:
	Rva00373530ResultData *value;
	Rva00373530WideResult() : value(0) {}
	Rva00373530WideResult(const Rva00373530WideResult &other) : value(other.value)
	{
		if (value) ++value->references;
	}
	~Rva00373530WideResult()
	{
		if (value && --value->references == 0) delete value;
	}
	Rva00373530Object *nextObject(Rva00373530Object *&object)
	{
		if (!value || value->current == value->end) return 0;
		object = (value->current++)->object;
		return object;
	}
};

class BfmeWideForwardC
{
public:
	Rva00373530WideResult bfmeForwardWideC(int, int, int, int, int);
};
extern BfmeWideForwardC *ThePartitionManager;

class Thing
{
public:
	Real bfmeRelativeAngleTo(const Coord3D *) const;
};
#pragma comment(linker, "/alternatename:?bfmeRelativeAngleTo@Thing@@QBEMPBUCoord3D@@@Z=?j_00049413@@YAXXZ")

class Gen_001BEC20
{
public:
	int bfmeScale() const;
};
#pragma comment(linker, "/alternatename:?bfmeScale@Gen_001BEC20@@QBEHXZ=?j_0003a391@@YAXXZ")

extern "C" void *__stdcall bfmeGo941G(void *, void *);
#pragma comment(linker, "/alternatename:_bfmeGo941G@8=?j_0000b069@@YAXXZ")

struct Rva00373530FindPositionOptions { unsigned char bytes[0x20]; };
extern Bool __cdecl findPositionAround(const Coord3D *,
	const Rva00373530FindPositionOptions *, Coord3D *);
#pragma comment(linker, "/alternatename:?findPositionAround@@YA_NPBUCoord3D@@PBURva00373530FindPositionOptions@@PAU1@@Z=?j_00026c4c@@YAXXZ")

extern Rva00373530Object *__cdecl rva00373530FindGate(Rva00373530Object *, int);
extern void *__cdecl rva00373530FindModule(Rva00373530Object *);
extern void __cdecl rva00373530Apply(void *, void *, int);

class Rva00373530
{
public:
	unsigned char pad00[8];
	Rva00373530Object *input;
	unsigned char pad0C[0xC4 - 0x0C];
	Rva00373530Object **begin;
	Rva00373530Object **end;
	void method(Bool flag);
};

void Rva00373530::method(Bool flag)
{
	volatile unsigned char frameScratch[0x3C];
	Rva00373530Object *object;
	Rva00373530Object **current = begin;
	int index = 0;
	Coord3D center = input->position;
	Coord3D result;
	Rva00373530FindPositionOptions options;
	options.bytes[0] = 0x80;
	Rva00373530GameLogic *logic = TheBfmeGameLogic;

	while (current + index < end)
	{
		object = current[index++];
		if (object == 0) continue;
		int bucketCount = (int)(logic->bucketEnd - logic->buckets);
		if (bucketCount == 0) continue;
		Rva00373530HashNode *node =
			logic->buckets[(UnsignedInt)object % bucketCount];
		while (node != 0 && node->key != object) node = node->next;
		if (node == 0 || node->value == 0) continue;

		Rva00373530Template *templ = node->value->thingTemplate;
		if (templ == 0) continue;
		const Overridable *resolved = (const Overridable *)templ;
		if (templ->nextOverride != 0)
			resolved = ((const Overridable *)templ->nextOverride)->getFinalOverride();
		if ((*(const unsigned int *)((const unsigned char *)resolved + 0xCC)
			& 0x08000000) == 0) continue;

		PartitionFilter root;
		root.vtable = 0x01083B80;
		root.next = 0;
		PartitionFilter query;
		query.vtable = 0x01085DC0;
		query.next = 0;
		query.link(&root);
		Rva00373530WideResult iterator =
			ThePartitionManager->bfmeForwardWideC(
				(int)&center, *(int *)&center.z, 1, (int)&query, 1);

		Rva00373530Object *candidate;
		Bool accepted = false;
		while (iterator.nextObject(candidate) != 0)
		{
			if (((Gen_001BEC20 *)candidate)->bfmeScale() < 0x11) continue;
			void *position = bfmeGo941G(&result, candidate);
			((Thing *)object)->bfmeRelativeAngleTo((const Coord3D *)position);
			Rva00373530Object *owner = rva00373530FindGate(candidate, 0);
			if (owner == 0) continue;
			if (findPositionAround(&center, &options, &result))
			{
				accepted = true;
				if (flag)
				{
					void *module = rva00373530FindModule(owner);
					if (module != 0) rva00373530Apply(module, &result, 0);
				}
			}
		}
		(void)accepted;
	}
	(void)frameScratch[0];
}
