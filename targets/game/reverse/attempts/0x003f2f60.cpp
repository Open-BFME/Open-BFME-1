// ?findPath@Pathfinder@@EAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@2@Z
// partial score=0.9 date=2026-09-28
// Pathfinder::findPath -- retail RVA 0x003F2F60, 1016 bytes.
//
// Identity: the lift name is confirmed and cited rather than guessed. The
// body installs nothing, but nine CRCParameterCheck traces inside it name the
// method ("Pathfinder::FindPath() called") and each callee it reaches
// ("QuickDoesPathExist", "CheckDestination", "FindHierarchicalPath"), the
// ParamCheck format string it hands to retail's own logger at 0x00065C80 is
// "Pathfinder::CheckDestination called with: ..." which only this body's
// checkDestination call can produce, and the ledger's virtual AIUpdate caller
// plus the Zero Hour twin at
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp:6388
// fix the parameter list (Object*, const LocomotorSet&, const Coord3D* from,
// const Coord3D* rawTo) and the `ret 0x10` cleanup.
//
// The real body goes here rather than into AIPathfind.cpp: that translation
// unit is the Zero Hour layout, its LocomotorSet has no AsciiString at +0x18
// and its headers know nothing of CRCParameterCheck, and vendored-header edits
// cost a full gate for every dependent body. Every class below is TU-local,
// exactly as PathfinderDestinationWork.cpp and PathfinderAdjustDestination003F6090.cpp
// do for the neighbouring BFME-layout Pathfinder bodies.
//
// Reconstruction shapes, not claims about upstream spelling:
//  - clip() takes the two world points, worldToCell() then writes the cell of
//    the clipped destination into the FIRST copy through its ICoord2D view, so
//    the same 12 bytes are the world point going in and the cell coming out.
//    That is why checkDestination and the "cell=%d,%d" trace read them as
//    integers while the "%g" trace reads the originals as reals.
//  - the override walk keeps upstream's inline recursive getFinalOverride,
//    inlined one level, which leaves `test m_template` and
//    `test m_nextOverride` sharing a jump target; the +0x2470C vector erase is
//    STLport's random-access __copy via vector::clear(), so the tag object is
//    materialised after its two pointer arguments.
//
// STATE OF PLAY (tools/probe.py --shape on THIS EXACT FILE: ours=1017 bytes,
// retail=1016, shape 0.985, 9 structural differences, 340 instructions on each
// side -- the instruction COUNT already agrees, so nothing is missing here,
// only mis-scheduled).
//
// !! KEEP THIS FILE UNDER ~18.4 KB (it is ~18.3 KB) AND RE-PROBE AFTER ANY
//    EDIT.  MSVC 7.1 flips this function's codegen when the TRANSLATION UNIT's
//    total size crosses ~18.4 KB even though the token stream is byte
//    identical: at 16.0 KB this code compiles to 1017 bytes (0.985), at
//    19.99 KB the SAME code compiles to 1020 bytes (0.968, 339 instructions).
//    Measured with one-line comment fillers, so it is SOURCE SIZE and not
//    line count (12 long filler lines flip it, 101 short ones do not).  A
//    long header therefore silently changes the measurement -- trim the
//    notes, do not just append them.
//
//  THE LEVER THAT GOT HERE (do not undo): `volatile` on all THREE pointer
//  parameters.  Without it the allocator gives esi=this, edi=obj and spills
//  from/rawTo: 987 bytes, 0.915, 30 differences.  With it the callee-saved
//  assignment is esi=this, ebx=from ([ebp+0x10]), edi=rawTo ([ebp+0x14]) and
//  obj is re-loaded from [ebp+8] at every use -- retail's allocation exactly.
//  `volatile` on `obj` ALONE is 1011 bytes / 0.892.  It is a reconstruction
//  device, not a claim about upstream spelling.
//
//  ALREADY CORRECT, do not "fix" it again: the nine trace sites and their
//  guard shape (`if (Glo012F0239 && TheCRCParameterCheck) { log(msg); if
//  (TheCRCParameterCheck) { log(fmt, ...) } }` -- the redundant re-test is
//  real and produces retail's two back-to-back CRC loads around every trace);
//  every format string and the whole varargs marshalling including the six
//  `fstp qword` promotions and the `add esp,0x40`/`0x20` fixups; the
//  AsciiString fallback `m_data ? m_data + 8 : 0x0107388B` (the payload must
//  stay an opaque `const char *` -- naming the header struct folds the add
//  into a lea); the class layout m_zoneManager at +0x0c9c and the point
//  vector at +0x2470c and the five-argument `std::copy` that clear() lowers
//  to; clip() argument order; worldToCell writing the cell through the first
//  copy's ICoord2D view; the eight-argument checkDestination shape (obj,
//  cell.x, cell.y, destinationLayer, radius, centerInCell, &out, 1); ~Path
//  called DIRECTLY so it must stay non-virtual; and the member-wise copy
//  `adjustTo.x = toPoint->x; ...` plus a `_ReadWriteBarrier()` BEFORE clip().
//  That last pair is what closed the copy block: as `Coord3D adjustTo =
//  *toPoint;` the compiler materialises the source pointer first
//  (`mov eax,edi`, two bytes longer than retail) and splits the copy in two.
//  Member-wise with the barrier it reads [edi+0..8] and [ebx+0..8] directly,
//  interleaves the two copies as retail does, and that block is now
//  byte-count-identical to retail (57 bytes, 15 instructions each).
//
//  STILL OPEN -- four residues, all scheduling, none missing code:
//  (1) PROLOGUE COPY-IN ORDER (2 diffs, byte-neutral).  The variable->register
//      map is IDENTICAL; only the emission order differs.  Retail emits each
//      copy-in right after the push of ITS register; we emit both after all
//      three pushes.
//  (2) TheCRCParameterCheck RELOAD in the FIRST trace (2 diffs) -- and this
//      is the ONLY size difference in the body: `mov eax,[addr]` is the
//      5-byte moffs form, `mov edx,[addr]` the 6-byte ModRM form, so
//      1017-vs-1016 is exactly this.  Both sides have three CRC loads in the
//      block.  Retail's argument load lands in EAX after `push eax` frees
//      it; we hoist ours into EDX before the float block, the only register
//      free there.  Retail keeps the locomotorSet name in EDX, we use ECX --
//      that register choice is the lever nobody has isolated yet.
//  (3) The from.z STORE PLACEMENT (2 diffs, byte-neutral): retail defers it
//      past the first `push` of the clip() arguments; we store it before.
//      All six stores are already in retail's order.
//  (4) The TheTerrainLogic LOAD (2 diffs, byte-neutral) is most likely an
//      aligner artefact of the +1 byte from (2), not a real difference.
//
//  LEVERS ALREADY TRIED, none of which moved it (do not repeat):
//   - dropping the fromPoint/toPoint aliases: WORSE (1028, 0.815).  They are
//     load-bearing -- they are what puts the locomotorSet name in the
//     [esp+0x14] slot instead of a register;
//   - hoisting the six log floats into Real locals: worse (frame 0x2c->0x3c);
//   - hoisting the two trace names into locals: removes (2) but breaks the
//     [esp+0x14] slot (1000 bytes, 0.965);
//   - reversing the alias order (fromPoint first): 0.929.  FIRST-reference
//     order picks BOTH the register and the emission order and always lands
//     the first-referenced value in EDI, while retail's first copy-in is EBX,
//     so the alias order cannot fix (1);
//   - `const Coord3D * const` aliases, `from ? from : from`, duplicate alias
//     reads, an early `fromPoint == 0` test, a barrier at function entry,
//     `!= 0` instead of truthiness on the CRC guards, a CRC local for the
//     guard only, `crc ? crc : 0` on the argument, memcpy for the copies,
//     interleaved member assignment, `Coord3D a = *p, b = *q;`: all
//     byte-identical or worse;
//   - shape_search over all 4 choices shape_family_levers.py offers for
//     sib,register,bool,test,copy,store,loop,branch,constant,frame: 9 trials,
//     no improvement.  The mechanical levers for this family are exhausted.
//
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// stlport
#include <vector>

