// ?ParseObjectDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// partial score=0.82 date=2026-09-10
// Clean reconstruction of the BFME map-object chunk parser.
//
// The callback is registered by MapUtil::ParseObjectsDataChunk.  Retail uses
// the name registry at 0x012EF1D8 to choose the dictionary-aware MapObject
// constructor; the predicate is the same body recovered as
// Rva00137E20ThingNameFilter::acceptsThingTemplateName.

// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef int NameKeyType;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AsciiString
{
public:
	void *m_data;
	AsciiString(const AsciiString &other);
	~AsciiString();
};

class Dict
{
public:
	Dict(int count = 0)
	{
		construct(count);
	}

	Dict(const Dict &other);
	Dict &operator=(const Dict &other)
	{
		assignFrom(&other);
		return *this;
	}
	~Dict()
	{
		releaseData();
	}

	int getType(NameKeyType key) const;

private:
	void construct(int count);
	void assignFrom(const Dict *other);
	void releaseData();

	void *m_data;
};

class DataChunkInput
{
public:
	Real readReal();
	Int readInt();
	AsciiString readAsciiString();
	Dict readDict();
};

class ThingTemplate
{
public:
	unsigned char m_padding[0xd0];
	unsigned int m_kindOf;
};

class ThingNameRegistry
{
public:
	Bool acceptsThingTemplateName(const AsciiString &name);
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class StaticNameKey
{
public:
	NameKeyType key() const;
};

class WaypointMap
{
public:
	Coord3D &lookup(const AsciiString &name);
};

class Coord3DList
{
public:
	void push_back(const Coord3D &value);
};

class MapObject
{
public:
	virtual void deleteInstance(Bool keep);

	MapObject(Coord3D location, AsciiString name, Real angle, Int flags,
		const Dict *dict, const ThingTemplate *thing);

	unsigned char m_padding[0x5c];

	Dict *getProperties()
	{
		return reinterpret_cast<Dict *>(reinterpret_cast<char *>(this) + 0x24);
	}

	const ThingTemplate *getThingTemplate() const;
	AsciiString getWaypointName();

	void setIsWaypoint()
	{
		*(Int *)(reinterpret_cast<char *>(this) + 0x44) |= 4;
	}
};

#pragma comment(linker, "/alternatename:?readReal@DataChunkInput@@QAEMXZ=?j_0002e5e1@@YAXXZ")
#pragma comment(linker, "/alternatename:?readInt@DataChunkInput@@QAEHXZ=?j_0003a805@@YAXXZ")
#pragma comment(linker, "/alternatename:?readAsciiString@DataChunkInput@@QAE?AVAsciiString@@XZ=?j_000041c9@@YAXXZ")
#pragma comment(linker, "/alternatename:?construct@Dict@@AAEXH@Z=?j_00002ecd@@YAXXZ")
#pragma comment(linker, "/alternatename:?assignFrom@Dict@@QAEXPBV1@@Z=?j_00045566@@YAXXZ")
#pragma comment(linker, "/alternatename:?getType@Dict@@QBEHH@Z=?j_0001efd8@@YAXXZ")
#pragma comment(linker, "/alternatename:?acceptsThingTemplateName@ThingNameRegistry@@QAE_NABVAsciiString@@@Z=?j_0002323b@@YAXXZ")
#pragma comment(linker, "/alternatename:?findTemplate@ThingNameRegistry@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ")
#pragma comment(linker, "/alternatename:??0MapObject@@QAE@UCoord3D@@VAsciiString@@MHPBVDict@@PBVThingTemplate@@@Z=?j_0001230a@@YAXXZ")
#pragma comment(linker, "/alternatename:?getThingTemplate@MapObject@@QBEPBVThingTemplate@@XZ=?j_00012814@@YAXXZ")
#pragma comment(linker, "/alternatename:?getWaypointName@MapObject@@QAE?AVAsciiString@@XZ=?j_00010f05@@YAXXZ")
#pragma comment(linker, "/alternatename:?lookup@WaypointMap@@QAEAAUCoord3D@@ABVAsciiString@@@Z=?j_0000cd97@@YAXXZ")
#pragma comment(linker, "/alternatename:?push_back@Coord3DList@@QAEXABUCoord3D@@@Z=?j_0001127f@@YAXXZ")

#define TheThingNameRegistry (*(ThingNameRegistry **)0x012EF1D8)
#define TheKey_waypointID (*(StaticNameKey *)0x012A77B0)
#define TheWaypoints (*(WaypointMap **)0x012F1588)
#define TheTechPositions (*(Coord3DList *)0x012F15A8)

// ?ParseObjectDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
struct DataChunkInfo
{
	unsigned char m_padding[8];
	unsigned short version;
};

Bool ParseObjectDataChunk(DataChunkInput &file, DataChunkInfo *info,
	void *userData)
{
	Bool readDict = info->version >= 2;

	Coord3D loc;
	loc.x = file.readReal();
	loc.y = file.readReal();
	loc.z = file.readReal();
	if (info->version <= 2)
		loc.z = 0;

	Real angle = file.readReal();
	Int flags = file.readInt();
	AsciiString name = file.readAsciiString();
	Dict dict;
	if (readDict)
		dict = file.readDict();

	MapObject *object;
	if (TheThingNameRegistry->acceptsThingTemplateName(name))
	{
		object = new MapObject(loc, name, angle, flags, &dict,
			TheThingNameRegistry->findTemplate(name));
	}
	else
	{
		object = new MapObject(loc, name, angle, flags, &dict,
			(const ThingTemplate *)0);
	}

	if (object->getProperties()->getType(TheKey_waypointID.key()) == 1)
	{
		object->setIsWaypoint();
		TheWaypoints->lookup(object->getWaypointName()) = loc;
	}
	else if (object->getThingTemplate() != 0 &&
		(object->getThingTemplate()->m_kindOf & 0x1000) != 0)
	{
		TheTechPositions.push_back(loc);
	}

	if (object != 0)
		object->deleteInstance(true);

	return 1;
}
