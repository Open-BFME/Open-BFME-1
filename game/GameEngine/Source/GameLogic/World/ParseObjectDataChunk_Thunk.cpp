// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
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

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "ascii_string.h"

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

extern const StaticNameKey TheKey_waypointID;

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

inline void *__cdecl operator new(unsigned int, void *p) { return p; }

namespace _STL
{
template <class T> class allocator
{
};
template <class T1, class T2> struct pair
{
};
// STLport's node allocator (_M_allocate at 0x0082E540).
template <bool __threads, int __inst> class __node_alloc
{
public:
	static void *__cdecl _M_allocate(unsigned int __n);
};

// The element construct helper list<T>::push_back calls (retail 0x000B73B0).
// It must be defined in this TU: VC7.1 treats a local whose address reaches
// only visible, non-capturing callees as unaliased, which is what lets the
// waypoint and constructor-argument copies of loc load ahead of their stores.
template <class T1, class T2>
void _Construct(T1 *p, const T2 &value)
{
	new (p) T1(value);
}

struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};

template <class T> struct _List_node : public _List_node_base
{
	T _M_data;
};

template <class T, class Traits> struct _List_iterator
{
	_List_iterator(_List_node_base *node) : _M_node(node) {}
	_List_node_base *_M_node;
};

template <class T> struct _Nonconst_traits
{
};

template <class T, class Alloc> class list
{
public:
	typedef _List_node<T> _Node;
	typedef _List_iterator<T, _Nonconst_traits<T> > iterator;

	iterator insert(iterator position, const T &value)
	{
		_Node *node = _M_create_node(value);
		_List_node_base *at = position._M_node;
		_List_node_base *before = at->_M_prev;
		node->_M_next = at;
		node->_M_prev = before;
		before->_M_next = node;
		at->_M_prev = node;
		return iterator(node);
	}

	void push_back(const T &value)
	{
		insert(iterator(this->_M_node), value);
	}

private:
	_Node *_M_create_node(const T &value)
	{
		_Node *node = (_Node *)__node_alloc<true, 0>::_M_allocate(sizeof(_Node));
		_Construct(&node->_M_data, value);
		return node;
	}

	_Node *_M_node;
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
// retail 0x012F15A8, the tech-position list, already recorded under this name
class Gen_00C70010Target;
extern Gen_00C70010Target TheBfmeObject_00C70010;
typedef _STL::list<Rva00452280Element, _STL::allocator<Rva00452280Element> > Rva00452280ElementList;

#define K_OBJECTS_VERSION_2 2

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
		pThisOne = new Rva0041230aMapObject(reinterpret_cast<const Vector3 &>(loc), name, angle, flags, &d,
			reinterpret_cast<Rva0088B70ThingRegistry *>(TheThingFactory)->findTemplate(name));
	else
		pThisOne = new Rva0041230aMapObject(reinterpret_cast<const Vector3 &>(loc), name, angle, flags, &d, 0);

	if (pThisOne->getProperties()->getType(TheKey_waypointID.key()) == Dict::DICT_INT)
	{
		pThisOne->setIsWaypoint();

		(*Rva012F1588)[reinterpret_cast<MapObject *>(pThisOne)->getWaypointName()] = reinterpret_cast<const Rva000C0D00Value &>(loc);
	}
	else if (pThisOne->getThingTemplate() && (pThisOne->getThingTemplate()->m_kindOf & 0x1000))
	{
		reinterpret_cast<Rva00452280ElementList &>(TheBfmeObject_00C70010).push_back(reinterpret_cast<const Rva00452280Element &>(loc));
	}

	delete pThisOne;
	return true;
}