typedef int Int;
typedef unsigned char Bool;
typedef float Real;

// Retail's own logger, 0x00065C80, reached through ILT thunk 0x0003A17A.
class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern bool Glo012F0239;							///< retail [0x012F0239]
extern "C" void __cdecl bfmeRetailCritterDesyncLog(CRCParameterCheck *, const char *, ...);

namespace Fp003F2F60
{
// The landed 168x552 mark grid, unchanged, so bfmeClearAL/bfmeFillAL resolve.
#include "../../Common/BfmeOneHundredSixtyEight.cpp"
}

// The empty AsciiString retail falls back to, 0x0107388B.
static const char Rva0107388BEmpty[] = "";

struct BfmeAsciiStringData
{
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

// BFME's StringBase<char>: the payload pointer is the only member and the
// characters start eight bytes into its buffer, so an unset string reads as
// the shared empty literal rather than as a null.  The payload stays an opaque
// `const char *` (the BfmeGrokSetIns.cpp spelling) because retail walks off it
// with a plain `add ...,8`; naming the header struct here folds that into a
// `lea ..., [eax+8]` and loses the shape at all three trace sites.
class BfmeAsciiString
{
public:
	const char *str() const { return m_data ? m_data + 8 : Rva0107388BEmpty; }

private:
	const char *m_data;
};

// The override walk, inlined one level at each call site; the recursive step
// stays out of line, which is the shape retail has at all three trace sites.
class BfmeFindPathOverridable
{
public:
	__declspec(noinline) BfmeFindPathOverridable *friend_getFinalOverride();
	BfmeFindPathOverridable *getFinalOverride()
	{
		return m_override ? m_override->friend_getFinalOverride() : this;
	}

