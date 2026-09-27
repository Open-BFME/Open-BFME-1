// ??0MapObject@@QAE@UCoord3D@@VAsciiString@@MHPBVDict@@PBVThingTemplate@@@Z
// partial score=0.31 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
// MapObject::MapObject, retail 0x00088160, 386 bytes. NOT YET MATCHED
// (partial, 404 bytes): see targets/game/reverse/re_attempts.log.
//
// IDENTITY. The name is the lift's, and it is proven here, not assumed:
//   * the body installs vtable 0x0107C7E0, the same vtable the MATCHED deleting
//     destructor ??1MapObject@@MAE@XZ (0x00088350) installs;
//   * the MATCHED caller ?duplicate@MapObject@@QAEPAV1@XZ (0x00089390) pushes
//     0x60 to operator new and calls this body with
//     (loc, objectName, angle, flags, &properties, thingTemplate) -- the same
//     six arguments, in this order, and 0x60 is this class's size;
//   * retail's caller copies Coord3D by value in 12 stack bytes, which fixes
//     the `UCoord3D@@` (trivially copyable, expanded) argument shape.
//
// WHY A SEPARATE TU. WorldHeightMap.cpp includes the Zero Hour MapObject.h,
// whose member order puts m_nextMapObject at +0x1C; retail puts it at +0x04
// (the constructor's first store and the destructor's list walk) and every
// later member four bytes lower, so m_location lands at +0x08 and
// m_properties at +0x24. The reference header is vendored, so the layout is
// declared here instead -- the same TU-scoped shim the other landed
// MapObject methods use (MapObject_verifyValidTeamMethodThunk.cpp).
//
// CALLEES (tools/callees.py 0x00088160 386):
//   0x00002ECD Dict::Dict(Int)                    ??0Dict@@QAE@H@Z
//   0x00088140 outlined copy of the by-value name parameter (not written here)
//   0x00887C90 StringBase<char>::set              ?set@?$StringBase@D@@QAEXABV1@@Z
//   0x00887940 StringBase<char>::releaseBuffer    ?releaseBuffer@?$StringBase@D@@AAEXXZ
//   0x0000991C Real normalizeAngle(Real)          ?normalizeAngle@@YAMM@Z
//   0x00045566 Dict::operator=                    ??4Dict@@QAEAAV0@ABV0@@Z
//   0x00009304 StaticNameKey::key()               ?key@StaticNameKey@@QBE?AW4NameKeyType@@XZ
//   0x00010A0A Dict::setInt                       ?setInt@Dict@@QAEXW4NameKeyType@@H@Z
//   0x00006F64 Dict::setBool                      ?setBool@Dict@@QAEXW4NameKeyType@@_N@Z
//
// WHAT IS STILL WRONG (probe: ours 404 bytes, retail 386, 231 differing
// non-reloc bytes, first divergence +25, 0.887 of instructions equal once
// registers and constants are normalised -- quality 1-(231+2*18)/386 = 0.31):
//
//  1. The frame. Retail keeps `this` in edi and the zero in esi; MSVC 7.1 gives
//     me this=esi, 0=ebx, &m_objectName=ebp, &m_properties=edi, and therefore
//     puts the vptr install after the +0x04 store instead of before it. Same
//     five callee-saved pushes, wrong roles. A base class for the vptr did not
//     move it (0.887 either way), so this is a source-shape lever, not a
//     declaration one -- docs/shape_levers.md rows 3-5 (register-mirror:
//     reorder local DEFINITIONS to retail's first-use order).
//  2. The name parameter. Retail copies the by-value AsciiString *in place in
//     its own argument slot* through one 21-byte helper at 0x00088140
//     (`push ecx; push eax; mov ecx,esi; mov [esp+4],0; call <StringBase copy
//     ctor>; mov eax,esi; pop ecx; ret`, which returns its destination in eax),
//     then `set`s from that eax and releases it. My four spellings all miss it:
//     `m_objectName.set(name)` (P7 shape) elides the copy entirely; a local
//     `AsciiString n = name` block copies into a dead argument slot addressed
//     by `lea` (this body, 404 B); `validateName(name, flags)` returning
//     AsciiString by value is NOT inlined by MSVC 7.1 even under __forceinline
//     and emits its own call plus a second copy (416 B). 0x00088140 takes its
//     source in EAX and its destination in ESI with no stack argument, which
//     no C++ spelling I tried makes a callee accept -- that helper is the lever
//     nobody has pulled yet.
//  3. Consequence of (2): the `set` argument is an `lea` of the local instead
//     of retail's `push eax` of the helper's return value, and the releaseBuffer
//     call is addressed with `lea` instead of retail's reused esi.
//
// Everything after the name block is already in retail's order, including the
// tail's 0x2C, 0x30, 0x28, 0x34..0x44 store run and the seven key calls
// (0x7F8=100 setInt, 0x810=1, 0x818=0, 0x820=0, 0x840=1, 0x870=1, 0x828=0,
// which is objectInitialHealth, objectEnabled, objectIndestructible,
// objectUnsellable, objectPowered, objectRecruitableAI, objectTargetable).
//
// LAYOUT WITNESSES. +0x2C m_renderObj and +0x34 m_bridgeTowers[4] come from
// the matched destructor; +0x24 m_properties and +0x14 m_objectName from its
// Dict and releaseBuffer calls; +0x44 m_runtimeFlags from ?duplicate's copy.
// +0x54, +0x58 (both set to 1) and +0x5C (set to 0, a RefCountClass* released
// through Rva01358E54 by the destructor) have no witness and no ZH name, so
// they keep address-derived names.

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
public:
	void set(const StringBase<T> &src);
	StringBase<T> &operator=(const StringBase<T> &src);
