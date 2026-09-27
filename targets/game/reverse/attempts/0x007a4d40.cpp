// ?rva007A4D40@Rva007A1230ArrayOwner@@QAEXPAX@Z
// partial score=0.906 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The owner and helper identities are address-derived where the evidence does
// not establish an original source name. Offsets come from the matched owner.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <new>
#include <set>

typedef int Int;

struct Vector3
{
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
	Vector3 Center;
	Vector3 Extent;

	void build(Vector3 *points, Int count);
};

class AsciiString;

template <class T>
class StringBase
{
	friend class BFMERetailAsciiString;
	friend class AsciiString;

private:
	void releaseBuffer(void);
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) {}
	~AsciiString(void) { releaseBuffer(); }

	const char *str(void) const
	{
		return (const char *)m_data;
	}
};

class BfmeOtherDOA;

class BfmeThingDOA
{
public:
	BfmeOtherDOA *bfmeGoDOA(BfmeOtherDOA *other, Int index);
};

enum WaterTextureIndex
{
	WATER_TEXTURE_0 = 0
};

class Rva007A1230ArrayOwner
{
public:
	void rva007A4D40(void *source);
};

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
};

extern void j_0000931d(void);
extern void j_00030413(void);
extern void j_00015d7a(void);
extern void j_0002687d(void);
extern void j_000490a3(void);

extern void *bfmeGoEMEb(void *name);
extern void Rva009EBAC0(Int assets);

typedef void (Rva007A1230ArrayOwner::*Rva007A4D40Cleanup)(void);
typedef void (Rva007A1230ArrayOwner::*Rva007A4D40SetTexture)(
	const AsciiString &, WaterTextureIndex);
typedef void (AABoxClass::*Rva007A4D40BuildBox)(Vector3 *, Int);
struct Rva0013FA60Target;
typedef Rva0013FA60Target *Rva0013FA60Key;
struct Rva007A4D40TreeHeader
{
	unsigned char m_color;
	unsigned char m_padding01[3];
	void *m_parent;
	void *m_left;
	void *m_right;
};

struct Rva0013FA60Iterator
{
	void *m_iterator;
};

typedef _STL::pair<Rva0013FA60Iterator, bool> Rva007A4D40InsertResult;

struct Rva0013FA60Set
{
	__forceinline Rva007A4D40InsertResult insert(
		const Rva0013FA60Key &key)
	{
		union
		{
			void (*raw)(void);
			Rva007A4D40InsertResult (Rva0013FA60Set::*member)(
				const Rva0013FA60Key &);
		} insertUnique;
		insertUnique.raw = j_00030413;
		return (this->*insertUnique.member)(key);
	}

	Rva007A4D40TreeHeader *m_header;
	unsigned int m_nodeCount;
	unsigned int m_keyCompare;
};

typedef char Rva0013FA60SetSizeCheck[
	(sizeof(Rva0013FA60Set) == 12) ? 1 : -1];

