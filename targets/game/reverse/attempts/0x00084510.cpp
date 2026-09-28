// ??0GlobalData@@QAE@XZ
// partial score=0.45 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// FULL-BODY DRAFT 2026-09-28 (opus-5.5). Every retail store, loop, call and
// the CRC tail is present, transcribed in retail order from dis_retail.py.
// Member types come from the binary's GameData field-parse table (VA
// 0x01077018: parseReal/Int/Bool/RGBColor/Coord3D/...); names come from
// name_oracle, else the INI key, else the offset. Unproven types carry the
// address: BfmeGdCrcValue0BD0 (+0xbd0 initialised to 0x254b6fae during member
// construction), m_rgb09bc/m_rgb09e0/m_pos0a04 (the three per-light arrays
// setTimeOfDay fills), m_lighting0734. The call at +0xdba is setTimeOfDay
// (0x00082AA0 copies m_terrainLighting[tod]); +0xe2c is new WeaponBonusSet
// (132 x 1.0f); +0xeb7.. is GetModuleFileNameA + openFile + CRC_Memory read
// loop + version fold + the inlined BigObf wrapper 0x00062EF0; m_bd8 = 2;
// +0xc74 = GetDoubleClickTime(). The older notes further down that deny a
// CRC pass or call the frame a placeholder are superseded.
//
// LAYOUT CORRECTED 2026-09-28 (opus-5.5). The earlier draft declared its
// m_pad_* arrays AFTER the members they should precede, so >=101 of 495
// members sat at offsets that contradicted their names; every order or
// initializer-list verdict before this one (#16-#20) was measured on that
// broken layout. Members are now sorted by their ///< offsets with
// regenerated m_gap_* fillers: offsetof matches the stated offset for all
// 495 names and sizeof(GlobalData) == 0x1290. The body is unchanged and still
// only about half of retail (529 of 857 instructions); see the verdict log
// for the missing parts. The "NO CRC" note below is WRONG: retail +0x0eb7..
// +0x0fe8 is GetModuleFileNameA + openFile + CRC_Memory read loop + version
// fold + BigObf wrapper, and the 0x10138 frame is a 0x104 path buffer plus a
// 0x10000 read block.
#include <vector>
#include <string.h>
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef bool Bool;
#define TRUE true
#define FALSE false

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

struct BfmeGdCoord3D
{
	Real x;
	Real y;
	Real z;
};

struct Coord2D
{
	Real x;
	Real y;
};

struct ICoord2D
{
	Int x;
	Int y;
};

// BFME's GameClientRandomVariable zeroes itself: retail clears all seven
// ParticleCursor* variables (+0xdd8..+0xe30) during member construction.
class GameClientRandomVariable
{
public:
	GameClientRandomVariable() : m_low(0), m_high(0), m_type(0) { }

	Real m_low;
	Real m_high;
	Int m_type;
};

// +0xbd0 is initialised to 0x254b6fae during member construction and again
// before the CRC pass, then receives the protected CRC result. Its type is
// not identified; this address-labelled wrapper reproduces the member init.
class BfmeGdCrcValue0BD0
{
public:
	BfmeGdCrcValue0BD0() : m_value(0x254b6fae) { }

	UnsignedInt m_value;
};

// new(0x210) filled with 132 x 1.0f and stored at +0xb94 (WeaponBonus field).
class WeaponBonusSet
{
public:
	WeaponBonusSet()
	{
		for (Int i = 0; i < 132; ++i)
			m_bonus[i] = 1.0f;
	}

	Real m_bonus[132];
};

class File
{
public:
	virtual ~File();
	virtual Bool open(const char *filename, Int access);
	virtual void close();
	virtual Int read(void *buffer, Int bytes);
};

class FileSystem
{
public:
	File *openFile(const char *filename, Int access);
};

extern FileSystem *TheFileSystem;

class Version
{
public:
	UnsignedInt getVersionNumber();
};

extern Version *TheVersion;

unsigned long CRC_Memory(const unsigned char *data, unsigned long length, unsigned long crc);

extern "C" __declspec(dllimport) unsigned long __stdcall GetModuleFileNameA(void *module, char *filename, unsigned long size);
extern "C" __declspec(dllimport) unsigned int __stdcall GetDoubleClickTime();

// The anti-tamper wrapper at 0x00062EF0 (BigObfHookWrappers.cpp), inlined here
// by retail: same slot, state object and fallback, reached through their ILTs.
typedef int (__cdecl *BigObfHook)(void *, void *, __int64);

struct BigObfSlot
{
	BigObfHook m_hook;
	BigObfHook m_alt;
	char m_pad[0x80];
	void *m_a;
	void *m_b;
};

extern BigObfSlot g_Slot012C233C;

class Obf00084510State
{
public:
	Obf00084510State(int *a, int *b);
	unsigned int m_bits[8];
};

int __cdecl Gen00084510Fallback(int a, int b);

#pragma comment(linker, "/alternatename:??0Obf00084510State@@QAE@PAH0@Z=?j_0002f923@@YAXXZ")
#pragma comment(linker, "/alternatename:?Gen00084510Fallback@@YAHHH@Z=?j_0003f508@@YAXXZ")
#pragma comment(linker, "/alternatename:?getVersionNumber@Version@@QAEIXZ=?j_0001b76b@@YAXXZ")
#pragma comment(linker, "/alternatename:?setTimeOfDay@GlobalData@@QAE_NH@Z=?j_0000ba64@@YAXXZ")

