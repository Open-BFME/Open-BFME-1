// ?ParseObjectDataChunk@WorldHeightMap@@KA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// partial score=0.9 date=2026-09-11
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
// this exact signature with a throwaway cl.exe compile (build/mangle_wh.cpp
// in a past session's scratch), not guessed.
//
// Every pin this body needs is already appended to reverse/symbols.csv
// (search for "0x00088B70" in the notes column): readReal (0x0002E5E1),
// readAsciiString (0x000041C9, as bfmeReadAsciiString@Rva0041230aFileView),
// Dict::Dict(int) (0x00002ECD), Dict::operator= (0x00045566),
// Dict::getType (0x0001EFD8), StaticNameKey::key (0x00009304, shared ILT
// slot), acceptsThingTemplateName/findTemplate TU-local views
// (0x0002323B / 0x00028560), the MapObject-alias ctor (0x0041230A), the
// name-wrapper dtor (0x00887940), and the singleton view global
// (bfmeThingRegistry_0088B70 at 0x012EF1D8). readInt, readDict and
// Dict::releaseData already had additive pins under their real names before
// this session. THE PIN VALUES don't depend on any part of this file
// landing; they're additive candidate resolutions and are safe to keep.
//
// STATE AS OF THIS BANK: probe.py reports ours=489, retail=545 bytes, and
// every byte through offset +0151 (into the MapObject construction) is
// byte-identical, including all 15+ resolved callees above. Three named,
// understood residual gaps remain, none of which further shape iteration
// in this session closed:
//
// 1. Missing EH bookkeeping before the MapObject-alias ctor call. Retail
//    emits `mov dword ptr [esp+0x38], esp` immediately before `call ctor`
//    (offset +0153 in the retail listing); no C++ shape tried (plain
//    `new T(args)`, explicit placement-new with a null check, a named vs.
//    split-statement local, a declared-only vs. inline dtor, a by-value vs.
//    by-reference `name` parameter, a lightweight forwarding string wrapper
//    matching Code/GameEngine/Source/Common/Rva00388820FindWaypointByName.cpp's
//    "declared dtor, no declared copy ctor" pattern) reproduces it. This
//    matches docs/lessons.md "The EH-temporary transposition: a two-byte
//    wall this toolchain cannot cross" almost exactly (same instruction,
//    `mov [esp+N],esp` before a by-value-class-argument-adjacent call,
//    documented there as tried under many /G*, /O*, /EH* flag combinations
//    and both destructor styles, all unsuccessful) -- treat as the same
//    class of toolchain wall, not a fresh one to keep grinding.
//
// 2. Return value. Retail's success path does `mov eax, esi` (copying the
//    raw newly-constructed pointer into eax, NOT a normalized bool 0/1) at
//    offset +01d8, and the early "z out of range" exit does `xor eax,eax`
//    (offset +0213) rather than setting al=1. A `Bool`-returning function
//    cannot produce a raw untested pointer copy under the C++ standard's
//    pointer-to-bool conversion rules (MSVC 7.1 obeys this), so no
//    Bool-typed source spelling reaches it; changing the declared return
//    type to void*/MapObject* would fix it, but the declaration lives in
//    the PRISTINE vendored reference header
//    (reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/
//    Include/W3DDevice/GameClient/WorldHeightMap.h), which must stay
//    unmodified. (The project's own shim at
//    reference/shims/bfmeheightmap/W3DDevice/GameClient/WorldHeightMap.h
//    is NOT on this TU's include path -- verified by its // cl: line -- so
//    editing it has no effect and is a dead end.) Whether BFME's real
//    declaration genuinely differs from Bool, or this needs inline asm as
//    a narrow codegen-blocker exception, is unresolved.
//
// 3. Tail merging. Retail duplicates the Dict/name release-and-return
//    sequence at BOTH exit points (the early z-bounds return and the
//    normal completion); the compiled shape below shares one epilogue for
//    both, which is smaller (489 vs 545 bytes) and shifts every later
//    offset. Not attempted: shape_levers.md's "identical return tails not
//    merged" lever (separate nested scopes ending exactly where each
//    retail destructor call sits) -- worth trying first in a follow-up,
//    since unlike gaps 1-2 it has no documented wall precedent.
//
// Everything else -- all field offsets (+0x24 properties, +0x44 runtime
// flags), the three dict-key/flag checks in ZH's original order
// (waypointID/bit4, lightHeightAboveTerrain/bit2, scorchType/bit8), the
// acceptsThingTemplateName filter ZH's version lacks, the absence of
// pPrevious/TheMapObjectListPtr linkage ZH's version has (genuinely not
// present in retail's bytes -- checked exhaustively) -- is verified
// correct against retail bytes, not guessed.

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
		return true;
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