private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &src);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	void *m_data;
};

// BFME's narrow string is ONE pointer wide and owns an out-of-line copy
// constructor and releaseBuffer on the base -- the model P7ByValueStringSetters
// and the stringinline shim both proved. Deriving publicly (not
// `: private`) is what keeps `set` callable on an AsciiString member here.
class AsciiString : public StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

// A `struct`, not a `class`: MSVC 7.1 mangles a trivially copyable by-value
// class argument U and a non-trivially copyable one V, and retail's name says
// UCoord3D@@ while its caller copies 12 bytes straight into the argument area.
struct Coord3D
{
	float m_x, m_y, m_z;
};

class ThingTemplate;
class RenderObjClass;
class Shadow;
class RefCountClass;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class StaticNameKey
{
public:
	NameKeyType key() const;
};

extern const StaticNameKey TheKey_objectInitialHealth;
extern const StaticNameKey TheKey_objectEnabled;
extern const StaticNameKey TheKey_objectIndestructible;
extern const StaticNameKey TheKey_objectUnsellable;
extern const StaticNameKey TheKey_objectPowered;
extern const StaticNameKey TheKey_objectRecruitableAI;
extern const StaticNameKey TheKey_objectTargetable;

// One pointer wide, like retail's (only m_data is touched by the constructor
// and the assignment operator).
class Dict
{
public:
	Dict(int numPairsToPreAllocate = 0);
	Dict &operator=(const Dict &src);
	void setInt(NameKeyType key, int value);
	void setBool(NameKeyType key, bool value);
private:
	void *m_data;
};

float normalizeAngle(float angle);

enum { BRIDGE_MAX_TOWERS = 4 };

// The virtual slot is MapObject's own: the matched destructor mangles MAE --
// protected, virtual -- so the vptr lives here and the constructor's
// `mov [edi], 0x107c7e0` is its install.
class MapObject
{
public:
	MapObject(Coord3D loc, AsciiString name, float angle, int flags,
		const Dict *props, const ThingTemplate *thingTemplate);

protected:
	virtual ~MapObject();

private:
	MapObject *m_nextMapObject;					///< +0x04
	Coord3D m_location;							///< +0x08
	AsciiString m_objectName;					///< +0x14
	const ThingTemplate *m_thingTemplate;		///< +0x18
	float m_angle;								///< +0x1C
	int m_flags;								///< +0x20
	Dict m_properties;							///< +0x24
	int m_color;								///< +0x28
	RenderObjClass *m_renderObj;				///< +0x2C
	Shadow *m_shadowObj;						///< +0x30
	RenderObjClass *m_bridgeTowers[BRIDGE_MAX_TOWERS];	///< +0x34
	int m_runtimeFlags;							///< +0x44
	char m_pad48[0x0C];							///< +0x48, unwritten by retail
	int m_rva54;								///< +0x54, set true
	int m_rva58;								///< +0x58, set true
	RefCountClass *m_rva5c;						///< +0x5C, set null
};

MapObject::MapObject(Coord3D loc, AsciiString name, float angle, int flags,
	const Dict *props, const ThingTemplate *thingTemplate)
	: m_nextMapObject(0)
{
	m_rva5c = 0;
	m_location = loc;
	{
		AsciiString n = name;
		m_objectName.set(n);
	}
	m_thingTemplate = thingTemplate;
	m_angle = normalizeAngle(angle);
	m_flags = flags;
	m_rva54 = true;
	m_rva58 = true;
	if (props)
	{
		m_properties = *props;
	}
	else
	{
		m_properties.setInt(TheKey_objectInitialHealth.key(), 100);
		m_properties.setBool(TheKey_objectEnabled.key(), true);
		m_properties.setBool(TheKey_objectIndestructible.key(), false);
		m_properties.setBool(TheKey_objectUnsellable.key(), false);
		m_properties.setBool(TheKey_objectPowered.key(), true);
		m_properties.setBool(TheKey_objectRecruitableAI.key(), true);
		m_properties.setBool(TheKey_objectTargetable.key(), false);
	}
	m_renderObj = 0;
	m_shadowObj = 0;
	m_color = (0xff) << 8;
	for (int i = 0; i < BRIDGE_MAX_TOWERS; ++i)
		m_bridgeTowers[i] = 0;
	m_runtimeFlags = 0;
}
