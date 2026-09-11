// ?ParseObjectDataChunk@WorldHeightMap@@KA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// partial score=0.97 date=2026-09-12
// Stashed reconstruction attempt for WorldHeightMap::ParseObjectDataChunk,
// retail RVA 0x00088B70, 545 bytes (dump d_00088b70.asm / d_0007cab0.asm).
// This body is not a standalone TU: it belongs inline in
// Code/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp,
// replacing the "present-unmatched" ParseObjectDataChunk/ParseObjectData
// pair at the same spot (the two-function ZH split is gone in retail; this
// merges them). Land by pasting the declarations + function back in there
// with the same // cl: line, not by compiling this file on its own.
//
// Symbol: ?ParseObjectDataChunk@WorldHeightMap@@KA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// (protected static, cdecl, bool return -- confirmed by callers already
// matched under real names: acceptsThingTemplateName@Rva00137E20ThingNameFilter
// at 0x00137E20 names its caller "ParseObjectDataChunk", and the
// _M_find@Rva00137E20ThingNameRegistry pin note says "reached from
// ParseObjectDataChunk predicate". The mangled name was verified against
// this exact signature with a throwaway cl.exe compile.
//
// Every pin this body needs is already in reverse/symbols.csv (search for
// "0x00088B70" in the notes column). THE PIN VALUES don't depend on any
// part of this file landing; they're additive candidate resolutions and are
// safe to keep.
//
// PROGRESS THIS SESSION (2026-09-12): probe.py now reports ours=541,
// retail=545 -- only 4 bytes off, up from the prior bank's ours=489
// (56 bytes off). The prior bank treated "return value shape" and "tail
// merging" as two separate residual gaps; they are THE SAME root cause.
//
// THE KEY FIX: the early "z out of range" exit must `return false;`, not
// `return true;`. Retail's compiled bytes prove this directly: the early
// exit's tail does `xor eax,eax` (returns 0) while the normal-completion
// tail does `mov eax,esi` (copies the raw MapObject pointer, non-zero/
// truthy). Because the two exits return DIFFERENT values, MSVC 7.1 cannot
// share one epilogue between them and compiles two separate release-and-
// return blocks, exactly matching retail's layout (0x160-0x1ec normal-path
// cleanup+return, 0x1ed-0x220 early-exit cleanup+return, near-duplicates of
// each other). The prior bank's source had BOTH exits returning `true`,
// which gave MSVC an identical byte sequence to fold into one shared tail
// (ours=489B) -- that fold was not a compiler quirk to work around with a
// nested-scope/tail-merge trick, it was CORRECT compiler behavior given a
// wrong source (both paths truly did return the same value). Restructuring
// with if/else vs. a bare early-return-then-fallthrough made no measured
// difference (both compile to 541B, confirmed by probe.py) -- the return
// VALUE divergence is what un-merges the tails, not the source's control
// shape. shape_levers.md's "tail merge" lever does not apply here; retag
// any future search for this symptom to check return-value divergence
// FIRST.
//
// This flips ZH's original semantics (ZH's ParseObjectData always
// `return true;`, even when discarding an out-of-range object) but matches
// retail's actual bytes, which is the standard this project measures
// against.
//
// TWO NAMED RESIDUAL GAPS REMAIN (4 bytes / a few instructions, not closed
// this session; both match previously-documented toolchain walls -- do not
// grind further without a genuinely new lever):
//
// 1. Missing EH bookkeeping: retail emits `mov dword ptr [esp+0x38], esp`
//    immediately before `call ctor` (this session's probe: retail offset
//    +0153); ours instead calls the ctor directly, 4 bytes shorter. This is
//    docs/lessons.md's "EH-temporary transposition" class (`mov [esp+N],esp`
//    recording a by-value-class-argument address before the ctor's `this`
//    setup). RULED OUT THIS SESSION: the documented fix for that exact
//    symptom -- passing the by-value argument through a StringInline-style
//    class whose copy ctor/dtor are INLINE FORWARDERS to an out-of-line
//    base (reference/shims/stringinline/StringInline.h pattern, base pins
//    already in symbols.csv as Rva0041230aNameBase ctor 0x00887B60 / dtor
//    0x00887940) -- does NOT apply to this call site. Declaring the
//    MapObject-alias ctor's `name` parameter BY VALUE as this inline-
//    forwarding type and passing `name` (not `nameRef`) regressed to
//    ours=555B (10 bytes OVER retail, not under) with esi/edi register
//    churn appearing much earlier in the body (edi used from +0xf3 on,
//    where retail and the by-ref version both use esi) -- i.e. retail does
//    NOT actually construct a by-value AsciiString copy at this call site
//    (no visible copy-ctor call in retail's bytes either), so the missing
//    instruction is NOT the by-value-string-argument case the lesson
//    documents. Left unresolved: whether it's an EH record for `loc`
//    (Coord3D, POD, passed by value with no destructor -- would be unusual
//    for MSVC to need an unwind record for a trivially-destructible
//    struct) or for the raw operator-new(0x60) memory block (placement-
//    delete-on-throw bookkeeping for the `new Rva0041230aMapObject(...)`
//    expression itself). Previously also ruled out (earlier session): plain
//    new-expression, explicit placement-new+null-check, split decl/
//    assignment, by-ref vs by-value name (this session re-confirmed by-value
//    regresses), and a StringInline-style forwarding wrapper on the name
//    argument specifically (this session, see above -- same conclusion via
//    a different, now-confirmed route).
//
// 2. Return-value normalization on the SUCCESS path: retail's `mov eax,esi`
//    copies the raw MapObject pointer into eax without normalizing to 0/1,
//    even though the mangled name's `_N` return-type code and the pristine
//    vendored reference header (WorldHeightMap.h) both confirm the return
//    type is genuinely `Bool` (=C++ bool, confirmed via
//    Libraries/Include/Lib/BaseType.h's `typedef bool Bool;`). A `bool`-
//    returning function performing a pointer-to-bool conversion should
//    normalize via test+setne under standard C++ semantics, which MSVC 7.1
//    obeys for an ordinary `return ptr;` or `return ptr != NULL;`. No C++
//    source spelling tried (across two sessions) reproduces a raw,
//    unnormalized register copy for a genuinely bool-typed return. The
//    vendored header cannot be edited to test a pointer-return hypothesis.
//    Unresolved: unknown whether this is a further undiscovered MSVC 7.1
//    quirk/flag or requires a narrow inline-asm exception for the return
//    sequence only.
//
// A smaller, apparently-linked shape difference (not separately scored):
// in BOTH cleanup+return blocks, ours pops the callee-saved registers
// (edi/esi/ebp/ebx) BEFORE restoring the SEH chain (`mov fs:[0],ecx`) and
// `add esp,0x28`; retail restores the SEH chain FIRST, then pops. Same
// instructions, different order, in both tails identically -- likely the
// same underlying EH-model difference as gap 1 rather than an independent
// wall; no separate lever attempted.
//
// Everything else -- all field offsets (+0x24 properties, +0x44 runtime
// flags), the three dict-key/flag checks in ZH's original order
// (waypointID/bit4, lightHeightAboveTerrain/bit2, scorchType/bit8), the
// acceptsThingTemplateName filter ZH's version lacks, the absence of
// pPrevious/TheMapObjectListPtr linkage ZH's version has, and now the full
// duplicated release-and-return shape at both exits -- is verified correct
// against retail bytes, not guessed.

