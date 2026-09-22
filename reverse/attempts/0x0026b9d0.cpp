// ?after@TaintSpecialPower@@QAEXPBUCoord3D@@@Z
// partial score=0.75 date=2026-09-22
// ?after@TaintSpecialPower@@QAEXPBUCoord3D@@@Z
// Corrected native reconstruction of0026B9D0/1109B, still partial.
// Current result1116B with514 non-relocation differences; frameB8 is correct.
// Independent review verified branches, receivers, arguments and lifetimes.
// Critical repairs: six-word masks/56B filters; temporary virtual-base cleanup;
// same-owner exclusion; float query ABI and unscaled terrain radius; OCLowner
// argument; separate Taint receiver and unconditional0026B950 helper call.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DBFME_STLP_NODE_ALLOC /Ireference/shims/sweep /Ireference/shims/stlp_nodealloc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE

#include <vector>
#include "PreRTS.h"
#include "GameLogic/ObjectIter.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Player;
class Matrix3D;
class Object;

// Exact released-twin result contract, copied from the landed
// DelayedLuaEventUpdate/ObjectBroadcastEvent bodies.  The result is a
// ref-counted handle to a vector of 8-byte object entries; `next` is the
// released native iterator operation, not a raw node cursor.
struct Rva0026B9D0Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva0026B9D0ResultData
{
	std::vector<Rva0026B9D0Entry> entries;
	Rva0026B9D0Entry *current;
	Int references;
};

struct BfmeWideResult
{
	Rva0026B9D0ResultData *value;

	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	BfmeWideResult &operator=(const BfmeWideResult &other)
	{
		if (this != &other)
		{
			if (--value->references == 0)
				delete value;
			value = other.value;
			++value->references;
		}
		return *this;
	}

	Object *next(Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}

	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}
};

// The retail tree is the already-landed pointer-identity _Rb_tree family.
// Using the native set supplies the insert_unique helper and the
// inlined find/cleanup walk seen in the second scan.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

struct Rva0025BD30Target;
typedef Rva0025BD30Target *Rva0025BD30Key;
typedef std::set<Rva0025BD30Key> PointerIdentityTree0025BD30;

#include <bitset>
struct Rva000C3DD0Mask
{
    std::bitset<192> m_bits;
    explicit Rva000C3DD0Mask(unsigned bit) { m_bits.set(bit); }
};

extern const Rva000C3DD0Mask g_bfmeKindofMaskNone;

// PhysicalC3DD0 copies two24-byte masks after its8-byte base (56B total).
// Six storage words and selectedbit151 are witnessed; the original logical
// bit-count is unknown, so this address-qualified view uses192 storage bits.
// Its call contract is the real PartitionFilterAcceptByKindOf constructor;
// the body target is ILT000382FD ->000C3DD0.
class PartitionFilter
{
public:
    PartitionFilter() : m_next(0) {}
    virtual ~PartitionFilter() {}
    virtual bool allow(Object *) = 0;
    PartitionFilter *m_next;
};
class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
    PartitionFilterAcceptByKindOf(const Rva000C3DD0Mask &mustBeSet,
        const Rva000C3DD0Mask &mustBeClear)
      : m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
    virtual bool allow(Object *);
private:
    Rva000C3DD0Mask m_mustBeSet, m_mustBeClear;
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(const Coord3D *, float, Int, PartitionFilter *, Int);
};

extern BfmeWideForwardC *ThePartitionManager;

class Object
{
public:
	unsigned char m_pad00[0x38];
	struct Coord3D m_position;
	unsigned char m_pad44[0x54];
	UnsignedInt m_status98;

	Player *getControllingPlayer() const;
};

class BfmeGameLogic
{
public:
	void destroyObject(Object *object);
};

extern BfmeGameLogic *TheBfmeGameLogic;

struct BfmePointFC
{
	float x;
	float y;
};

class BfmeTaintManager
{
public:
	void bfmeApplyCircleWorld(const BfmePointFC *point, float radius,
		Int amount, Bool absolute);
};

extern BfmeTaintManager *TheTaintManager;

class FXList
{
public:
	Bool bfmeIsBlocked();
	void doFXPos(const struct Coord3D *primary, const Matrix3D *primaryMtx,
		float primarySpeed, const struct Coord3D *secondary) const;
};

// Real callee contract at 0x001D67C0 (ILT 0x00002A59), from the landed
// BfmeThingFB twin.  The four payload types are intentionally opaque: this
// body only forwards the call to its child virtuals.
class BfmeThingFB
{
public:
	void bfmeTellFB(void *, void *, void *, void *);
};