	Int m_unknown00;
	BfmeFindPathOverridable *m_override;
};

BfmeFindPathOverridable *BfmeFindPathOverridable::friend_getFinalOverride()
{
	if (m_override)
		return m_override->friend_getFinalOverride();
	return this;
}

// The template name the trace prints. Only the +0x20 AsciiString is read.
class BfmeFindPathTemplate : public BfmeFindPathOverridable
{
public:
	char m_unmodelled08[0x20 - 8];
	BfmeAsciiString m_nameString;					///< retail this+0x20
};

enum PlayerType { PLAYER_HUMAN = 0, PLAYER_COMPUTER = 1 };

class Player
{
public:
	PlayerType getPlayerType() const { return m_playerType; }

	char m_unmodelled00[0x2c];
	PlayerType m_playerType;						///< retail this+0x2c
};

// upstream layout: .../GameEngine/Include/GameLogic/LocomotorSet.h plus the
// BFME-only m_name the trace prints at +0x18.
class LocomotorSet
{
public:
	Int getValidSurfaces() const { return m_validLocomotorSurfaces; }

	char m_unmodelled00[0x10];
	Int m_validLocomotorSurfaces;					///< retail this+0x10
	char m_unmodelled14[0x18 - 0x14];
	BfmeAsciiString m_name;						///< retail this+0x18
};

// upstream layout: .../GameEngine/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: .../GameEngine/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum { LAYER_INVALID = 0 };

class Object
{
public:
	__forceinline BfmeFindPathTemplate *getTemplate() const
	{
		BfmeFindPathTemplate *t = m_template;
		if (t && t->m_override)
			t = (BfmeFindPathTemplate *)t->m_override->friend_getFinalOverride();
		return t;
	}
	Player *getControllingPlayer() const;			///< ILT thunk at 0x00020824