static __forceinline int protectCrc00062EF0(int a, int b)
{
	BigObfHook hook = g_Slot012C233C.m_hook;
	if (hook)
		goto hot;
	if (g_Slot012C233C.m_alt)
	{
hot:
		void *pa = g_Slot012C233C.m_a;
		void *pb = g_Slot012C233C.m_b;
		Obf00084510State o(&a, &b);
		return hook(pa, pb, (__int64)(int)&o);
	}
	return Gen00084510Fallback(a, b);
}
//
// Open-BFME5: GlobalData::GlobalData(), retail 0x00084510, 4621 bytes
// (the ledger's 4499-byte estimate was stale -- the extent ends in `ret`
// at +0x120c, confirmed with dis_retail.py; this is the real boundary).
//
// STRUCTURAL DRAFT, not yet byte-exact. This is the store-run-constructor /
// unwind-state lever from docs/shape_levers.md applied at scale: the /EHsc
// FuncInfo at VA 0x011E2888 lists 50 states (build/ehmap.py), each a
// destructible sub-object of GlobalData in DECLARATION order. Every state's
// funclet was disassembled (mov ecx,[ebp-0x10134]; add ecx,<offset>; jmp
// <dtor>, or the eh-vector iterator form for arrays) to recover the member
// list below -- offset, size and destructor identity for all 49 of
// GlobalData's own destructible members (state 0 destroys the inherited
// SubsystemInterface base).
//
// Every destructible type below is REUSED, not re-modelled:
//   - BFMERetailAsciiString: the project's standard AsciiString stand-in
//     (dtor ILT 0x0000D828, already pinned everywhere).
//   - _STL::vector<BFMERetailAsciiString>: dtor already pinned at 0x000658A0
//     under this exact template spelling (symbols.csv:4134) -- ICF-folded
//     onto ??1PlayerUpgradeSpecialPowerModuleData, confirmed by inspecting
//     the callee body's loop shape and by SubsystemLegend.cpp's own working
//     vector<AsciiString> member using the same dtor address.
//   - AttributeHandleStandIn: already a MATCHED class (ctor 0x0003747A, dtor
//     0x0039D550) in AttributeHandleStandInDestructor.cpp /
//     AttributeModifierAuraUpdateModuleDataCtorThunk.cpp -- declared here,
//     not redefined, so the linker resolves to the existing body.
//   - Coord3D: real, already-matched class (coord3d.cpp; default ctor
//     0x00016C93->0x00083330, 3 bytes, dtor 0x00016C93 thunk chain ends at
//     ??1Coord3D). Minimal local redeclaration (name + size only) to avoid
//     pulling in the full header graph, exactly like BFMERetailAsciiString
//     stands in for the real AsciiString elsewhere in this project.
//   - Rva00083150: already-matched class (Rva00083150Ctor.cpp) -- a 0x300
//     byte, six-row/32-float grid defaulted to 1.0f, called via a plain
//     thiscall ctor with NO unwind state (its own ctor cannot throw, so it
//     never got a state slot -- that is why 50 states cover only 49 of
//     GlobalData's members plus the SubsystemInterface base).
//   - BfmeGdElem36 / BfmeGdUnicodeString: two NEW stand-ins, pinned below.
//     BfmeGdElem36 is a 36-byte element (three 18-element array members at
//     +0x224/+0x4ac/+0x734) whose real ctor (0x00083440: mov eax,ecx / ret)
//     and dtor (0x00083450: ret) are BOTH empty -- confirmed by disassembly,
//     so the element's actual field layout is irrelevant to this function's
//     bytes and is left as an opaque byte blob.  BfmeGdUnicodeString's dtor
//     is retail's own real UnicodeString release path (0x0045EEA0 is an ILT
//     that jumps to the already-pinned ??1UnicodeString@@QAE@XZ body at
//     0x008881D0); a locally-named stand-in avoids an ODR clash with the
//     full UnicodeString class already defined in
//     Code/GameEngine/Source/Common/System/UnicodeString.cpp.
//
// UPDATE (worker W6, wave 2): the assigned brief's "CRC tail" theory for the
// 0x10138-byte __chkstk frame is WRONG -- checked directly against the full
// call list of the retail body (every `call`/`call [..]` instruction from
// +0x0 to +0x120c, 47 total): there is NO GetModuleFileName, NO File::open,
// NO read loop and NO CRC object anywhere in this function. The only import
// call is `call dword ptr [0x1359000]` at +0x0ffe, which reverse/imports.csv
// identifies as USER32!GetDoubleClickTime (matches ZH's tail-of-ctor
// `m_doubleClickTimeMS = GetDoubleClickTime();`, so the general "this is
// ZH's ctor tail" mapping still holds -- just not the CRC part). The other
// unresolved tail calls (0x1b76b, 0xa984, 0x2f923, 0x3f508) are all
// already-matched `gen-thunk` placeholder rows (Code/gen_small/thunks_*.cpp)
// -- 5-byte jump stubs to FUN_004aea50 / FUN_00465250 / etc, not identified
// real callees yet.
//
// What the buffer actually IS is still unresolved, but its SIZE is now
// pinned empirically: adding an unused (one volatile byte touched) local
// `char[0x10134]` reproduces retail's exact `mov eax, 0x10138` / __chkstk
// prologue (0x10134 local + 4 bytes compiler overhead = 0x10138) and pushes
// the first diff from the missing-chkstk-call point to the next one (score
// 2774 -> 2820 bytes, still far short of 4621). Per docs/shape_levers.md
// "frame first": this only gets the PROLOGUE aligned; everything after it
// still needs real content, at which point the buffer's shape may turn out
// to matter (e.g. if it's really several arrays MSVC coalesced).
//
// Retail water loop at +0x068d..+0x06e6 is four iterations. It starts
// edi at this+0xbc, writes 13 separate dwords at edi-0x10 through
// edi+0xb0, calls the narrow-string release path with ecx=edi-0x20
// (this+0x9c+i*4), then advances edi by four. The matching GeneralsMD
// GlobalData constructor clears m_vertexWaterAvailableMaps[i] after those
// 13 initializers; its inline clear() delegates to releaseBuffer().
// This draft now includes that missing call, using the existing pinned
// BFMERetailAsciiString releaseBuffer body at 0x00887940. No byte-match
// result has been claimed for this change.
//
// Other loops, calls, BFME-specific scalar defaults and the large stack
// frame remain unresolved; the original 0.2 score is not an updated score.
//
// NOT YET DONE (why this is a partial, not a landed body):
//   - Many BFME scalar members are named by offset and the initializer
//     list is incomplete, notably retail-only stores before the water loop,
//     the three lighting grids, and fields after the final default loop.
//   - At least three call sites (+0x40f/+0x421 `RetailLayoutString::set`,
//     +0xc72 `UnicodeString::set`) assign LITERAL STRING content to specific
//     AsciiString/UnicodeString members -- these need the literal bytes read
//     out of retail's .rdata and are not yet reproduced.
//   - GlobalData's own vtable store (`mov dword ptr [esi], 0x0107C68C` right
//     after the SubsystemInterface base ctor call) has no pin yet; nothing
//     in this file forces our compiled vtable to that literal.
//   - Trailing calls through thunks 0x1b76b, 0xa984, 0x2f923 and 0x3f508,
//     plus the indirect call through edi, still need genuine source paths.
//     The import through [0x1359000] is GetDoubleClickTime.
//
// The size below is verified: SubsystemInterface (8) + the member list =
// 0x1290, matching newOverride's own comment that `operator new` is handed
// 0x1290 and m_next lives at +0x128c.

class SubsystemInterface
{
public:
	SubsystemInterface();                                      ///< matched 0x009A1A30
	virtual ~SubsystemInterface();                              ///< matched 0x009A1A40

private:
	unsigned int m_pad04;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) { }
	~BFMERetailAsciiString() { releaseBuffer(); }
	BFMERetailAsciiString &operator=(const BFMERetailAsciiString &s) { set(s); return *this; }
	void set(const BFMERetailAsciiString &s);
	void set(const char *s, int len);
	void set(const char *s) { set(s, strlen(s)); }
	void clear() { releaseBuffer(); }
	void releaseBuffer(); // Retail AsciiString::clear() delegates to this pinned release path.

	void *m_data;
};

// AttributeHandleStandIn: already matched at
// Code/GameEngine/Source/GameLogic/Object/Update/AttributeHandleStandInDestructor.cpp
// (dtor 0x0039D550) / AttributeModifierAuraUpdateModuleDataCtorThunk.cpp
// (ctor pinned 0x0003747A). Declared, not redefined.
class AttributeHandleStandIn
{
public:
	AttributeHandleStandIn();
	~AttributeHandleStandIn();

private:
	unsigned int m_value;
};

// Real, already-matched class (Code/Libraries/Source/WWVegas/WWMath/coord3d.cpp).
// Minimal local redeclaration: name + size only, ctor/dtor resolved externally.
class Coord3D
{
public:
	Coord3D();
	~Coord3D();

public:
	float x, y, z;
};

// Already-matched class (Code/GameEngine/Source/Common/Rva00083150Ctor.cpp):
// six rows of 32 floats, all defaulted to 1.0f, nothrow ctor (no unwind state).
class Rva00083150
{
public:
	Rva00083150();

private:
	unsigned int m_grid[6][32];
};

// New stand-in: retail's element ctor (0x00083440: mov eax,ecx / ret) and
// dtor (0x00083450: ret) are both empty, so the field layout does not matter
// to this function's bytes.  Pinned below.
class BfmeGdElem36
{
public:
	BfmeGdElem36() { }
	~BfmeGdElem36() { }

public:
	RGBColor ambient;
	RGBColor diffuse;
	BfmeGdCoord3D lightPos;
};

// New stand-in for the UnicodeString-shaped member at +0x1280.  Retail's
// dtor call goes through ILT 0x0045EEA0, which itself jumps to the
// already-pinned ??1UnicodeString@@QAE@XZ body at 0x008881D0. A locally
// named class avoids redefining the real UnicodeString from
// Code/GameEngine/Source/Common/System/UnicodeString.cpp in this TU.
class BfmeGdUnicodeString
{
public:
	BfmeGdUnicodeString() : m_data(0) { }
	~BfmeGdUnicodeString();

private:
	void *m_data;
};

class GlobalData : public SubsystemInterface
{
public:
	GlobalData();
	Bool setTimeOfDay(Int tod);

	static GlobalData *m_theOriginal;

