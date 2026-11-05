// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00088140 (21 B) is Zero Hour WorldHeightMap.cpp's file-static validateName,
// returned by value into the MapObject constructor at 0x00088160, whose only call
// (0x000881CB) passes the name in EAX and the result slot in ESI. That private
// convention is what MSVC 7.1 gives a file-static; the unused flags argument drops out.
// Zero Hour takes the name by value; retail releases nothing here, so BFME takes it by
// reference.
// The constructor (retail 0x00088160, 386 B) lives here beside it so the call keeps
// that private convention. BFME's constructor also takes the name by reference (see
// targets/game/reverse/identity_evidence/00088160-mapobject-ctor-name-by-reference.md),
// and retail reuses the dead parameter slot as validateName's return slot. The class
// layout is the one MapObjectDestructor.cpp witnesses for the matched destructor.
// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp:68

#include "ascii_string.h"

typedef int Int;

// ?validateName@@YA?AVAsciiString@@ABV1@H@Z
static __declspec(noinline) AsciiString validateName(const AsciiString &n, Int flags)
{
	return n;
}

typedef float Real;
typedef bool Bool;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };

class StaticNameKey
{
public:
	NameKeyType key() const;
	operator NameKeyType() const { return key(); }

private:
	NameKeyType m_key;
	const char *m_name;
};

// The default-property keys. Two are recorded under their Zero Hour names; the
// other five have no ledger owner yet, so they keep their retail addresses (in
// Zero Hour order: objectEnabled, objectIndestructible, objectPowered,
// objectRecruitableAI, objectTargetable).
extern const StaticNameKey TheKey_objectInitialHealth;
extern const StaticNameKey g_Va012A7810;
extern const StaticNameKey g_Va012A7818;
extern const StaticNameKey TheKey_objectUnsellable;
extern const StaticNameKey g_Va012A7840;
extern const StaticNameKey g_Va012A7870;
extern const StaticNameKey g_Va012A7828;

class Dict
{
public:
	Dict(Int numPairsToPreAllocate = 0);
	~Dict() { releaseData(); }
	Dict &operator=(const Dict &src);
	void setInt(NameKeyType key, Int value);
	void setBool(NameKeyType key, Bool value);

private:
	void releaseData();
	void *m_data;
};

Real normalizeAngle(Real angle);

class ThingTemplate;
class RenderObjClass;
class Shadow;
typedef unsigned int AudioHandle;

enum { BRIDGE_MAX_TOWERS = 4 };

// Layout as in MapObjectDestructor.cpp (the matched destructor at 0x00088350).
class Rva00088350RefPtr
{
public:
	Rva00088350RefPtr() : m_ptr(0) {}
	~Rva00088350RefPtr();

private:
	void *m_ptr;
};

// Retail clears the list link before it installs MapObject's vptr, which is the
// order a base-class member initializer gives.
class MapObjectBase
{
public:
	MapObjectBase() : m_nextMapObject(0) {}
	virtual ~MapObjectBase() {}

protected:
	class MapObject *m_nextMapObject;		///< +0x04
};

class MapObject : public MapObjectBase
{
public:
	MapObject(Coord3D loc, const AsciiString &name, Real angle, Int flags, const Dict *props,
		const ThingTemplate *thingTemplate);

protected:
	virtual ~MapObject();

private:
	Coord3D m_location;				///< +0x08
	AsciiString m_objectName;			///< +0x14
	const ThingTemplate *m_thingTemplate;		///< +0x18
	Real m_angle;					///< +0x1C
	Int m_flags;					///< +0x20
	Dict m_properties;				///< +0x24
	Int m_color;					///< +0x28
	RenderObjClass *m_renderObj;			///< +0x2C
	Shadow *m_shadowObj;				///< +0x30
	RenderObjClass *m_bridgeTowers[BRIDGE_MAX_TOWERS];	///< +0x34
	Int m_runtimeFlags;				///< +0x44
	char m_pad48[0x0C];				///< +0x48
	AudioHandle m_rva54;				///< +0x54
	AudioHandle m_rva58;				///< +0x58
	Rva00088350RefPtr m_rva5c;			///< +0x5C
};

// ??0MapObject@@QAE@UCoord3D@@ABVAsciiString@@MHPBVDict@@PBVThingTemplate@@@Z
MapObject::MapObject(Coord3D loc, const AsciiString &name, Real angle, Int flags, const Dict *props,
	const ThingTemplate *thingTemplate)
{
	m_location = loc;
	m_objectName = validateName(name, flags);
	m_thingTemplate = thingTemplate;
	m_angle = normalizeAngle(angle);
	m_flags = flags;
	m_rva54 = 1;
	m_rva58 = 1;
	if (props)
	{
		m_properties = *props;
	}
	else
	{
		m_properties.setInt(TheKey_objectInitialHealth, 100);
		m_properties.setBool(g_Va012A7810, true);
		m_properties.setBool(g_Va012A7818, false);
		m_properties.setBool(TheKey_objectUnsellable, false);
		m_properties.setBool(g_Va012A7840, true);
		m_properties.setBool(g_Va012A7870, true);
		m_properties.setBool(g_Va012A7828, false);
	}
	m_renderObj = 0;
	m_shadowObj = 0;
	m_color = 0xff << 8;
	for (Int i = 0; i < BRIDGE_MAX_TOWERS; ++i)
		m_bridgeTowers[i] = 0;
	m_runtimeFlags = 0;
}