	void *m_vtable;									///< retail this+0x00
	BfmeFindPathTemplate *m_template;				///< retail this+0x04
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *, const Coord3D *);
};

extern TerrainLogic *TheTerrainLogic;				///< retail [0x012EF4CC]

class Path
{
public:
	// Non-virtual on purpose: retail destroys through a direct call
	// (??1Path@@MAE@XZ at 0x003FEB80), so declaring the dtor virtual here
	// would emit a vtable load and an indirect call instead.
	~Path();
};

class Pathfinder
{
private:
	virtual Path *findPath(Object *obj, const LocomotorSet &locomotorSet,
		const Coord3D *from, const Coord3D *rawTo);

public:
	Bool clientSafeQuickDoesPathExist(Object *, const Coord3D *, const Coord3D *, Bool);
	void clip(Coord3D *from, Coord3D *to);
	Bool checkDestination(Object *, Int, Int, PathfindLayerEnum, Int, Bool, Int **, Bool);
	Path *findHierarchicalPath(Bool, Int, Object *, const Coord3D *, const Coord3D *, Bool, Bool);
	Path *internalFindPath(Object *, const LocomotorSet &, const Coord3D *, const Coord3D *);

protected:
	void getRadiusAndCenter(const Object *, Int &, Bool &);
	Bool worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex);

private:
	// The compiler-inserted vptr already occupies this+0x00 (findPath is
	// virtual, which is what the EA in the mangled name records), so there is
	// NO explicit vtable member here: adding one shifts every later field by
	// four and lands the zone manager on 0x0ca0 instead of retail's 0x0c9c.
	char m_unmodelled00[0xc9c - 4];
	Fp003F2F60::BfmeGridAL m_zoneManager;			///< retail this+0x0c9c
	char m_unmodelledca0[0x2470c - 0x242d0];
	std::vector<Coord3D> m_hierPoints;				///< retail this+0x2470c
};

Path *Pathfinder::findPath(Object * volatile obj, const LocomotorSet &locomotorSet,
	const Coord3D * volatile from, const Coord3D * volatile rawTo)
{
	const Coord3D *toPoint = rawTo;
	const Coord3D *fromPoint = from;
	if (Glo012F0239 && TheCRCParameterCheck)
	{
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
			"CritterDesync:    Pathfinder::FindPath() called");
		if (TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
				"    obj=%s, locomotorSet=%s, from=%g,%g,%g, to=%g,%g,%g",
				obj->getTemplate()->m_nameString.str(),
				locomotorSet.m_name.str(),
				fromPoint->x, fromPoint->y, fromPoint->z, toPoint->x, toPoint->y, toPoint->z);
	}

	if (!clientSafeQuickDoesPathExist(obj, fromPoint, toPoint, false))
	{
		if (Glo012F0239 && TheCRCParameterCheck)
		{
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
				"CritterDesync:    QuickDoesPathExist failed, returning NULL");
			if (TheCRCParameterCheck)
				bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
					"    obj=%s, locomotorSet=%s, from=%g,%g,%g",
					obj->getTemplate()->m_nameString.str(),
					locomotorSet.m_name.str(),
					fromPoint->x, fromPoint->y, fromPoint->z, toPoint->x, toPoint->y, toPoint->z);
		}
		return 0;
	}

	{
		Bool centerInCell = true;
		Int radius = 0;
		getRadiusAndCenter(obj, radius, centerInCell);

		Coord3D adjustTo, adjustFrom;
		adjustTo.x = toPoint->x;
		adjustTo.y = toPoint->y;
		adjustTo.z = toPoint->z;
		adjustFrom.x = fromPoint->x;
		adjustFrom.y = fromPoint->y;
		adjustFrom.z = fromPoint->z;
		_ReadWriteBarrier();
		clip(&adjustFrom, &adjustTo);
		worldToCell(&adjustTo, (ICoord2D *)&adjustFrom);
		PathfindLayerEnum destinationLayer =
			TheTerrainLogic->getLayerForDestination(obj, &adjustTo);

		Int *destinationPoints;
		ICoord2D *cell = (ICoord2D *)&adjustFrom;
		if (!checkDestination(obj, cell->x, cell->y, destinationLayer, radius,
				centerInCell, &destinationPoints, true))
		{
			if (Glo012F0239 && TheCRCParameterCheck)
			{
				bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
					"CritterDesync:    CheckDestination() failed, returning NULL");
				if (TheCRCParameterCheck)
					bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
						"    obj=%s, cell=%d,%d, destinationLayer=%d, radius=%d, centerInCell=%s",
						obj->getTemplate()->m_nameString.str(),
						cell->x, cell->y, destinationLayer, radius,
						centerInCell ? "TRUE" : "FALSE");
			}
			return 0;
		}

		Bool isHuman = true;
		if (obj->getControllingPlayer() &&
				obj->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER)
		{
			if (Glo012F0239 && TheCRCParameterCheck)
				bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
					"CritterDesync:    isHuman set to FALSE");
			isHuman = false;			// computer gets to cheat.
		}

		m_hierPoints.clear();
		m_zoneManager.bfmeClearAL();

		Path *hPat = findHierarchicalPath(isHuman,
			locomotorSet.getValidSurfaces(), obj, fromPoint, toPoint, false, false);
		if (hPat)
		{
			if (Glo012F0239 && TheCRCParameterCheck)
				bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
					"CritterDesync:    FindHierarchicalPath succeeds");
			hPat->~Path();
			::operator delete(hPat);
		}
		else
		{
			if (Glo012F0239 && TheCRCParameterCheck)
				bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
					"CritterDesync:    FindHierarchicalPath fails");
			m_zoneManager.bfmeFillAL();
		}

		return internalFindPath(obj, locomotorSet, fromPoint, toPoint);
	}
}