	BFMERetailAsciiString m_mapName;				///< +0x8
	BFMERetailAsciiString m_moveHintName;				///< +0xc
	BFMERetailAsciiString m_str_10;				///< +0x10
	BFMERetailAsciiString m_str_14;				///< +0x14
	Bool m_showProps;				///< +0x18
	Bool m_pushAsideShrubs;				///< +0x19
	UnsignedByte m_1a;				///< +0x1a
	UnsignedByte m_1b;				///< +0x1b
	UnsignedByte m_1c;				///< +0x1c
	UnsignedByte m_1d;				///< +0x1d
	Bool m_useFpsLimit;				///< +0x1e
	Bool m_useHighQualityVideo;				///< +0x1f
	Bool m_dumpAssetUsage;				///< +0x20
	UnsignedByte m_gap0021[0x3];
	Int m_framesPerSecondLimit;				///< +0x24
	Bool m_disablePixelShader;				///< +0x28
	Bool m_windowed;				///< +0x29
	Bool m_skipMapUnroll;				///< +0x2a
	UnsignedByte m_gap002b[0x1];
	Int m_xResolution;				///< +0x2c
	Int m_yResolution;				///< +0x30
	Int m_maxShellScreens;				///< +0x34
	Bool m_useCloudMap;				///< +0x38
	Bool m_showWater;				///< +0x39
	Bool m_showRoads;				///< +0x3a
	Bool m_showTrees;				///< +0x3b
	Bool m_useReverseMouseScroll;				///< +0x3c
	UnsignedByte m_gap003d[0x3];
	Int m_use3WayTerrainBlends;				///< +0x40
	Bool m_useLightMap;				///< +0x44
	Bool m_bilinearTerrainTex;				///< +0x45
	Bool m_trilinearTerrainTex;				///< +0x46
	Bool m_anisotropicTerrainTex;				///< +0x47
	UnsignedInt m_48;				///< +0x48
	Bool m_multiPassTerrain;				///< +0x4c
	Bool m_adjustCliffTextures;				///< +0x4d
	Bool m_stretchTerrain;				///< +0x4e
	Bool m_useHalfHeightMap;				///< +0x4f
	Bool m_drawEntireTerrain;				///< +0x50
	UnsignedByte m_gap0051[0x3];
	Int m_terrainLOD;				///< +0x54
	UnsignedByte m_58;				///< +0x58
	UnsignedByte m_59;				///< +0x59
	UnsignedByte m_gap005a[0x2];
	Int m_terrainLODTargetTimeMS;				///< +0x5c
	UnsignedByte m_60;				///< +0x60
	Bool m_rightMouseAlwaysScrolls;				///< +0x61
	Bool m_useWaterPlane;				///< +0x62
	Bool m_useCloudPlane;				///< +0x63
	Bool m_useShadowVolumes;				///< +0x64
	Bool m_useShadowDecals;				///< +0x65
	UnsignedByte m_gap0066[0x2];
	Int m_textureReductionFactor;				///< +0x68
	UnsignedInt m_6c;				///< +0x6c
	Bool m_enableBehindBuildingMarkers;				///< +0x70
	UnsignedByte m_gap0071[0x3];
	Real m_waterPositionX;				///< +0x74
	Real m_waterPositionY;				///< +0x78
	Real m_waterPositionZ;				///< +0x7c
	Real m_waterExtentX;				///< +0x80
	Real m_waterExtentY;				///< +0x84
	Int m_waterType;				///< +0x88
	Bool m_showSoftWaterEdge;				///< +0x8c
	UnsignedByte m_8d;				///< +0x8d
	Bool m_liveCampaignMode;				///< +0x8e
	Bool m_hideLivingWorldRegions;				///< +0x8f
	Bool m_livingWorldTurbo;				///< +0x90
	UnsignedByte m_gap0091[0x3];
	BFMERetailAsciiString m_str_94;				///< +0x94
	Int m_featherWater;				///< +0x98
	BFMERetailAsciiString m_strArr_9c[4];				///< +0x9c
	Real m_vertexWaterHeightClampLow[4];				///< +0xac
	Real m_vertexWaterHeightClampHi[4];				///< +0xbc
	Real m_vertexWaterAngle[4];				///< +0xcc
	Real m_vertexWaterXPosition[4];				///< +0xdc
	Real m_vertexWaterYPosition[4];				///< +0xec
	Real m_vertexWaterZPosition[4];				///< +0xfc
	Int m_vertexWaterXGridCells[4];				///< +0x10c
	Int m_vertexWaterYGridCells[4];				///< +0x11c
	Real m_vertexWaterGridSize[4];				///< +0x12c
	Real m_vertexWaterAttenuationA[4];				///< +0x13c
	Real m_vertexWaterAttenuationB[4];				///< +0x14c
	Real m_vertexWaterAttenuationC[4];				///< +0x15c
	Real m_vertexWaterAttenuationRange[4];				///< +0x16c
	Real m_downwindAngle;				///< +0x17c
	Bool m_drawSkyBox;				///< +0x180
	UnsignedByte m_gap0181[0x3];
	Real m_defaultCameraMinHeight;				///< +0x184
	Real m_defaultCameraMaxHeight;				///< +0x188
	Real m_defaultCameraPitchAngle;				///< +0x18c
	Real m_defaultCameraYawAngle;				///< +0x190
	Real m_defaultCameraScrollSpeedScalar;				///< +0x194
	Real m_terrainHeightAtEdgeOfMap;				///< +0x198
	Real m_unitDamagedThresh;				///< +0x19c
	Real m_unitReallyDamagedThresh;				///< +0x1a0
	Real m_groundStiffness;				///< +0x1a4
	Real m_structureStiffness;				///< +0x1a8
	Real m_gravity;				///< +0x1ac
	Real m_stealthFriendlyOpacity;				///< +0x1b0
	UnsignedInt m_defaultOcclusionDelay;				///< +0x1b4
	UnsignedByte m_1b8;				///< +0x1b8
	UnsignedByte m_gap01b9[0x3];
	Real m_partitionCellSize;				///< +0x1bc
	BfmeGdCoord3D m_ammoPipWorldOffset;				///< +0x1c0
	BfmeGdCoord3D m_containerPipWorldOffset;				///< +0x1cc
	Coord2D m_ammoPipScreenOffset;				///< +0x1d8
	Coord2D m_containerPipScreenOffset;				///< +0x1e0
	Real m_ammoPipScaleFactor;				///< +0x1e8
	Real m_containerPipScaleFactor;				///< +0x1ec
	Int m_maxTerrainTracks;				///< +0x1f0
	UnsignedInt m_1f4;				///< +0x1f4
	UnsignedInt m_1f8;				///< +0x1f8
	UnsignedInt m_1fc;				///< +0x1fc
	BFMERetailAsciiString m_levelGainAnimationName;				///< +0x200
	Real m_levelGainAnimationDisplayTimeInSeconds;				///< +0x204
	Real m_levelGainAnimationZRisePerSecond;				///< +0x208
	BFMERetailAsciiString m_getHealedAnimationName;				///< +0x20c
	Real m_getHealedAnimationDisplayTimeInSeconds;				///< +0x210
	Real m_getHealedAnimationZRisePerSecond;				///< +0x214
	Int m_timeOfDay;				///< +0x218
	Int m_weather;				///< +0x21c
	Bool m_makeTrackMarks;				///< +0x220
	Bool m_hideGarrisonFlags;				///< +0x221
	Bool m_forceModelsToFollowTimeOfDay;				///< +0x222
	Bool m_forceModelsToFollowWeather;				///< +0x223
	BfmeGdElem36 m_terrainLighting[6][3];				///< +0x224
	BfmeGdElem36 m_terrainObjectsLighting[6][3];				///< +0x4ac
	BfmeGdElem36 m_lighting0734[6][3];				///< +0x734
	RGBColor m_rgb09bc[3];				///< +0x9bc
	RGBColor m_rgb09e0[3];				///< +0x9e0
	Coord3D m_pos0a04[3];				///< +0xa04
	UnsignedInt m_a28;				///< +0xa28
	Real m_soloPlayerHealthBonusForDifficulty[6];				///< +0xa2c
	Int m_maxVisibleTranslucentObjects;				///< +0xa44
	UnsignedInt m_a48;				///< +0xa48
	UnsignedInt m_a4c;				///< +0xa4c
	UnsignedInt m_a50;				///< +0xa50
	Real m_occludedLuminanceScale;				///< +0xa54
	Int m_numGlobalLights;				///< +0xa58
	Int m_maxRoadSegments;				///< +0xa5c
	Int m_maxRoadVertex;				///< +0xa60
	Int m_maxRoadIndex;				///< +0xa64
	Int m_maxRoadTypes;				///< +0xa68
	Bool m_audioOn;				///< +0xa6c
	Bool m_musicOn;				///< +0xa6d
	Bool m_soundsOn;				///< +0xa6e
	Bool m_sounds3DOn;				///< +0xa6f
	Bool m_speechOn;				///< +0xa70
	Bool m_ambientStreamsOn;				///< +0xa71
	UnsignedByte m_a72;				///< +0xa72
	Bool m_videoOn;				///< +0xa73
	Bool m_disableCameraMovement;				///< +0xa74
	Bool m_showSelectedUnitMarker;				///< +0xa75
	Bool m_useSimpleHordeDecals;				///< +0xa76
	Bool m_useSimpleMergeDecals;				///< +0xa77
	Real m_opacityOfSimpleMergeDecals;				///< +0xa78
	UnsignedByte m_a7c;				///< +0xa7c
	UnsignedByte m_a7d;				///< +0xa7d
	UnsignedByte m_a7e;				///< +0xa7e
	UnsignedByte m_a7f;				///< +0xa7f
	Bool m_showClientPhysics;				///< +0xa80
	Bool m_showTerrainNormals;				///< +0xa81
	UnsignedByte m_gap0a82[0x2];
	UnsignedInt m_a84;				///< +0xa84
	Bool m_debugAI;				///< +0xa88
	UnsignedByte m_gap0a89[0x3];
	Bool m_debugAIObstacles;				///< +0xa8c
	Bool m_showObjectHealth;				///< +0xa8d
	UnsignedByte m_a8e;				///< +0xa8e
	Bool m_showTooltips;				///< +0xa8f
	UnsignedByte m_a90;				///< +0xa90
	UnsignedByte m_a91;				///< +0xa91
	UnsignedByte m_a92;				///< +0xa92
	UnsignedByte m_a93;				///< +0xa93
	UnsignedByte m_a94;				///< +0xa94
	UnsignedByte m_a95;				///< +0xa95
	UnsignedByte m_a96;				///< +0xa96
	UnsignedByte m_a97;				///< +0xa97
	UnsignedInt m_a98;				///< +0xa98
	UnsignedByte m_a9c;				///< +0xa9c
	UnsignedByte m_a9d;				///< +0xa9d
	UnsignedByte m_a9e;				///< +0xa9e
	UnsignedByte m_a9f;				///< +0xa9f
	UnsignedByte m_aa0;				///< +0xaa0
	UnsignedByte m_gap0aa1[0x3];
	BFMERetailAsciiString m_str_aa4;				///< +0xaa4
	BFMERetailAsciiString m_str_aa8;				///< +0xaa8
	UnsignedByte m_aac;				///< +0xaac
	UnsignedByte m_gap0aad[0x3];
	Int m_fixedSeed;				///< +0xab0
	Real m_particleScale;				///< +0xab4
	BFMERetailAsciiString m_autoFireParticleSmallPrefix;				///< +0xab8
	BFMERetailAsciiString m_autoFireParticleSmallSystem;				///< +0xabc
	Int m_autoFireParticleSmallMax;				///< +0xac0
	BFMERetailAsciiString m_autoFireParticleMediumPrefix;				///< +0xac4
	BFMERetailAsciiString m_autoFireParticleMediumSystem;				///< +0xac8
	Int m_autoFireParticleMediumMax;				///< +0xacc
	BFMERetailAsciiString m_autoFireParticleLargePrefix;				///< +0xad0
	BFMERetailAsciiString m_autoFireParticleLargeSystem;				///< +0xad4
	Int m_autoFireParticleLargeMax;				///< +0xad8
	BFMERetailAsciiString m_autoSmokeParticleSmallPrefix;				///< +0xadc
	BFMERetailAsciiString m_autoSmokeParticleSmallSystem;				///< +0xae0
	Int m_autoSmokeParticleSmallMax;				///< +0xae4
	BFMERetailAsciiString m_autoSmokeParticleMediumPrefix;				///< +0xae8
	BFMERetailAsciiString m_autoSmokeParticleMediumSystem;				///< +0xaec
	Int m_autoSmokeParticleMediumMax;				///< +0xaf0
	BFMERetailAsciiString m_autoSmokeParticleLargePrefix;				///< +0xaf4
	BFMERetailAsciiString m_autoSmokeParticleLargeSystem;				///< +0xaf8
	Int m_autoSmokeParticleLargeMax;				///< +0xafc
	BFMERetailAsciiString m_autoAflameParticlePrefix;				///< +0xb00
	BFMERetailAsciiString m_autoAflameParticleSystem;				///< +0xb04
	Int m_autoAflameParticleMax;				///< +0xb08
	UnsignedInt m_b0c;				///< +0xb0c
	UnsignedInt m_b10;				///< +0xb10
	Int m_firewallBehavior;				///< +0xb14
	UnsignedByte m_b18;				///< +0xb18
	UnsignedByte m_gap0b19[0x3];
	Int m_firewallPortOverride;				///< +0xb1c
	Int m_firewallPortAllocationDelta;				///< +0xb20
	Int m_baseValuePerSupplyBox;				///< +0xb24
	Int m_supplyBoxesPerTree;				///< +0xb28
	Real m_BuildSpeed;				///< +0xb2c
	Real m_MinDistFromEdgeOfMapForBuild;				///< +0xb30
	Real m_SupplyBuildBorder;				///< +0xb34
	Real m_allowedHeightVariationForBuilding;				///< +0xb38
	Real m_MinLowEnergyProductionSpeed;				///< +0xb3c
	Real m_MaxLowEnergyProductionSpeed;				///< +0xb40
	Real m_LowEnergyPenaltyModifier;				///< +0xb44
	Real m_MultipleFactory;				///< +0xb48
	Real m_RefundPercent;				///< +0xb4c
	UnsignedInt m_timeAfterDamageUntilRepairAllowed;				///< +0xb50
	Real m_commandCenterHealRange;				///< +0xb54
	Real m_commandCenterHealAmount;				///< +0xb58
	Int m_maxLineBuildObjects;				///< +0xb5c
	Int m_maxTunnelCapacity;				///< +0xb60
	Real m_horizontalScrollSpeedFactor;				///< +0xb64
	Real m_verticalScrollSpeedFactor;				///< +0xb68
	Real m_screenEdgeScrollSpeedFactor;				///< +0xb6c
	UnsignedInt m_screenEdgeScrollRampTime;				///< +0xb70
	Real m_scrollAmountCutoff;				///< +0xb74
	Real m_cameraAdjustSpeed;				///< +0xb78
	Bool m_enforceMaxCameraHeight;				///< +0xb7c
	UnsignedByte m_b7d;				///< +0xb7d
	UnsignedByte m_gap0b7e[0x2];
	BFMERetailAsciiString m_str_b80;				///< +0xb80
	BFMERetailAsciiString m_str_b84;				///< +0xb84
	UnsignedByte m_b88;				///< +0xb88
	UnsignedByte m_gap0b89[0x3];
	Int m_maxParticleCount;				///< +0xb8c
	Int m_maxFieldParticleCount;				///< +0xb90
	WeaponBonusSet * m_weaponBonusSet;				///< +0xb94
	UnsignedInt m_b98;				///< +0xb98
	Real m_healthBonus[3];				///< +0xb9c
	Real m_defaultStructureRubbleHeight;				///< +0xba8
	Real m_attributeModifierArmorMaxBonus;				///< +0xbac
	BFMERetailAsciiString m_shellMapName;				///< +0xbb0
	Bool m_shellMapOn;				///< +0xbb4
	Bool m_shellMapOffByCommandArgument;				///< +0xbb5
	Bool m_playIntro;				///< +0xbb6
	UnsignedByte m_bb7;				///< +0xbb7
	UnsignedByte m_bb8;				///< +0xbb8
	UnsignedByte m_bb9;				///< +0xbb9
	UnsignedByte m_gap0bba[0x2];
	Real m_keyboardScrollFactor;				///< +0xbbc
	Real m_keyboardDefaultScrollFactor;				///< +0xbc0
	UnsignedByte m_bc4;				///< +0xbc4
	UnsignedByte m_bc5;				///< +0xbc5
	UnsignedByte m_gap0bc6[0x2];
	UnsignedInt m_bc8;				///< +0xbc8
	UnsignedByte m_gap0bcc[0x4];
	BfmeGdCrcValue0BD0 m_bd0;				///< +0xbd0
	UnsignedInt m_bd4;				///< +0xbd4
	Int m_movementPenaltyDamageState;				///< +0xbd8
	Real m_damageRadiusMinimumForSplash;				///< +0xbdc
	Int m_groupSelectMinSelectSize;				///< +0xbe0
	Real m_groupSelectVolumeBase;				///< +0xbe4
	Real m_groupSelectVolumeIncrement;				///< +0xbe8
	Int m_maxUnitSelectSounds;				///< +0xbec
	Real m_selectionFlashSaturationFactor;				///< +0xbf0
	Bool m_selectionFlashHouseColor;				///< +0xbf4
	UnsignedByte m_gap0bf5[0x3];
	Real m_cameraAudibleRadius;				///< +0xbf8
	Real m_groupMoveClickToGatherFactor;				///< +0xbfc
	UnsignedInt m_c00;				///< +0xc00
	UnsignedByte m_c04;				///< +0xc04
	UnsignedByte m_c05;				///< +0xc05
	UnsignedByte m_c06;				///< +0xc06
	UnsignedByte m_c07;				///< +0xc07
	UnsignedByte m_c08;				///< +0xc08
	UnsignedByte m_c09;				///< +0xc09
	UnsignedByte m_c0a;				///< +0xc0a
	UnsignedByte m_c0b;				///< +0xc0b
	UnsignedByte m_c0c;				///< +0xc0c
	Bool m_useCameraInReplay;				///< +0xc0d
	UnsignedByte m_gap0c0e[0x2];
	Real m_shakeSubtleIntensity;				///< +0xc10
	Real m_shakeNormalIntensity;				///< +0xc14
	Real m_shakeStrongIntensity;				///< +0xc18
	Real m_shakeSevereIntensity;				///< +0xc1c
	Real m_shakeCineExtremeIntensity;				///< +0xc20
	Real m_shakeCineInsaneIntensity;				///< +0xc24
	Real m_maxShakeIntensity;				///< +0xc28
	Real m_maxShakeRange;				///< +0xc2c
	Real m_sellPercentage;				///< +0xc30
	Real m_baseRegenHealthPercentPerSecond;				///< +0xc34
	UnsignedInt m_baseRegenDelay;				///< +0xc38
	Int m_hotKeyTextColor;				///< +0xc3c
	BFMERetailAsciiString m_specialPowerViewObjectName;				///< +0xc40
	_STL::vector<BFMERetailAsciiString> m_standardPublicBones;				///< +0xc44
	Bool m_showMetrics;				///< +0xc50
	UnsignedByte m_gap0c51[0x3];
	UnsignedInt m_defaultStartingCash;				///< +0xc54
	UnsignedByte m_c58;				///< +0xc58
	UnsignedByte m_c59;				///< +0xc59
	UnsignedByte m_gap0c5a[0x2];
	Int m_powerBarBase;				///< +0xc5c
	Real m_powerBarIntervals;				///< +0xc60
	Int m_powerBarYellowRange;				///< +0xc64
	UnsignedInt m_c68;				///< +0xc68
	UnsignedInt m_unlookPersistDuration;				///< +0xc6c
	UnsignedByte m_c70;				///< +0xc70
	UnsignedByte m_gap0c71[0x3];
	UnsignedInt m_c74;				///< +0xc74
	RGBColor m_shroudColor;				///< +0xc78
	UnsignedByte m_clearAlpha;				///< +0xc84
	UnsignedByte m_fogAlpha;				///< +0xc85
	UnsignedByte m_shroudAlpha;				///< +0xc86
	UnsignedByte m_gap0c87[0x1];
	RGBColor m_taintColor;				///< +0xc88
	RGBColor m_elvenWoodColor;				///< +0xc94
	UnsignedByte m_taintAlpha;				///< +0xca0
	UnsignedByte m_gap0ca1[0x3];
	Int m_networkFPSHistoryLength;				///< +0xca4
	Int m_networkLatencyHistoryLength;				///< +0xca8
	Int m_networkRunAheadMetricsTime;				///< +0xcac
	Int m_networkCushionHistoryLength;				///< +0xcb0
	Int m_networkRunAheadSlack;				///< +0xcb4
	Int m_networkKeepAliveDelay;				///< +0xcb8
	Int m_networkDisconnectTime;				///< +0xcbc
	Int m_networkPlayerTimeoutTime;				///< +0xcc0
	Int m_networkDisconnectScreenNotifyTime;				///< +0xcc4
	Real m_keyboardCameraRotateSpeed;				///< +0xcc8
	Int m_playStats;				///< +0xccc
	UnsignedInt m_defaultVoiceAttackChargeTimeout;				///< +0xcd0
	Real m_defaultMaxDistanceForEngaged;				///< +0xcd4
	UnsignedInt m_defaultEngagedStateTimeout;				///< +0xcd8
	Int m_animationSharingCap;				///< +0xcdc
	Real m_animationSharingFrameTolerance;				///< +0xce0
	Real m_animationSharingSpeedTolerance;				///< +0xce4
	Real m_animationSharingWorryThreshold;				///< +0xce8
	Real m_animationSharingDrasticThreshold;				///< +0xcec
	UnsignedByte m_cf0;				///< +0xcf0
	UnsignedByte m_cf1;				///< +0xcf1
	UnsignedByte m_cf2;				///< +0xcf2
	UnsignedByte m_cf3;				///< +0xcf3
	UnsignedByte m_cf4;				///< +0xcf4
	Bool m_taintOn;				///< +0xcf5
	UnsignedByte m_cf6;				///< +0xcf6
	UnsignedByte m_cf7;				///< +0xcf7
	UnsignedByte m_cf8;				///< +0xcf8
	UnsignedByte m_cf9;				///< +0xcf9
	UnsignedByte m_cfa;				///< +0xcfa
	UnsignedByte m_cfb;				///< +0xcfb
	UnsignedByte m_cfc;				///< +0xcfc
	UnsignedByte m_gap0cfd[0x3];
	UnsignedInt m_d00;				///< +0xd00
	UnsignedByte m_d04;				///< +0xd04
	UnsignedByte m_d05;				///< +0xd05
	UnsignedByte m_gap0d06[0x2];
	UnsignedInt m_d08;				///< +0xd08
	UnsignedByte m_d0c;				///< +0xd0c
	UnsignedByte m_d0d;				///< +0xd0d
	UnsignedByte m_gap0d0e[0x2];
	UnsignedInt m_d10;				///< +0xd10
	UnsignedByte m_gap0d14[0x4];
	UnsignedInt m_d18;				///< +0xd18
	UnsignedByte m_d1c;				///< +0xd1c
	UnsignedByte m_gap0d1d[0x3];
	UnsignedInt m_d20;				///< +0xd20
	UnsignedInt m_d24;				///< +0xd24
	UnsignedByte m_d28;				///< +0xd28
	UnsignedByte m_gap0d29[0x3];
	UnsignedInt m_d2c;				///< +0xd2c
	UnsignedInt m_d30;				///< +0xd30
	UnsignedByte m_gap0d34[0x24];
	UnsignedByte m_d58;				///< +0xd58
	UnsignedByte m_gap0d59[0x3];
	UnsignedInt m_d5c;				///< +0xd5c
	UnsignedInt m_d60;				///< +0xd60
	UnsignedByte m_gap0d64[0x20];
	UnsignedByte m_d84;				///< +0xd84
	UnsignedByte m_d85;				///< +0xd85
	UnsignedByte m_d86;				///< +0xd86
	UnsignedByte m_d87;				///< +0xd87
	UnsignedByte m_d88;				///< +0xd88
	UnsignedByte m_d89;				///< +0xd89
	UnsignedByte m_d8a;				///< +0xd8a
	UnsignedByte m_d8b;				///< +0xd8b
	BFMERetailAsciiString m_str_d8c;				///< +0xd8c
	BFMERetailAsciiString m_str_d90;				///< +0xd90
	UnsignedInt m_d94;				///< +0xd94
	UnsignedInt m_d98;				///< +0xd98
	UnsignedInt m_d9c;				///< +0xd9c
	UnsignedInt m_da0;				///< +0xda0
	UnsignedInt m_da4;				///< +0xda4
	UnsignedInt m_da8;				///< +0xda8
	UnsignedByte m_dac;				///< +0xdac
	UnsignedByte m_gap0dad[0x3];
	UnsignedInt m_db0;				///< +0xdb0
	UnsignedByte m_db4;				///< +0xdb4
	UnsignedByte m_db5;				///< +0xdb5
	UnsignedByte m_db6;				///< +0xdb6
	UnsignedByte m_gap0db7[0x1];
	BFMERetailAsciiString m_str_db8;				///< +0xdb8
	UnsignedByte m_dbc;				///< +0xdbc
	UnsignedByte m_dbd;				///< +0xdbd
	UnsignedByte m_dbe;				///< +0xdbe
	UnsignedByte m_dbf;				///< +0xdbf
	BFMERetailAsciiString m_str_dc0;				///< +0xdc0
	BFMERetailAsciiString m_str_dc4;				///< +0xdc4
	UnsignedInt m_dc8;				///< +0xdc8
	UnsignedByte m_dcc;				///< +0xdcc
	UnsignedByte m_dcd;				///< +0xdcd
	UnsignedByte m_gap0dce[0x2];
	BFMERetailAsciiString m_str_dd0;				///< +0xdd0
	UnsignedInt m_particleCursorBurstCount;				///< +0xdd4
	GameClientRandomVariable m_particleCursorBurstFactor;				///< +0xdd8
	Real m_particleCursorStopBurstFactor;				///< +0xde4
	UnsignedInt m_particleCursorBurstFrequency;				///< +0xde8
	GameClientRandomVariable m_particleCursorParticleLife;				///< +0xdec
	GameClientRandomVariable m_particleCursorSystemLife;				///< +0xdf8
	GameClientRandomVariable m_particleCursorDriftVelX;				///< +0xe04
	GameClientRandomVariable m_particleCursorDriftVelY;				///< +0xe10
	GameClientRandomVariable m_particleCursorVelocityDrag;				///< +0xe1c
	GameClientRandomVariable m_particleCursorParticleSize;				///< +0xe28
	Bool m_particleCursorPerFrameSize;				///< +0xe34
	UnsignedByte m_gap0e35[0x3];
	Int m_particleCursorAlpha;				///< +0xe38
	ICoord2D m_particleCursorOffset;				///< +0xe3c
	ICoord2D m_progressMovieOffset;				///< +0xe44
	ICoord2D m_progressMovieSize;				///< +0xe4c
	Bool m_useHelpTextSystem;				///< +0xe54
	Bool m_guiTextureFiltering;				///< +0xe55
	UnsignedByte m_gap0e56[0x2];
	Real m_cameraLockHeightDelta;				///< +0xe58
	Real m_cameraTerrainSampleRadiusForHeight;				///< +0xe5c
	Bool m_enableHouseColor;				///< +0xe60
	UnsignedByte m_gap0e61[0x3];
	Real m_cameraEaseFactor;				///< +0xe64
	UnsignedInt m_e68;				///< +0xe68
	UnsignedByte m_e6c;				///< +0xe6c
	UnsignedByte m_gap0e6d[0x3];
	Int m_goodCommandPoints;				///< +0xe70
	Int m_evilCommandPoints;				///< +0xe74
	Int m_goodCommandPointsBonus;				///< +0xe78
	Int m_evilCommandPointsBonus;				///< +0xe7c
	Int m_goodCommandPointsAI;				///< +0xe80
	Int m_evilCommandPointsAI;				///< +0xe84
	Int m_goodCommandPointsMP2;				///< +0xe88
	Int m_evilCommandPointsMP2;				///< +0xe8c
	Int m_goodCommandPointsMP3;				///< +0xe90
	Int m_evilCommandPointsMP3;				///< +0xe94
	Int m_goodCommandPointsMP4;				///< +0xe98
	Int m_evilCommandPointsMP4;				///< +0xe9c
	Int m_goodCommandPointsMP56;				///< +0xea0
	Int m_evilCommandPointsMP56;				///< +0xea4
	Int m_goodCommandPointsMP78;				///< +0xea8
	Int m_evilCommandPointsMP78;				///< +0xeac
	Int m_initialMaxRingLevel;				///< +0xeb0
	Real m_resourceBonusMultiplier;				///< +0xeb4
	Int m_goodCommandPointLimit;				///< +0xeb8
	Int m_evilCommandPointLimit;				///< +0xebc
	Int m_powerLimit;				///< +0xec0
	Real m_resourceMultiplierLimit;				///< +0xec4
	UnsignedByte m_ec8;				///< +0xec8
	UnsignedByte m_gap0ec9[0x3];
	UnsignedInt m_ecc;				///< +0xecc
	UnsignedByte m_ed0;				///< +0xed0
	UnsignedByte m_ed1;				///< +0xed1
	UnsignedByte m_gap0ed2[0x2];
	UnsignedInt m_ed4;				///< +0xed4
	UnsignedInt m_ed8;				///< +0xed8
	AttributeHandleStandIn m_attr_edc;				///< +0xedc
	Rva00083150 m_grid_ee0;				///< +0xee0
	_STL::vector<BFMERetailAsciiString> m_vec_11e0;				///< +0x11e0
	UnsignedByte m_11ec;				///< +0x11ec
	UnsignedByte m_gap11ed[0x3];
	UnsignedInt m_11f0;				///< +0x11f0
	Int m_blockedByWallLeeway;				///< +0x11f4
	Real m_secondsBeforeBaseCheckActive;				///< +0x11f8
	UnsignedByte m_11fc;				///< +0x11fc
	UnsignedByte m_gap11fd[0x3];
	BFMERetailAsciiString m_str_1200;				///< +0x1200
	BFMERetailAsciiString m_str_1204;				///< +0x1204
	_STL::vector<BFMERetailAsciiString> m_vec_1208;				///< +0x1208
	UnsignedInt m_1214;				///< +0x1214
	UnsignedInt m_1218;				///< +0x1218
	AttributeHandleStandIn m_attr_121c;				///< +0x121c
	Real m_shrubBrightnessScale;				///< +0x1220
	Int m_scoreKeeperUnitsBuiltMultiplier;				///< +0x1224
	Int m_scoreKeeperUnitsDestroyedMultiplier;				///< +0x1228
	Int m_scoreKeeperStructuresBuiltMultiplier;				///< +0x122c
	Int m_scoreKeeperStructuresDestroyedMultiplier;				///< +0x1230
	Int m_scoreKeeperHeroesVettedMultiplier;				///< +0x1234
	Int m_scoreKeeperUnitsVettedMultiplier;				///< +0x1238
	Int m_scoreKeeperObjectivesCompletedMultiplier;				///< +0x123c
	Int m_scoreKeeperSuppliesCollectedMultiplier;				///< +0x1240
	Int m_scoreKeeperPowerPointsMultiplier;				///< +0x1244
	Int m_scoreKeeperRegionCommandPointsMultiplier;				///< +0x1248
	Int m_scoreKeeperRegionResourcesMultiplier;				///< +0x124c
	Int m_scoreKeeperRegionPowerPointsMultiplier;				///< +0x1250
	Int m_scoreKeeperTimeTakenMultiplier;				///< +0x1254
	Int m_scoreKeeperTimeTakenMaximumScore;				///< +0x1258
	Int m_scoreKeeperTimeTakenMinimumScore;				///< +0x125c
	Int m_scoreKeeperTotalVictoryRequiredScore;				///< +0x1260
	Int m_scoreKeeperNormalVictoryRequiredScore;				///< +0x1264
	Int m_scoreKeeperNormalVictoryRequiredObjectivesPercentage;				///< +0x1268
	UnsignedByte m_126c;				///< +0x126c
	UnsignedByte m_gap126d[0x3];
	Int m_tintUnitIfPathingForMoreThan;				///< +0x1270
	Real m_clampedLOSHeightForCastleStructures;				///< +0x1274
	UnsignedByte m_1278;				///< +0x1278
	UnsignedByte m_gap1279[0x3];
	BFMERetailAsciiString m_str_127c;				///< +0x127c
	BfmeGdUnicodeString m_ustr_1280;				///< +0x1280
	BFMERetailAsciiString m_str_1284;				///< +0x1284
	BFMERetailAsciiString m_userDataLeafName;				///< +0x1288