// 0x001AC3D0 is a direct callee of this body (ILT 0x000017CB).  Its two
// arguments and thiscall shape are proven by the retail body; the semantic
// owner/name is not.  It is kept address-derived deliberately.
struct Rva003FD060TerrainLogic
{
	void rva001AC3D0(const struct Coord3D *, float);
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;

// Exact landed adapter contract at ILT 0x00042CD0 -> 0x001A64F0.
class TerrainLogicP48
{
public:
	void adapter(Int, Int, Int);
};

// Exact landed null-checked virtual-forwarder contract at ILT 0x00037330
// -> 0x001A3190.  The receiver is immaterial to the target body, which
// reloads its own visual singleton, but the call is a real thiscall.
class Rva001A3190GuardedVCall
{
public:
	void forward(Int, Int, Int);
};

extern const float g_bfmeK1266B;       // retail 0x01075340
extern const float g_bfme107faa8;      // retail 0x0107FAA8

struct TaintSpecialPowerModuleData
{
	unsigned char m_pad00[0x210];
	UnsignedInt m_taintObject;           // +0x210, field identity not needed here
	float m_radius;                      // +0x214
	FXList *m_taintFX;                   // +0x218
	BfmeThingFB *m_taintOCL;             // +0x21C
};

class TaintSpecialPower
{
public:
	void after(const struct Coord3D *loc);
	void rva0026B950(const struct Coord3D *loc, void *name);

	unsigned char m_pad00[4];
	TaintSpecialPowerModuleData *m_moduleData; // +0x04
	Object *m_object;                          // +0x08
	unsigned char m_pad0C[4];
};

void TaintSpecialPower::after(const struct Coord3D *loc)
{
	TaintSpecialPowerModuleData *data = m_moduleData;
	float radius = data->m_radius;
	Object *owner = m_object;

	{



			BfmeWideResult iterator = ThePartitionManager->bfmeForwardWideC(
				loc, radius * *(const float *)0x010B4BCC, 0, &PartitionFilterAcceptByKindOf(Rva000C3DD0Mask(151), g_bfmeKindofMaskNone), 1);

			// Retail constructs the native _Rb_tree only after the first
			// wide-result is live: its 0x14-byte header allocation is visible
			// immediately after the first forward call.  Keeping this object
			// here also keeps it alive for the second scan.
			PointerIdentityTree0025BD30 matches;

		Object *candidate;
		while (iterator.next(candidate))
		{
			if (candidate->getControllingPlayer() ==
				owner->getControllingPlayer())
				continue;

			matches.insert((Rva0025BD30Key)candidate);
			TheTerrainLogic->rva001AC3D0(&candidate->m_position,
				radius);
			TheBfmeGameLogic->destroyObject(candidate);
		}

	{



			iterator = ThePartitionManager->bfmeForwardWideC(
				loc, radius * g_bfmeK1266B, 0, &PartitionFilterAcceptByKindOf(Rva000C3DD0Mask(151), g_bfmeKindofMaskNone), 1);

		Object *candidate;
		while (iterator.next(candidate))
		{
			if (candidate->getControllingPlayer() ==
				owner->getControllingPlayer())
				continue;

			Rva0025BD30Key key = (Rva0025BD30Key)candidate;
			if (matches.find(key) != matches.end())
				continue;

			Coord3D point = candidate->m_position;
			Int amount = (candidate->m_status98 & 0x80000) ? 0xff : 0;
			TheTaintManager->bfmeApplyCircleWorld(
					(const BfmePointFC *)&point, radius, amount, true);
			}
		}

	// The next two terrain calls are retained with their real arities.  The
	// retail pushes show the radius as raw float bits in these integer-forward
	// contracts, so keep a bit-preserving local rather than inventing a named
	// semantic field.
	Int radiusBits = *(const Int *)&radius;
	reinterpret_cast<TerrainLogicP48 *>(TheTerrainLogic)->adapter(
		(Int)loc, radiusBits, 1);
	float adjustedRadius = radius + g_bfme107faa8;
	reinterpret_cast<Rva001A3190GuardedVCall *>(TheTerrainLogic)->forward(
		(Int)loc, *(const Int *)&adjustedRadius, 1);

	FXList *fx = data->m_taintFX;
	if (fx != 0 && !fx->bfmeIsBlocked())
		fx->doFXPos(loc, 0, 0.0f, 0);

	BfmeThingFB *ocl = data->m_taintOCL;
    if (ocl != 0)
    {
        Coord3D oclPoint = *loc;
        // At retail+3A7 two pushes have moved ESP: [ESP+28] is the
        // saved owner Object*, not the just-copied point's x word.
        ocl->bfmeTellFB(owner, &oclPoint, 0, 0);
    }
    // [ESP+54] restores the saved TaintSpecialPower receiver. This call
    // is outside the optional OCL branch, and its body reads this+8.
    rva0026B950(loc, &data->m_taintObject);
    TheTaintManager->bfmeApplyCircleWorld((const BfmePointFC *)loc, radius, 0, true);
	}
}
