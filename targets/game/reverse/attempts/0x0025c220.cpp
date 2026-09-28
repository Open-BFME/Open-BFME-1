// ?finish@ElvenWoodSpecialPower@@QAEXPAVSpecialPowerLocation@@@Z
// partial score=0.3325 date=2026-09-28
// ?finish@ElvenWoodSpecialPower@@QAEXPAVSpecialPowerLocation@@@Z
// retail RVA 0x0025C220, 1152 bytes.  Attempt reconstruction; not yet exact.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Identity.  The matched caller
// ElvenWoodSpecialPowerDoSpecialPowerAtLocation.cpp (retail 0x0025CAA0, the
// doSpecialPowerAtLocation override) reaches this body through the ILT thunk
// 0x0003E757, whose ledger pin is
// ?finish@ElvenWoodSpecialPower@@QAEXPAVSpecialPowerLocation@@@Z, and the body
// ends in `ret 4`, so it takes exactly that one pointer.  The receiver is the
// ElvenWoodSpecialPower module: +0x04 is the module data and +0x08 is the
// Object.  The shipped random-site string in the neighbouring body
// Rva0025C7C0ElvenWoodChoice.cpp pins the file:
// "F:\bfme\Code\gameengine\Source\GameLogic\Object\SpecialPower\
//  ElvenWoodSpecialPower.cpp", line 232, which is after this body.
//
// Frame.  Retail reserves 0xB8 and lays it out (offsets from the bottom of the
// `sub esp,0xb8` block, called F below):
//
//   F+0x00  BfmeWideResult        the one partition result, reused by both
//                                sweeps; the second sweep copy-assigns through
//                                a fresh temporary at F+0x08
//   F+0x04  Real                  m_moduleData->m_radius
//   F+0x08  Object *              the `next()` out-parameter, and the temporary
//                                the second sweep's result is built in
//   F+0x0C  ModuleData *          m_moduleData (this + 4), cached
//   F+0x10  Object *              m_object (this + 8), cached
//   F+0x14  24 bytes              the second kind mask; later the status mask,
//                                then the Coord3D copies handed to the taint
//                                circle and the thing-FX list
//   F+0x2C  24 bytes              the first kind mask; dies at the filter
//                                constructor and is reused by the set
//   F+0x44  ElvenWoodSpecialPower *  this, cached for applyAt0025C010
//   F+0x48  PartitionFilterAcceptByKindOf  (0x30 bytes)
//   F+0x80  PartitionFilterAcceptByKindOf  (0x30 bytes)
//
// Both filters take the same mask -- bit 147 (dword 4 = 0x00800000) of a
// 192-bit KindOfMaskType -- and KINDOFMASK_NONE (0x012ED8B8) as must-be-clear.
// The two partition queries are radius*2.1 (0x010B4BCC) and radius*4.0
// (0x01075340); the closing taint circle is radius+50.0 (0x0107FAA8).  The
// per-object tint test reads bit 83 (0x00080000 of the object's third status
// word) and the single setStatus call sets bit 83 of the first status word.
// Nothing in the binary names those bits, so they stay address-derived.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <bitset>
#include <set>
#include <vector>
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

// The two bit indices the body witnesses.  Bit 147 of a 192-bit
// KindOfMaskType is dword 4 bit 19; bit 83 of the 96-bit status mask used by
// Object::setStatus is dword 2 bit 19 as well.
enum
{
	// The kind filter's set bit lands in dword 4 of the 24-byte mask as
	// 0x00800000, so the index is 4*32+23 = 151 -- not the 147 the earlier
	// banked attempt used, which emitted 0x00080000 in dword 2.
	RVA_0025C220_KIND_BIT = 151,
	// setStatus's 12-byte mask is F+0x14 with dword 2 = 0x00080000, and the
	// per-object tint test reads the same value out of Object+0x98, so the
	// index is 2*32+19 = 83.
	RVA_0025C220_STATUS_BIT = 83
};