#pragma comment(linker, "/alternatename:_bfmeRetailCritterDesyncLog=?j_0003a17a@@YAXXZ")
#pragma comment(linker, "/alternatename:?friend_getFinalOverride@BfmeFindPathOverridable@@QAEPAV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?getRadiusAndCenter@Pathfinder@@IAEXPBVObject@@AAHAA_N@Z=?j_000461ff@@YAXXZ")
#pragma comment(linker, "/alternatename:?clip@Pathfinder@@QAEXPAUCoord3D@@0@Z=?j_00041bff@@YAXXZ")
#pragma comment(linker, "/alternatename:?worldToCell@Pathfinder@@QAE_NPBVCoord3D@@PAUICoord2D@@@Z=?j_000171e8@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLayerForDestination@TerrainLogic@@QAE?AW4PathfindLayerEnum@@PAVObject@@PBVCoord3D@@@Z=?j_0001c675@@YAXXZ")
#pragma comment(linker, "/alternatename:?checkDestination@Pathfinder@@QAE_NPAVObject@@HHW4PathfindLayerEnum@@H_NPAAPAAPA_N@Z=?j_00049f3f@@YAXXZ")
#pragma comment(linker, "/alternatename:?clientSafeQuickDoesPathExist@Pathfinder@@QAE_NPAVObject@@PBVCoord3D@@0_N@Z=?j_0004a327@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeClearAL@Fp003F2F60@BfmeGridAL@@QAEXXZ=?j_0000145b@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeFillAL@Fp003F2F60@BfmeGridAL@@QAEXXZ=?j_00010fa5@@YAXXZ")
#pragma comment(linker, "/alternatename:?findHierarchicalPath@Pathfinder@@QAEPAVPath@@_NPAVObject@@PBVCoord3D@@0_N1@Z=?j_0001fa14@@YAXXZ")
#pragma comment(linker, "/alternatename:?internalFindPath@Pathfinder@@QAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBVCoord3D@@2@Z=?j_000155eb@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Path@@QAE@XZ=?j_0000ca68@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Path@@MAE@XZ=?j_0000ca68@@YAXXZ")