// TU-local view of the retail singleton at 0x012EF1D8 for the two calls
// this body routes through thunks at 0x0002323B and 0x00028560; the real
// global is already pinned elsewhere as TheThingFactory (type ThingFactory*),
// so this uses its own name to avoid a conflicting redeclaration.
class Rva0088B70ThingRegistry
{
public:
	bool acceptsThingTemplateName(const AsciiString &name);
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern Rva0088B70ThingRegistry *bfmeThingRegistry_0088B70;

// The real AsciiString's destructor (and releaseBuffer()) is a fully inline
// InterlockedDecrement/free sequence, but retail's actual bytes for this
// body call a single out-of-line releaseBuffer (matched already, real name
// pinned at 0x00887940; the same body many other TUs reach as
// releaseBuffer@BFMERetailAsciiString). A lightweight view with only a
// declared dtor -- no inline body -- reproduces that single-call shape; it
// is binary compatible with the real AsciiString (a single data pointer),
// so `name` is declared with this type and read through a matching TU-local
// view of DataChunkInput whose reader routes through the same thunk
// (0x000041C9) the real readAsciiString call already uses.
class Rva0041230aName
{
public:
	~Rva0041230aName();
	void *m_data;
};
class Rva0041230aFileView
{
public:
	Rva0041230aName bfmeReadAsciiString();
};

// TU-local view of MapObject sized and shaped only for what this body
// touches. Retail allocates through plain operator new(0x60) and calls the
// ctor via a thunk at 0x0041230A, not through MapObject's own pool-glued
// (protected) operator new, so this stays a distinct class rather than
// reusing MapObject directly. getProperties() sits at +0x24 (a Dict, the
// same offset MapObject::m_properties has) and the flag word this body ORs
// into sits at +0x44 (MapObject::m_runtimeFlags); MO_LIGHT/MO_WAYPOINT/
// MO_SCORCH are 0x02/0x04/0x08 in the real class. sizeof() is padded to the
// real class's 0x60 so the operator-new size argument matches.
class Rva0041230aMapObject
{
public:
	char m_pad0[0x24];
	Dict m_properties;
	char m_pad1[0x44 - 0x24 - sizeof(Dict)];
	Int m_runtimeFlags;
	char m_pad2[0x60 - 0x44 - sizeof(Int)];
public:
	Rva0041230aMapObject(Coord3D loc, const AsciiString &name, Real angle, Int flags,
		const Dict *props, const ThingTemplate *tmplate);
	Dict *getProperties() { return &m_properties; }
	void setIsWaypoint() { m_runtimeFlags |= 0x04; }
	void setIsLight() { m_runtimeFlags |= 0x02; }
	void setIsScorch() { m_runtimeFlags |= 0x08; }
};

// ?ParseObjectDataChunk@WorldHeightMap@@KA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
Bool WorldHeightMap::ParseObjectDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	Coord3D loc;
	loc.x = file.readReal();
	loc.y = file.readReal();
	loc.z = file.readReal();