template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;

public:
	enum BogusInitType { kInit = 0 };

	BitFlags(BogusInitType, Int idx1, Int idx2)
	{
		m_bits._Unchecked_set((size_t)idx1);
		m_bits._Unchecked_set((size_t)idx2);
	}

	Bool test(Int idx) const
	{
		return m_bits._Unchecked_test((size_t)idx);
	}
};

typedef BitFlags<192> KindOfMaskType;
typedef BitFlags<96> StatusMaskType;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Matrix3D
{
	int m_unknown[9];
};

class Object;
class Player;
class FXList;
class BfmeTaintManager;
class Rva0025C220TerrainLogic;
class Rva0025C220ThingFB;
class GameLogic;
class Rva0025C7C0Location;
class PartitionFilterAcceptByKindOf;

//----------------------------------------------------------------------------
// The owning-result partition iterator.  An owning std::vector of 8-byte
// entries plus a cursor and a reference count, behind a 4-byte handle, with a
// hand-written copy constructor, destructor and copy assignment so that
// MSVC 7.1 emits the same destroy-then-copy shape retail has after the
// second query (the self test is `lea ecx,[F+0x00]; cmp ecx,esi`).
//----------------------------------------------------------------------------
struct BfmeWideEntry
{
	Object *object;
	UnsignedInt unknown04;
};

struct BfmeWideData
{
	std::vector<BfmeWideEntry> entries;
	BfmeWideEntry *current;
	Int references;
};

struct BfmeWideResult
{
	BfmeWideData *value;

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
		object = value->current->object;
		++value->current;
		return object;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(const Coord3D *position, Real range,
		Int order, PartitionFilterAcceptByKindOf *filter, Bool mustBeValid);
};

// The three radius constants the body reads, and the singletons it reaches
// the partition manager, the taint manager and the terrain through.
extern const Real BfmeRva0025C220RangeScale;    // 0x010B4BCC = 2.1
extern const Real BfmeRva0025C220TaintScale;    // 0x01075340 = 4.0
extern const Real BfmeRva0025C220TaintMargin;   // 0x0107FAA8 = 50.0

extern BfmeWideForwardC *ThePartitionManager;
extern const KindOfMaskType KINDOFMASK_NONE;
extern Rva0025C220TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;
extern BfmeTaintManager *TheTaintManager;

class FXList
{
public:
	Bool bfmeIsBlocked() const;
	void doFXPos(const Coord3D *position, const Matrix3D *a,
		const Matrix3D *b, Int mode) const;
};

class BfmeTaintManager
{
public:
	void bfmeApplyCircleWorld(const Coord3D *centre, Real range,
		unsigned char tint, Bool permanent);
};

class GameLogic
{
public:
	void destroyObject(Object *object);
};

class Rva0025C220ThingFB
{
public:
	void tellFB(Object *owner, Coord3D position, void *a, void *b);
};

// The terrain singleton's clearOne (ILT 0x000017CB -> 0x001AC3D0) plus the two
// four-argument thunks the body calls after the sweeps: 0x00042CD0 ->
// 0x001A64F0 and 0x00037330 -> 0x001A3190.
class Rva0025C220TerrainLogic
{
public:
	void clearOne001AC3D0(const Coord3D *position, Real range);
	void adapter001A64F0(const Coord3D *position, Real range, Int order);
	void forward001A3190(const Coord3D *position, Real range, Int order);
};

//----------------------------------------------------------------------------
// The BFME partition filters: the out-of-line constructor at 0x000C3DD0
// (ILT 0x000382FD) stores the PartitionFilter vtable, zeroes the next pointer
// and copies the two 24-byte masks to +0x08 and +0x20.
//----------------------------------------------------------------------------
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