struct Rva007A4D40AssetList
{
	Rva0013FA60Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

void Rva007A1230ArrayOwner::rva007A4D40(void *source)
{
	Rva007A1230ArrayOwner *owner = this;
	Rva007A4D40Source *record = (Rva007A4D40Source *)source;
	unsigned char *self = (unsigned char *)owner;

	union
	{
		void (*raw)(void);
		Rva007A4D40Cleanup member;
	} cleanup;
	cleanup.raw = j_000490a3;
	(owner->*cleanup.member)();

	self[4] = record->m_flag40;
	*(void **)(self + 8) = record->m_field44;
	self[0x3c] = record->m_flag60;
	*(Vector3 *)(self + 0x40) = record->m_position64;
	*(unsigned int *)(self + 0x4c) = record->m_value70;
	*(unsigned int *)(self + 0x50) = record->m_value74;
	*(unsigned int *)(self + 0x60) = record->m_value7c;

	Int pointCount = record->m_pointCount;
	*(Int *)(self + 0x58) = pointCount;
	Vector3 *points = new Vector3[pointCount];
	*(Vector3 **)(self + 0x54) = points;

	for (Int pointIndex = 0, pointOffset = 0;
		*(Vector3 **)(self + 0x54) != 0 &&
		pointIndex < *(Int *)(self + 0x58);
		++pointIndex, pointOffset += 0xc)
	{
		Int sourceIndex = pointIndex;
		if (pointOffset < 0)
			sourceIndex = 0;
		if (sourceIndex >= record->m_pointCount)
			sourceIndex = record->m_pointCount - 1;

		Rva007A4D40Point *point = record->m_points + sourceIndex;
		Vector3 *destination = (Vector3 *)(pointOffset +
			(unsigned)*(Vector3 **)(self + 0x54));
		destination->set((float)point->X, (float)point->Y,
			(float)point->Z);
	}

	if (!*(unsigned char *)(self + 0x64))
	{
		AABoxClass bounds;
		union
		{
			void (*raw)(void);
			Rva007A4D40BuildBox member;
		} build;
		build.raw = j_0002687d;
		(bounds.*build.member)(*(Vector3 **)(self + 0x54),
			*(Int *)(self + 0x58));
		*(unsigned int *)(self + 0x68) = *(unsigned int *)&bounds.Center.X;
		*(unsigned int *)(self + 0x6c) = *(unsigned int *)&bounds.Center.Y;
		*(unsigned int *)(self + 0x70) = *(unsigned int *)&bounds.Center.Z;
		*(unsigned int *)(self + 0x74) = *(unsigned int *)&bounds.Extent.X;
		*(unsigned int *)(self + 0x78) = *(unsigned int *)&bounds.Extent.Y;
		*(unsigned int *)(self + 0x7c) = *(unsigned int *)&bounds.Extent.Z;
		*(unsigned char *)(self + 0x64) = 1;
	}

	Rva007A4D40AssetList assets;
	assets.m_prototypes.m_header = 0;
	assets.m_prototypes.m_header = (Rva007A4D40TreeHeader *)
		_STL::__new_alloc::allocate(0x14);
	assets.m_prototypes.m_nodeCount = 0;
	assets.m_prototypes.m_header->m_color = 0;
	assets.m_prototypes.m_header->m_parent = 0;
	assets.m_prototypes.m_header->m_left = assets.m_prototypes.m_header;
	assets.m_prototypes.m_header->m_right = assets.m_prototypes.m_header;
	assets.m_treeLayoutPad = 0;
	assets.m_changed = true;
	for (Int index = 0; index < 6; ++index)
	{
		{
			AsciiString texture;
			BfmeOtherDOA *textureResult =
				reinterpret_cast<BfmeThingDOA *>(record)->bfmeGoDOA(
					reinterpret_cast<BfmeOtherDOA *>(&texture), index);

			union
			{
				void (*raw)(void);
				Rva007A4D40SetTexture member;
			} setTexture;
			setTexture.raw = j_0000931d;
			(owner->*setTexture.member)(
				*reinterpret_cast<AsciiString *>(textureResult),
				(WaterTextureIndex)index);
		}

		AsciiString assetName;
		BfmeOtherDOA *assetNameResult =
			reinterpret_cast<BfmeThingDOA *>(record)->bfmeGoDOA(
				reinterpret_cast<BfmeOtherDOA *>(&assetName), index);
		const char *name = reinterpret_cast<AsciiString *>(assetNameResult)->str();
		if (name)
			name += 8;
		else
			name = (const char *)0x0107388b;
		Rva0013FA60Key prototype = (Rva0013FA60Key)bfmeGoEMEb(
			(void *)name);
		if (assets.m_prototypes.insert(prototype).second)
			assets.m_changed = true;
	}

	Rva009EBAC0((Int)&assets);
	union
	{
		void (*raw)(void);
		void (Rva0013FA60Set::*member)(void);
	} destroy;
	destroy.raw = j_00015d7a;
	(assets.m_prototypes.*destroy.member)();
}