	Real minZ = -100*MAP_XY_FACTOR;
	Real maxZ = (255*10)*MAP_HEIGHT_SCALE;

	if (info->version <= K_OBJECTS_VERSION_2) {
		loc.z = 0;
	}

	Real angle = file.readReal();
	Int flags = file.readInt();
	Rva0041230aName name = reinterpret_cast<Rva0041230aFileView &>(file).bfmeReadAsciiString();
	Dict d(0);
	if (info->version >= K_OBJECTS_VERSION_2)
	{
		d = file.readDict();
	}

	if (loc.z<minZ || loc.z>maxZ) {
		return false;
	}

	const AsciiString &nameRef = *reinterpret_cast<const AsciiString *>(&name);
	const ThingTemplate *tmplate = NULL;
	if (bfmeThingRegistry_0088B70->acceptsThingTemplateName(nameRef))
		tmplate = bfmeThingRegistry_0088B70->findTemplate(nameRef);

	Rva0041230aMapObject *pThisOne;

	pThisOne = new Rva0041230aMapObject(loc, nameRef, angle, flags, &d, tmplate);

	if (pThisOne->getProperties()->getType(TheKey_waypointID) == Dict::DICT_INT)
		pThisOne->setIsWaypoint();

	if (pThisOne->getProperties()->getType(TheKey_lightHeightAboveTerrain) == Dict::DICT_REAL)
		pThisOne->setIsLight();

	if (pThisOne->getProperties()->getType(TheKey_scorchType) == Dict::DICT_INT)
		pThisOne->setIsScorch();

	return true;
}