//----------------------------------------------------------------------------
// The Object fields the body witnesses: +0x38 is the position, +0x90 the
// 96-bit status mask whose third word the tint test reads.
//----------------------------------------------------------------------------
class Object
{
public:
	Player *getControllingPlayer() const;
	void setStatus(const StatusMaskType &status, Bool on);

	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x4c];
	StatusMaskType m_status;   // +0x90
};

//----------------------------------------------------------------------------
// The module data: +0x21C the template name the lookup at 0x0025C010 takes,
// +0x224 the radius, +0x228 the FX list, +0x22C the thing-FX list.
//----------------------------------------------------------------------------
struct ElvenWoodSpecialPowerModuleData
{
	unsigned char m_pad00[0x21c];
	AsciiString m_templateName;
	unsigned char m_pad220[4];
	Real m_radius;
	FXList *m_fxList;
	Rva0025C220ThingFB *m_thingFB;
};

// A SpecialPowerLocation leads with its position: the body passes the
// location itself wherever a Coord3D * is expected.
class SpecialPowerLocation
{
public:
	Coord3D m_position;
};

// The template lookup at 0x0025C010, reached through ILT 0x00028C5E; the
// neighbouring body calls it on the same receiver.
class Rva0025C7C0Owner
{
public:
	void *applyAt0025C010(Rva0025C7C0Location *location,
		const AsciiString &name);
};

//----------------------------------------------------------------------------
class ElvenWoodSpecialPower : public Rva0025C7C0Owner
{
public:
	void finish(SpecialPowerLocation *subject);

private:
	void *m_vtable;                                // this + 0
	ElvenWoodSpecialPowerModuleData *m_moduleData;   // this + 4
	Object *m_object;                                // this + 8
};

// Every callee here is reached through an ILT thunk in retail, so each
// declaration below is redirected to the thunk the body actually calls.
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?setStatus@Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z=?j_000307E7@@YAXXZ")
#pragma comment(linker, "/alternatename:?destroyObject@GameLogic@@QAEXPAVObject@@@Z=?j_0001D0DE@@YAXXZ")
#pragma comment(linker, "/alternatename:?doFXPos@FXList@@QBEXPBUCoord3D@@PBVMatrix3D@@M0@Z=?j_0001BB21@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeIsBlocked@FXList@@QBE_NXZ=?j_00011F77@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeApplyCircleWorld@BfmeTaintManager@@QAEXPBUBfmePointFC@@MH_N@Z=?j_0008810D0@@YAXXZ")
#pragma comment(linker, "/alternatename:?adapter001A64F0@Rva0025C220TerrainLogic@@QAEXPBUCoord3D@@MH0@Z=?j_00042cd0@@YAXXZ")
#pragma comment(linker, "/alternatename:?forward001A3190@Rva0025C220TerrainLogic@@QAEXPBUCoord3D@@MH0@Z=?j_00037330@@YAXXZ")
#pragma comment(linker, "/alternatename:?clearOne001AC3D0@Rva0025C220TerrainLogic@@QAEXPBUCoord3D@@MH@Z=?j_000017cb@@YAXXZ")
#pragma comment(linker, "/alternatename:?tellFB@Rva0025C220ThingFB@@QAEXPAXPAUBCoord3D@@PAX0@Z=?j_00002a59@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeForwardWideC@BfmeWideForwardC@@QAE?AUBfmeWideResult@@HHHHH@Z=?j_0009f2960@@YAXXZ")