	GlobalData *m_next;				///< +0x128c
};

// ??0GlobalData@@QAE@XZ
GlobalData::GlobalData()
{
	Int i, j;

	if (m_theOriginal == NULL)
		m_theOriginal = this;

	m_next = NULL;
	m_cf0 = 0;
	m_cf1 = 0;
	m_cf2 = 1;
	m_cf4 = 1;
	m_taintOn = FALSE;
	m_db6 = 0;
	m_cf6 = 0;
	m_cf7 = 0;
	m_cf8 = 0;
	m_d84 = 0;
	m_d85 = 0;
	m_d86 = 0;
	m_d88 = 0;
	m_d87 = 0;
	m_d08 = 0;
	m_d0c = 0;
	m_cf3 = 1;
	m_d0d = 0;
	m_d10 = 0x20;
	m_d18 = 5;
	m_d58 = 0;
	m_d5c = 0x41200000;  // float bits 1e+01f
	m_d60 = 5;
	m_d1c = 0;
	m_d20 = 0x1388;
	m_d24 = 5;
	m_d28 = 0;
	m_d2c = 0x2710;
	m_d30 = 5;
	m_d05 = 0;
	m_d04 = 0;
	m_d00 = -1;
	m_cf9 = 0;
	m_cfa = 0;
	m_cfb = 0;
	m_cfc = 0;
	m_d94 = 0;
	m_d98 = 0;
	m_d9c = 0;
	m_da0 = 0;
	m_da4 = 0;
	m_da8 = 0;
	m_dac = 1;
	m_d89 = 0;
	m_d8a = 0;
	m_d8b = 0;
	m_str_d8c.set(".\\");
	m_str_d90.set("MOTD.txt");
	m_db0 = 0x5a;
	m_db4 = 1;
	m_dbc = 1;
	m_dbd = 0;
	m_dc8 = 0x3f800000;  // float bits 1.0f
	m_dcc = 0;
	m_dcd = 0;
	m_db5 = 0;
	m_str_94.clear();
	m_hideLivingWorldRegions = FALSE;
	m_liveCampaignMode = TRUE;
	m_livingWorldTurbo = FALSE;
	m_resourceBonusMultiplier = 1e+01f;
	m_initialMaxRingLevel = 2;
	m_goodCommandPointLimit = 0xc8;
	m_evilCommandPointLimit = 0x258;
	m_powerLimit = 0xa;
	m_resourceMultiplierLimit = 4.0f;
	m_a7c = 0;
	m_playStats = -1;
	m_bc5 = 0;
	m_mapName.clear();
	m_moveHintName.clear();
	m_str_10.clear();
	m_str_14.clear();
	m_showProps = TRUE;
	m_pushAsideShrubs = FALSE;
	m_1a = 1;
	m_1b = 1;
	m_1c = 0;
	m_1d = 1;
	m_useFpsLimit = FALSE;
	m_useHighQualityVideo = TRUE;
	m_dumpAssetUsage = FALSE;
	m_framesPerSecondLimit = 0;
	m_disablePixelShader = FALSE;
	m_windowed = FALSE;
	m_xResolution = 0x400;
	m_yResolution = 0x300;
	m_showRoads = TRUE;
	m_showTrees = TRUE;
	m_maxShellScreens = 0;
	m_useCloudMap = FALSE;
	m_showWater = TRUE;
	m_useReverseMouseScroll = FALSE;
	m_useLightMap = FALSE;
	m_bilinearTerrainTex = FALSE;
	m_trilinearTerrainTex = FALSE;
	m_48 = 0;
	m_multiPassTerrain = FALSE;
	m_adjustCliffTextures = FALSE;
	m_stretchTerrain = FALSE;
	m_use3WayTerrainBlends = 1;
	m_useHalfHeightMap = FALSE;
	m_60 = 1;
	m_terrainLOD = 8;
	m_terrainLODTargetTimeMS = 0;
	m_58 = 1;
	m_59 = 1;
	m_rightMouseAlwaysScrolls = FALSE;
	m_useWaterPlane = FALSE;
	m_useCloudPlane = FALSE;
	m_downwindAngle = -0.785f;
	m_useShadowVolumes = FALSE;
	m_useShadowDecals = FALSE;
	m_textureReductionFactor = -1;
	m_6c = 0;
	m_enableBehindBuildingMarkers = TRUE;
	m_a90 = 0;
	m_a91 = 0;
	m_a92 = 0;
	m_a93 = 0;
	m_a94 = 1;
	m_a95 = 1;
	m_a96 = 0;
	m_a97 = 0;
	m_a98 = 1;
	m_a9c = 0;
	m_a9d = 0;
	m_a9e = 0;
	m_a9f = 0;
	m_aa0 = 0;
	m_fixedSeed = -1;
	m_horizontalScrollSpeedFactor = 1.0f;
	m_verticalScrollSpeedFactor = 1.0f;
	m_screenEdgeScrollSpeedFactor = 1.0f;
	m_screenEdgeScrollRampTime = 0x12c;
	m_waterPositionX = 0.0f;
	m_waterPositionY = 0.0f;
	m_waterPositionZ = 0.0f;
	m_waterExtentX = 0.0f;
	m_waterExtentY = 0.0f;
	m_waterType = 0;
	m_featherWater = 0;
	m_showSoftWaterEdge = TRUE;
	m_8d = 0;
	m_defaultVoiceAttackChargeTimeout = 0x32;
	m_defaultMaxDistanceForEngaged = 3e+01f;
	m_defaultEngagedStateTimeout = 0xa;
	m_animationSharingCap = 0x64;
	m_animationSharingFrameTolerance = 5.0f;
	m_animationSharingSpeedTolerance = 0.1f;
	m_animationSharingWorryThreshold = 0.25f;
	m_animationSharingDrasticThreshold = 0.5f;
	m_showMetrics = FALSE;
	for (i = 0; i < 4; ++i)
	{
		m_vertexWaterHeightClampLow[i] = 0.0f;
		m_vertexWaterHeightClampHi[i] = 0.0f;
		m_vertexWaterAngle[i] = 0.0f;
		m_vertexWaterXPosition[i] = 0.0f;
		m_vertexWaterYPosition[i] = 0.0f;
		m_vertexWaterZPosition[i] = 0.0f;
		m_vertexWaterXGridCells[i] = 0;
		m_vertexWaterYGridCells[i] = 0;
		m_vertexWaterGridSize[i] = 0.0f;
		m_vertexWaterAttenuationA[i] = 0.0f;
		m_vertexWaterAttenuationB[i] = 0.0f;
		m_vertexWaterAttenuationC[i] = 0.0f;
		m_vertexWaterAttenuationRange[i] = 0.0f;
		m_strArr_9c[i].clear();
	}
	m_drawSkyBox = FALSE;
	m_maxTerrainTracks = 0;
	m_levelGainAnimationDisplayTimeInSeconds = 0.0f;
	m_levelGainAnimationZRisePerSecond = 0.0f;
	m_getHealedAnimationDisplayTimeInSeconds = 0.0f;
	m_getHealedAnimationZRisePerSecond = 0.0f;
	m_1f4 = 0x64;
	m_1f8 = 0x19;
	m_1fc = 0x493e0;
	m_timeOfDay = 2;
	m_weather = 0;
	m_makeTrackMarks = FALSE;
	m_hideGarrisonFlags = FALSE;
	m_forceModelsToFollowTimeOfDay = TRUE;
	m_forceModelsToFollowWeather = TRUE;
	m_partitionCellSize = 0.0f;
	m_ammoPipScaleFactor = 1.0f;
	m_containerPipScaleFactor = 1.0f;
	m_ammoPipWorldOffset.x = 0.0f;
	m_ammoPipWorldOffset.y = 0.0f;
	m_ammoPipWorldOffset.z = 0.0f;
	m_containerPipWorldOffset.x = 0.0f;
	m_containerPipWorldOffset.y = 0.0f;
	m_containerPipWorldOffset.z = 0.0f;
	m_ammoPipScreenOffset.y = 0.0f;
	m_ammoPipScreenOffset.x = 0.0f;
	m_containerPipScreenOffset.y = 0.0f;
	m_containerPipScreenOffset.x = 0.0f;
	for (j = 0; j < 3; ++j)
	{
		m_rgb09bc[j].red = 0.0f;
		m_rgb09bc[j].green = 0.0f;
		m_rgb09bc[j].blue = 0.0f;
		m_rgb09e0[j].red = 0.0f;
		m_rgb09e0[j].green = 0.0f;
		m_rgb09e0[j].blue = 0.0f;
		m_pos0a04[j].x = 0.0f;
		m_pos0a04[j].y = 0.0f;
		m_pos0a04[j].z = -1.0f;
		for (i = 0; i < 6; ++i)
		{
			m_terrainLighting[i][j].ambient.red = 0.0f;
			m_terrainLighting[i][j].ambient.green = 0.0f;
			m_terrainLighting[i][j].ambient.blue = 0.0f;
			m_terrainLighting[i][j].diffuse.red = 0.0f;
			m_terrainLighting[i][j].diffuse.green = 0.0f;
			m_terrainLighting[i][j].diffuse.blue = 0.0f;
			m_terrainLighting[i][j].lightPos.x = 0.0f;
			m_terrainLighting[i][j].lightPos.y = 0.0f;
			m_terrainLighting[i][j].lightPos.z = -1.0f;
			m_terrainObjectsLighting[i][j].ambient.red = 0.0f;
			m_terrainObjectsLighting[i][j].ambient.green = 0.0f;
			m_terrainObjectsLighting[i][j].ambient.blue = 0.0f;
			m_terrainObjectsLighting[i][j].diffuse.red = 0.0f;
			m_terrainObjectsLighting[i][j].diffuse.green = 0.0f;
			m_terrainObjectsLighting[i][j].diffuse.blue = 0.0f;
			m_terrainObjectsLighting[i][j].lightPos.x = 0.0f;
			m_terrainObjectsLighting[i][j].lightPos.y = 0.0f;
			m_terrainObjectsLighting[i][j].lightPos.z = -1.0f;
		}
	}
	m_a28 = 0x3f800000;  // float bits 1.0f
	m_numGlobalLights = 3;
	m_maxRoadSegments = 0;
	m_maxRoadVertex = 0;
	m_maxRoadIndex = 0;
	m_maxRoadTypes = 0;
	m_baseValuePerSupplyBox = 0x64;
	m_supplyBoxesPerTree = 1;
	m_audioOn = TRUE;
	m_musicOn = TRUE;
	m_soundsOn = TRUE;
	m_sounds3DOn = TRUE;
	m_speechOn = TRUE;
	m_ambientStreamsOn = TRUE;
	m_a72 = 0;
	m_videoOn = TRUE;
	m_disableCameraMovement = FALSE;
	m_showSelectedUnitMarker = TRUE;
	m_useSimpleHordeDecals = FALSE;
	m_useSimpleMergeDecals = FALSE;
	m_opacityOfSimpleMergeDecals = 0.3f;
	m_maxVisibleTranslucentObjects = 0x200;
	m_a48 = 0x200;
	m_a4c = 0x200;
	m_a50 = 0x200;
	m_occludedLuminanceScale = 0.5f;
	m_a7f = 1;
	m_a84 = 0;
	m_particleScale = 1.0f;
	m_autoFireParticleSmallMax = 0;
	m_autoFireParticleMediumMax = 0;
	m_autoFireParticleLargeMax = 0;
	m_autoSmokeParticleSmallMax = 0;
	m_autoSmokeParticleMediumMax = 0;
	m_autoSmokeParticleLargeMax = 0;
	m_autoAflameParticleMax = 0;
	m_autoFireParticleSmallPrefix.clear();
	m_autoFireParticleMediumPrefix.clear();
	m_autoFireParticleLargePrefix.clear();
	m_autoSmokeParticleSmallPrefix.clear();
	m_autoSmokeParticleMediumPrefix.clear();
	m_autoSmokeParticleLargePrefix.clear();
	m_autoAflameParticlePrefix.clear();
	m_autoFireParticleSmallSystem.clear();
	m_autoFireParticleMediumSystem.clear();
	m_autoFireParticleLargeSystem.clear();
	m_autoSmokeParticleSmallSystem.clear();
	m_autoSmokeParticleMediumSystem.clear();
	m_autoSmokeParticleLargeSystem.clear();
	m_autoAflameParticleSystem.clear();
	m_levelGainAnimationName.clear();
	m_getHealedAnimationName.clear();
	m_specialPowerViewObjectName.clear();
	m_drawEntireTerrain = FALSE;
	m_maxParticleCount = 0;
	m_maxFieldParticleCount = 0x1e;
	m_debugAI = FALSE;
	m_debugAIObstacles = FALSE;
	m_showClientPhysics = TRUE;
	m_showTerrainNormals = FALSE;
	m_showObjectHealth = TRUE;
	m_a8e = 1;
	m_showTooltips = TRUE;
	m_a91 = 0;
	m_defaultCameraPitchAngle = 37.5f;
	m_defaultCameraYawAngle = 0.0f;
	m_defaultCameraScrollSpeedScalar = 1.0f;
	m_defaultCameraMinHeight = 1e+02f;
	m_defaultCameraMaxHeight = 3e+02f;
	m_cameraLockHeightDelta = 2.5e+02f;
	m_terrainHeightAtEdgeOfMap = 0.0f;
	m_cameraEaseFactor = 0.2f;
	m_unitDamagedThresh = 0.5f;
	m_unitReallyDamagedThresh = 0.1f;
	m_groundStiffness = 0.5f;
	m_structureStiffness = 0.5f;
	m_gravity = -1.0f;
	m_stealthFriendlyOpacity = 0.5f;
	m_defaultOcclusionDelay = 0xf;
	m_1b8 = 0;
	m_b0c = 1;
	m_b10 = 0;
	m_BuildSpeed = 0.0f;
	m_MinDistFromEdgeOfMapForBuild = 0.0f;
	m_SupplyBuildBorder = 0.0f;
	m_allowedHeightVariationForBuilding = 0.0f;
	m_MinLowEnergyProductionSpeed = 0.0f;
	m_MaxLowEnergyProductionSpeed = 0.0f;
	m_LowEnergyPenaltyModifier = 0.0f;
	m_MultipleFactory = 0.0f;
	m_RefundPercent = 0.0f;
	m_commandCenterHealRange = 0.0f;
	m_commandCenterHealAmount = 0.0f;
	m_maxTunnelCapacity = 0;
	m_maxLineBuildObjects = 0;
	m_damageRadiusMinimumForSplash = 4.0f;
	m_groupSelectMinSelectSize = 5;
	m_groupSelectVolumeBase = 0.5f;
	m_groupSelectVolumeIncrement = 0.02f;
	m_maxUnitSelectSounds = 8;
	m_selectionFlashSaturationFactor = 0.5f;
	m_selectionFlashHouseColor = FALSE;
	m_cameraAudibleRadius = 5e+02f;
	m_groupMoveClickToGatherFactor = 1.0f;
	m_shakeSubtleIntensity = 0.5f;
	m_shakeNormalIntensity = 1.0f;
	m_shakeStrongIntensity = 2.5f;
	m_shakeSevereIntensity = 5.0f;
	m_shakeCineExtremeIntensity = 8.0f;
	m_shakeCineInsaneIntensity = 12.0f;
	m_maxShakeIntensity = 1e+01f;
	m_maxShakeRange = 1.5e+02f;
	m_sellPercentage = 1.0f;
	m_baseRegenHealthPercentPerSecond = 0.0f;
	m_baseRegenDelay = 0;
	m_timeAfterDamageUntilRepairAllowed = 0xa;
	m_a7d = 0;
	m_a7e = 0;
	m_hotKeyTextColor = 0xffffff00;
	m_shroudColor.red = 1.0f;
	m_shroudColor.green = 1.0f;
	m_shroudColor.blue = 1.0f;
	m_clearAlpha = 0xff;
	m_fogAlpha = 0x7f;
	m_shroudAlpha = 0;
	m_taintColor.red = 1.0f;
	m_taintColor.green = 1.0f;
	m_taintColor.blue = 1.0f;
	m_taintAlpha = 0x80;
	m_powerBarBase = 7;
	m_powerBarIntervals = 3.0f;
	m_powerBarYellowRange = 5;
	m_c68 = 0x3f800000;  // float bits 1.0f
	m_standardPublicBones.clear();
	m_c00 = 0;
	m_c04 = 1;
	m_c05 = 0;
	m_c09 = 0;
	m_c06 = 0;
	m_c07 = 0;
	m_c08 = 0;
	m_firewallBehavior = 0;
	m_b18 = 0;
	m_firewallPortOverride = 0;
	m_firewallPortAllocationDelta = 0;
	m_c0a = 0;
	m_c0b = 0;
	m_c0c = 0;
	m_useCameraInReplay = FALSE;
	m_c58 = 0;
	m_c59 = 0;
	m_unlookPersistDuration = 0x1e;
	m_ecc = 0;
	m_ed0 = 0;
	m_ed1 = 1;
	m_ed4 = 0x3f333333;  // float bits 0.7f
	m_ed8 = 0;
	m_networkFPSHistoryLength = 0x1e;
	m_networkLatencyHistoryLength = 0xc8;
	m_networkRunAheadMetricsTime = 0x1f4;
	m_networkCushionHistoryLength = 0xa;
	m_networkRunAheadSlack = 0xa;
	m_networkKeepAliveDelay = 0x14;
	m_networkDisconnectTime = 0x1388;
	m_networkPlayerTimeoutTime = 0xea60;
	m_networkDisconnectScreenNotifyTime = 0x3a98;
	m_dbe = 0;
	m_dbf = 0;
	setTimeOfDay(m_timeOfDay);
	m_b7d = 0;
	m_str_b80.clear();
	m_str_b84.clear();
	m_b88 = 0;
	m_b98 = 0x3f800000;  // float bits 1.0f
	m_healthBonus[0] = 1.0f;
	m_healthBonus[1] = 1.0f;
	m_healthBonus[2] = 1.0f;
	m_soloPlayerHealthBonusForDifficulty[0] = 1.0f;
	m_soloPlayerHealthBonusForDifficulty[1] = 1.0f;
	m_soloPlayerHealthBonusForDifficulty[2] = 1.0f;
	m_soloPlayerHealthBonusForDifficulty[3] = 1.0f;
	m_soloPlayerHealthBonusForDifficulty[4] = 1.0f;
	m_soloPlayerHealthBonusForDifficulty[5] = 1.0f;
	m_defaultStructureRubbleHeight = 1.0f;
	m_weaponBonusSet = new WeaponBonusSet;
	m_shellMapName.set("Maps\\ShellMap1\\ShellMap1.map");
	m_shellMapOn = TRUE;
	m_shellMapOffByCommandArgument = FALSE;
	m_playIntro = TRUE;
	m_skipMapUnroll = FALSE;
	m_bb7 = 0;
	m_bb8 = 0;
	m_bb9 = 0;
	m_keyboardScrollFactor = 1.0f;
	m_keyboardDefaultScrollFactor = 1.0f;
	m_scrollAmountCutoff = 1e+01f;
	m_cameraAdjustSpeed = 0.1f;
	m_enforceMaxCameraHeight = TRUE;
	m_attributeModifierArmorMaxBonus = 1.0f;
	m_bd0.m_value = 0x254b6fae;
	m_bd4 = -1;

	unsigned long exeCRC = 0;
	char buffer[260];
	GetModuleFileNameA(NULL, buffer, sizeof(buffer));
	File *fp = TheFileSystem->openFile(buffer, 0x41);
	if (fp != NULL)
	{
		unsigned char crcBlock[0x10000];
		Int amtRead;
		while ((amtRead = fp->read(crcBlock, 0x10000)) > 0)
			exeCRC = CRC_Memory(crcBlock, amtRead, exeCRC);
		fp->close();
	}
	if (TheVersion)
	{
		UnsignedInt version = TheVersion->getVersionNumber();
		exeCRC = CRC_Memory((const unsigned char *)&version, 4, exeCRC);
	}
	m_bd0.m_value = protectCrc00062EF0(exeCRC, exeCRC);
	m_movementPenaltyDamageState = 2;
	m_c70 = 0;
	m_c74 = GetDoubleClickTime();
	m_aac = 0;
	m_keyboardCameraRotateSpeed = 0.1f;
	m_particleCursorBurstCount = 0xa;
	m_particleCursorBurstFrequency = 5;
	m_particleCursorPerFrameSize = FALSE;
	m_particleCursorAlpha = 0xff;
	m_particleCursorOffset.y = 0;
	m_particleCursorOffset.x = 0;
	m_progressMovieOffset.x = 0xffffff6a;
	m_progressMovieOffset.y = 0xffffff60;
	m_progressMovieSize.y = 0x80;
	m_progressMovieSize.x = 0x80;
	m_useHelpTextSystem = FALSE;
	m_guiTextureFiltering = TRUE;
	m_cameraTerrainSampleRadiusForHeight = 0.0f;
	m_e68 = 0x3f800000;  // float bits 1.0f
	m_e6c = 0;
	m_enableHouseColor = FALSE;
	m_goodCommandPoints = 0x3c;
	m_evilCommandPoints = 0x7d;
	m_goodCommandPointsBonus = 0xa;
	m_evilCommandPointsBonus = 0x19;
	m_goodCommandPointsAI = 0x64;
	m_evilCommandPointsAI = 0x12c;
	m_goodCommandPointsMP2 = 0x64;
	m_evilCommandPointsMP2 = 0x12c;
	m_goodCommandPointsMP3 = 0x50;
	m_evilCommandPointsMP3 = 0x96;
	m_goodCommandPointsMP4 = 0x50;
	m_evilCommandPointsMP4 = 0x78;
	m_goodCommandPointsMP56 = 0x3c;
	m_evilCommandPointsMP56 = 0x50;
	m_goodCommandPointsMP78 = 0x32;
	m_evilCommandPointsMP78 = 0x3c;
	m_ec8 = 0;
	m_11ec = 0;
	m_11f0 = 0;
	m_blockedByWallLeeway = 3;
	m_secondsBeforeBaseCheckActive = 5.0f;
	m_11fc = 1;
	m_shrubBrightnessScale = 1.0f;
	m_126c = 1;
	m_tintUnitIfPathingForMoreThan = 0;
	m_clampedLOSHeightForCastleStructures = 4e+01f;
	m_scoreKeeperUnitsBuiltMultiplier = 1;
	m_scoreKeeperUnitsDestroyedMultiplier = 1;
	m_scoreKeeperStructuresBuiltMultiplier = 1;
	m_scoreKeeperStructuresDestroyedMultiplier = 1;
	m_scoreKeeperHeroesVettedMultiplier = 1;
	m_scoreKeeperUnitsVettedMultiplier = 1;
	m_scoreKeeperObjectivesCompletedMultiplier = 1;
	m_scoreKeeperSuppliesCollectedMultiplier = 1;
	m_scoreKeeperPowerPointsMultiplier = 1;
	m_scoreKeeperRegionCommandPointsMultiplier = 1;
	m_scoreKeeperRegionResourcesMultiplier = 1;
	m_scoreKeeperRegionPowerPointsMultiplier = 1;
	m_scoreKeeperTimeTakenMultiplier = 1;
	m_scoreKeeperTimeTakenMaximumScore = 1;
	m_scoreKeeperTimeTakenMinimumScore = 1;
	m_scoreKeeperTotalVictoryRequiredScore = 1;
	m_scoreKeeperNormalVictoryRequiredScore = 1;
	m_scoreKeeperNormalVictoryRequiredObjectivesPercentage = 1;
	m_1214 = 0xff0b5ef2;
	m_1218 = 0xffd92102;
	m_1278 = 0;
}
