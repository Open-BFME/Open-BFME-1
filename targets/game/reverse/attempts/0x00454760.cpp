// ?ParseObjectDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// partial score=0.9934 date=2026-10-31
// cl: /DNDEBUG /MD /EHsc
// Retail 0x00454760, the "Object" chunk callback MapUtil's
// ParseObjectsDataChunk (0x00454A60) registers: Zero Hour MapUtil.cpp:129.
// BFME checks acceptsThingTemplateName before resolving the template (as the
// WorldHeightMap object reader at 0x00088B70 in MapObject.cpp does), dropped
// the supply-position branch and deletes the object through its virtual
// destructor. The callee views below reuse the names that reader proved.

typedef bool Bool;
typedef int Int;
typedef float Real;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AsciiString
{
public:
	~AsciiString();
	void *m_data;
};

class Dict
{
public:
	enum DataType
	{
		DICT_BOOL = 0,
		DICT_INT = 1
	};

	Dict(Int numPairsToPreAllocate = 0);
	~Dict()
	{
		releaseData();
	}
	Dict &operator=(const Dict &src);
	DataType getType(NameKeyType key) const;

private:
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

struct DataChunkInfo
{
	unsigned char m_unreconstructed_00[8];
	unsigned short version;
};

class StaticNameKey
{
public:
	NameKeyType key() const;
};

extern StaticNameKey TheKey_waypointID;

class ThingTemplate
{
public:
	unsigned char m_unreconstructed_00[0xd0];
	unsigned int m_kindOf;		///< retail +0xD0; 0x1000 is the tech-building bit
};

// TU-local view of the template singleton (see MapObject.cpp).
class Rva0088B70ThingRegistry
{
public:
	bool acceptsThingTemplateName(const AsciiString &name);
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class BfmeThingFactory;
extern BfmeThingFactory *TheThingFactory;

// Retail MapObject::getThingTemplate body 0x00087E80 (opaque ledger name).
struct BfmeSlotJA;
class BfmeThing932A
{
public:
	BfmeSlotJA *bfmeGo932A();
};

struct Coord3D;
class Vector3
{
public:
	Vector3(Real x, Real y, Real z)
	{
		X = x;
		Y = y;
		Z = z;
	}
	Vector3(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
	}
	// Retail reads x and y before storing x, z, y (template-branch argument copy).
	Vector3(const Coord3D &c, int) { unsigned x = *(const volatile unsigned *)&c.x; unsigned y = *(const volatile unsigned *)&c.y; *(unsigned *)&X = x; *(unsigned *)&Z = *(const unsigned *)&c.z; *(unsigned *)&Y = y; }
	Real X;
	Real Y;
	Real Z;
};

class MapObject
{
public:
	AsciiString getWaypointName();
};

class Rva0041230aMapObject
{
public:
	Rva0041230aMapObject(Vector3 loc, const AsciiString &name, Real angle, Int flags,
		const Dict *props, const ThingTemplate *tmplate);
	virtual ~Rva0041230aMapObject();

	Dict *getProperties() { return &m_properties; }
	void setIsWaypoint() { m_runtimeFlags |= 0x04; }
	AsciiString getWaypointName() { return reinterpret_cast<MapObject *>(this)->getWaypointName(); }
	const ThingTemplate *getThingTemplate()
	{
		return reinterpret_cast<const ThingTemplate *>(reinterpret_cast<BfmeThing932A *>(this)->bfmeGo932A());
	}

	char m_pad0[0x24 - 4];
	Dict m_properties;
	char m_pad1[0x44 - 0x24 - sizeof(Dict)];
	Int m_runtimeFlags;
	char m_pad2[0x60 - 0x44 - sizeof(Int)];
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T1, class T2> struct pair
{
};
template <class T, class Alloc> class list
{
public:
	void push_back(const T &x);
};
template <class Key, class T, class Compare, class Alloc> class map
{
public:
	T &operator[](const Key &k);
};
}

// MapUtil's WaypointMap value and tech-position list element (retail
// instantiations 0x000C0D00 and 0x00452280).
struct Rva000C0D00Less
{
};
struct Rva000C0D00Value
{
	Real x;
	Real y;
	Real z;
};
struct Rva00452280Element
{
	char m_body[12];
};

class WaypointMap : public _STL::map<AsciiString, Rva000C0D00Value, Rva000C0D00Less,
	_STL::allocator<_STL::pair<const AsciiString, Rva000C0D00Value> > >
{
};

// MapUtil file-scope m_waypoints and m_techPositions.
extern WaypointMap *Rva012F1588;
extern _STL::list<Rva00452280Element, _STL::allocator<Rva00452280Element> > Rva012F15A8;
#define TheTechPositions Rva012F15A8

#define K_OBJECTS_VERSION_2 2

// ?ParseObjectDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// The waypoint store reads x and y before writing, like the template branch's Vector3.
static inline void assignWaypoint(Rva000C0D00Value &w, const Coord3D &c)
{
	unsigned x = *(const volatile unsigned *)&c.x; unsigned y = *(const volatile unsigned *)&c.y; *(volatile unsigned *)&w.x = x; unsigned z = *(const volatile unsigned *)&c.z; *(volatile unsigned *)&w.y = y; *(volatile unsigned *)&w.z = z;
}

// ?ParseObjectDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
Bool ParseObjectDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	Bool readDict = info->version >= K_OBJECTS_VERSION_2;

	Coord3D loc;
	loc.x = file.readReal();
	loc.y = file.readReal();
	loc.z = file.readReal();
	if (info->version <= K_OBJECTS_VERSION_2)
	{
		loc.z = 0;
	}

	Real angle = file.readReal();
	Int flags = file.readInt();
	AsciiString name = file.readAsciiString();
	Dict d;
	if (readDict)
	{
		d = file.readDict();
	}

	Rva0088B70ThingRegistry *factory = reinterpret_cast<Rva0088B70ThingRegistry *>(TheThingFactory);
	Rva0041230aMapObject *pThisOne;
	if (factory->acceptsThingTemplateName(name))
		pThisOne = new Rva0041230aMapObject(Vector3(loc, 0), name, angle, flags, &d,
			reinterpret_cast<Rva0088B70ThingRegistry *>(TheThingFactory)->findTemplate(name));
	else
		pThisOne = new Rva0041230aMapObject(reinterpret_cast<const Vector3 &>(loc), name, angle, flags, &d, 0);

	if (pThisOne->getProperties()->getType(TheKey_waypointID.key()) == Dict::DICT_INT)
	{
		pThisOne->setIsWaypoint();

		assignWaypoint((*Rva012F1588)[pThisOne->getWaypointName()], loc);
	}
	else if (pThisOne->getThingTemplate() && (pThisOne->getThingTemplate()->m_kindOf & 0x1000))
	{
		TheTechPositions.push_back(reinterpret_cast<const Rva00452280Element &>(loc));
	}

	delete pThisOne;
	return true;
}