// ?finish@ElvenWoodSpecialPower@@QAEXPAVSpecialPowerLocation@@@Z
// retail 0x0025C220
void ElvenWoodSpecialPower::finish(SpecialPowerLocation *subject)
{
	// Retail's prologue caches the module data, reads +0x224 for the radius,
	// caches the Object and this.  The two kind masks and the two filters
	// occupy F+0x14/F+0x2C and F+0x48/F+0x80 respectively.
	// Slot map verified against the retail body (offsets from the top of the
	// `sub esp,0xb8` block):
	//   F+0x00 BfmeWideResult  the one partition result; the second sweep
	//                          copy-assigns into it
	//   F+0x04 Real            m_moduleData->m_radius
	//   F+0x08 Object *        the next() out-parameter, then the temporary
	//                          the second sweep's result is built in
	//   F+0x0C ModuleData *    m_moduleData (this + 4)
	//   F+0x10 Object *        m_object (this + 8)
	//   F+0x14 24 bytes        the second kind mask; later the 12-byte status
	//                          mask, the Coord3D copies and the set pointer
	//   F+0x2C 24 bytes        the first kind mask, later the owning set
	//   F+0x44 this
	//   F+0x48 PartitionFilterAcceptByKindOf (0x30 bytes)
	//   F+0x80 PartitionFilterAcceptByKindOf (0x30 bytes)
	//   F+0xC0 the `push -1` slot MSVC uses for the /EHsc state byte
	ElvenWoodSpecialPowerModuleData *const data = m_moduleData;
	Real const range = data->m_radius;
	Object *const owner = m_object;

	// First sweep: everything the wider circle holds that belongs to another
	// player is remembered and destroyed, so that the second sweep only has
	// to taint what is left standing.
	KindOfMaskType wanted(KindOfMaskType::kInit, RVA_0025C220_KIND_BIT,
		RVA_0025C220_KIND_BIT);
	PartitionFilterAcceptByKindOf firstFilter(wanted, KINDOFMASK_NONE);
	BfmeWideResult found = ThePartitionManager->bfmeForwardWideC(
		&subject->m_position, range * BfmeRva0025C220RangeScale, 0,
		&firstFilter, 1);
	_STL::set<Object *> destroyed;
	Object *object;
	while (found.next(object))
	{
		if (object->getControllingPlayer() == owner->getControllingPlayer())
			continue;
		destroyed.insert(object);
		TheTerrainLogic->clearOne001AC3D0(&object->m_position, range);
		TheGameLogic->destroyObject(object);
	}

	// Second sweep: the same kind mask over the tighter circle, tainting
	// every survivor the first sweep did not claim.
	KindOfMaskType wantedToo(KindOfMaskType::kInit, RVA_0025C220_KIND_BIT,
		RVA_0025C220_KIND_BIT);
	PartitionFilterAcceptByKindOf secondFilter(wantedToo, KINDOFMASK_NONE);
	found = ThePartitionManager->bfmeForwardWideC(&subject->m_position,
		range * BfmeRva0025C220TaintScale, 0, &secondFilter, 1);
	while (found.next(object))
	{
		if (object->getControllingPlayer() == owner->getControllingPlayer())
			continue;
		if (destroyed.find(object) != destroyed.end())
			continue;
		Coord3D centre = object->m_position;
		TheTaintManager->bfmeApplyCircleWorld(&centre, range,
			object->m_status.test(RVA_0025C220_STATUS_BIT) ? 0xff : 0, 1);
	}

	// Close the power out on the ground the player clicked.
	TheTerrainLogic->adapter001A64F0(&subject->m_position, range, 2);
	TheTerrainLogic->forward001A3190(&subject->m_position,
		range + BfmeRva0025C220TaintMargin, 2);
	if (data->m_fxList != 0 && !data->m_fxList->bfmeIsBlocked())
		data->m_fxList->doFXPos(&subject->m_position, 0, 0, 0);
	if (data->m_thingFB != 0)
		data->m_thingFB->tellFB(owner, subject->m_position, 0, 0);

	Object *named = (Object *)applyAt0025C010(
		(Rva0025C7C0Location *)subject, data->m_templateName);
	if (named != 0)
		named->setStatus(StatusMaskType(StatusMaskType::kInit,
			RVA_0025C220_STATUS_BIT, RVA_0025C220_STATUS_BIT), 1);
	TheTaintManager->bfmeApplyCircleWorld(&subject->m_position, range,
		0xff, 1);
}
